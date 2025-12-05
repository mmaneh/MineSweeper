#include "statuspanel.h"
#include <QHBoxLayout>
#include <QFont>

StatusPanel::StatusPanel(QWidget *parent)
    : QWidget(parent)
{
    mineCounter = new QLabel("000", this);
    timer       = new QLabel("000", this);

    mineCounter->setStyleSheet("color: #FFC107; font: bold 38px 'Segoe UI', sans-serif; background: transparent;");
    timer->setStyleSheet(      "color: #FFC107; font: bold 38px 'Segoe UI', sans-serif; background: transparent;");

    mineCounter->setFixedWidth(110);
    timer->setFixedWidth(110);
    mineCounter->setAlignment(Qt::AlignCenter);
    timer->setAlignment(Qt::AlignCenter);

    restartBtn = new QPushButton("🙂", this);
    restartBtn->setFixedSize(56, 56);
    restartBtn->setStyleSheet(
        "QPushButton {"
        "  background: #FFC107; border: 2px solid #FFF8E1; border-radius: 28px; font-size: 36px;" // Gold Background
        "}"
        "QPushButton:hover { background: #FFD740; }"
        "QPushButton:pressed { background: #FFAB00; }"
        );

    difficultyLabel = new QLabel("Difficulty: Beginner", this);
    difficultyLabel->setStyleSheet("color: #FFF8E1; font: 13px 'Segoe UI'; background: transparent;");
    backBtn = new QPushButton("Back", this);
    backBtn->setStyleSheet(
        "QPushButton { background: #5C4033; border: 1px solid #FFF8E1; border-radius: 8px; padding: 6px 16px; color: #FFF8E1; font-weight: bold; }"
        "QPushButton:hover { background: #3E2723; }" // Dark Chocolate Hover
        );
    qtimer = new QTimer(this);
    qtimer->setInterval(1000);
    connect(qtimer, &QTimer::timeout, this, &StatusPanel::updateTime);

    connect(restartBtn, &QPushButton::clicked, this, &StatusPanel::restartClicked);
    connect(backBtn,    &QPushButton::clicked, this, &StatusPanel::backClicked);

    auto *layout87 = new QHBoxLayout(this);
    layout87->setSpacing(20);
    layout87->setContentsMargins(20, 12, 20, 12);

    layout87->addStretch();
    layout87->addWidget(backBtn);
    layout87->addWidget(difficultyLabel);
    layout87->addStretch();

    layout87->addWidget(mineCounter);
    layout87->addStretch();

    layout87->addWidget(restartBtn);

    layout87->addStretch();
    layout87->addWidget(timer);
    layout87->addStretch();

    setStyleSheet("StatusPanel { background: #3E2723; border-bottom: 2px solid #5C4033; }");

}

void StatusPanel::setMineCount(int count)
{
    int display = count;
    if (count < 0) {
        display = -count;
       mineCounter->setStyleSheet("color: #E74C3C; font: bold 42px 'Segoe UI'; background: transparent;");
    } else {
        mineCounter->setStyleSheet("color: #FFC107; font: bold 38px 'Segoe UI', sans-serif; background: transparent;");
    }
    mineCounter->setText(QString("%1").arg(display, 3, 10, QChar('0')));
}

void StatusPanel::setDifficultyLabel(const QString &text)
{
    difficultyLabel->setText("Difficulty: " + text);
}

void StatusPanel::setFaceState(GameState state)
{
    if (state == GameState::Playing) restartBtn->setText("🙂");
    else if (state == GameState::Won)   restartBtn->setText("😎");
    else restartBtn->setText("💀");
}

void StatusPanel::startTimer()
{
    elapsedSeconds = 0;
    timer->setText("000");
    qtimer->start();
}

void StatusPanel::stopTimer()
{
    qtimer->stop();
}

void StatusPanel::resetTimer()
{
    elapsedSeconds = 0;
    timer->setText("000");
}

void StatusPanel::updateTime()
{
    elapsedSeconds++;
    timer->setText(QString("%1").arg(elapsedSeconds, 3, 10, QChar('0')));

    if (elapsedSeconds >= 999) {
        timer->setText("999");
        qtimer->stop();
    }
}
