// cellbutton.cpp
#include "cellbutton.h"
#include <QMouseEvent>

CellButton::CellButton(int row, int col, QWidget *parent)
    : QPushButton(parent), m_row(row), m_col(col)
{
    setFixedSize(30, 30);
    setFocusPolicy(Qt::NoFocus);

    setStyleSheet(
        "QPushButton {"
        "   background-color: #bdbebf;"
        "   border: 2px outset #808080;"
        "   border-top-color: #dfdfdf;"
        "   border-left-color: #dfdfdf;"
        "   border-right-color: #808080;"
        "   border-bottom-color: #808080;"
        "}"
        "QPushButton:pressed {"
        "   border: 2px inset #808080;"
        "   padding: 2px;"
        "}"
        );
}

void CellButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit leftClicked(m_row, m_col);
    else if (event->button() == Qt::RightButton)
        emit rightClicked(m_row, m_col);

    QPushButton::mousePressEvent(event);
}
