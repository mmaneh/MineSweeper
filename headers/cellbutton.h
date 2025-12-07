#ifndef CELLBUTTON_H
#define CELLBUTTON_H
#include <QPushButton>
#include <QMouseEvent>

enum class CellState {
    Covered,
    Flagged,
    RevealedEmpty,
    RevealedNumber,
    RevealedMine,
    RevealedWrongFlag
};

class CellButton : public QPushButton
{
    Q_OBJECT
public:
    CellButton(int i, int j, QWidget *parent = nullptr);

    int getRow() const {return row;}
    int getCol() const {return col;}

    void mousePressEvent(QMouseEvent *event) override;
    void setState(CellState state, int number = 0);
    CellState getState() const {return m_state;}
    void updateAppearance();
signals:
    void leftClicked(int row, int col);
    void rightClicked(int row, int col);

private:
    int row;
    int col;
    int m_number;
    CellState m_state;
};

#endif // CELLBUTTON_H
