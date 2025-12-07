#ifndef CELLMODEL_H
#define CELLMODEL_H

class CellModel
{
public:
    CellModel();
    bool hasMine() const;
    int adjacentMines() const;
    bool isRevealed() const;
    bool isFlagged() const;

    void setMine(bool value);
    void setAdjacentMines(int count);
    void setRevealed(bool value);
    void setFlagged(bool value);
private:
    bool m_hasMine;
    int m_adjacentMines;
    bool m_isRevealed;
    bool m_isFlagged;
};

#endif // CELLMODEL_H
