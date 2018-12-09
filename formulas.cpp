#include "formulas.h"
#include "ui_formulas.h"

formulas::formulas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::formulas)
{
    ui->setupUi(this);
}

formulas::~formulas()
{
    delete ui;
}

void formulas::on_pushButton_clicked()
{
    this->close();
    emit firstWindow();
}
