#include <QApplication>
#include "AppManager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    AppManager manager;
    manager.startApp();

    return app.exec();
}
