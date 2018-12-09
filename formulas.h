#ifndef FORMULAS_H
#define FORMULAS_H

#include <QWidget>

namespace Ui {
class formulas;
}

class formulas : public QWidget
{
    Q_OBJECT

public:
    explicit formulas(QWidget *parent = nullptr);
    ~formulas();

signals:
    void firstWindow();


private slots:
    void on_pushButton_clicked();

private:
    Ui::formulas *ui;
};

#endif // FORMULAS_H
