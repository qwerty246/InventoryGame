#include <inventory/InventoryView.h>
#include <item/AppleLabel.h>
#include <item/ItemDelegate.h>
#include <item/ItemMimeData.h>

#include <QDrag>
#include <QDragEnterEvent>
#include <QHeaderView>
#include <QMouseEvent>
#include <QtMultimedia/QMediaPlayer>

InventoryView::InventoryView(int labelSize, QWidget* pParent) :
    QTableView(pParent),
    _labelSize(labelSize),
    _inventoryRow(3),
    _inventoryColumn(3),
    _typeRole(Qt::UserRole + 1),
    _countRole(_typeRole + 1)
{
    horizontalHeader()->setDefaultSectionSize(_labelSize);
    verticalHeader()->setDefaultSectionSize(_labelSize);

    horizontalHeader()->hide();
    verticalHeader()->hide();

    setItemDelegate(new ItemDelegate(_countRole, this));

    setDragEnabled(true);
    setAcceptDrops(true);

    setFixedSize(_labelSize * _inventoryRow,
                 _labelSize * _inventoryColumn);

    setFrameShape(QFrame::NoFrame);
}

int InventoryView::GetInventoryRow() const
{
    return _inventoryRow;
}

int InventoryView::GetInventoryColumn() const
{
    return _inventoryColumn;
}

int InventoryView::GetTypeRole() const
{
    return _typeRole;
}

int InventoryView::GetCountRole() const
{
    return _countRole;
}

void InventoryView::mousePressEvent(QMouseEvent* pEvent)
{
    QModelIndex modeIndex = indexAt(pEvent->pos());
    if ((pEvent->button() == Qt::RightButton))
    {
        QAbstractItemModel* pModel = qobject_cast<QAbstractItemModel*>(model());
        if (pModel)
        {
            if (pModel->setData(modeIndex,
                                modeIndex.data(_countRole).toInt() - 1,
                                _countRole))
            {
                QMediaPlayer mediaPlayer;
                mediaPlayer.setMedia(QUrl::fromLocalFile("biting.wav"));
                mediaPlayer.setVolume(50);
                mediaPlayer.play();
            }
        }
    }

    QTableView::mousePressEvent(pEvent);
}

void InventoryView::dragEnterEvent(QDragEnterEvent* pEvent)
{
    if (pEvent->mimeData()->hasFormat("application/apple"))
    {
        pEvent->acceptProposedAction();
    }
}

void InventoryView::dragLeaveEvent(QDragLeaveEvent*)
{
    _draggingModel = QModelIndex();
}

void InventoryView::dragMoveEvent(QDragMoveEvent* pEvent)
{
    if (_draggingModel == indexAt(pEvent->pos()))
    {
        pEvent->ignore();
        return;
    }
    pEvent->acceptProposedAction();
}

void InventoryView::dropEvent(QDropEvent* pEvent)
{
    QModelIndex modelIndex = indexAt(pEvent->pos());
    QAbstractItemModel* pModel = qobject_cast<QAbstractItemModel*>(model());
    int itemType = static_cast<const ItemMimeData*>(pEvent->mimeData())->GetType();
    if (itemType)
    {
        if (modelIndex.data(_typeRole).toInt() == itemType)
        {
            int itemCount = modelIndex.data(_countRole).toInt();
            if (pEvent->source() != this)
            {
                pModel->setData(modelIndex, itemCount + 1, _countRole);
            }
            else
            {
                pModel->setData(modelIndex,
                                itemCount + _draggingModel.data(_countRole).toInt(),
                                _countRole);

                pModel->setData(_draggingModel, 0, _countRole);
            }
        }
        else
        {
            if (pEvent->source() != this)
            {
                pModel->setData(modelIndex, itemType, _typeRole);
            }
            else
            {
                QList<QVariant> listItem;
                listItem.append(_draggingModel.data(_typeRole).toInt());
                listItem.append(_draggingModel.data(_countRole).toInt());
                if (pModel->setData(modelIndex, listItem, _typeRole))
                {
                    pModel->setData(_draggingModel, 0, _countRole);
                }
            }
        }
    }
    setCurrentIndex(modelIndex);
}

void InventoryView::startDrag(Qt::DropActions supportedActions)
{
    _draggingModel = currentIndex();
    QTableView::startDrag(supportedActions);
}
