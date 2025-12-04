#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "boardwidget.h"
#include <statuspanel.h>
#include <QVBoxLayout>
#include <QWidget>
#include <QMenuBar>
#include <QDebug>
#include <QMessageBox>

class StatusPanel;
class QWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(int rows, int cols, int mines, QWidget *parent = nullptr);

private slots:
    void onRestartClicked();
    void onBackClicked();
    void onNewGame();
    void onChangeDifficulty();
    void onExitGame();
    void setupMenu();
    void setupUi();

private:
    int rows;
    int cols;
    int mines;

    StatusPanel *statusPanel;
    QWidget *gameBoardPlaceholder;
    BoardWidget *boardWidget;
};


#endif // MAINWINDOW_H

