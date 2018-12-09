#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QGraphicsScene>
#include <QPaintEvent>
#include <QPainter>

#include <formulas.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int n;
    double mu;
    double  l;
    int m;


private slots:
    void on_pushButton_clicked();

    void on_action_3_triggered();

    void on_About_triggered();

    void on_calculate_clicked();

    void on_clear_clicked();

    void on_graph_clicked();

    void on_action_5_triggered();

    void on_action_6_triggered();

    void on_pushButton_2_clicked();



    void on_action_4_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *rectangle;
    QGraphicsLineItem *line;

    formulas *FWindow;


    int fact(int x);
    double sum(double x);
};

#endif // MAINWINDOW_H
