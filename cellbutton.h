// cellbutton.h
#ifndef CELLBUTTON_H
#define CELLBUTTON_H

#include <QPushButton>

class CellButton : public QPushButton
{
    Q_OBJECT

public:
    CellButton(int row, int col, QWidget *parent = nullptr);

    int row() const { return m_row; }
    int col() const { return m_col; }

protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void leftClicked(int row, int col);
    void rightClicked(int row, int col);

private:
    int m_row, m_col;
};

#endif // CELLBUTTON_H
