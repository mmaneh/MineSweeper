#include "mainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), rows(9), cols(9), mines(10)
{
    setupMenu();
    setupUi();
}
MainWindow::MainWindow(int r, int c, int m, QWidget *parent)
    : QMainWindow(parent), rows(r), cols(c), mines(m)
{
    setupMenu();
    setupUi();
}

void MainWindow::setupMenu()
{
    QMenu *gameMenu = menuBar()->addMenu("Game");
    gameMenu->addAction("New Game", this, &MainWindow::onNewGame);
    gameMenu->addAction("Change Difficulty", this, &MainWindow::onChangeDifficulty);
    gameMenu->addSeparator();
    gameMenu->addAction("Exit", this, &MainWindow::onExitGame);

    QMenu *helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction("How To Play", [](){
        QMessageBox::information(nullptr, "How to Play",
                                 "• Left-click: reveal tile\n"
                                 "• Right-click: flag tile\n"
                                 "• Clear all safe tiles to win");
    });
    helpMenu->addAction("About", [](){
        QMessageBox::about(nullptr, "About",
                           "Minesweeper Project\nCreated by Mane Mkhitaryan");
    });
}

void MainWindow::setupUi()
{
    setWindowTitle("Minesweeper");
    setMinimumSize(600, 600);

    QWidget *central = new QWidget(this);
    central->setStyleSheet("background-color: #3E2723;");
    setCentralWidget(central);

    auto *vbox = new QVBoxLayout(central);
    vbox->setContentsMargins(5,5,5,5);
    vbox->setSpacing(10);

    statusPanel = new StatusPanel();
    statusPanel->setMineCount(mines);
    QString diff = (rows==9) ? "Beginner" : (rows==16 && cols==16) ? "Intermediate" : "Expert";
    statusPanel->setDifficultyLabel(diff);

    connect(statusPanel, &StatusPanel::restartClicked, this, &MainWindow::onRestartClicked);
    connect(statusPanel, &StatusPanel::backClicked, this, &MainWindow::onBackClicked);

    vbox->addWidget(statusPanel);

    boardWidget = new BoardWidget(rows, cols, this);
    boardWidget->setEnabled(true);
    vbox->addWidget(boardWidget, 1);

    connect(boardWidget, &BoardWidget::onLeftClicked, this, &MainWindow::onLeftCellClicked);
    connect(boardWidget, &BoardWidget::onRightClicked, this, &MainWindow::onRightCellClicked);
}
void MainWindow::onLeftCellClicked(int row, int col) {
    if (!firstClick) {
        firstClick = true;
        statusPanel->startTimer();
    }
    qDebug() << "Left cell is clicked" << row << col;
}
void MainWindow::onRightCellClicked(int row, int col) {
    if (!firstClick) {
        firstClick = true;
        statusPanel->startTimer();
    }

    qDebug() << "Right cell is clicked" << row << col;
}

void MainWindow::setupGame(int rows, int cols, int mines) {
    this->rows = rows;
    this->cols = cols;
    this->mines = mines;
}
void MainWindow::onRestartClicked()
{
    qDebug() << "Restart clicked";
    statusPanel->resetTimer();
    statusPanel->stopTimer();
    statusPanel->setFaceState(GameState::Playing);
    statusPanel->setMineCount(mines);

}

void MainWindow::onBackClicked()
{
    emit backRequested();

}

void MainWindow::onNewGame()
{
    qDebug() << "New Game triggered";
}

void MainWindow::onChangeDifficulty()
{
    qDebug() << "Change Difficulty triggered";
}

void MainWindow::onExitGame()
{
    close();
}
