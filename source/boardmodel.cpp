#include "boardmodel.h"

BoardModel::BoardModel() : m_gameState(GameState::NotStarted) {}

void BoardModel::initializeBoard(int rows, int cols, int mineCount) {
    if (rows <= 0 || cols <= 0)
        throw std::invalid_argument("Rows and columns must be positive.");
    if (mineCount < 0 || mineCount > rows * cols)
        throw std::invalid_argument("Invalid mine count.");

    m_rows = rows;
    m_cols = cols;
    m_mineCount = mineCount;
    m_gameState = GameState::NotStarted;

    m_grid.clear();
    m_grid.resize(rows);
    for (int i = 0; i < rows; ++i) {
        m_grid[i].resize(cols);
    }
    m_minesPlaced = false;
    m_placedMineCount = 0;
}
void BoardModel::placeMines(int i, int j) {
    std::uniform_int_distribution<int> rowDist(0, m_rows - 1);
    std::uniform_int_distribution<int> colDist(0, m_cols - 1);
    int count = 0;
    m_firstClickRow = i;
    m_firstClickCol = j;
    while(count < m_mineCount) {
        int r = rowDist(gen);
        int c = colDist(gen);

        if (r == m_firstClickRow && c == m_firstClickCol) continue;
        if (m_grid[r][c].hasMine()) continue;
        m_grid[r][c].setMine(true);

        ++count;
    }
    m_minesPlaced = true;
    m_placedMineCount = count;
    adjMineCount();
}

void BoardModel::adjMineCount() {
    int count = 0;
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            if (m_grid[i][j].hasMine()) {
                m_grid[i][j].setAdjacentMines(-1);
                continue;
            }
            for (auto d : dir) {
                int x = d.first + i;
                int y = d.second + j;
                if (isValidPosition(x,y) && m_grid[x][y].hasMine()) ++count;
            }
            m_grid[i][j].setAdjacentMines(count);
        }
    }
}
CellModel& BoardModel::getCell(int row, int col) {
    if (!isValidPosition(row, col))
        throw std::out_of_range("Invalid cell position");
    return m_grid[row][col];
}

const CellModel& BoardModel::getCell(int row, int col) const {
    if (!isValidPosition(row, col))
        throw std::out_of_range("Invalid cell position");
    return m_grid[row][col];
}

bool BoardModel::isValidPosition(int row, int col) const {
    return row >= 0 && row < m_rows && col >= 0 && col < m_cols;
}

void BoardModel::setGameState(GameState state) { m_gameState = state; }
