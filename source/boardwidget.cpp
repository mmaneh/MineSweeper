#include "boardwidget.h"

BoardWidget::BoardWidget(int rows, int cols, QWidget *parent) :
    QWidget(parent), m_rows(rows), m_cols(cols)
{
    layout = new QGridLayout(this);
    btns.resize(m_rows);
    for (int i = 0; i < m_rows; ++i) {
        btns[i].resize(cols);
        for (int j = 0; j < m_cols; ++j) {
            btns[i][j] = new CellButton(i, j, this);
            btns[i][j]->setFixedSize(30, 30);
           btns[i][j]->setStyleSheet("background-color: #C0C0C0;");
            layout->addWidget(btns[i][j],i,j);

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
