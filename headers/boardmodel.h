#ifndef BOARDMODEL_H
#define BOARDMODEL_H
#include "cellmodel.h"
#include <vector>
#include <random>

enum class GameState { NotStarted, Playing, Won, Lost };

class BoardModel {
public:
    BoardModel();

    void initializeBoard(int rows, int cols, int mineCount);
    void placeMines(int excludeRow, int excludeCol);

    CellModel& getCell(int row, int col);
    const CellModel& getCell(int row, int col) const;

    int getRows() const {return m_rows;}
    int getCols() const{return m_cols;}
    int getMineCount() const{return m_mineCount;}


    bool isValidPosition(int row, int col) const;

    GameState getGameState() const {return m_gameState;}
    void setGameState(GameState state);

    bool isFirstClick() const { return !m_minesPlaced; }
    int getPlacedMineCount() const { return m_placedMineCount; }
    void adjMineCount();
private:
    int m_rows = 0;
    int m_cols = 0;
    int m_mineCount = 0;

    int m_firstClickRow = -1;
    int m_firstClickCol = -1;

    bool m_minesPlaced = false;
    int m_placedMineCount = 0;

    std::vector<std::vector<CellModel>> m_grid;
    GameState m_gameState = GameState::NotStarted;
    std::random_device rd;
    std::mt19937 gen;
    std::vector<std::pair<int,int>> dir = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1},
    };
};

#endif // BOARDMODEL_H
