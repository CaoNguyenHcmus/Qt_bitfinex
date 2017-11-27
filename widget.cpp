#include "widget.h"

#if 1   //for bitfinex API
#include <iostream>
#include <fstream>
#include <time.h>
#include <errno.h>
#include "BitfinexAPI.hpp"
#include <QByteArray>

#include <QDebug>

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

#include <QMessageBox>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
#endif

#include "main.h"
#include "exchange.h"
#include "exchange_bitfinex.h"
#include "menu/currencymenu.h"

#include "iniengine.h" /* setCurrencyPairsList constructor */

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    setupUi(this);

    QRegExp regExp("([0-9]*[.])?[0-9]+");
    amountEdit->setValidator(new QRegExpValidator(regExp, this));
    priceEdit->setValidator(new QRegExpValidator(regExp, this)); //this->ui->priceEdit

    connect(getButton, SIGNAL(clicked()), this, SLOT(get_data())); //ham get_data nen dat trong public slots:
    //connect(this->ui->exitButton, SIGNAL(clicked()), this, SLOT(reject())); //unknow issue here
    //OK
//    connect(this->ui->exitButton, SIGNAL(clicked()), this, SLOT(setValue())); //Click button-> emit
//    connect(this, SIGNAL(valueChanged(double)), this->ui->marketBid, SLOT(setValue(double)));
    connect(this, SIGNAL(valueChanged(double)), marketBid, SLOT(setValue(double)));
#if 1
    currencyMenu = new CurrencyMenu(currencyMenuTool);
    // QStringList currencyItems;
    // currencyItems << "BTC/USD [exchange]";
    //currencyMenu->setPairs(currencyItems);

    /**/
    //int indexCurrency = 0;
    //when setCurrenInex is call > currencyMenuChanged > and connect to main window
    //Is also call when 1 cell cointain coin is clicked()
    //currencyMenu->setCurrentIndex(indexCurrency); /* just demo: move to setCurrencyPairsList*/
    //ket noi giua
    connect(currencyMenu, &CurrencyMenu::currencyMenuChanged, this, &Widget::currencyMenuChanged);
#endif

    symbols =
    {
        "btcusd",
        "ltcusd",
        "ethusd",
        "etcusd",
        "zecusd",
        "xmrusd",
        "iotusd",
        "eosusd",
        "bchusd",
        "omgusd"
    };

    for(int i = 0; i < symbols.size(); i++){
//        qDebug()<< "DEBUG: i= " << i << "value :"<< symbols[i] <<"\n" ;
        currencyMenuCombo->addItem(symbols[i]);
    }
}

Widget::~Widget()
{
    #if 0
    delete ui;
    #endif
}

void Widget::get_data()
{

    //okButton->setEnabled(lineEdit->hasAcceptableInput());
    qDebug()<< "debug: get_data...";
    const char *keyFilePath = "key.md";
    ifstream ifs(keyFilePath);
    if (!ifs.is_open())
    {
//        cout << "Can't open file: " << argv[1] << endl;
        cout << "Can't open file: " << endl;
        //qDebug << "Can't open file: " << keyFilePath << endl;
      //return -1;
    }
    else
    {
        string accessKey, secretKey;
        getline(ifs, accessKey);
        getline(ifs, secretKey);

        qDebug()<< "Finish get key...";
        BitfinexAPI bfxAPI(accessKey, secretKey);
        string response;
        int errCode;

        /////////////////////////////////////////////////////////////////////////
        //  Examples
        //  Note that default values are not mandatory. See BitfinexAPI.hpp
        //  for details.
        /////////////////////////////////////////////////////////////////////////

        ///  Public endpoints ///
        qDebug()<< "Begin getTicker...";
          //errCode = bfxAPI.getTicker(response, "btcusd");
#if 1 /*TODO: will make a function later */
        QString QStringTicker = currencyMenuCombo->currentText();
        //qDebug()<< "DEBUG get: " << QStringTicker <<"\n" ;
        //std::cout << "DEBUG get: " << QStringTicker.toLocal8Bit().constData() <<"\n" ; //https://stackoverflow.com/questions/4214369/how-to-convert-qstring-to-stdstring
        std::string ticker = QStringTicker.toLocal8Bit().constData();
        if(ticker == "None"){ //Check error
            QMessageBox msgBox;
            //qDebug()<< "debug: please set input_amount";
            msgBox.setText("please set ticker");
            msgBox.exec();
            return; //exit a function
        }
#endif /*TODO: will make a function later */
        errCode = bfxAPI.getTicker(response, ticker);
        qDebug()<< "Finish getTicker...";
        //  errCode = bfxAPI.getStats(response, "btcusd");
        //  errCode = bfxAPI.getFundingBook(response, "USD", 50, 50);
        //  errCode = bfxAPI.getOrderBook(response, "btcusd", 50, 50, 1);
        //  errCode = bfxAPI.getTrades(response, "btcusd", 0L, 50);
        //  errCode = bfxAPI.getLends(response, "USD", 0L, 50);
        //  errCode = bfxAPI.getSymbols(response);
        //  errCode = bfxAPI.getSymbolDetails(response);

        /// Authenticated endpoints ///

        //  Account  //
        //  errCode = bfxAPI.getAccountInfo(response);
        //  errCode = bfxAPI.getSummary(response);
        //  errCode = bfxAPI.deposit(response, "bitcoin", "deposit", 1);
        //  errCode = bfxAPI.getKeyPermissions(response);
        //  errCode = bfxAPI.getMarginInfos(response);
        //  errCode = bfxAPI.getBalances(response);
        //  errCode = bfxAPI.transfer(response, 0.1, "BTC", "trading", "deposit");
        //  errCode = bfxAPI.withdraw(response); // configure withdraw.conf file before use
        //
        //  Orders  //
        //  errCode = bfxAPI.newOrder(response, "btcusd", 0.01, 983, "sell", "exchange limit", 0, 1,
        //                           0, 0, 0);
        //
        //  How to create vOrders object for newOrders() call
        //  BitfinexAPI::vOrders orders =
        //  {
        //      {"btcusd", 0.1, 950, "sell", "exchange limit"},
        //      {"btcusd", 0.1, 950, "sell", "exchange limit"},
        //      {"btcusd", 0.1, 950, "sell", "exchange limit"}
        //  };
        //  errCode = bfxAPI.newOrders(response, orders);
        //
        //  errCode = bfxAPI.cancelOrder(response, 13265453586LL);
        //
        //  How to create ids object for cancelOrders() call
        //  BitfinexAPI::vIds ids =
        //  {
        //      12324589754LL,
        //      12356754322LL,
        //      12354996754LL
        //  };
        //  errCode = bfxAPI.cancelOrders(response, ids);
        //
        //  errCode = bfxAPI.cancelAllOrders(response);
        //  errCode = bfxAPI.replaceOrder(response, 1321548521LL, "btcusd", 0.05, 1212, "sell",
        //                                "exchange limit", 0, 0);
        //  errCode = bfxAPI.getOrderStatus(response, 12113548453LL);
        //  errCode = bfxAPI.getActiveOrders(response);
        //
        //  Positions  //
        //  errCode = bfxAPI.getActivePositions(response);
        //  errCode = bfxAPI.claimPosition(response, 156321412LL, 150);
        //
        //  Historical data  //
        //  errCode = bfxAPI.getBalanceHistory(response, "USD", 0L, 0L, 500, "all");
        //  errCode = bfxAPI.getDWHistory(response, "BTC", "all", 0L , 0L, 500);
        //  errCode = bfxAPI.getPastTrades(response, "btcusd", 0L, 0L, 500, 0);
        //
        //  Margin funding  //
        //  errCode = bfxAPI.newOffer(response, "USD", 12000, 25.2, 30, "lend");
        //  errCode = bfxAPI.cancelOffer(response, 12354245628LL);
        //  errCode = bfxAPI.getOfferStatus(response, 12313541215LL);
        //  errCode = bfxAPI.getActiveCredits(response);
        //  errCode = bfxAPI.getOffers(response);
        //  errCode = bfxAPI.getTakenFunds(response);
        //  errCode = bfxAPI.getUnusedTakenFunds(response);
        //  errCode = bfxAPI.getTotalTakenFunds(response);
        //  errCode = bfxAPI.closeLoan(response, 1235845634LL);

        /////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////

        cout << "Response: " << response << endl;
        cout << "Error code: " << errCode << endl;

        ////////////////

        //Convert
        QString json_string = QString::fromStdString(response);
        qDebug() << json_string;

        QByteArray json_bytes = json_string.toLocal8Bit();

        auto json_doc=QJsonDocument::fromJson(json_bytes);

        if(json_doc.isNull()){
            qDebug()<<"Failed to create JSON doc.";
            exit(2);
        }
        if(!json_doc.isObject()){
            qDebug()<<"JSON is not an object.";
            exit(3);
        }

        QJsonObject json_obj=json_doc.object();

        if(json_obj.isEmpty()){
            qDebug()<<"JSON object is empty.";
            exit(4);
        }

        //----
        QVariantMap json_map = json_obj.toVariantMap();
        qDebug()<< json_map["mid"].toDouble();
        qDebug()<< json_map["bid"].toFloat();
        qDebug()<< json_map["volume"].toDouble();
        qDebug()<< json_map["timestamp"].toFloat();

        ifs.close();
        // function here
        //marketBid->setValue(1);
        //emit valueChanged(10);
        //marketBid->setValue(20.f);
        //setValue(10);
        //connect(this, SIGNAL(valueChanged(double)), marketBid, SLOT(valueChanged(double)));
        double value = json_map["mid"].toDouble();
        cout << "value" << value << endl;
        emit valueChanged(value);
    }
}
void Widget::setValue()
{       int value = 10.f;
        cout << "value" << value << endl;
        emit valueChanged(value);
}

void Widget::on_buyButton_clicked()
{
    QString input_amount, input_price;
    QMessageBox msgBox;
    qDebug()<< "debug: on_buyButton_clicked()";
    cout << "debug: lineEdit\n";
    if(amountEdit->text().isEmpty() == true)
    {
        qDebug()<< "debug: please set input_amount";
        msgBox.setText("please set input_amount");
        msgBox.exec();
        return; //exit a function
    } else{
        input_amount = amountEdit->text();
        qDebug()<< "debug: input_amount: " << input_amount;
    }
    
    if(priceEdit->text().isEmpty() == true)
    {
        qDebug()<< "debug: please set input_price";
        msgBox.setText("please set input_price");
        msgBox.exec();
        return; //exit a function
    } else{
        input_price = priceEdit->text();
        qDebug()<< "debug: input_price: " << input_price;
    }
#if 1
    std::string order_types;
    if (margincheckBox->isChecked()) {
        order_types = "limit";
        std::cout<< "WARNING: using margin..." << order_types << "\n";
    } else {
        order_types = "exchange limit";
        std::cout<< "Using normal trading... "<< order_types <<"\n";
    }
#endif 
    const char *keyFilePath = "key.md";
    ifstream ifs(keyFilePath);
    if (!ifs.is_open())
    {
        cout << "Can't open file: " << endl;
    }
    else
    {
        string accessKey, secretKey;
        getline(ifs, accessKey);
        getline(ifs, secretKey);

        qDebug()<< "Finish get key...";
        BitfinexAPI bfxAPI(accessKey, secretKey);
        string response;
        int errCode;
        //  Orders  //
        qDebug()<< "Begin Orders...";
#if 1 /*TODO: will make a function later */
        QString QStringTicker = currencyMenuCombo->currentText();
        //qDebug()<< "DEBUG get: " << QStringTicker <<"\n" ;
        //std::cout << "DEBUG get: " << QStringTicker.toLocal8Bit().constData() <<"\n" ; //https://stackoverflow.com/questions/4214369/how-to-convert-qstring-to-stdstring
        std::string ticker = QStringTicker.toLocal8Bit().constData();
        if(ticker == "None"){ //Check error
            QMessageBox msgBox;
            //qDebug()<< "debug: please set input_amount";
            msgBox.setText("please set ticker");
            msgBox.exec();
            return; //exit a function
        }
#endif /*TODO: will make a function later */
        #if 0
        newOrder(string &result, const string &symbol, const double &amount,
                 const double &price, const string &side, const string &type,
                 const bool &is_hidden, const bool &is_postonly,
                 const bool &use_all_available, const bool &ocoorder,
                 const double &buy_price_oco)
        #endif
        
        //qDebug()<< "amount: " << input_amount << "price: " << input_price;
        errCode = bfxAPI.newOrder(response, ticker, input_amount.toFloat(), input_price.toFloat(), "buy", order_types, 0, 1, 0, 0, 0);
        //
        //  How to create vOrders object for newOrders() call
        //  BitfinexAPI::vOrders orders =
        //  {
        //      {"btcusd", 0.1, 950, "sell", "exchange limit"},
        //      {"btcusd", 0.1, 950, "sell", "exchange limit"},
        //      {"btcusd", 0.1, 950, "sell", "exchange limit"}
        //  };
        //  errCode = bfxAPI.newOrders(response, orders);
        //
        //  errCode = bfxAPI.cancelOrder(response, 13265453586LL);
        //
        //  How to create ids object for cancelOrders() call
        //  BitfinexAPI::vIds ids =
        //  {
        //      12324589754LL,
        //      12356754322LL,
        //      12354996754LL
        //  };
        //  errCode = bfxAPI.cancelOrders(response, ids);
        //
        //  errCode = bfxAPI.cancelAllOrders(response);
        //  errCode = bfxAPI.replaceOrder(response, 1321548521LL, "btcusd", 0.05, 1212, "sell",
        //                                "exchange limit", 0, 0);
        //  errCode = bfxAPI.getOrderStatus(response, 12113548453LL);
        //  errCode = bfxAPI.getActiveOrders(response);
        //

        /////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////

        cout << "Response: " << response << endl;
        cout << "Error code: " << errCode << endl;

        ////////////////
#if 0
        //Convert
        QString json_string = QString::fromStdString(response);
        qDebug() << json_string;

        QByteArray json_bytes = json_string.toLocal8Bit();

        auto json_doc=QJsonDocument::fromJson(json_bytes);

        if(json_doc.isNull()){
            qDebug()<<"Failed to create JSON doc.";
            exit(2);
        }
        if(!json_doc.isObject()){
            qDebug()<<"JSON is not an object.";
            exit(3);
        }

        QJsonObject json_obj=json_doc.object();

        if(json_obj.isEmpty()){
            qDebug()<<"JSON object is empty.";
            exit(4);
        }

        //----
        QVariantMap json_map = json_obj.toVariantMap();
        qDebug()<< json_map["mid"].toDouble();
        qDebug()<< json_map["bid"].toFloat();
        qDebug()<< json_map["volume"].toDouble();
        qDebug()<< json_map["timestamp"].toFloat();


        // function here
        //marketBid->setValue(1);
        //emit valueChanged(10);
        //marketBid->setValue(20.f);
        //setValue(10);
        //connect(this, SIGNAL(valueChanged(double)), marketBid, SLOT(valueChanged(double)));
        double value = json_map["mid"].toDouble();
        cout << "value" << value << endl;
        emit valueChanged(value);
 #endif
        ifs.close();
    }
}
void Widget::on_sellButton_clicked()
{
    QString input_amount, input_price;
    QMessageBox msgBox;
    qDebug()<< "debug: on_buyButton_clicked()";
    cout << "debug: lineEdit\n";
    if(amountEdit->text().isEmpty() == true)
    {
        qDebug()<< "debug: please set input_amount";
        msgBox.setText("please set input_amount");
        msgBox.exec();
        return; //exit a function
    } else{
        input_amount = amountEdit->text();
        qDebug()<< "debug: input_amount: " << input_amount;
    }

    if(priceEdit->text().isEmpty() == true)
    {
        qDebug()<< "debug: please set input_price";
        msgBox.setText("please set input_price");
        msgBox.exec();
        return; //exit a function
    } else{
        input_price = priceEdit->text();
        qDebug()<< "debug: input_price: " << input_price;
    }
#if 1
    std::string order_types;
    if (margincheckBox->isChecked()) {
        order_types = "limit";
        std::cout<< "WARNING: using margin..." << order_types << "\n";
    } else {
        order_types = "exchange limit";
        std::cout<< "Using normal trading... "<< order_types <<"\n";
    }
#endif 
    const char *keyFilePath = "key.md";
    ifstream ifs(keyFilePath);
    if (!ifs.is_open())
    {
        cout << "Can't open file: " << endl;
    }
    else
    {
        string accessKey, secretKey;
        getline(ifs, accessKey);
        getline(ifs, secretKey);

        qDebug()<< "Finish get key...";
        BitfinexAPI bfxAPI(accessKey, secretKey);
        string response;
        int errCode;
        //  Orders  //
        qDebug()<< "Begin Orders...";
#if 1 /*TODO: will make a function later */
        QString QStringTicker = currencyMenuCombo->currentText();
        //qDebug()<< "DEBUG get: " << QStringTicker <<"\n" ;
        //std::cout << "DEBUG get: " << QStringTicker.toLocal8Bit().constData() <<"\n" ; //https://stackoverflow.com/questions/4214369/how-to-convert-qstring-to-stdstring
        std::string ticker = QStringTicker.toLocal8Bit().constData();
        if(ticker == "None"){ //Check error
            QMessageBox msgBox;
            //qDebug()<< "debug: please set input_amount";
            msgBox.setText("please set ticker");
            msgBox.exec();
            return; //exit a function
        }
#endif /*TODO: will make a function later */
        //qDebug()<< "amount: " << input_amount << "price: " << input_price;
        errCode = bfxAPI.newOrder(response, ticker, input_amount.toFloat(), input_price.toFloat(), "sell", order_types, 0, 1, 0, 0, 0);
        //
        //  How to create vOrders object for newOrders() call
        //  BitfinexAPI::vOrders orders =
        //  {
        //      {"btcusd", 0.1, 950, "sell", "exchange limit"},
        //      {"btcusd", 0.1, 950, "sell", "exchange limit"},
        //      {"btcusd", 0.1, 950, "sell", "exchange limit"}
        //  };
        //  errCode = bfxAPI.newOrders(response, orders);
        //
        //  errCode = bfxAPI.cancelOrder(response, 13265453586LL);
        //
        //  How to create ids object for cancelOrders() call
        //  BitfinexAPI::vIds ids =
        //  {
        //      12324589754LL,
        //      12356754322LL,
        //      12354996754LL
        //  };<<
        //  errCode = bfxAPI.cancelOrders(response, ids);
        //
        //  errCode = bfxAPI.cancelAllOrders(response);
        //  errCode = bfxAPI.replaceOrder(response, 1321548521LL, "btcusd", 0.05, 1212, "sell",
        //                                "exchange limit", 0, 0);
        //  errCode = bfxAPI.getOrderStatus(response, 12113548453LL);
        //  errCode = bfxAPI.getActiveOrders(response);
        //

        /////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////

        cout << "Response: " << response << endl;
        cout << "Error code: " << errCode << endl;

        ////////////////
        ifs.close();
    }
}

void Widget::on_pushButton_clicked()
{
    cout << "Check history dev\n";
    qDebug()<< "debug: get_data...";
    
    const char *keyFilePath = "key.md";
    ifstream ifs(keyFilePath);
    if (!ifs.is_open())
    {
//        cout << "Can't open file: " << argv[1] << endl;
        cout << "Can't open file: " << endl;
        //qDebug << "Can't open file: " << keyFilePath << endl;
        //return -1;
    }
    else
    {
        string accessKey, secretKey;
        getline(ifs, accessKey);
        getline(ifs, secretKey);

        qDebug()<< "Finish get key...";
        BitfinexAPI bfxAPI(accessKey, secretKey);
        string response;
        int errCode;

        /////////////////////////////////////////////////////////////////////////
        //  Examples
        //  Note that default values are not mandatory. See BitfinexAPI.hpp
        //  for details.
        /////////////////////////////////////////////////////////////////////////

        ///  Public endpoints ///
        qDebug()<< "Begin Historical data...";
#if 1 /*TODO: will make a function later */
        QString QStringTicker = currencyMenuCombo->currentText();
        //qDebug()<< "DEBUG get: " << QStringTicker <<"\n" ;
        //std::cout << "DEBUG get: " << QStringTicker.toLocal8Bit().constData() <<"\n" ; //https://stackoverflow.com/questions/4214369/how-to-convert-qstring-to-stdstring
        std::string ticker = QStringTicker.toLocal8Bit().constData();
        if(ticker == "None"){ //Check error
            QMessageBox msgBox;
            //qDebug()<< "debug: please set input_amount";
            msgBox.setText("please set ticker");
            msgBox.exec();
            return; //exit a function
        }
#endif /*TODO: will make a function later */
            //errCode = bfxAPI.getTicker(response, "btcusd");
        //errCode = bfxAPI.getTicker(response, "eosusd");
        //qDebug()<< "Finish getTicker...";
        //  errCode = bfxAPI.getStats(response, "btcusd");
        //  errCode = bfxAPI.getFundingBook(response, "USD", 50, 50);
        //  errCode = bfxAPI.getOrderBook(response, "btcusd", 50, 50, 1);
        //  errCode = bfxAPI.getTrades(response, "btcusd", 0L, 50);
        //  errCode = bfxAPI.getLends(response, "USD", 0L, 50);
        //  errCode = bfxAPI.getSymbols(response);
        //  errCode = bfxAPI.getSymbolDetails(response);

        /// Authenticated endpoints ///

        //  Account  //
        //  errCode = bfxAPI.getAccountInfo(response);
        //  errCode = bfxAPI.getSummary(response);
        //  errCode = bfxAPI.deposit(response, "bitcoin", "deposit", 1);
        //  errCode = bfxAPI.getKeyPermissions(response);
        //  errCode = bfxAPI.getMarginInfos(response);
        //  errCode = bfxAPI.getBalances(response);
        //  errCode = bfxAPI.transfer(response, 0.1, "BTC", "trading", "deposit");
        //  errCode = bfxAPI.withdraw(response); // configure withdraw.conf file before use
        //
        //  Orders  //
        //  errCode = bfxAPI.newOrder(response, "btcusd", 0.01, 983, "sell", "exchange limit", 0, 1,
        //                           0, 0, 0);
        //
        //  How to create vOrders object for newOrders() call
        //  BitfinexAPI::vOrders orders =
        //  {
        //      {"btcusd", 0.1, 950, "sell", "exchange limit"},
        //      {"btcusd", 0.1, 950, "sell", "exchange limit"},
        //      {"btcusd", 0.1, 950, "sell", "exchange limit"}
        //  };
        //  errCode = bfxAPI.newOrders(response, orders);
        //
        //  errCode = bfxAPI.cancelOrder(response, 13265453586LL);
        //
        //  How to create ids object for cancelOrders() call
        //  BitfinexAPI::vIds ids =
        //  {
        //      12324589754LL,
        //      12356754322LL,
        //      12354996754LL
        //  };
        //  errCode = bfxAPI.cancelOrders(response, ids);
        //
        //  errCode = bfxAPI.cancelAllOrders(response);
        //  errCode = bfxAPI.replaceOrder(response, 1321548521LL, "btcusd", 0.05, 1212, "sell",
        //                                "exchange limit", 0, 0);
        //  errCode = bfxAPI.getOrderStatus(response, 12113548453LL);
        //  errCode = bfxAPI.getActiveOrders(response);
        //
        //  Positions  //
        //  errCode = bfxAPI.getActivePositions(response);
        //  errCode = bfxAPI.claimPosition(response, 156321412LL, 150);
        //
        //  Historical data  //
        //  errCode = bfxAPI.getBalanceHistory(response, "USD", 0L, 0L, 500, "all");
        //  errCode = bfxAPI.getDWHistory(response, "BTC", "all", 0L , 0L, 500);
        /*
        int BitfinexAPI::
        getPastTrades(string &result, const string &symbol, const time_t &timestamp, const time_t &until, const int &limit_trades, const bool reverse) */
        int limit_trades = 1; //get last trade
        errCode = bfxAPI.getPastTrades(response, ticker, 0L, 0L, limit_trades, 0);
        //
        //  Margin funding  //
        //  errCode = bfxAPI.newOffer(response, "USD", 12000, 25.2, 30, "lend");
        //  errCode = bfxAPI.cancelOffer(response, 12354245628LL);
        //  errCode = bfxAPI.getOfferStatus(response, 12313541215LL);
        //  errCode = bfxAPI.getActiveCredits(response);
        //  errCode = bfxAPI.getOffers(response);
        //  errCode = bfxAPI.getTakenFunds(response);
        //  errCode = bfxAPI.getUnusedTakenFunds(response);
        //  errCode = bfxAPI.getTotalTakenFunds(response);
        //  errCode = bfxAPI.closeLoan(response, 1235845634LL);

        /////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////

        cout << "Response: " << response << endl;
        cout << "Error code: " << errCode << endl;
        ifs.close();
    }
}
//Know how convert QJSonArray from QJSonDocument and query in  QJSonObject via QVariantMap
void Widget::on_queryButton_clicked()
{
    qDebug()<< "debug: on_queryButton_clicked...";

    const char *keyFilePath = "key.md";
    ifstream ifs(keyFilePath);
    if (!ifs.is_open())
    {
//        cout << "Can't open file: " << argv[1] << endl;
        cout << "Can't open file: " << endl;
        //qDebug << "Can't open file: " << keyFilePath << endl;
      //return -1;
    }
    else
    {
        string accessKey, secretKey;
        getline(ifs, accessKey);
        getline(ifs, secretKey);

        qDebug()<< "Finish get key...";
        BitfinexAPI bfxAPI(accessKey, secretKey);
        string response;
        int errCode;

        //  errCode = bfxAPI.cancelOrders(response, ids);
        //
        //  errCode = bfxAPI.cancelAllOrders(response);
        //  errCode = bfxAPI.replaceOrder(response, 1321548521LL, "btcusd", 0.05, 1212, "sell",
        //                                "exchange limit", 0, 0);
        //errCode = bfxAPI.getOrderStatus(response, 12113548453LL);
        errCode = bfxAPI.getActiveOrders(response);

        /////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////

        cout << "Response: " << response << endl;
        cout << "Error code: " << errCode << endl;

        ////////////////
#if 1
        //Convert
        QString json_string = QString::fromStdString(response);
//        qDebug() << json_string;

        QByteArray json_bytes = json_string.toLocal8Bit();

        auto jsonResponse=QJsonDocument::fromJson(json_bytes);
//        QJsonObject jsonObject = jsonResponse.object(); //https://stackoverflow.com/questions/19822211/qt-parsing-json-using-qjsondocument-qjsonobject-qjsonarray
        QJsonArray jsonArray = jsonResponse.array(); //Returns the QJsonArray contained in the document.

        foreach (const QJsonValue & value, jsonArray) {
            QJsonObject json_obj = value.toObject();
            QVariantMap json_map = json_obj.toVariantMap();
            //QStringList orders_list;
#if 0
int replaceOrder(string &result, const long long &order_id, const string &symbol,
                 const double &amount, const double &price, const string &side,
                 const string &type, const bool &is_hidden = 0,
                 const bool &use_remaining = 0);

            QString orders = json_map["id"].toString() + json_map["symbol"].toString() + \
                    json_map["original_amount"].toString() + json_map["price"].toString() + json_map["side"].toString() + \
                    json_map["type"].toString();

            qDebug() << "orders (QString type): "<< orders;
#endif
            qDebug()<< json_map["id"].toString() << json_map["cid_date"].toString() << json_map["symbol"].toString() \
            << json_map["price"].toString() << json_map["side"].toString() << json_map["type"].toString() << json_map["original_amount"].toString();
        }
        //----
#endif
        ifs.close();
    }
}
/* TODO: This function will be implement in algothm trading NOT on a button */
void Widget::on_replaceOrderButton_clicked()
{
    qDebug()<< "debug: on_replaceOrderButton_clicked...";

    const char *keyFilePath = "key.md";
    ifstream ifs(keyFilePath);
    if (!ifs.is_open())
    {
        qDebug() << "Can't open file: " << keyFilePath << endl;
      return;
    }
    else
    {
        string accessKey, secretKey;
        getline(ifs, accessKey);
        getline(ifs, secretKey);

        qDebug()<< "Finish get key...";
        BitfinexAPI bfxAPI(accessKey, secretKey);
        string response;
        int errCode;

        //  errCode = bfxAPI.cancelOrders(response, ids);
        //
        //  errCode = bfxAPI.cancelAllOrders(response);

        #if 0
        int replaceOrder(string &result, const long long &order_id, const string &symbol,
                         const double &amount, const double &price, const string &side,
                         const string &type, const bool &is_hidden = 0,
                         const bool &use_remaining = 0);
        #endif
//        errCode = bfxAPI.replaceOrder(response, 1321548521LL, "btcusd", 0.05, 1212, "sell",
        //                                "exchange limit", 0, 0);
        //errCode = bfxAPI.getOrderStatus(response, 12113548453LL);
        //errCode = bfxAPI.getActiveOrders(response);

        /////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////

        cout << "Response: " << response << endl;
        cout << "Error code: " << errCode << endl;

        ////////////////
#if 0
        //Convert
        QString json_string = QString::fromStdString(response);
//        qDebug() << json_string;

        QByteArray json_bytes = json_string.toLocal8Bit();

        auto jsonResponse=QJsonDocument::fromJson(json_bytes);
//        QJsonObject jsonObject = jsonResponse.object(); //https://stackoverflow.com/questions/19822211/qt-parsing-json-using-qjsondocument-qjsonobject-qjsonarray
        QJsonArray jsonArray = jsonResponse.array(); //Returns the QJsonArray contained in the document.

        foreach (const QJsonValue & value, jsonArray) {
            QJsonObject json_obj = value.toObject();
            QVariantMap json_map = json_obj.toVariantMap();
            qDebug()<< json_map["id"].toString() << json_map["cid_date"].toString() << json_map["symbol"].toString() \
            << json_map["price"].toString() << json_map["side"].toString() << json_map["type"].toString();
        }
#if 0
        if(jsonObject.isNull()){
            qDebug()<<"Failed to create JSON doc.";
            exit(2);
        }
        if(!jsonObject.isObject()){
            qDebug()<<"JSON is not an object.";
//            exit(3);
        }

        QJsonObject json_obj=json_doc.object();

        if(jsonObject.isEmpty()){
            qDebug()<<"JSON object is empty.";
//            exit(4);
        }
#endif
        //----
        //QVariantMap json_map = json_obj.toVariantMap();
        //qDebug()<< json_map["id"].toDouble();
//        qDebug()<< json_map["bid"].toFloat();
//        qDebug()<< json_map["volume"].toDouble();
//        qDebug()<< json_map["timestamp"].toFloat();
#endif
        ifs.close();
#if 0
        // function here
        //marketBid->setValue(1);
        //emit valueChanged(10);
        //marketBid->setValue(20.f);
        //setValue(10);
        //connect(this, SIGNAL(valueChanged(double)), marketBid, SLOT(valueChanged(double)));
        double value = json_map["mid"].toDouble();
        cout << "value" << value << endl;
        emit valueChanged(value);
#endif
    }
}
//this value of spin box get from indicatorengine emit. here is slot
void Widget::indicatorHighChanged(QString symbol, double val)
{
    if (baseValues.currentPair.symbolSecond().startsWith(symbol, Qt::CaseInsensitive)){
        //setSpinValue(marketHigh, val);
        marketHigh->setValue(IndicatorEngine::getValue(baseValues.exchangeName +'_' + baseValues.currentPair.symbol + "_High"));
        //setSpinValue(marketHigh, 0.0);
        //setSpinValue(ui.marketHigh, IndicatorEngine::getValue(baseValues.exchangeName +'_' + baseValues.currentPair.symbol + "_High"));
        qDebug() << "Send data to spinbox marketHigh>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
    }
}

void Widget::indicatorLowChanged(QString symbol, double val)
{
    if (baseValues.currentPair.symbolSecond().startsWith(symbol, Qt::CaseInsensitive)){
        marketLow->setValue(IndicatorEngine::getValue(baseValues.exchangeName +'_' + baseValues.currentPair.symbol + "_Low"));
        qDebug() << "Send data to spinbox marketLow>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
        //setSpinValue(ui.marketLow, val);
    }
}

void Widget::indicatorBuyChanged(QString symbol, double val)
{
    if (baseValues.currentPair.symbolSecond().startsWith(symbol, Qt::CaseInsensitive))
    {
        /*
        if (val == 0.0)
            val = ui.marketLast->value();

        if (val == 0.0)
            val = ui.marketBid->value();

        if (ui.marketAsk->value() == 0.0 && val > 0.0)
            ui.buyPricePerCoin->setValue(val);

        setSpinValue(ui.marketAsk, val);
        */
        marketAsk->setValue(IndicatorEngine::getValue(baseValues.exchangeName +'_' + baseValues.currentPair.symbol + "_Buy"));
    }
}

void Widget::indicatorSellChanged(QString symbol, double val)
{
    qDebug() << "Send data to spinbox marketBid>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
    if (baseValues.currentPair.symbolSecond().startsWith(symbol, Qt::CaseInsensitive))
    {
        // if (val == 0.0)
        //     val = ui.marketLast->value();

        // if (val == 0.0)
        //     val = ui.marketAsk->value();

        // if (ui.marketBid->value() == 0.0 && val > 0.0)
        //     ui.sellPricePerCoin->setValue(val);
        //setSpinValue(ui.marketBid, val);
        marketBid->setValue(IndicatorEngine::getValue(baseValues.exchangeName + '_' + baseValues.currentPair.symbol + "_Sell"));
    }
}

void Widget::indicatorLastChanged(QString symbol, double val)
{
    if (baseValues.currentPair.symbolSecond().startsWith(symbol, Qt::CaseInsensitive))
    {
        marketLast->setValue(IndicatorEngine::getValue(baseValues.exchangeName + '_' + baseValues.currentPair.symbol + "_Last"));
        //setSpinValue(ui.marketLast, val);
    }
}

void Widget::indicatorVolumeChanged(QString symbol, double val)
{
    if (baseValues.currentPair.symbolSecond().startsWith(symbol, Qt::CaseInsensitive))
    {
        marketVolume->setValue(IndicatorEngine::getValue(baseValues.exchangeName + '_' + baseValues.currentPair.symbol + "_Volume"));
        //setSpinValue(ui.marketVolume, val);
    }
}

void Widget::debug_message(QString symbol, double value)
{
    qDebug() << "emit indicatorHighChanged(symbol, value) receive....";
}
//init will call setCurrencyPairsList() after that user click to pair list will call to currencyMenuChanged
void Widget::setCurrencyPairsList()
{
    qDebug() << "setCurrencyPairsList: IniEngine::getPairsCount(): " << IniEngine::getPairsCount() <<"....";
    baseValues.currencyPairMap.clear();
    //QString savedCurrency = iniSettings->value("Profile/Currency", "BTC/USD").toString(); /* We don't save setting now */
    int indexCurrency = 0;
    QStringList currencyItems;
    
    for (int n = 0; n < IniEngine::getPairsCount(); n++)
    {   
        CurrencyPairItem pairItem = IniEngine::getPairs()->at(n);
        
        if (pairItem.currRequestSecond.isEmpty())
            baseValues.currencyPairMap[pairItem.symbol] = pairItem;
        else
        {
            baseValues.currencyPairMap[pairItem.symbol + pairItem.currRequestSecond.toUpper()] = pairItem;

            if (pairItem.currRequestSecond == "exchange")
                baseValues.currencyPairMap[pairItem.symbol] = pairItem;
        }
        #if 0
        if (pairItem.name == savedCurrency)
            indexCurrency = n;
        #endif
        currencyItems << pairItem.name;
        qDebug() << "setCurrencyPairsList count: " << n << "\tcurrencyItems: " << currencyItems ;    
    }
    #if 1
    //when setCurrenInex is call > currencyMenuChanged > and connect to main window
    //Is also call when 1 cell cointain coin is clicked()
    //currencyItems << "BTC/USD [exchange]";
    currencyMenu->setPairs(currencyItems);
    currencyMenu->setCurrentIndex(indexCurrency);
    #endif
    #if 0
    ui.filterOrdersCurrency->clear();
    ui.filterOrdersCurrency->insertItems(0, currencyItems);
    ui.filterOrdersCurrency->setCurrentIndex(0);
    #endif
}
// Important function to change UI get value when we choose a cell cointain pair
void Widget::currencyMenuChanged(int val)
{
    qDebug() << "0000000000000000000000 main window: 0000000000000000000000" << val;
    #if 0
    if (!constructorFinished || val < 0 || IniEngine::getPairsCount() != currencyMenu->count())
        return;

    /*bool fastChange = ui.currencyComboBox->itemText(val).left(5) ==
                      ui.currencyComboBox->itemText(lastLoadedCurrency).left(5);
    if (val == lastLoadedCurrency)
        return;
    */
    #endif
    //lastLoadedCurrency = val;
    
    CurrencyPairItem nextCurrencyPair = IniEngine::getPairs()->at(val);
    //bool currencyAChanged = nextCurrencyPair.currAStr != baseValues.currentPair.currAStr;
    //bool currencyBChanged = nextCurrencyPair.currBStr != baseValues.currentPair.currBStr;
    #if 0
    /*if (fastChange)
    {
        baseValues.currentPair = nextCurrencyPair;

        setSpinValue(ui.accountBTC, 0.0);
        setSpinValue(ui.accountUSD, 0.0);

        Q_FOREACH (RuleWidget* currentGroup, ui.tabRules->findChildren<RuleWidget*>())
            currentGroup->currencyChanged();

        Q_FOREACH (ScriptWidget* currentGroup, ui.tabRules->findChildren<ScriptWidget*>())
            currentGroup->currencyChanged();

        return;
    }*/

    fillAllUsdLabels(this, nextCurrencyPair.currBStr);
    fillAllBtcLabels(this, nextCurrencyPair.currAStr);

    // TODO: ?? fillAll Usd/Btc for float

    iniSettings->setValue("Profile/Currency", ui.currencyMenuTool->text());

    if (currencyAChanged)
        setSpinValue(ui.accountBTC, 0.0);

    if (currencyBChanged)
        setSpinValue(ui.accountUSD, 0.0);

    ui.buyTotalSpend->setValue(0.0);
    ui.sellTotalBtc->setValue(0.0);
    ui.tradesVolume5m->setValue(0.0);
    setSpinValue(ui.ruleAmountToReceiveValue, 0.0);
    setSpinValue(ui.ruleTotalToBuyValue, 0.0);
    setSpinValue(ui.ruleAmountToReceiveBSValue, 0.0);
    setSpinValue(ui.ruleTotalToBuyBSValue, 0.0);

    precentBidsChanged(0.0);
    tradesModel->clear();
    tradesPrecentLast = 0.0;

    QString buyGroupboxText = julyTr("GROUPBOX_BUY", "Buy %1");
    bool buyGroupboxCase = false;

    if (buyGroupboxText.length() > 2)
        buyGroupboxCase = buyGroupboxText.at(2).isUpper();

    if (buyGroupboxCase)
        buyGroupboxText = buyGroupboxText.arg(nextCurrencyPair.currAName.toUpper());
    else
        buyGroupboxText = buyGroupboxText.arg(nextCurrencyPair.currAName);

    ui.widgetBuy->parentWidget()->setWindowTitle(buyGroupboxText);

    QString sellGroupboxText = julyTr("GROUPBOX_SELL", "Sell %1");
    bool sellGroupboxCase = true;

    if (sellGroupboxText.length() > 2)
        sellGroupboxCase = sellGroupboxText.at(2).isUpper();

    if (sellGroupboxCase)
        sellGroupboxText = sellGroupboxText.arg(nextCurrencyPair.currAName.toUpper());
    else
        sellGroupboxText = sellGroupboxText.arg(nextCurrencyPair.currAName);

    ui.widgetSell->parentWidget()->setWindowTitle(sellGroupboxText);

    if (currentExchange->clearHistoryOnCurrencyChanged)
    {
        historyModel->clear();

        setSpinValue(ui.ordersLastBuyPrice, 0.0);
        setSpinValue(ui.ordersLastSellPrice, 0.0);
    }

    static int firstLoad = 0;

    if (firstLoad++ > 1)
    {
        firstLoad = 3;
        emit clearValues();
    }

    clearDepth();

    marketPricesNotLoaded = true;
    balanceNotLoaded = true;
    fixDecimals(this);

    iniSettings->sync();
    #endif
    baseValues.currentPair = nextCurrencyPair;
    qDebug() << "baseValues.currentPair.symbol: " << baseValues.currentPair.symbol ;
    #if 0
    depthAsksModel->fixTitleWidths();
    depthBidsModel->fixTitleWidths();

    calcOrdersTotalValues();

    ui.filterOrdersCurrency->setCurrentIndex(val);

    currencyChangedDate = TimeSync::getTimeT();

    setSpinValue(ui.ordersLastBuyPrice, 0.0);
    setSpinValue(ui.ordersLastSellPrice, 0.0);

    fixDecimals(this);

    emit getHistory(true);
    emit clearCharts();
    chartsView->clearCharts();

    setSpinValue(ui.marketHigh, IndicatorEngine::getValue(baseValues.exchangeName +
                 '_' + baseValues.currentPair.symbol + "_High"));
    setSpinValue(ui.marketLow, IndicatorEngine::getValue(baseValues.exchangeName +
                 '_' + baseValues.currentPair.symbol + "_Low"));
    setSpinValue(ui.marketLast, IndicatorEngine::getValue(baseValues.exchangeName +
                 '_' + baseValues.currentPair.symbol + "_Last"));
    setSpinValue(ui.marketVolume, IndicatorEngine::getValue(baseValues.exchangeName +
                 '_' + baseValues.currentPair.symbol + "_Volume"));
    setSpinValue(ui.marketAsk, IndicatorEngine::getValue(baseValues.exchangeName +
                 '_' + baseValues.currentPair.symbol + "_Buy"));
    setSpinValue(ui.marketBid, IndicatorEngine::getValue(baseValues.exchangeName +
                 '_' + baseValues.currentPair.symbol + "_Sell"));

    if (ui.marketAsk->value())
        ui.buyPricePerCoin->setValue(ui.marketAsk->value());
    else
        ui.buyPricePerCoin->setValue(100.0);

    if (ui.marketBid->value())
        ui.sellPricePerCoin->setValue(ui.marketBid->value());
    else
        ui.sellPricePerCoin->setValue(200.0);
    #endif
}

void Widget::setupClass()
{
    qDebug() << "TRACE: " << __func__ <<"()...";
#if 1 /* Dev WebSocket from Qt bitcoin trader */
    baseValues.restSign;    /* = NULL: Segmentation fault (core dumped)*/
    baseValues.restKey;    /* = NULL: Segmentation fault (core dumped)*/
 //    currentExchange = new Exchange_Bitfinex(baseValues.restSign, baseValues.restKey);
     currentExchange = new Exchange_Bitfinex();
     currentExchange->setupApi(this, false);
    /* Issues: setupApi run too slow. Should be wait here */
#if 1 /*https://stackoverflow.com/questions/28192668/qt-wait-for-some-time-in-a-function-without-hanging-the-ui?noredirect=1&lq=1*/
    QEventLoop loop;
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    timer.start(1000);
    loop.exec();
#endif
     qDebug() << "currentExchange->setupApi(this, false) done and begining setCurrencyPairsList...............";
     setCurrencyPairsList(); /* TODO */
#if 0
     {
        QEventLoop waitStarted;
        connect(currentExchange, &Exchange::started, &waitStarted, &QEventLoop::quit);
        currentExchangeThread->start();
        waitStarted.exec();
    }
#endif
     currencyMenuChanged(currencyMenu->getCurrentIndex());

     //currentExchange->secondSlot();
     /* Starting thread to get data from web */
     currentExchange->start();
 #endif
    #if 0
    currentExchangeThread.reset(new QThread);
    currentExchange->moveToThread(currentExchangeThread.data());
    connect(currentExchangeThread.data(), &QThread::started, currentExchange, &Exchange::run);

    baseValues.restSign.clear();

    currentExchange->setupApi(this, false);
    setCurrencyPairsList();
    setApiDown(false);

    if (!currentExchange->exchangeTickerSupportsHiLowPrices)
        for (int n = 0; n < ui.highLowLayout->count(); n++)
        {
            QWidgetItem* curWid = dynamic_cast<QWidgetItem*>(ui.highLowLayout->itemAt(n));

            if (curWid)
                curWid->widget()->setVisible(false);
        }

    if (!currentExchange->supportsExchangeFee)
    {
        ui.accountFee->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        ui.accountFee->setReadOnly(false);

        setSpinValue(ui.accountFee, iniSettings->value("Profile/CustomFee", 0.35).toDouble());
        ui.feeSpinboxLayout->addWidget(new JulySpinBoxPicker(ui.accountFee));
    }

    if (!currentExchange->supportsExchangeVolume)
    {
        ui.marketVolumeLabel->setVisible(false);
        ui.btcLabel4->setVisible(false);
        ui.marketVolume->setVisible(false);
    }

    if (currentExchange->clearHistoryOnCurrencyChanged || currentExchange->exchangeDisplayOnlyCurrentPairOpenOrders)
    {
        ui.ordersFilterCheckBox->setVisible(false);

        if (currentExchange->exchangeDisplayOnlyCurrentPairOpenOrders)
            ui.ordersFilterCheckBox->setChecked(true);

        ui.filterOrdersCurrency->setVisible(false);
        ui.centerOrdersTotalSpacer->setVisible(true);
    }
    else
        ui.centerOrdersTotalSpacer->setVisible(false);

    if (!currentExchange->supportsLoginIndicator)
    {
        ui.loginVolumeBack->setVisible(false);
        QSize sz = ui.widgetAccount->maximumSize();
        ui.widgetAccount->setMaximumSize(QSize(200, sz.height()));
    }
    else if (currentExchange->supportsLoginIndicator && !currentExchange->supportsAccountVolume)
    {
        ui.labelAccountVolume->setVisible(false);
        ui.btcLabelAccountVolume->setVisible(false);
        ui.accountVolume->setVisible(false);
    }

    ordersModel->checkDuplicatedOID = currentExchange->checkDuplicatedOID;

    ui.widgetStaysOnTop->setChecked(iniSettings->value("UI/WindowOnTop", false).toBool());

    if (baseValues.httpRequestInterval < currentExchange->minimumRequestIntervalAllowed)
        baseValues.httpRequestInterval = currentExchange->minimumRequestIntervalAllowed;

    if (baseValues.httpRequestTimeout < currentExchange->minimumRequestTimeoutAllowed)
        baseValues.httpRequestTimeout = currentExchange->minimumRequestTimeoutAllowed;

    iniSettings->sync();

    if (!ui.widgetStaysOnTop->isChecked())
        on_widgetStaysOnTop_toggled(ui.widgetStaysOnTop->isChecked());

    currencyMenuChanged(currencyMenu->getCurrentIndex());

    {
        QEventLoop waitStarted;
        connect(currentExchange, &Exchange::started, &waitStarted, &QEventLoop::quit);
        currentExchangeThread->start();
        waitStarted.exec();
    }

    ui.buyPercentage->setMaximumWidth(ui.buyPercentage->height());
    ui.sellPercentage->setMaximumWidth(ui.sellPercentage->height());

    int nextTheme = iniSettings->value("UI/NightMode", 0).toInt();

    if (nextTheme == 1)
        on_buttonNight_clicked();
    else if (nextTheme == 2)
    {
        baseValues.currentTheme = 1;
        on_buttonNight_clicked();
    }

    languageChanged();

    reloadScripts();
    fixDepthBidsTable();

    IndicatorEngine::global();
    #endif
}