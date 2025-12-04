// main.cpp
#include <QApplication>
#include "welcomewindow.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WelcomeWindow welcome;
    welcome.show();

    // When user picks difficulty → open MainWindow
    QObject::connect(&welcome, &WelcomeWindow::difficultySelected, [&](int rows, int cols, int mines){
        welcome.hide();
        MainWindow *game = new MainWindow(rows, cols, mines);
        game->show();
    });

    return a.exec();
}
