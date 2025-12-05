#include "cellbutton.h"

CellButton::CellButton(int i, int j, QWidget *parent)
    : QPushButton(parent), row(i), col(j) {}

void CellButton::mousePressEvent(QMouseEvent *event) {

    if (event->button() == Qt::LeftButton) {
        emit leftClicked(row, col);
    }else if (event->button() == Qt::RightButton) {
        emit rightClicked(row, col);
    }
       QPushButton::mousePressEvent(event);
}
