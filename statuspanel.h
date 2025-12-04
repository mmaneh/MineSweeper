#ifndef STATUSPANEL_H
#define STATUSPANEL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>

enum class GameState { Playing, Won, Lost };

class StatusPanel : public QWidget
{
    Q_OBJECT

public:
    explicit StatusPanel(QWidget *parent = nullptr);

    void setMineCount(int count);
    void setDifficultyLabel(const QString &text);
    void setFaceState(GameState state);

    void startTimer();
    void stopTimer();
    void resetTimer();

signals:
    void restartClicked();
    void backClicked();

private slots:
    void updateTime();

private:
    QLabel *mineCounter;
    QLabel *timer;
    QLabel *mineIcon;
    QLabel *timeIcon;
    QLabel *difficultyLabel;

    QPushButton *restartBtn;
    QPushButton *backBtn;

    QTimer *qtimer;
    int elapsedSeconds = 0;
};

#endif // STATUSPANEL_H
