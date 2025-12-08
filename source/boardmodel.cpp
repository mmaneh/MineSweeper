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
void BoardModel::revealAllMines() {
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            if (m_grid[i][j].hasMine()) m_grid[i][j].setRevealed(true);
        }
    }
}
bool BoardModel::checkWinCondition() {
    int total = m_rows * m_cols;
    return revealedCount == (total - m_mineCount);
}
bool BoardModel::checkLossCondition() {
    return revealedMine;
}
bool BoardModel::toggleFlag(int r, int c) {
    if (!isValidPosition(r, c)) return false;
    if (isGameOver()) return false;
    if (m_grid[r][c].isRevealed()) return false;
    if (!m_grid[r][c].isRevealed()) {
        if(!m_grid[r][c].isFlagged()) m_grid[r][c].setFlagged(true), ++flaggedCount;
        else  m_grid[r][c].setFlagged(false), --flaggedCount;
    }
    return true;
}

int BoardModel::getFlaggedCount() const {
    return flaggedCount;
}

int BoardModel::getRemainingMineCount() const{
    return m_mineCount - flaggedCount;
}

bool BoardModel::isCellFlagged(int row, int col) const {
    if (!isValidPosition(row, col))
        return false;
    return m_grid[row][col].isFlagged();
}

void BoardModel::revealCell(int i, int j) {
    if (!isValidPosition(i,j)) return;
     if (isGameOver()) return;
        CellModel& c = m_grid[i][j];

        if (c.isFlagged() || c.isRevealed()) return;
        c.setRevealed(true);
        ++revealedCount;
        if (c.hasMine()) {
            m_gameState = GameState::Lost,
            revealedMine = true;
            revealAllMines();
            return;
        }
        if (c.adjacentMines() > 0){
            if (checkWinCondition()) m_gameState = GameState::Won;
            return;
        }
        floodFill(i,j);
        if (checkWinCondition()) m_gameState = GameState::Won;
}

void BoardModel::floodFill(int i, int j) {
    std::queue<std::pair<int, int>> cells;
    std::vector<std::vector<bool>> visited(m_rows, std::vector<bool>(m_cols,false));
    cells.push({i,j});
    visited[i][j] = true;
    while(!cells.empty()) {
        auto [r, c] = cells.front();
        cells.pop();

        if (m_grid[r][c].isRevealed()) continue;
        m_grid[r][c].setRevealed(true);
        ++revealedCount;

        if (m_grid[r][c].adjacentMines() > 0 ) continue;

        for (auto d : dir) {
            int x = d.first + r;
            int y = d.second + c;
            if(isValidPosition(x,y) && !m_grid[x][y].isFlagged() && !m_grid[x][y].isRevealed() && !visited[x][y]) {
                cells.push({x,y});
                visited[x][y] = true;
            }
        }
    }
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
void BoardModel::resetGame() {
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            CellModel& cell = m_grid[i][j];
            cell.setMine(false);
            cell.setAdjacentMines(0);
            cell.setRevealed(false);
            cell.setFlagged(false);
        }
    }


    m_gameState = GameState::NotStarted;
    m_minesPlaced = false;
    m_firstClickRow = -1;
    m_firstClickCol = -1;
    flaggedCount = 0;
    revealedCount = 0;
    revealedMine = false;
    m_placedMineCount = 0;
}

void BoardModel::newGame(int rows, int cols, int mineCount) {
    if (rows != m_rows || cols != m_cols) {
        m_rows = rows;
        m_cols = cols;
        m_grid.clear();
        m_grid.resize(rows);
        for (int i = 0; i < rows; ++i) {
            m_grid[i].resize(cols);
        }
    }

    m_mineCount = mineCount;

    resetGame();
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

bool BoardModel::isGameOver() const {
    return m_gameState == GameState::Won || m_gameState == GameState::Lost;
}

