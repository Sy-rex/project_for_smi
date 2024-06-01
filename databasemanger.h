#ifndef databasemanger_H
#define databasemanger_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

class databasemanger
{
public:
    static databasemanger& instance();
    bool openDatabase();
    QSqlDatabase database() const;

private:
    databasemanger();
    ~databasemanger();
    databasemanger(const databasemanger&) = delete;
    databasemanger& operator=(const databasemanger&) = delete;
    QSqlDatabase m_db;
};

#endif // databasemanger_H
