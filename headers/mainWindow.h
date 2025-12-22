#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "boardwidget.h"
#include "gamecontroller.h"
#include <statuspanel.h>
#include <QVBoxLayout>
#include <QWidget>
#include <QMenuBar>
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>

class StatusPanel;
class QWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(int rows, int cols, int mines, QWidget *parent = nullptr);
    void setupGame(int rows, int cols, int mines);
private:
    void setupMenu();
    void setupUi();
private slots:
    void onRestartClicked();
    void onBackClicked();
    void onNewGame();
    void onChangeDifficulty();
    void onExitGame();
    void updateCellFromModel(int row, int col);

signals:
    void backRequested();

private:
    int rows;
    int cols;
    int mines;

    StatusPanel *statusPanel;
    QWidget *gameBoardPlaceholder;
    BoardWidget *boardWidget;
    GameController *controller;

};


#endif // MAINWINDOW_H

