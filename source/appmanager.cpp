#include "AppManager.h"
#include <QDebug>

AppManager::AppManager(QObject *parent)
    : QObject(parent),
    welcomeWindow(nullptr),
    gameWindow(nullptr)
{
}

AppManager::~AppManager()
{
    delete welcomeWindow;
    delete gameWindow;
}

void AppManager::startApp()
{
    welcomeWindow = new WelcomeWindow();
    welcomeWindow->show();

    connect(welcomeWindow, &WelcomeWindow::difficultySelected,
            this, &AppManager::openGame);
}

void AppManager::openGame(int rows, int cols, int mines)
{
    if (welcomeWindow) welcomeWindow->hide();
    gameWindow = new MainWindow(rows, cols, mines);
    gameWindow->show();
    connect(gameWindow, &MainWindow::backRequested,
            this, &AppManager::returnToMenu);
}

void AppManager::returnToMenu()
{
    qDebug() << "Returning to welcome window";

    if (gameWindow) {
        gameWindow->hide();
        delete gameWindow;
        gameWindow = nullptr;
    }

    if (welcomeWindow) welcomeWindow->show();
}

