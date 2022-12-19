#include <inventory/InventoryView.h>
#include <item/AppleLabel.h>
#include <item/ItemDelegate.h>
#include <item/ItemMimeData.h>

#include <QDrag>
#include <QDragEnterEvent>
#include <QHeaderView>
#include <QMouseEvent>
#include <QtMultimedia/QMediaPlayer>

InventoryView::InventoryView(QWidget* pParent) :
    QTableView(pParent)
{
    horizontalHeader()->setDefaultSectionSize(AppleLabel::LABEL_SIZE);
    verticalHeader()->setDefaultSectionSize(AppleLabel::LABEL_SIZE);

    horizontalHeader()->hide();
    verticalHeader()->hide();

    setItemDelegate(new ItemDelegate(this));

    setDragEnabled(true);
    setAcceptDrops(true);

    setFixedSize(AppleLabel::LABEL_SIZE * INVENTORY_ROW,
                 AppleLabel::LABEL_SIZE * INVENTORY_COLUMN);

    setFrameShape(QFrame::NoFrame);
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
                                modeIndex.data(COUNT_ROLE).toInt() - 1,
                                COUNT_ROLE))
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
        if (modelIndex.data(TYPE_ROLE).toInt() == itemType)
        {
            int itemCount = modelIndex.data(COUNT_ROLE).toInt();
            if (pEvent->source() != this)
            {
                pModel->setData(modelIndex, itemCount + 1, COUNT_ROLE);
            }
            else
            {
                pModel->setData(modelIndex,
                                itemCount + _draggingModel.data(COUNT_ROLE).toInt(),
                                COUNT_ROLE);

                pModel->setData(_draggingModel, 0, COUNT_ROLE);
            }
        }
        else
        {
            if (pEvent->source() != this)
            {
                pModel->setData(modelIndex, itemType, TYPE_ROLE);
            }
            else
            {
                QList<QVariant> listItem;
                listItem.append(_draggingModel.data(TYPE_ROLE).toInt());
                listItem.append(_draggingModel.data(COUNT_ROLE).toInt());
                if (pModel->setData(modelIndex, listItem, TYPE_ROLE))
                {
                    pModel->setData(_draggingModel, 0, COUNT_ROLE);
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
