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
    gameMenu->addAction("Close", this, &MainWindow::onExitGame);

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
    //boardWidget->generateMockBoard();
    boardWidget->setEnabled(true);
    vbox->addWidget(boardWidget, 1);

    connect(boardWidget, &BoardWidget::requestCellUpdate, this, &MainWindow::updateCellFromModel);

    controller = new GameController(rows, cols, mines, this);

    connect(controller, &GameController::mineCounterUpdated,
            statusPanel, &StatusPanel::setMineCount);

    connect(controller, &GameController::gameStateChanged,
            statusPanel, &StatusPanel::setFaceState);

    connect(controller, &GameController::timerUpdated,
            statusPanel, &StatusPanel::setTime);

    connect(controller, &GameController::boardUpdated,
            boardWidget, [this]() {
                for (int r = 0; r < rows; ++r) {
                    for (int c = 0; c < cols; ++c) {
                        updateCellFromModel(r, c);
                    }
                }
            });

    connect(controller, &GameController::cellUpdated,
            this, &MainWindow::updateCellFromModel);

    connect(controller, &GameController::gameWon,
            this, [](){ qDebug() << "Game Won!"; });

    connect(controller, &GameController::gameLost,
            this, [](){ qDebug() << "Game Lost!"; });

    connect(boardWidget, &BoardWidget::onLeftClicked,
            controller, &GameController::handleCellLeftClick);

    connect(boardWidget, &BoardWidget::onRightClicked,
            controller, &GameController::handleCellRightClick);

    connect(boardWidget, &BoardWidget::requestCellUpdate,
            this, &MainWindow::updateCellFromModel);


}

void MainWindow::updateCellFromModel(int row, int col)
{
    const CellModel& cell = controller->getCellState(row, col);

    if (controller->getGameState() == GameState::Lost &&
        cell.isFlagged() && !cell.hasMine()) {
        boardWidget->setCellState(row, col, CellState::RevealedWrongFlag);
        return;
    }

    if (!cell.isRevealed()) {
        if (cell.isFlagged())
            boardWidget->setCellState(row, col, CellState::Flagged);
        else
            boardWidget->setCellState(row, col, CellState::Covered);
        return;
    }

    if (cell.hasMine()) {
        boardWidget->setCellState(row, col, CellState::RevealedMine);
        return;
    }

    int n = cell.adjacentMines();
    if (n == 0)
        boardWidget->setCellState(row, col, CellState::RevealedEmpty);
    else
        boardWidget->setCellState(row, col, CellState::RevealedNumber, n);
}

void MainWindow::setupGame(int rows, int cols, int mines) {
    this->rows = rows;
    this->cols = cols;
    this->mines = mines;
}
void MainWindow::onRestartClicked()
{
    qDebug() << "Restart clicked";
    if (controller)
        controller->handleRestart();

}

void MainWindow::onBackClicked()
{
    emit backRequested();

}

void MainWindow::onNewGame()
{
    onRestartClicked();
    qDebug() << "New Game triggered";
}

void MainWindow::onChangeDifficulty()
{
    QStringList difficulties = {"Beginner", "Intermediate", "Expert"};
    bool ok;
    QString choice = QInputDialog::getItem(this, "Select Difficulty",
                                           "Difficulty:", difficulties, 0, false, &ok);
    if (ok && !choice.isEmpty()) {
        if (choice == "Beginner") {
            setupGame(9, 9, 10);
            statusPanel->setDifficultyLabel("Beginner");
        } else if (choice == "Intermediate") {
            setupGame(16, 16, 40);
            statusPanel->setDifficultyLabel("Intermediate");
        } else if (choice == "Expert") {
            setupGame(16, 30, 99);
            statusPanel->setDifficultyLabel("Expert");
        }

        auto *vbox = qobject_cast<QVBoxLayout*>(centralWidget()->layout());

        if (boardWidget) {
            vbox->removeWidget(boardWidget);
            boardWidget->deleteLater();
            boardWidget = nullptr;
        }

        boardWidget = new BoardWidget(rows, cols, this);
        boardWidget->setEnabled(true);
        vbox->addWidget(boardWidget, 1);

        connect(boardWidget, &BoardWidget::onLeftClicked,
                controller, &GameController::handleCellLeftClick);
        connect(boardWidget, &BoardWidget::onRightClicked,
                controller, &GameController::handleCellRightClick);
        connect(boardWidget, &BoardWidget::requestCellUpdate,
                this, &MainWindow::updateCellFromModel);

        controller->handleDifficultyChange(rows, cols, mines);

        qDebug() << "Change Difficulty triggered";
    }
}

void MainWindow::onExitGame()
{
    close();
}
