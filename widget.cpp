#include "widget.h"

#if 1   //for bitfinex API
#include <iostream>
#include <fstream>
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

#include "menu/currencymenu.h"

//class CurrencyMenu;

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
#if 0
    currencyMenu = new CurrencyMenu(ui->currencyMenuTool);
    //connect(currencyMenu, &CurrencyMenu::currencyMenuChanged, this, &QtBitcoinTrader::currencyMenuChanged);
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
        "eosusd"
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
        errCode = bfxAPI.newOrder(response, ticker, input_amount.toFloat(), input_price.toFloat(), "buy", "exchange limit", 0, 1, 0, 0, 0);
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
        errCode = bfxAPI.newOrder(response, ticker, input_amount.toFloat(), input_price.toFloat(), "sell", "exchange limit", 0, 1, 0, 0, 0);
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
