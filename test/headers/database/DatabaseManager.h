#pragma once

#include <QSqlDatabase>

//INFO Класс обеспечивает подключение к БД и взаимодействие с ней.
//INFO Реализован как синглтон. Для взаимодействия с базой данных есть два специальных метода.
class DatabaseManager
{
private:
    //INFO Эти методы запривачены для реализации синглтона
    DatabaseManager();
    Q_DISABLE_COPY(DatabaseManager)
    DatabaseManager(DatabaseManager&&);
    DatabaseManager& operator=(DatabaseManager&&);
public:
    ~DatabaseManager() Q_DECL_EQ_DEFAULT;
public:
    //INFO Возвращает пустой SQL-запрос, связанный с БД
    static QSqlQuery CreateSqlQuery();

    //INFO Выполняет SQL-запрос. Если запрос не выполнен, завершает работу программы
    static void ExecuteSqlQuery(QSqlQuery& sqlQuery);
private:
    QSqlDatabase _database;
};
