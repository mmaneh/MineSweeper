#include "boardwidget.h"

BoardWidget::BoardWidget(int rows, int cols, QWidget *parent) :
    QWidget(parent), m_rows(rows), m_cols(cols)
{
    layout = new QGridLayout(this);
    layout->setSpacing(3);
    layout->setContentsMargins(0,0,0,0);

    btns.resize(m_rows);
    for (int i = 0; i < m_rows; ++i) {
        btns[i].resize(cols);
        for (int j = 0; j < m_cols; ++j) {
            btns[i][j] = new CellButton(i, j, this);
            btns[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            layout->addWidget(btns[i][j], i, j);

            connect(btns[i][j], &CellButton::leftClicked, this, &BoardWidget::handleLeftClick);
            connect(btns[i][j], &CellButton::rightClicked, this, &BoardWidget::handleRightClick);
        }
    }

    setLayout(layout);
}

void BoardWidget::handleLeftClick(int row, int col) {
    qDebug() << "Left click at " << row << col;
    emit onLeftClicked(row, col);
}

void BoardWidget::handleRightClick(int row, int col) {
    qDebug() << "Right click at " << row << col;
    emit onRightClicked(row, col);
}
void BoardWidget::setCellState(int row, int col, CellState state, int number) {
    btns[row][col]->setState(state, number);
    btns[row][col]->updateAppearance();
}
void BoardWidget::generateMockBoard() {
    if (m_rows < 3 || m_cols < 3) return;

    int r = 0, c = 0;


    setCellState(r, c++, CellState::Covered);

    setCellState(r, c++, CellState::Flagged);

    setCellState(r, c++, CellState::RevealedEmpty);

    for (int num = 1; num <= 8; ++num) {
        if (c >= m_cols) { c = 0; r++; }
        setCellState(r, c++, CellState::RevealedNumber, num);
    }

    if (c >= m_cols) { c = 0; r++; }
    setCellState(r, c++, CellState::RevealedMine);

    if (c >= m_cols) { c = 0; r++; }
    setCellState(r, c++, CellState::RevealedWrongFlag);

    for (; r < m_rows; ++r) {
        for (; c < m_cols; ++c) {
            setCellState(r, c, CellState::Covered);
        }
        c = 0;
    }
}
