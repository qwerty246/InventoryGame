#include <inventory/InventoryView.h>
#include <item/ItemDelegate.h>

#include <QPainter>

ItemDelegate::ItemDelegate(int countRole, QObject* pParent) :
    QStyledItemDelegate(pParent),
    _countRole(countRole)
{}

void ItemDelegate::paint(QPainter* pPainter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    int itemCount = index.data(_countRole).toInt();
    if (itemCount > 0)
    {
        QRect rect = option.rect;
        if (static_cast<QWidget*>(parent())->isEnabled())
        {
            pPainter->drawPixmap(rect, CreatePixmap(index.data(Qt::DecorationRole).toString()));
        }
        else
        {
            pPainter->drawPixmap(rect, CreatePixmap(index.data(Qt::DecorationRole).toString(), rect.size()));
        }
        pPainter->drawText(rect, Qt::AlignBottom | Qt::AlignRight, QString::number(itemCount));
    }
}

QPixmap ItemDelegate::CreatePixmap(const QString& sData, QSize size) const
{
    if (size.isEmpty())
    {
        return QPixmap(sData);
    }
    else
    {
        return QIcon(sData).pixmap(size, QIcon::Disabled, QIcon::Off);
    }
}
