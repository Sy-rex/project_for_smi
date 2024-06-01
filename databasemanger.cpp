#include "databasemanger.h"

databasemanger::databasemanger()
{
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setUserName("postgres");
    m_db.setPassword("12345");
    m_db.setDatabaseName("smi");
    m_db.setHostName("localhost");
}

databasemanger::~databasemanger()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

databasemanger& databasemanger::instance()
{
    static databasemanger instance;
    return instance;
}

bool databasemanger::openDatabase()
{
    if (!m_db.isOpen()) {
        if (m_db.open()) {
            qDebug() << "Connected to database";
            return true;
        } else {
            qDebug() << "Failed to connect to database: " << m_db.lastError().text();
            return false;
        }
    }
    return true;
}

QSqlDatabase databasemanger::database() const
{
    return m_db;
}
