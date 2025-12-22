#include "cellbutton.h"

CellButton::CellButton(int i, int j, QWidget *parent)
    : QPushButton(parent), row(i), col(j) {
        updateAppearance();
}

void CellButton::setState(CellState state, int number) {
    m_state = state;
    m_number = number;
    updateAppearance();
}
void CellButton::updateAppearance() {

    if (m_state == CellState::Covered) {
        setText("");
        setStyleSheet(
            "background-color: #E0C3A0;"
            "border: 2px solid #C0A080;"
            "border-radius: 2px;"
            );
    }else if (m_state == CellState::Flagged) {
        setStyleSheet(
            "background-color: #E0C3A0;"
            "border: 2px solid #C0A080;"
            "border-radius: 2px;"
            );
        setText("🚩");
    }else if (m_state == CellState::RevealedEmpty) {
        setText("");
        setStyleSheet(
            "background-color: #F5F5DC;"
            "border: 1px solid #C0A080;"
            );
    }else if (m_state == CellState::RevealedNumber) {
        setStyleSheet(
            "background-color: #F5F5DC;"
            "border: 1px solid #C0A080;"
            );

        if (m_number >= 1 && m_number <= 8) setText(QString::number(m_number));
        if (m_number == 1) setStyleSheet(styleSheet() + "color: #0000FF;");
        else if (m_number == 2) setStyleSheet(styleSheet() + "color: #008000;");
        else if (m_number == 3) setStyleSheet(styleSheet() + "color: #FF0000;");
        else if (m_number == 4) setStyleSheet(styleSheet() + "color: #000080;");
        else if (m_number == 5) setStyleSheet(styleSheet() + "color: #800000;");
        else if (m_number == 6) setStyleSheet(styleSheet() + "color: #008080;");
        else if (m_number == 7) setStyleSheet(styleSheet() + "color: #000000;");
        else if (m_number == 8) setStyleSheet(styleSheet() + "color: #808080;");
    }else if(m_state == CellState::RevealedMine) {
        setStyleSheet(
            "background-color: #FF4500;"  // bright orange-red, stands out
            "border: 1px solid #C00000;"
            "color: black;"
            );
        setText("💣");
    }else if (m_state == CellState::RevealedWrongFlag) {
        setStyleSheet(
            "background-color: #FFD700;" // gold/yellow, stands out on beige
            "border: 2px solid #C0A000;"
            );
        setText("🚩");
    }

}
void CellButton::mousePressEvent(QMouseEvent *event) {

    if (m_state == CellState::Covered || m_state == CellState::Flagged) {
        setStyleSheet(
            "background-color: #D1B27A;"
            "border: 2px solid #C0A080;"
            "border-radius: 2px;"
            );
    }

    if (event->button() == Qt::LeftButton) {
        emit leftClicked(row, col);
    }else if (event->button() == Qt::RightButton) {
        emit rightClicked(row, col);
    }
       QPushButton::mousePressEvent(event);

           updateAppearance();
}
