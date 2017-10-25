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
        errCode = bfxAPI.getTicker(response, "eosusd");
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
        #if 0
        newOrder(string &result, const string &symbol, const double &amount,
                 const double &price, const string &side, const string &type,
                 const bool &is_hidden, const bool &is_postonly,
                 const bool &use_all_available, const bool &ocoorder,
                 const double &buy_price_oco)
        #endif
        
        //qDebug()<< "amount: " << input_amount << "price: " << input_price;
        errCode = bfxAPI.newOrder(response, "eosusd", input_amount.toFloat(), input_price.toFloat(), "buy", "exchange limit", 0, 1, 0, 0, 0);
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