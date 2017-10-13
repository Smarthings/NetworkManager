#include "networkwireless.h"

NetworkWireless::NetworkWireless(QObject *parent) : QObject(parent),
    timer(new QTimer)
{
    this->getInterface();
    this->startWlan();
    this->getCurrentConnection();
    this->getSqlSavedWireless();
    this->scanWireless();

    connect(&process, SIGNAL(finished(int)), this, SLOT(parseScanWireless(int)));
    connect(timer, &QTimer::timeout, this, &NetworkWireless::scanWireless, Qt::UniqueConnection);
    timer->start(2500);
}

void NetworkWireless::getInterface()
{
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for (auto &interface : interfaces) {
        if (QString(interface.name()).indexOf("w") >= 0) {
            this->interface = interface.name();
            return;
        }
    }
}

void NetworkWireless::startWlan()
{
    QString command = QString("/bin/sh -c \"ifdown %1; ifup %2\" ").arg(interface).arg(interface);
    QProcess _startWlan;
    _startWlan.start(command);

    if (_startWlan.waitForFinished())
        qDebug() << command << "Error" << _startWlan.errorString();
    else
        qDebug() << _startWlan.readAll();
    _startWlan.close();
}

void NetworkWireless::getCurrentConnection()
{
    QString command = QString("iwconfig %1").arg(interface);
    QProcess _getCurrentConnection;
    _getCurrentConnection.start(command);

    if (!_getCurrentConnection.waitForFinished())
        qDebug() << command << "Error" << _getCurrentConnection.errorString();
    else {
        QString result = _getCurrentConnection.readAll();
        QRegularExpression reg_SSID("(ESSID:.*)");
        QRegularExpressionMatch match_SSID = reg_SSID.match(result);
        if (match_SSID.hasMatch()) {
            v_wifi_connected = QString(match_SSID.captured()).replace("\"", "").replace(" ", "").split(":").at(1);
            Q_EMIT wifi_connectedChanged();
        }
    }
}

void NetworkWireless::scanWireless()
{
    if (busy)
        return;
    busy = true;
    Q_EMIT searchChanged();

    QString command = QString("iwlist %1 scan").arg(interface);
    process.start(command);
}

void NetworkWireless::parseScanWireless(int status)
{
    list_wifi.clear();

    QRegularExpression reg_START("(Cell.*- Address: .*)");
    QRegularExpression reg_SSID("(ESSID:.*)");
    QRegularExpression reg_CHANNEL("(Channel:.*)");
    QRegularExpression reg_ENCRIPTION("(Encryption key:.*)");
    QRegularExpression reg_QUALITY("(Quality=.* Signal level=.*)");

    QJsonObject object;

    if (status == 0) {
        while (!process.atEnd()) {
            QString line = process.readLine();

            QRegularExpressionMatch match_START = reg_START.match(line);
            if (match_START.hasMatch() && object.length() > 0) {
                list_wifi.append(object.toVariantMap());
                object = {};
            }

            QRegularExpressionMatch match_SSID = reg_SSID.match(line);
            if (match_SSID.hasMatch()) {
                QStringList split = match_SSID.captured().replace("\"", "").split(":");
                object.insert(split.at(0), split.at(1));
                QStringList savedPass = this->findSavedWireless(split.at(1));
                if (savedPass.count() > 0) {
                    object.insert("id", savedPass.at(0));
                    object.insert("saved", savedPass.at(1));
                }
                if (split.at(1) == v_wifi_connected)
                    object.insert("connect", true);
            }

            QRegularExpressionMatch match_CHANNEL = reg_CHANNEL.match(line);
            if (match_CHANNEL.hasMatch()) {
                QStringList split = match_CHANNEL.captured().replace("\"", "").split(":");
                object.insert(split.at(0), split.at(1));
            }

            QRegularExpressionMatch match_ENCRIPTION = reg_ENCRIPTION.match(line);
            if (match_ENCRIPTION.hasMatch()) {
                QStringList split = match_ENCRIPTION.captured().replace("\"", "").replace(" key", "").split(":");
                object.insert(split.at(0), split.at(1));
            }

            QRegularExpressionMatch match_QUALITY = reg_QUALITY.match(line);
            if (match_QUALITY.hasMatch()) {
                QStringList split = match_QUALITY.captured().replace("\"", "").split(" ");
                split = QString(split.at(0)).split("=");
                object.insert(split.at(0), split.at(1));
            }

            if (process.atEnd()) {
                list_wifi.append(object.toVariantMap());
                object = {};
            }
        }
        if (!list_wifi.isEmpty())
            Q_EMIT listWifiChanged();
        process.close();
    }
    busy = false;
    Q_EMIT searchChanged();
}

void NetworkWireless::setWifi(QJsonObject wifi)
{
    this->busyIndicator(true);
    QStringList data;
    data << wifi.value("ESSID").toString() << wifi.value("password").toString();

    QString command = QString("wpa_passphrase \"%1\" \"%2\"").arg(data.at(0)).arg(data.at(1));
    QProcess wifiWrite;
    wifiWrite.start(command);

    if (!wifiWrite.waitForFinished())
        qDebug() << "Error" << wifiWrite.errorString();
    else {
        QString contentWpaSupplicant;

        QRegularExpression errorMsg("(Passphrase must be.*)");
        QRegularExpression sharpPsk("(#psk=.*)");
        QRegularExpression psk("(psk=.*)");

        while (!wifiWrite.atEnd()) {
            QString line = wifiWrite.readLine();

            QRegularExpressionMatch match_errorMsg = errorMsg.match(line);
            if (match_errorMsg.hasMatch()) {
                v_error = match_errorMsg.captured();
                Q_EMIT errorChanged();
                return;
            }

            QRegularExpressionMatch match_sharpPsk = sharpPsk.match(line);
            if (match_sharpPsk.hasMatch()) {
                if (data.at(1) == QString(match_sharpPsk.captured()).replace("\"", "").split("=")[1])
                    continue;
            }

            QRegularExpressionMatch match_psk = psk.match(line);
            if (match_psk.hasMatch()) {
                QString pass_crypt = QString(match_psk.captured()).split("=")[1];
                db->insertWireless(data.at(0), pass_crypt);
            }
            contentWpaSupplicant.append(line);
        }
        wifiWrite.close();
        if (this->write_wpa_supplicant(contentWpaSupplicant))
            this->restartWireless();

        this->getSqlSavedWireless();
        this->getCurrentConnection();
    }
    this->busyIndicator(false);
}

bool NetworkWireless::write_wpa_supplicant(QString content_wpa)
{
    QFile wpa_supplicant("/etc/wpa_supplicant.conf");
    if (!wpa_supplicant.open(QIODevice::WriteOnly)) {
        qDebug() << "Error" << wpa_supplicant.errorString();
        return false;
    }
    if (!wpa_supplicant.write(content_wpa.toUtf8(), content_wpa.length())) {
        qDebug() << "Error" << wpa_supplicant.errorString();
        return false;
    }
    wpa_supplicant.close();
    if (wpa_supplicant.isOpen()) {
        qDebug() << "Error" << wpa_supplicant.errorString();
        return false;
    }
    return true;
}

bool NetworkWireless::restartWireless()
{
    QString command = QString("/bin/sh -c \"ifdown %1; ifup %2\" ").arg(interface).arg(interface);
    QProcess _restartWireless;
    _restartWireless.start(command);

    if (!_restartWireless.waitForFinished()) {
        qDebug() << "Error" << _restartWireless.errorString();
        return false;
    }
    qDebug() << "Ok" << command;
    return true;
}

void NetworkWireless::forgetNetwork(QJsonObject wifi)
{
    db->deleteWireless(wifi.value("id").toString().toInt());
    this->getSqlSavedWireless();
}

void NetworkWireless::connectWifi(QString ssid, QString psk)
{
    this->busyIndicator(true);
    QString content_wpa =
            QString("network={\n\
        ssid=\"%1\"\n\
        psk=%2\n}\n").arg(ssid).arg(psk);
    if (this->write_wpa_supplicant(content_wpa))
        this->restartWireless();
    this->busyIndicator(false);
}

void NetworkWireless::disconnectWifi()
{
    this->busyIndicator(true);
    QString content_wpa = "network={\n\
            ssid=''\n\
            psk=''\n}\n";
    if (this->write_wpa_supplicant(content_wpa))
        this->restartWireless();
    this->busyIndicator(false);
}

void NetworkWireless::getSqlSavedWireless()
{
    v_wifi_saved = db->selectWirelress();
}

QStringList NetworkWireless::findSavedWireless(QString name)
{
    QStringList result;
    for (auto &list : v_wifi_saved) {
        if (list.at(1) == name) {
            result << list.at(0) << list.at(2);
            return result;
        }
    }
    return result;
}

void NetworkWireless::busyIndicator(bool status)
{
    v_busy = status;
    busyChanged();
}

NetworkWireless::~NetworkWireless()
{
    delete timer;
}
