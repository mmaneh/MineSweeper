#ifndef CELLBUTTON_H
#define CELLBUTTON_H
#include <QPushButton>
#include <QMouseEvent>

class CellButton : public QPushButton
{
    Q_OBJECT
public:
    CellButton(int i, int j, QWidget *parent = nullptr);

    int getRow() const {return row;}
    int getCol() const {return col;}

    void mousePressEvent(QMouseEvent *event) override;

signals:
    void leftClicked(int row, int col);
    void rightClicked(int row, int col);

private:
    int row;
    int col;
};

#endif // CELLBUTTON_H
