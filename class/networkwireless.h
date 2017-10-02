#ifndef NETWORKWIRELESS_H
#define NETWORKWIRELESS_H

#include <QObject>
#include <QNetworkInterface>
#include <QProcess>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>
#include <QTimer>
#include <QFile>

class NetworkWireless : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QVariant> listWifi READ listWifi NOTIFY listWifiChanged)
    Q_PROPERTY(bool search READ search NOTIFY searchChanged)
    Q_PROPERTY(QJsonObject connectWifi READ connectWifi WRITE setWifi NOTIFY connectWifiChanged)

public:
    explicit NetworkWireless(QObject *parent = nullptr);
    ~NetworkWireless();

Q_SIGNALS:
    void listWifiChanged();
    void connectWifiChanged();
    void searchChanged();

private:
    void getInterface();

public slots:
    void setWifi(QJsonObject wifi);

protected slots:
    void startWlan();
    void getCurrentConnection();
    void scanWireless();
    void parseScanWireless(int status);

protected:
    QStringList ifaces;
    QProcess process;

    QList<QVariant> list_wifi;
    QList<QVariant> listWifi() { return list_wifi; }

    QJsonObject connect_wifi;
    QJsonObject connectWifi() { return connect_wifi; }

    bool busy = false;
    bool search() { return busy; }

    QTimer *timer;
};

#endif // NETWORKWIRELESS_H
