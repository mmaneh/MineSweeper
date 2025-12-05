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

    centralWidget()->setStyleSheet("background-color: #3E2723;");


    QLabel *wlcMessage = new QLabel("Welcome To Minesweeper");
    wlcMessage->setAlignment(Qt::AlignCenter);
    wlcMessage->setStyleSheet("color: #FFF8E1;"
                              "font: bold 28px 'Segoe UI';");

    QLabel *diff = new QLabel("Choose The Difficulty");
    diff->setAlignment(Qt::AlignCenter);
    diff->setStyleSheet("color: #FFF8E1;"
                        "font: 22px 'Segoe UI';");

    beginnerbtn = new QPushButton("Beginner\n9x9, 10 Mines");
    intermediatebtn = new QPushButton("Intermediate\n16x16, 40 Mines");
    expertbtn = new QPushButton("Expert\n16x30, 99 Mines");
    QFont btnFont("Segoe UI", 12);  // font family + size
    beginnerbtn->setFont(btnFont);
    intermediatebtn->setFont(btnFont);
    expertbtn->setFont(btnFont);
    QString diffBtnStyle =
        "QPushButton {"
        "  background-color: #5C4033;" // Warm Taupe
        "  color: #FFF8E1;" // Bright Gold Accent Text
        "  border: 1px solid #E0C3A0;" // Almond border
        "  border-radius: 12px;"
        "  font: bold 20px 'Segoe UI';"
        "  padding: 10px 20px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #7B5C49;" // Slightly Lighter Hover
        "}"
        "QPushButton:pressed {"
        "  background-color: #3E2723;" // Dark Chocolate Pressed State
        "}";
    beginnerbtn->setStyleSheet(diffBtnStyle);
    intermediatebtn->setStyleSheet(diffBtnStyle);
    expertbtn->setStyleSheet(diffBtnStyle);


    howToPlay = new QPushButton("How To Play");
    about = new QPushButton("About");

    QString secondaryBtnStyle =
        "QPushButton {"
        "background-color: #3E2723;" // Dark Chocolate
        "color: #FFF8E1;" // Ivory Cream Text
        "font-weight:bold;"
        "border-radius:18px;"
        "padding:8px;"
        "border: 1px solid #5C4033;" // Subtle Taupe Border
        "}"
        "QPushButton:hover {"
        "background-color:#5C4033;" // Warm Taupe Hover
        "}";
    howToPlay->setStyleSheet(secondaryBtnStyle);
    about->setStyleSheet(secondaryBtnStyle);



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

