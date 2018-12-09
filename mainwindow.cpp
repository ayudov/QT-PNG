#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QString"
#include "qmath.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1260,625);
    FWindow = new formulas();
    connect(FWindow, &formulas::firstWindow, this, &MainWindow::show);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int min = ui->a->value();
    int max = ui->b->value();
    int N = ui->N->value();

    QString numout = "";
    if (min >= max && N==0){QMessageBox::information(this,tr("Помилка"),tr("Верхня границя має бути більшою за нижню та кількість чисел має бути більше '0'"));}
    else if (min >= max){QMessageBox::information(this,tr("Помилка"),tr("Верхня границя має бути більшою за нижню"));}
    else if (N==0){QMessageBox::information(this,tr("Помилка"),tr("Кількість чисел має бути більше '0'"));}
    else{
        for (int i = 1;i<=N;i++){
            int rand_num = min + rand()%(max - min +1);
            numout.append(QString::number(i) + ": " + QString::number(rand_num)+"\n");
        }
        ui->numout->setText(numout);
    }
 }


void MainWindow::on_action_3_triggered()
{
     QMessageBox::information(this,tr("Інструкція"),tr("Виберіть кількість чисел, нижню та верхню границі, та натисніть на 'Згенерувати число'.\nВерхня границя має бути більшою за нижню!\nЩоб все стерти, натисніть кнопку 'Стерти'"));
}


void MainWindow::on_action_4_triggered()
{
    QMessageBox::information(this,tr("Інструкція"),tr("Виберіть всі початкові значення (не залишайте їх ріними 0!), та виберіть необхідну дію.\nЩоб все стерти, натисніть кнопку 'Стерти'"));
}

void MainWindow::on_About_triggered()
{
    QMessageBox::information(this,tr("Про"),tr("Програма створена по дисципліні 'Комп'ютерне модулювання-1'.\nЮдов Андрій\nГрупа ІК-61\n2018 рік."));
}

void MainWindow::on_calculate_clicked()
{
    ui->conditions->clear();
    QString output = "";

    n = ui->n->value();
    mu = ui->mu->value();
    l = ui->l->value();
    m = ui->mm->value();

    if (n != 0){
        for (int i=0; i<= n + m; i++){
            if (i<=n){
                output.append("S" + QString::number(i)+":" + QString::number(i) + " зайнято"+"\n");
            }
            else if(i<=n+m){
                output.append("S" + QString::number(i)+":" + QString::number(n) + " зайнято, " + QString::number(i-n) + " у черзі" + "\n");
            }
        }
    }
    else {QMessageBox::warning(this,tr("Помилка"),tr("Будь-ласка, виберіть значення 'n'"));}

    ui->conditions->setText(output);
}

void MainWindow::on_graph_clicked()
{
    ui->graph_2->clear();
    QString graph ="";

    n = ui->n->value();
    m = ui->mm->value();


    if (n != 0){
        for (int i=0; i<= n + m; i++){
            if (i<=n){
                graph.append("|S" + QString::number(i) + "| ");
                if (i!=n){
                    graph.append("<-" + QString::number(i+1) + "*μ,λ-> ");
                }

            }
            else if(i<=n+m){
                if (i == n+1){graph.append("<- " + QString::number(n) + "*μ,λ-> ");}
                graph.append("|S" + QString::number(i)+"| ");
                if (i!=n+m){
                    graph.append("<-" + QString::number(n)+"*μ,λ-> ");
                }
            }
        }
    }
    else {QMessageBox::warning(this,tr("Помилка"),tr("Будь-ласка, виберіть значення 'n'"));}
    ui->graph_2->setText(graph);
}

void MainWindow::on_clear_clicked(){

    ui->conditions->clear();
    ui->graph_2->clear();
    ui->numout->clear();
    ui->P0->display(0);
    ui->Noch->display(0);
    ui->Toch->display(0);
    ui->Nsk->display(0);
}

void MainWindow::on_action_5_triggered()
{
    QMessageBox::information(this,tr("Початкові умови"),tr("Генерація псевдовипадкових чисел із використаннія функції rand() та створення багатоканальної системи масового обслуговування із обмеженням на довжину черги."));
}

void MainWindow::on_action_6_triggered()
{
    FWindow->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    n = ui->n->value();
    m = ui->mm->value();
    l = ui->l->value();
    mu = ui->mu->value();
    double psi = l/mu;

    if (n == 0.0 || m == 0.0 || l == 0.0 || mu == 0.0){QMessageBox::information(this,tr("Помилка"),tr("Початкові значення мають бути більші за '0'"));}
    else{
        double P0 = 0;
        double  p = double(ui->l->value())/double(ui->mu->value());
    //считаем P0
        if (n == int(l) && mu == 1.0){
            double sum1 = 0;
            for (int i = 0;i<=n-1;i++){sum1 = sum1 + pow(p,i)/fact(i);}
            double sum2 = m*pow(p,n)/fact(n);
            P0 = 1/(sum1+sum2);
            ui->P0->display(P0);
        }
        else {
            double sum1 = 0;
            for (int i = 0;i<=n;i++){sum1 = sum1 + pow(p,i)/fact(i);}
            double sum2 = 0;
            for (int i = 1;i<=m;i++){sum2 = sum2 + pow(p/n,i);}
            sum2 *= pow(p,n)/fact(n);
            P0 = 1/(sum1+sum2);
            ui->P0->display(P0);
        }


    // считаем Noch
        double Noch = 0;
        if (n == int(l) && mu == 1.0){
            double Noch1 = pow(p,n+1)/(n*fact(n));
            double Noch2 = m*(m+1)/2;
            Noch = Noch1 * Noch2 * P0;
            ui->Noch->display(Noch);
        }
        else{
            double Noch1 = pow(p,n+1)/(n*fact(n));
            double Noch2 = (1-1*pow((p/n),m) * (m + 1 - m * p/n))/pow(1-p/n,2);
            Noch = Noch1 * Noch2 * P0;
            ui->Noch->display(Noch);
        }

    // считаем Toch
        double Toch = Noch/l;
        ui->Toch->display(Toch);

    // считаем Nsk
        double sum = 0;
        for (int i = 0;i<=n-1;i++){sum = sum + (n - i)*pow(psi,n)/fact(n)*P0;}
        double Nsk = sum;
        ui->Nsk->display(Nsk);
    }
}


int MainWindow::fact(int x)
{
    if (x == 0)        // HERE 5 is not equal to 1 so goes to else
    {
        return 1;
    }else
    {
        return x*fact(x-1); // returns 5*4*3*2*1  when x==1 it returns 1
    }
}

