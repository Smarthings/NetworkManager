#include "database.h"

Database::Database(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open()) {
        qDebug() << "Error: connection with database failed";
    } else {
        this->createTableMain();
    }
}

void Database::createTableMain()
{
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS wireless (id INTEGER PRIMARY KEY AUTOINCREMENT, ssid TEXT, pass_crypt TEXT);");

    if (!query.exec())
        qDebug() << "Query error: " << query.lastError();
}

bool Database::insertWireless(QString ssid, QString pass_crypt)
{
    QSqlQuery query;
    query.prepare("INSERT INTO wireless (ssid, pass_crypt) VALUES(:ssid, :pass_crypt)");
    query.bindValue(0, ssid);
    query.bindValue(1, pass_crypt);

    if (!query.exec()) {
        qDebug() << "Query error: " << query.lastError();
        return false;
    }
    return true;
}

bool Database::deleteWireless(quint32 id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM wireless WHERE id=:id");
    query.bindValue(0, id);

    if (!query.exec()) {
        qDebug() << "Query error: " << query.lastError();
        return false;
    }
    return true;
}

QList<QStringList> Database::selectWirelress()
{
    QList<QStringList> list_result;
    QSqlQuery query;
    query.prepare("SELECT * FROM wireless;");

    if (!query.exec()) {
        qDebug() << "Query error: " << query.lastError();
        return list_result;
    }

    while (query.next()) {
        QStringList row;
        row.append(query.value("id").toString());
        row.append(query.value("ssid").toString());
        row.append(query.value("pass_crypt").toString());

        list_result << row;
    }
    return list_result;
}

Database::~Database()
{
    m_db.close();
}


