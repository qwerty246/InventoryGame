#include <database/DatabaseManager.h>

#include <QFileInfo>
#include <QMessageBox>
#include <QSqlQuery>

DatabaseManager::DatabaseManager()
{
    if (!QFileInfo::exists("./bases/inventory.db"))
    {
        QMessageBox::critical(Q_NULLPTR, "Critical error", "Database \"bases/inventory.db\" not found.");
        exit(1);
    }
    _database = QSqlDatabase::addDatabase("QSQLITE", "./bases/inventory.db");
    _database.setConnectOptions("QSQLITE_OPEN_URI");
    _database.setDatabaseName("./bases/inventory.db");

    if (!_database.open())
    {
        QMessageBox::critical(Q_NULLPTR, "Critical error", "Can not connect to \"bases/inventory.db\" database.");
        exit(1);
    }

    QSqlQuery sqlQuery(_database);
    sqlQuery.prepare("PRAGMA foreign_keys = on");
    ExecuteSqlQuery(sqlQuery);
}

QSqlQuery DatabaseManager::CreateSqlQuery()
{
    static DatabaseManager dataBaseManager;
    return QSqlQuery(dataBaseManager._database);
}

void DatabaseManager::ExecuteSqlQuery(QSqlQuery& sqlQuery)
{
    sqlQuery.exec();
    if (!sqlQuery.isActive())
    {
        QMessageBox::critical(Q_NULLPTR, "Critical error", "Unable to send database query: " + sqlQuery.lastQuery());
        exit(1);
    }
}
