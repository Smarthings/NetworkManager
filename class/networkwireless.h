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

#include "./database.h"

class NetworkWireless : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QVariant> listWifi READ listWifi NOTIFY listWifiChanged)
    Q_PROPERTY(bool search READ search NOTIFY searchChanged)
    Q_PROPERTY(QJsonObject connectWifi READ connectWifi WRITE setWifi NOTIFY connectWifiChanged)
    Q_PROPERTY(QString wifi_connected READ wifi_connected NOTIFY wifi_connectedChanged)

public:
    explicit NetworkWireless(QObject *parent = nullptr);
    ~NetworkWireless();

Q_SIGNALS:
    void listWifiChanged();
    void connectWifiChanged();
    void searchChanged();
    void wifi_connectedChanged();

private:
    void getInterface();

public slots:
    void setWifi(QJsonObject wifi);

protected slots:
    void startWlan();
    void getCurrentConnection();
    void scanWireless();
    void parseScanWireless(int status);
    void getSqlSavedWireless();

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

    QString wifi_connected() { return v_wifi_connected; }
    QString v_wifi_connected = "off/any";

    Database *db = new Database("NetworkManager.sql");
};

#endif // NETWORKWIRELESS_H
