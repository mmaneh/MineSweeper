#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>

class WelcomeWindow : public QMainWindow
{
    Q_OBJECT


public:    
    WelcomeWindow(QWidget *parent = nullptr);
    ~WelcomeWindow();
    void setupUi();
    void connections();
signals:
    void difficultySelected(int row, int col, int mines);
private:
    QPushButton *beginnerbtn;
    QPushButton *intermediatebtn;
    QPushButton *expertbtn;
    QPushButton *howToPlay;
    QPushButton *about;
    QVBoxLayout *vlayout;

};
#endif // WELCOMEWINDOW_H
