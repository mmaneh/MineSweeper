#include "welcomewindow.h"
#include <QMessageBox>
#include <QDebug>

WelcomeWindow::WelcomeWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    vlayout = new QVBoxLayout();
    vlayout->setAlignment(Qt::AlignCenter);
    vlayout->setSpacing(15);
    central->setLayout(vlayout);

    setupUi();
    connections();
}

void WelcomeWindow::setupUi() {
    setWindowTitle("Minesweeper — Welcome");
    setFixedSize(400, 450);


   centralWidget()->setStyleSheet("background-color: #d0d0d0;");


    QLabel *wlcMessage = new QLabel("Welcome To Minesweeper");
    wlcMessage->setAlignment(Qt::AlignCenter);
    wlcMessage->setStyleSheet("font-size: 24px; font-weight: bold; color:white;");

    QLabel *diff = new QLabel("Choose The Difficulty");
    diff->setAlignment(Qt::AlignCenter);
    diff->setStyleSheet("font-size: 20px; font-weight: bold; color:white;");

    beginnerbtn = new QPushButton("Beginner\n9x9, 10 Mines");
    intermediatebtn = new QPushButton("Intermediate\n16x16, 40 Mines");
    expertbtn = new QPushButton("Expert\n16x30, 99 Mines");

    QString diffBtnStyle =
        "QPushButton {"
        "background-color: #6c6c6c;"
        "color: white;"
        "font-size: 16px;"
        "font-weight: bold;"
        "border-radius: 12px;"
        "min-height: 60px;"
        "}"
        "QPushButton:hover {"
        "background-color: #505050;"
        "}";

    beginnerbtn->setStyleSheet(diffBtnStyle);
    intermediatebtn->setStyleSheet(diffBtnStyle);
    expertbtn->setStyleSheet(diffBtnStyle);


    howToPlay = new QPushButton("How To Play");
    about = new QPushButton("About");

    QString smallBtnStyle =
        "QPushButton {"
        "color:white; font-weight:bold; border-radius:18px; padding:8px;"
        "}"
        "QPushButton:hover { opacity:0.8; }";

    howToPlay->setStyleSheet(
        "QPushButton {"
        "background-color: #6c7a89;"
        "color:white;"
        "font-weight:bold;"
        "border-radius:18px;"
        "padding:8px;"
        "}"
        "QPushButton:hover {"
        "background-color:#5a6876;"
        "}");

    about->setStyleSheet(
        "QPushButton {"
        "background-color: #8e7c6f;"
        "color:white;"
        "font-weight:bold;"
        "border-radius:18px;"
        "padding:8px;"
        "}"
        "QPushButton:hover {"
        "background-color:#7a6a5f;"
        "}");



    vlayout->addWidget(wlcMessage);
    vlayout->addWidget(diff);

    vlayout->addWidget(beginnerbtn);
    vlayout->addWidget(intermediatebtn);
    vlayout->addWidget(expertbtn);


    vlayout->addSpacing(10);

    vlayout->addWidget(howToPlay);
    vlayout->addWidget(about);
}

void WelcomeWindow::connections() {

    connect(beginnerbtn, &QPushButton::clicked, this, [this]() {
        qDebug() << "Beginner selected";
        emit difficultySelected(9, 9, 10);
    });

    connect(intermediatebtn, &QPushButton::clicked, this, [this]() {
        qDebug() << "Intermediate selected";
        emit difficultySelected(16, 16, 40);
    });

    connect(expertbtn, &QPushButton::clicked, this, [this]() {
        qDebug() << "Expert selected";
        emit difficultySelected(16, 30, 99);
    });

    connect(howToPlay, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(
            this, "How to Play",
            "• Left-click to reveal tiles.\n"
            "• Right-click to place flags.\n"
            "• Numbers show nearby mines.\n"
            "• Clear all safe tiles to win."
            );
    });

    connect(about, &QPushButton::clicked, this, [this]() {
        QMessageBox::about(
            this, "About",
            "Minesweeper Project\n"
            "Created by Mane Mkhitaryan\n"
            "Qt6 C++ Application"
            );
    });
}

WelcomeWindow::~WelcomeWindow() {}

