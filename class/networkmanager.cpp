#include "networkmanager.h"

NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{
    qDebug() << "Network Manager";
    this->getInterfaces();
}

void NetworkManager::getInterfaces()
{
    QList<QNetworkInterface> interface = QNetworkInterface::allInterfaces();
    for (auto &iface : interface) {
        QJsonObject obj;
        if (iface.name() == QString("lo"))
            continue;
        obj.insert("name", iface.name());
        obj.insert("status", iface.flags().testFlag(QNetworkInterface::IsUp));
        obj.insert("macaddress", iface.hardwareAddress());
        if (iface.name().indexOf("wl") >= 0) {
            obj.insert("type", "wireless");
        }
        if (iface.name().indexOf("eth") >= 0 || iface.name().indexOf("enp") >= 0) {
            obj.insert("type", "wired");
        }
        for (auto &addr : iface.addressEntries()) {
            if (!addr.ip().isLoopback() && addr.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                obj.insert("ipaddress", addr.ip().toString());
                obj.insert("broadcast", addr.broadcast().toString());
                obj.insert("netmask", addr.netmask().toString());
            }
            if (iface.name().indexOf("wl") >= 0) {
                obj.insert("ssid", this->getCurrentConnection(iface.name()));
            }
        }
        interfaces.append(obj.toVariantMap());
    }
    Q_EMIT interfacesChanged();
}

QString NetworkManager::getCurrentConnection(QString interface)
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
            return QString(match_SSID.captured()).replace("\"", "").replace(" ", "").split(":").at(1);
        }
    }
}
