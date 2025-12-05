#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H
#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include <cellbutton.h>

class BoardWidget : public QWidget
{
    Q_OBJECT
public:
    BoardWidget(int rows, int cols, QWidget *parent = nullptr);

private slots:
    void handleLeftClick(int row, int col);
    void handleRightClick(int row, int col);

signals:
   void onRightClicked(int row, int col);
   void onLeftClicked(int row, int col);

private:
    int m_rows;
    int m_cols;
    QGridLayout *layout;
    QVector<QVector<CellButton*>> btns;
};

#endif // BOARDWIDGET_H
