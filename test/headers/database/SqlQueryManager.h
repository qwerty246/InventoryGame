#pragma once

#include <QString>
#include <QModelIndex>
#include <QPixmap>

//INFO Класс содержит все SQL-запросы, используемые программой
class SqlQueryManager
{
private:
    SqlQueryManager() Q_DECL_EQ_DEFAULT;
    ~SqlQueryManager() Q_DECL_EQ_DEFAULT;
public:
    //INFO Метод возвращает изображение яблока
    static QPixmap GetImage(int type);

    //INFO Метод добавляет в БД данные о типе и количестве объектов в ячейке
    static void InsertToCell(const QModelIndex& index, int type, int count);

    //INFO Метод возвращает тип объекта
    //  0 - пустая ячейка
    //  1 - яблоко
    static int GetTypeFromDB(const QModelIndex& index);

    //INFO Метод возвращает путь к файлу с изображением объекта
    static QString GetImagePathFromDB(const QModelIndex& index);

    //INFO Метод возвращает количество объектов в ячейке
    static int GetCountFromDB(const QModelIndex& index);

    //INFO Метод записывает количество объектов в ячейке в БД
    static void WriteCountToDB(const QModelIndex& index, int count);

    //INFO Метод полностью очищает весь инвентарь
    static void ClearInventory();
private:
    //INFO Метод проверяет, пустая ячейка или нет
    static bool IsEmpty(int row, int column);

    //INFO Метод очищает ячейку с координатами row и column
    static void ClearCell(int row, int column);
};
