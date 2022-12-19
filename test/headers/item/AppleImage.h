#pragma once

#include <QLabel>

//INFO Класс содержит изображение яблока. Реализован как синглтон.
class AppleImage: public QLabel
{
private:
    //INFO Эти методы запривачены для реализации синглтона
    Q_OBJECT
    AppleImage() Q_DECL_EQ_DEFAULT;
    Q_DISABLE_COPY(AppleImage)
    AppleImage(AppleImage&&);
    AppleImage& operator=(AppleImage&&);
public:
    virtual ~AppleImage() Q_DECL_EQ_DEFAULT;
public:
    //INFO Метод возвращает изображение яблока
    static const QPixmap& GetImage(int type);
private:
    QPixmap _pixmap;
};
