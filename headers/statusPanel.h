#ifndef STATUSPANEL_H
#define STATUSPANEL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "gamestate.h"

class StatusPanel : public QWidget
{
    Q_OBJECT

public:
    explicit StatusPanel(QWidget *parent = nullptr);

    void setMineCount(int count);
    void setDifficultyLabel(const QString &text);
    void setFaceState(GameState state);
    void setTime(int seconds);

signals:
    void restartClicked();
    void backClicked();


private:
    QLabel *mineCounter;
    QLabel *timer;
    QLabel *difficultyLabel;

    QPushButton *restartBtn;
    QPushButton *backBtn;

};

#endif // STATUSPANEL_H
