#include <window/MainMenu.h>

#include <QGridLayout>

MainMenu::MainMenu(int width, QWidget* pParent) :
    QWidget(pParent),
    _pButtonNewGame(new QPushButton("New game", this)),
    _pButtonExit(new QPushButton("Exit", this))
{
    QGridLayout* pGridLayout = new QGridLayout(this);
    pGridLayout->setMargin(2);
    pGridLayout->addWidget(_pButtonNewGame, 0, 0);
    pGridLayout->addWidget(_pButtonExit, 0, 1);
    setLayout(pGridLayout);
    setGeometry(0, 0, width, height());

    connect(_pButtonNewGame, SIGNAL(clicked()), SIGNAL(NewGame()));
    connect(_pButtonExit, SIGNAL(clicked()), SIGNAL(Exit()));
}
