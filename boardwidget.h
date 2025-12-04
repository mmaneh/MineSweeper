// boardwidget.h
#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <vector>
#include "cellbutton.h"

class BoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BoardWidget(int rows, int cols, int totalMines, QWidget *parent = nullptr);

public slots:
    void newGame();

signals:
    void cellLeftClicked(int row, int col);
    void cellRightClicked(int row, int col);

private:
    int m_rows, m_cols, m_totalMines;
    std::vector<std::vector<CellButton*>> m_buttons;
};

#endif // BOARDWIDGET_H
