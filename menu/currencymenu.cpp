#include <QScreen>
#include <QToolButton>
#include <QScrollBar>
#include "currencymenucell.h"
#include "currencymenu.h"
#include "ui_currencymenu.h"
#include <QDebug>

CurrencyMenu::CurrencyMenu(QToolButton * _parentButton):
    QMenu(),
    ui(new Ui::CurrencyMenu),
    parentButton(_parentButton),
    currentIndex(0),
    setCurrencyVisible(false)
{
    ui->setupUi(this);
    parentButton->setMenu(this);
    ui->filterWidget->setFixedHeight(ui->filterWidget->minimumSizeHint().height());
}

CurrencyMenu::~CurrencyMenu()
{
    delete ui;
}
/* filterLinex_textChanged slot */
void CurrencyMenu::on_filterLine_textChanged(QString filter)
{
    #if 1
    if (currencyPairs.size() != ui->currencyLayout->count())
        return;

    filter = filter.toUpper();
    qDebug() << filter;
    setCurrencyVisible = false;
    bool bufferVisible;
    ui->scrollArea->hide();

    for (int i = 0; i < currencyPairs.size(); ++i)
    {
        bufferVisible = currencyPairs.at(i).contains(filter);
        ui->currencyLayout->itemAt(i)->widget()->setVisible(bufferVisible);

        if (bufferVisible && !setCurrencyVisible)
            setCurrencyVisible = true;
    }

    currencyResize();
    #endif
}

/* khi usr nhap ticker input on_filterLine_textChanged slot thi se hien ra danh sach coin */
void CurrencyMenu::currencyResize()
{
    #if 1
    QPoint pos = parentButton->mapToGlobal(QPoint(0, 0));
    int width = ui->currencyLayout->minimumSize().width();
    int height = 0;
    int maxHeight = ui->scrollAreaWidgetContents->minimumSizeHint().height() + ui->filterWidget->height() + 2;

    for (QScreen* screen : QGuiApplication::screens())
    {
        QRect screenRect = screen->geometry();

        if (screenRect.contains(pos))
        {
            height = screenRect.bottom() - pos.y() - parentButton->height() - 10;
        }
    }

    if (height > maxHeight)
    {
        height = maxHeight;
        ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }
    else
    {
        ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        width += ui->scrollArea->verticalScrollBar()->width();
    }

    if (width < 58)
        width = 58;

    if (height < 28)
        height = 28;

    setFixedSize(width, height);

    if (setCurrencyVisible)
    {
        ui->scrollArea->show();
    }
    #endif
}

void CurrencyMenu::setPairs(const QStringList& newCurrencyPairs)
{
    if (newCurrencyPairs.isEmpty())
        return;

    currentIndex = 0;
    currencyPairs = newCurrencyPairs;

    displayPairs();
}

void CurrencyMenu::displayPairs()
{
    QPalette palette;
    QString highlight       = palette.color(QPalette::Highlight).name();
    QString highlightedText = palette.color(QPalette::HighlightedText).name();
    QString currencyStyle = "QWidget:hover{background-color:" + highlight + ";color:" + highlightedText + "}";

    for (int i = 0; i < currencyPairs.size(); ++i)
    {
        ui->currencyLayout->addWidget(new CurrencyMenuCell(currencyPairs.at(i), currencyStyle, i, this));
    }
}
//setCurrentIndex dc goi khi 1 cell chua coin dc chon
//when setCurrenInex is call > currencyMenuChanged > and connect to main window
void CurrencyMenu::setCurrentIndex(const int newCurrentIndex)
{
    if (newCurrentIndex < 0 || newCurrentIndex > currencyPairs.size())
        return;

    currentIndex = newCurrentIndex;
    parentButton->setText(currencyPairs.at(currentIndex));
    parentButton->setFixedWidth(parentButton->minimumSizeHint().width());
    qDebug() << "emit currencyMenuChanged(currentIndex):" << currentIndex << currencyPairs.at(currentIndex)<<"...";
    emit currencyMenuChanged(currentIndex);
}
/* Tu dong Resize scrollArea luc khoi tao */
void CurrencyMenu::showEvent(QShowEvent*)
{
    currencyResize();
}


void CurrencyMenu::currencySelect(const int newCurrentIndex)
{
    setCurrentIndex(newCurrentIndex);
    hide();
}
int CurrencyMenu::getCurrentIndex()
{
    return currentIndex;
}