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
    int getCurrentIndex();
    void setCurrentIndex(const int);
    void currencySelect(const int); /* This func support currencymenu cell get index via event mousePressEvent */
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
    void showEvent(QShowEvent*); /* This event handler can be reimplemented in a subclass to receive widget show events which are passed in the event parameter. */
    void currencyResize();
//    void mouseReleaseEvent(QMouseEvent*); /* This event handler, for event event, can be reimplemented in a subclass to receive mouse release events for the widget. */
};
#endif // CURRENCYMENU_H
