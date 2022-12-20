#include <window/Window.h>

#include <QApplication>
#include <QGridLayout>

Window::Window(QWidget* pParent):
    QMainWindow(pParent),
    _pInventoryView(new InventoryView(this)),
    _pInventoryTable(_pInventoryView->GetInventoryRow(), _pInventoryView->GetInventoryRow(),
                     _pInventoryView->GetTypeRole(), _pInventoryView->GetCountRole(), this),
    _pAppleLabel(new AppleLabel(this)),
    _pButtonMainMenu(new QPushButton("Main menu", this)),
    _pMainMenu(Q_NULLPTR)
{
    QGridLayout* pGridLayout = new QGridLayout(this);
    pGridLayout->addWidget(_pInventoryView, 0, 0, 2, 1, Qt::AlignCenter);
    pGridLayout->addWidget(_pButtonMainMenu, 1, 1, 1, 1, Qt::AlignCenter);

    QGridLayout* pGridLayoutApple = new QGridLayout(this);
    pGridLayoutApple->addWidget(_pAppleLabel, 0, 0, 1, 1, Qt::AlignCenter);
    pGridLayout->addLayout(pGridLayoutApple, 0, 1, 1, 1);

    _pWidget = new QWidget(this);
    _pWidget->setLayout(pGridLayout);
    setCentralWidget(_pWidget);
    setFixedSize(minimumSizeHint());

    _pMainMenu = new MainMenu(width(), this);
    connect(_pButtonMainMenu, SIGNAL(clicked()), SLOT(ShowMainMenu()));
    connect(_pMainMenu, SIGNAL(NewGame()), SLOT(NewGame()));
    connect(_pMainMenu, SIGNAL(Exit()), SLOT(Exit()));
    pGridLayout->setContentsMargins(0, _pMainMenu->height(), 0, 0);

    _pInventoryView->setModel(&_pInventoryTable);
    setMinimumSize(width(), height() + _pMainMenu->height());

    show();
    ShowMainMenu();
}

void Window::ShowMainMenu()
{
    _pWidget->setEnabled(false);
    _pMainMenu->setEnabled(true);
}

void Window::NewGame()
{
    _pWidget->setEnabled(true);
    _pMainMenu->setEnabled(false);
    _pInventoryTable.ResetTable();
}

void Window::Exit()
{
    QApplication::quit();
}
