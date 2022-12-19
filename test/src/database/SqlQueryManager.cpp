#include <database/DatabaseManager.h>
#include <database/SqlQueryManager.h>

#include <QSqlQuery>

QPixmap SqlQueryManager::GetImage(int type)
{
    QSqlQuery sqlQuery = DatabaseManager::CreateSqlQuery();
    sqlQuery.prepare("SELECT image FROM items WHERE key = :key");
    sqlQuery.bindValue(0, type);
    DatabaseManager::ExecuteSqlQuery(sqlQuery);

    if (sqlQuery.first())
    {
        return sqlQuery.value(0).toString();
    }
    return QPixmap();
}

void SqlQueryManager::InsertToCell(const QModelIndex& index, int type, int count)
{
    QSqlQuery sqlQuery = DatabaseManager::CreateSqlQuery();
    sqlQuery.prepare("INSERT "
                     "INTO inventory (row, column, item_key, count) "
                     "VALUES (:row, :column, :item_key, :count)");
    sqlQuery.bindValue(0, index.row());
    sqlQuery.bindValue(1, index.column());
    sqlQuery.bindValue(2, type);
    sqlQuery.bindValue(3, count);
    DatabaseManager::ExecuteSqlQuery(sqlQuery);
}

int SqlQueryManager::GetTypeFromDB(const QModelIndex& index)
{
    QSqlQuery sqlQuery = DatabaseManager::CreateSqlQuery();
    sqlQuery.prepare("SELECT item_key "
                     "FROM inventory "
                     "WHERE row = :row AND column = :column");
    sqlQuery.bindValue(0, index.row());
    sqlQuery.bindValue(1, index.column());
    DatabaseManager::ExecuteSqlQuery(sqlQuery);
    if (sqlQuery.first())
    {
        return sqlQuery.value(0).toInt();
    }
    return 0;
}

QString SqlQueryManager::GetImagePathFromDB(const QModelIndex& index)
{
    QSqlQuery sqlQuery = DatabaseManager::CreateSqlQuery();
    sqlQuery.prepare("SELECT image "
                     "FROM items "
                     "WHERE key = "
                     "(SELECT item_key "
                     "FROM inventory "
                     "WHERE row = :row AND column = :column)");
    sqlQuery.bindValue(0, index.row());
    sqlQuery.bindValue(1, index.column());
    DatabaseManager::ExecuteSqlQuery(sqlQuery);
    if (sqlQuery.first())
    {
        return sqlQuery.value(0).toString();
    }
    return QString();
}

int SqlQueryManager::GetCountFromDB(const QModelIndex& index)
{
    QSqlQuery sqlQuery = DatabaseManager::CreateSqlQuery();
    sqlQuery.prepare("SELECT count "
                     "FROM inventory "
                     "WHERE row = :row AND column = :column");
    sqlQuery.bindValue(0, index.row());
    sqlQuery.bindValue(1, index.column());
    DatabaseManager::ExecuteSqlQuery(sqlQuery);
    if (sqlQuery.first())
    {
        return sqlQuery.value(0).toInt();
    }
    return 0;
}

void SqlQueryManager::WriteCountToDB(const QModelIndex& index, int count)
{
    if (IsEmpty(index.row(), index.column()))
    {
        return;
    }
    if (count == 0)
    {
        ClearCell(index.row(), index.column());
        return;
    }
    QSqlQuery sqlQuery = DatabaseManager::CreateSqlQuery();
    sqlQuery.prepare("UPDATE inventory "
                     "SET count = :count "
                     "WHERE row = :row AND column = :column");
    sqlQuery.bindValue(0, count);
    sqlQuery.bindValue(1, index.row());
    sqlQuery.bindValue(2, index.column());
    DatabaseManager::ExecuteSqlQuery(sqlQuery);
}

void SqlQueryManager::ClearInventory()
{
    QSqlQuery sqlQuery = DatabaseManager::CreateSqlQuery();
    sqlQuery.prepare("DELETE FROM inventory ");
    DatabaseManager::ExecuteSqlQuery(sqlQuery);
}

bool SqlQueryManager::IsEmpty(int row, int column)
{
    QSqlQuery sqlQuery = DatabaseManager::CreateSqlQuery();
    sqlQuery.prepare("SELECT COUNT(*) FROM inventory "
                     "WHERE row = :row AND column = :column");
    sqlQuery.bindValue(0, row);
    sqlQuery.bindValue(1, column);
    DatabaseManager::ExecuteSqlQuery(sqlQuery);
    if (sqlQuery.first())
    {
        return (sqlQuery.value(0).toInt() == 0);
    }
    return false;
}

void SqlQueryManager::ClearCell(int row, int column)
{
    QSqlQuery sqlQuery = DatabaseManager::CreateSqlQuery();
    sqlQuery.prepare("DELETE FROM inventory "
                     "WHERE row = :row AND column = :column");
    sqlQuery.bindValue(0, row);
    sqlQuery.bindValue(1, column);
    DatabaseManager::ExecuteSqlQuery(sqlQuery);
}
