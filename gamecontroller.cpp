#include "gamecontroller.h"

GameController::GameController(int rows, int cols, int mines, QObject* parent)
    : QObject(parent), m_rows(rows), m_cols(cols), m_mines(mines), isFirstClick(true) {

    m_board.initializeBoard(rows, cols, mines);

    emit boardUpdated();
    emit mineCounterUpdated(m_board.getRemainingMineCount());
    emit gameStateChanged(m_board.getGameState());
}

void GameController::handleDifficultyChange(int rows, int cols, int mines)
{


    m_rows = rows;
    m_cols = cols;
    m_mines = mines;

    m_board.newGame(rows, cols, mines);
    isFirstClick = true;

    emit boardUpdated();
    emit mineCounterUpdated(m_board.getRemainingMineCount());
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
        emit gameStateChanged(GameState::Playing);
    }

    m_board.revealCell(row, col);

    emit cellUpdated(row, col);
    emit boardUpdated();

    if (m_board.getGameState() == GameState::Won) {
        emit gameWon();
    }
    else if (m_board.getGameState() == GameState::Lost) {
        emit gameLost();
    }

    emit gameStateChanged(m_board.getGameState());
}

void GameController::handleCellRightClick(int row, int col)
{
    if (m_board.toggleFlag(row, col)) {
        emit cellUpdated(row, col);
        emit mineCounterUpdated(m_board.getRemainingMineCount());
    }
}

void GameController::handleRestart()
{

    m_board.newGame(m_rows, m_cols, m_mines);
    isFirstClick = true;

    emit boardUpdated();
    emit mineCounterUpdated(m_board.getRemainingMineCount());
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
