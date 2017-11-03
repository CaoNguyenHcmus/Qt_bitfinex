#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ui_widget.h"
#include <QDebug>

#if 0
namespace Ui {
class Widget;
}
#endif
class Widget : public QWidget, public Ui::Widget //multiple inherence
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void get_data();
    void setValue();

signals:
    void valueChanged(double);
/*
private slots:
    void on_exitButton_clicked();
*/
private slots:
    void on_buyButton_clicked();
    void on_sellButton_clicked();
    void on_pushButton_clicked();

    void on_queryButton_clicked();

    void on_replaceOrderButton_clicked();

private:
    //Ui::Widget *ui;
    std::vector<QString> symbols; // possible symbol pairs

};

#endif // WIDGET_H
