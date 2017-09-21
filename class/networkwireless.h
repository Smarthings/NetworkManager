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

class NetworkWireless : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QVariant> listWifi READ listWifi NOTIFY listWifiChanged)
    Q_PROPERTY(bool search READ search NOTIFY searchChanged)

public:
    explicit NetworkWireless(QObject *parent = nullptr);
    ~NetworkWireless();

Q_SIGNALS:
    void listWifiChanged();
    void searchChanged();

private:
    void getInterface();

public slots:

protected slots:
    void scanWireless();
    void parseScanWireless(int status);

protected:
    QStringList ifaces;
    QProcess process;

    QList<QVariant> list_wifi;
    QList<QVariant> listWifi() { return list_wifi; }

    bool busy = false;
    bool search() { return busy; }

    QTimer *timer;
};

#endif // NETWORKWIRELESS_H
