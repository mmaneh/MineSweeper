// main.cpp
#include <QApplication>
#include "welcomewindow.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WelcomeWindow welcome;
    welcome.show();
    MainWindow* game = nullptr;

    QObject::connect(&welcome, &WelcomeWindow::difficultySelected, [&](int rows, int cols, int mines){
        welcome.hide();
        game = new MainWindow(rows, cols, mines);
        game->show();

        QObject::connect(game, &MainWindow::backRequested, [&, game](){
            game->hide();
            welcome.show();
        });
    });


    return a.exec();
}
