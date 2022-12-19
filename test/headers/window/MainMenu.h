#pragma once

#include <QWidget>
#include <QPushButton>

//INFO Класс отвечает за работу главного меню
class MainMenu : public QWidget
{
private:
    Q_OBJECT
public:
    MainMenu(int width, QWidget* pParent = Q_NULLPTR);
    virtual ~MainMenu() Q_DECL_EQ_DEFAULT;
signals:
    //INFO Сигнал, который при клике на кнопку "New game" инициирует начало новой игры
    void NewGame();

    //INFO Сигнал, который при клике на кнопку "Exit" инициирует завершение работы программы
    void Exit();
private:
    QPushButton* _pButtonNewGame;
    QPushButton* _pButtonExit;
};
