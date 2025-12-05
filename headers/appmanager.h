#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QObject>
#include "mainwindow.h"
#include "welcomewindow.h"

class AppManager : public QObject
{
    Q_OBJECT
public:
    explicit AppManager(QObject *parent = nullptr);
    ~AppManager();

    void startApp();

private slots:
    void openGame(int rows, int cols, int mines);
    void returnToMenu();

private:
    WelcomeWindow* welcomeWindow;
    MainWindow* gameWindow;
};

#endif // APPMANAGER_H

