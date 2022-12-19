#pragma once

#include <inventory/InventoryTable.h>
#include <inventory/InventoryView.h>
#include <item/AppleLabel.h>
#include <window/MainMenu.h>

#include <QMainWindow>
#include <QPushButton>

//INFO Класс отвечает за работу игрового окна
class Window : public QMainWindow
{
private:
    Q_OBJECT
public:
    Window(QWidget* pParent = Q_NULLPTR);
    virtual ~Window() Q_DECL_EQ_DEFAULT;
private slots:
    //INFO Слот отображает главное меню, содержащее кнопки "New game" и "Exit"
    void ShowMainMenu();

    //INFO Слот запускает новую игру (ресетит инвентарь)
    void NewGame();

    //INFO Слот завершает работу приложения
    void Exit();
private:
    InventoryTable _pInventoryTable;
    InventoryView* _pInventoryView;
    AppleLabel* _pAppleLabel;
    QPushButton* _pButtonMainMenu;
    MainMenu* _pMainMenu;
    QWidget* _pWidget;
};
