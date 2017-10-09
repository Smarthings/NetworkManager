#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);

signals:

public slots:
};

#endif // NETWORKMANAGER_H