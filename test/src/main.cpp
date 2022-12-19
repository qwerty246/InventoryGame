#include <window/Window.h>

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Window window;
    return app.exec();
}
