#include <database/SqlQueryManager.h>
#include <inventory/InventoryTable.h>
#include <inventory/InventoryView.h>
#include <item/ItemMimeData.h>

int InventoryTable::rowCount(const QModelIndex&) const
{
    return InventoryView::INVENTORY_ROW;
}

int InventoryTable::columnCount(const QModelIndex&) const
{
    return InventoryView::INVENTORY_COLUMN;
}

QVariant InventoryTable::data(const QModelIndex& index, int role) const
{
    if (role == InventoryView::COUNT_ROLE)
    {
        return SqlQueryManager::GetCountFromDB(index);
    }
    else if (role == InventoryView::TYPE_ROLE)
    {
        return SqlQueryManager::GetTypeFromDB(index);
    }
    return SqlQueryManager::GetImagePathFromDB(index);
}

bool InventoryTable::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role == InventoryView::COUNT_ROLE)
    {
        if (value.canConvert(QMetaType::Int))
        {
            SqlQueryManager::WriteCountToDB(index, value.toInt());
            emit dataChanged(index, index, QVector<int>(1, InventoryView::COUNT_ROLE));
            return false;
        }
    }
    else if (role == InventoryView::TYPE_ROLE)
    {
        if (value.canConvert(QMetaType::Int))
        {
            SqlQueryManager::InsertToCell(index, value.toInt(), 1);
            emit dataChanged(index, index, QVector<int>(1, InventoryView::TYPE_ROLE));
        }
        else if (value.canConvert<QList<QVariant>>())
        {
            SqlQueryManager::InsertToCell(index, value.toList().at(0).toInt(), value.toList().at(1).toInt());
            emit dataChanged(index, index, QVector<int>(1, InventoryView::TYPE_ROLE));
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
    return new ItemMimeData(indexes.at(0).data(InventoryView::TYPE_ROLE).toInt());
}

void InventoryTable::ResetTable()
{
    beginResetModel();
    SqlQueryManager::ClearInventory();
    endResetModel();
}
