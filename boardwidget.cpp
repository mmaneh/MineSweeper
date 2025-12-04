// boardwidget.cpp
#include "boardwidget.h"
#include <QGridLayout>
#include <QDebug>

BoardWidget::BoardWidget(int rows, int cols, int totalMines, QWidget *parent)
    : QWidget(parent), m_rows(rows), m_cols(cols), m_totalMines(totalMines)
{
    setStyleSheet("background-color: #c0c0c0;");

    auto *grid = new QGridLayout(this);
    grid->setSpacing(0);
    grid->setContentsMargins(10, 10, 10, 10);

    m_buttons.resize(rows, std::vector<CellButton*>(cols));

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            auto *btn = new CellButton(r, c, this);
            m_buttons[r][c] = btn;
            grid->addWidget(btn, r, c);

            connect(btn, &CellButton::leftClicked,  this, &BoardWidget::cellLeftClicked);
            connect(btn, &CellButton::rightClicked, this, &BoardWidget::cellRightClicked);
        }
    }

    setMinimumSize(cols * 32 + 20, rows * 32 + 20);
}

void BoardWidget::newGame()
{
    for (auto &row : m_buttons) {
        for (auto *btn : row) {
            btn->setText("");
            btn->setEnabled(true);
            btn->setIcon(QIcon());
            btn->setStyleSheet(
                "QPushButton {"
                "   background-color: #bdbebf;"
                "   border: 2px outset #808080;"
                "   border-top-color: #dfdfdf;"
                "   border-left-color: #dfdfdf;"
                "}"
                );
        }
    }

    qDebug() << "BoardWidget: New game started";
}
