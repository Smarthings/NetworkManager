#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariantList>
#include <QStringList>

class Database
{
public:
    Database(const QString &path);
    ~Database();
    bool insertWireless(QString ssid, QString pass_crypt);
    bool deleteWireless(quint32 id);
    QList<QStringList> selectWirelress();

protected:
    void createTableMain();

private:
    QSqlDatabase m_db;
};

#endif // DATABASE_H
