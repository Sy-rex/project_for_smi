#include "databasemanger.h"
#include "registration.h"
#include "QDebug"

void databasemanger::setToggled(bool toggled) {
    m_toggled = toggled;
    qDebug() << "USER" << m_toggled;
}

databasemanger::databasemanger(bool m_toggled)
{
    if (m_toggled)
    {
        qDebug() << "READER" << m_toggled;
        m_db = QSqlDatabase::addDatabase("QPSQL");
        m_db.setUserName("reader_user");
        m_db.setPassword("12345");
        m_db.setDatabaseName("smi");
        m_db.setHostName("localhost");
    } else {
        qDebug() << "EDITOR" << m_toggled;
        m_db = QSqlDatabase::addDatabase("QPSQL");
        m_db.setUserName("editor_user");
        m_db.setPassword("12345");
        m_db.setDatabaseName("smi");
        m_db.setHostName("localhost");
    }
}

databasemanger::~databasemanger()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

databasemanger& databasemanger::instance(bool m_toggled)
{
    static databasemanger instance(m_toggled);
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
