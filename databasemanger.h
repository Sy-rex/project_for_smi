#ifndef databasemanger_H
#define databasemanger_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

class databasemanger
{
public:
    static databasemanger& instance(bool m_toggled);
    bool openDatabase();
    QSqlDatabase database() const;
    void setToggled(bool toggled);

private:
    databasemanger(bool m_toggled);
    ~databasemanger();
    databasemanger(const databasemanger&) = delete;
    databasemanger& operator=(const databasemanger&) = delete;
    QSqlDatabase m_db;
    bool m_toggled;
};

#endif // databasemanger_H
