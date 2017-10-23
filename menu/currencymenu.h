#ifndef CURRENCYMENU_H
#define CURRENCYMENU_H

#include <QMenu>

//The QToolButton class provides a quick-access button to commands or options, usually used inside a QToolBar.
class QToolButton;

namespace Ui
{
    class CurrencyMenu;
}

class CurrencyMenu : public QMenu
{
    Q_OBJECT
public:
    explicit CurrencyMenu(QToolButton*);
    ~CurrencyMenu();
signals:

private slots:

private:
    Ui::CurrencyMenu* ui;
};
#endif // CURRENCYMENU_H
