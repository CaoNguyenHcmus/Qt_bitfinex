#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ui_widget.h"
#include <QDebug>

namespace Ui {
class Widget;
}

class Widget : public QWidget, public Ui::Widget
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

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
