#include "currencymenu.h"
#include "ui_currencymenu.h"


CurrencyMenu::CurrencyMenu(QToolButton * _parentButton):
    QMenu(),
    ui(new Ui::CurrencyMenu)
//    parentButton(_parentButton)
//    currentIndex(0),
//    setCurrencyVisible(false)
{
    ui->setupUi(this);
    //parentButton->setMenu(this);
    //ui->filterWidget->setFixedHeight(ui->filterWidget->minimumSizeHint().height());
}

CurrencyMenu::~CurrencyMenu()
{
    delete ui;
}
