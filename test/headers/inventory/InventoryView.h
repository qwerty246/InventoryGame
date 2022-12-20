#pragma once

#include <QTableView>

//INFO Класс отвечает за вид инвентаря и взаимодействие с ним пользователя
class InventoryView : public QTableView
{
public:
    InventoryView(int labelSize, QWidget* pParent = Q_NULLPTR);
    virtual ~InventoryView() Q_DECL_EQ_DEFAULT;
public:
    int GetInventoryRow() const;
    int GetInventoryColumn() const;
    int GetTypeRole() const;
    int GetCountRole() const;
private:
    //INFO Метод воспроизводит звук откусывания яблока
    virtual void mousePressEvent(QMouseEvent* pEvent) Q_DECL_FINAL;

    //INFO Метод проводит проверку на допустимость формата перед принятием события
    virtual void dragEnterEvent(QDragEnterEvent* pEvent) Q_DECL_FINAL;

    //INFO Метод создает новый drag'n'drop объект
    virtual void dragLeaveEvent(QDragLeaveEvent*) Q_DECL_FINAL;

    //INFO Метод игнорирует событие переноса, если изначальная и конечная ячейки совпадают
    virtual void dragMoveEvent(QDragMoveEvent* pEvent) Q_DECL_FINAL;

    //INFO Метод обрабатывает логику "бросания" объекта в ячейку
    virtual void dropEvent(QDropEvent* pEvent) Q_DECL_FINAL;

    //INFO Метод запоминает, откуда происходит перенос объекта
    virtual void startDrag(Qt::DropActions supportedActions) Q_DECL_FINAL;
private:
    QModelIndex _draggingModel;
    const int _labelSize;
    const int _inventoryRow;
    const int _inventoryColumn;
    const int _typeRole;
    const int _countRole;
};
