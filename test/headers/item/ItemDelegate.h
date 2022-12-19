#pragma once

#include <QStyledItemDelegate>

//INFO Класс отвечает за отрисовку изображений объектов
class ItemDelegate : public QStyledItemDelegate
{
private:
    Q_OBJECT
public:
    ItemDelegate(QObject* pParent = Q_NULLPTR) : QStyledItemDelegate(pParent) {}
    virtual ~ItemDelegate() Q_DECL_EQ_DEFAULT;
public:
    //INFO Переопределенный метод отрисовывает объекты
    virtual void paint(QPainter* pPainter, const QStyleOptionViewItem& option, const QModelIndex& index) const Q_DECL_FINAL;
private:
    //INFO Метод возвращает либо оригинальное изображение, либо затемненное
    //INFO (в случае, когда инвентарь временно не доступен пользователю)
    QPixmap CreatePixmap(const QString& sData, QSize size = {0, 0}) const;
};
