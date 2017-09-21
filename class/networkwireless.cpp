#include "networkwireless.h"

NetworkWireless::NetworkWireless(QObject *parent) : QObject(parent),
    timer(new QTimer)
{
    this->getInterface();
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
            ifaces.append(interface.name());
        }
    }
}

void NetworkWireless::scanWireless()
{
    if (busy)
        return;
    busy = true;
    Q_EMIT searchChanged();

    QString command = QString("iwlist %1 scan").arg(ifaces.at(0));
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
    }
    busy = false;
    Q_EMIT searchChanged();
}

NetworkWireless::~NetworkWireless()
{
    delete timer;
}
