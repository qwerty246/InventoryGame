#include <item/AppleImage.h>
#include <item/AppleLabel.h>
#include <item/ItemMimeData.h>

#include <QApplication>
#include <QDrag>
#include <QMouseEvent>

AppleLabel::AppleLabel(QWidget* pParent) :
    QLabel(pParent),
    _type(1),
    _labelSize(128),
    _dragPosition()
{
    setFixedSize(QSize(LABEL_SIZE, LABEL_SIZE));
    setPixmap(AppleImage::GetImage(_type));
}

void AppleLabel::mouseMoveEvent(QMouseEvent* pEvent)
{
    if ((pEvent->pos() - _dragPosition).manhattanLength()
        < QApplication::startDragDistance())
    {
        return;
    }

    QDrag* pDrag = new QDrag(this);
    ItemMimeData* pItemMimeData = new ItemMimeData(_type);
    pDrag->setPixmap(AppleImage::GetImage(_type));
    pDrag->setHotSpot(pEvent->pos());
    pDrag->setMimeData(pItemMimeData);
    pDrag->exec(Qt::CopyAction);
    delete pDrag;
}

void AppleLabel::mousePressEvent(QMouseEvent* pEvent)
{
    if (pEvent->buttons()& Qt::LeftButton)
    {
        _dragPosition = pEvent->pos();
    }
    QLabel::mousePressEvent(pEvent);
}
