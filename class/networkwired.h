#ifndef NETWORKWIRED_H
#define NETWORKWIRED_H

#include <QObject>

class NetworkWired : public QObject
{
    Q_OBJECT
public:
    explicit NetworkWired(QObject *parent = nullptr);

signals:

public slots:
};

#endif // NETWORKWIRED_H