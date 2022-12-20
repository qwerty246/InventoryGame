#include <database/SqlQueryManager.h>
#include <inventory/InventoryTable.h>
#include <inventory/InventoryView.h>
#include <item/ItemMimeData.h>

InventoryTable::InventoryTable(int inventoryRow, int inventoryColumn,
                               int typeRole, int countRole, QObject* pParent) :
    QAbstractTableModel(pParent),
    _inventoryRow(inventoryRow),
    _inventoryColumn(inventoryColumn),
    _typeRole(typeRole),
    _countRole(countRole)
{}

int InventoryTable::rowCount(const QModelIndex&) const
{
    return _inventoryRow;
}

int InventoryTable::columnCount(const QModelIndex&) const
{
    return _inventoryColumn;
}

QVariant InventoryTable::data(const QModelIndex& index, int role) const
{
    if (role == _countRole)
    {
        return SqlQueryManager::GetCountFromDB(index);
    }
    else if (role == _typeRole)
    {
        return SqlQueryManager::GetTypeFromDB(index);
    }
    return SqlQueryManager::GetImagePathFromDB(index);
}

bool InventoryTable::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role == _countRole)
    {
        if (value.canConvert(QMetaType::Int))
        {
            SqlQueryManager::WriteCountToDB(index, value.toInt());
            emit dataChanged(index, index, QVector<int>(1, _countRole));
            return false;
        }
    }
    else if (role == _typeRole)
    {
        if (value.canConvert(QMetaType::Int))
        {
            SqlQueryManager::InsertToCell(index, value.toInt(), 1);
            emit dataChanged(index, index, QVector<int>(1, _typeRole));
        }
        else if (value.canConvert<QList<QVariant>>())
        {
            SqlQueryManager::InsertToCell(index, value.toList().at(0).toInt(), value.toList().at(1).toInt());
            emit dataChanged(index, index, QVector<int>(1, _typeRole));
        }
    }
    return true;
}

Qt::ItemFlags InventoryTable::flags(const QModelIndex& index) const
{
    return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | QAbstractTableModel::flags(index);
}

QMimeData* InventoryTable::mimeData(const QModelIndexList& indexes) const
{
    return new ItemMimeData(indexes.at(0).data(_typeRole).toInt());
}

void InventoryTable::ResetTable()
{
    beginResetModel();
    SqlQueryManager::ClearInventory();
    endResetModel();
}
