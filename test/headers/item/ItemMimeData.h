#pragma once

#include <QMimeData>

//INFO Класс участвует в обработке drag'n'drop событий
class ItemMimeData : public QMimeData
{
public:
    ItemMimeData(int type) : _type(type) {}
    virtual ~ItemMimeData() Q_DECL_EQ_DEFAULT;
public:
    //INFO Переопределенный метод возвращает поддерживаемый формат "application/apple"
    virtual QStringList formats() const Q_DECL_FINAL;
    //INFO Переопределенный метод проверяет наличие поддерживаемого формата "application/apple"
    virtual bool hasFormat(const QString& mimeType) const Q_DECL_FINAL;
public:
    //INFO Метод возвращает тип объекта
    int GetType() const;
private:
    int _type;
};
