#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QList>
#include <QStringList>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QHostInfo>
#include <QJsonObject>
#include <QProcess>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

class NetworkManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QVariant> getInfo READ getInfo NOTIFY getInfoChanged)

public:
    explicit NetworkManager(QObject *parent = nullptr);

Q_SIGNALS:
    void getInfoChanged();

private slots:

public slots:

protected:
    QList<QVariant> interfaces;
    QList<QVariant> getInfo() { return interfaces; }

    void getInterfaces();
    QString getCurrentConnection(QString interface);
};

#endif // NETWORKMANAGER_H
