#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets/QToolButton>
#include "ui_widget.h"
#include <QDebug>

class CurrencyMenu;
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
    
    void setCurrencyPairsList();
    CurrencyMenu* currencyMenu;
    void setupClass();
    
    
public slots:
    void get_data();
    void setValue();

    void indicatorHighChanged(QString, double);
    // void indicatorLowChanged(QString, double);
    void indicatorSellChanged(QString, double);
    // void indicatorLastChanged(QString, double);
    // void indicatorBuyChanged(QString, double);
    // void indicatorVolumeChanged(QString, double);
    
    void debug_message(QString, double);
    /* ket noi giua menucell toi main window display ui */
    void currencyMenuChanged(int);

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
