#pragma once

#include <QLabel>

//INFO Класс представляет собой лейбл яблока на главном окне,
//INFO который является бесконечным источником яблок
class AppleLabel : public QLabel
{
private:
    Q_OBJECT
public:
    AppleLabel(QWidget* pParent = Q_NULLPTR);
    virtual ~AppleLabel() Q_DECL_EQ_DEFAULT;
public:
    //INFO Метод обрабатывает перенос drag'n'drop объекта
    virtual void mouseMoveEvent(QMouseEvent* pEvent) Q_DECL_FINAL;
    //INFO Метод создает новый drag'n'drop объект
    virtual void mousePressEvent(QMouseEvent* pEvent) Q_DECL_FINAL;
public:
    enum
    {
        LABEL_SIZE = 128
    };
private:
    const int _type;
    const int _labelSize;
    QPoint _dragPosition;
};
