#pragma once

#include <QAbstractTableModel>

//INFO Класс отвечает за связь данных инвентаря с базой данных
class InventoryTable : public QAbstractTableModel
{
private:
    Q_OBJECT
public:
    InventoryTable(QObject* pParent = Q_NULLPTR) : QAbstractTableModel(pParent) {}
    virtual ~InventoryTable() Q_DECL_EQ_DEFAULT;
public:
    //INFO Метод возвращает ширину инвентаря
    virtual int rowCount(const QModelIndex&) const Q_DECL_FINAL;

    //INFO Метод возвращает высоту инвентаря
    virtual int columnCount(const QModelIndex&) const Q_DECL_FINAL;

    //INFO Метод возвращает данные из базы данных в зависимости от типа
    virtual QVariant data(const QModelIndex& index, int role) const Q_DECL_FINAL;

    //INFO Метод записывает данные в базу данных в зависимости от типа
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role) Q_DECL_FINAL;

    //INFO Метод возвращает флаги доступных действий
    virtual Qt::ItemFlags flags(const QModelIndex& index) const Q_DECL_FINAL;

    //INFO Метод возвращает QMimeData, участвующий в обработке drag'n'drop событий
    virtual QMimeData* mimeData(const QModelIndexList& indexes) const Q_DECL_FINAL;
public slots:
    //INFO Метод очищает базу данных и инвентарь
    void ResetTable();
};
