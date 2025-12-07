#include "cellmodel.h"
CellModel::CellModel() : m_hasMine(false), m_adjacentMines(0), m_isRevealed(false), m_isFlagged(false) {}


bool CellModel::hasMine() const { return m_hasMine; }
int CellModel::adjacentMines() const { return m_adjacentMines; }
bool CellModel::isRevealed() const { return m_isRevealed; }
bool CellModel::isFlagged() const { return m_isFlagged; }


void CellModel::setMine(bool value) { m_hasMine = value; }
void CellModel::setAdjacentMines(int count) { m_adjacentMines = count; }
void CellModel::setRevealed(bool value) { m_isRevealed = value; }
void CellModel::setFlagged(bool value) { m_isFlagged = value; }

