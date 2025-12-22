#include "gamecontroller.h"

GameController::GameController(int rows, int cols, int mines, QObject* parent)
    : QObject(parent), m_rows(rows), m_cols(cols), m_mines(mines), isFirstClick(true) {

    m_board.initializeBoard(rows, cols, mines);
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);  // 1000ms = 1 second
    elapsedSeconds = 0;
    connect(m_timer, &QTimer::timeout, this, &GameController::onTimerTick);

    emit boardUpdated();
    emit mineCounterUpdated(m_board.getRemainingMineCount());
    emit gameStateChanged(m_board.getGameState());
}

void GameController::startTimer()
{
    if (!m_timer->isActive()) {
        m_timer->start();
    }
}

void GameController::stopTimer()
{
    m_timer->stop();
}

void GameController::resetTimer()
{
    stopTimer();
    elapsedSeconds = 0;
    emit timerUpdated(elapsedSeconds);
}

void GameController::onTimerTick()
{
    ++elapsedSeconds;
    if (elapsedSeconds > 999) {
        elapsedSeconds = 999;  // Cap at 999 like classic Minesweeper
    }
    emit timerUpdated(elapsedSeconds);
}
void GameController::handleDifficultyChange(int rows, int cols, int mines)
{


    m_rows = rows;
    m_cols = cols;
    m_mines = mines;

    m_board.newGame(rows, cols, mines);
    isFirstClick = true;
    resetTimer();
    emit boardUpdated();
    emit mineCounterUpdated(m_board.getRemainingMineCount());
    emit timerUpdated(0);
    emit gameStateChanged(GameState::NotStarted);
}
void GameController::handleCellLeftClick(int row, int col)
{
    if (m_board.isGameOver())
        return;

    if (isFirstClick) {
        m_board.placeMines(row, col);
        isFirstClick = false;
        m_board.setGameState(GameState::Playing);
        startTimer();
        emit gameStateChanged(GameState::Playing);
    }

    m_board.revealCell(row, col);

    emit cellUpdated(row, col);
    emit boardUpdated();

    if (m_board.getGameState() == GameState::Won) {
        stopTimer();
        emit gameWon();
    }
    else if (m_board.getGameState() == GameState::Lost) {
        stopTimer();
        emit gameLost();
    }

    emit gameStateChanged(m_board.getGameState());
}

void GameController::handleCellRightClick(int row, int col)
{
    if (m_board.isGameOver())
        return;
    if (m_board.toggleFlag(row, col)) {
        emit mineCounterUpdated(m_board.getRemainingMineCount());
        emit cellUpdated(row, col);
    }
}

void GameController::handleRestart()
{

    m_board.resetGame();
    isFirstClick = true;
    resetTimer();
    emit boardUpdated();
    emit mineCounterUpdated(m_board.getRemainingMineCount());
    emit timerUpdated(0);
    emit gameStateChanged(GameState::NotStarted);
}

const CellModel& GameController::getCellState(int row, int col) const
{
    return m_board.getCell(row, col);
}

int GameController::getCellNumber(int row, int col) const
{
    return m_board.getCell(row, col).adjacentMines();
}

GameState GameController::getGameState() const
{
    return m_board.getGameState();
}
