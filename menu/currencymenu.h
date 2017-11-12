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
    void setPairs(const QStringList&);
    //int count();
    //int getCurrentIndex();
    void setCurrentIndex(const int);
    //void currencySelect(const int);
signals:
    void currencyMenuChanged(int);

private slots:
    void on_filterLine_textChanged(QString);

private:
    Ui::CurrencyMenu* ui;
    QToolButton* parentButton;
    QStringList currencyPairs;
    int currentIndex;
    bool setCurrencyVisible;
    void displayPairs();
    // void showEvent(QShowEvent*);
    void currencyResize();
    //void mouseReleaseEvent(QMouseEvent*);
};
#endif // CURRENCYMENU_H
