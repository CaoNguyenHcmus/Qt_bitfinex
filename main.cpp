#include "widget.h"
#include <QApplication>
#include <iostream>
#include <fstream>
#include "BitfinexAPI.hpp"
#include "updaterdialog.h"
#include "main.h"
#include "exchange.h"
#include <QByteArray>
#include <QDebug>

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

#include "iniengine.h"
using std::cout;
using std::endl;
using std::ifstream;
using std::string;


BaseValues* baseValues_;
void BaseValues::Construct()
{
    /*
    forceDotInSpinBoxes = true;
    scriptsThatUseOrderBookCount = 0;
    */
    trafficSpeed = 0;
    /*
    trafficTotal = 0;
    trafficTotalType = 0;
    */
    currentExchange_ = 0;
    /*
    currentTheme = 0;
    gzipEnabled = true;
    appVerIsBeta = false;
    jlScriptVersion = 1.0;
    appVerStr = "1.4006";
    appVerReal = appVerStr.toDouble();

    if (appVerStr.size() > 4)
    {
        if (appVerStr.size() == 7)
            appVerStr.remove(6, 1);

        appVerStr.insert(4, ".");
    }

    appVerLastReal = appVerReal;
*/
    logThread = 0;
/*
    highResolutionDisplay = true;
    timeFormat = QLocale().timeFormat(QLocale::LongFormat).replace(" ", "").replace("t", "");
    dateTimeFormat = QLocale().dateFormat(QLocale::ShortFormat) + " " + timeFormat;
    depthCountLimit = 100;
    depthCountLimitStr = "100";
    uiUpdateInterval = 100;
    supportsUtfUI = true;

#ifdef Q_WS_WIN

    if (QSysInfo::windowsVersion() <= QSysInfo::WV_XP)
        supportsUtfUI = false;

#endif

    upArrow = QByteArray::fromBase64("4oaR");
    downArrow = QByteArray::fromBase64("4oaT");

    if (baseValues.supportsUtfUI)
    {
        upArrowNoUtf8 = upArrow;
        downArrowNoUtf8 = downArrow;
    }
    else
    {
        upArrowNoUtf8 = ">";
        downArrowNoUtf8 = "<";
    }
*/
    httpRequestInterval = 400; /* julyhttp.cpp:915:91: error: ‘struct BaseValues’ has no member named ‘httpRequestTimeout’*/
    httpRequestTimeout = 5000; /* julyhttp.cpp:915:91: error: ‘struct BaseValues’ has no member named ‘httpRequestTimeout’*/
/*
    httpRetryCount = 5;
    apiDownCount = 0;
    groupPriceValue = 0.0;
    defaultHeightForRow_ = 22;

    selectSystemLanguage();
*/
}
int main(int argc, char *argv[])
{
#if 1 /* integrating bitfinex exchange */
    baseValues_ = new BaseValues;
    baseValues.Construct();
    //baseValues.mainWindow_ = new Widget;
#endif
    QApplication a(argc, argv);
    //a.setApplicationName("QtBitcoinTrader");
    
    //baseValues.mainWindow_ = new QtBitcoinTrader;
    IniEngine::global(); //get pair list from exchange
    Widget *dialog = new Widget;
    baseValues.mainWindow_ = dialog;
    //baseValues.mainWindow_->show();
   
    dialog->show();

    return a.exec();
#if 0
    const char *keyFilePath = "key.md";
    ifstream ifs(keyFilePath);
    if (!ifs.is_open())
    {
        cout << "Can't open file: " << argv[1] << endl;
        return -1;
    }
    else
    {
        string accessKey, secretKey;
        getline(ifs, accessKey);
        getline(ifs, secretKey);

        BitfinexAPI bfxAPI(accessKey, secretKey);
        string response;
        int errCode;

        /////////////////////////////////////////////////////////////////////////
        //  Examples
        //  Note that default values are not mandatory. See BitfinexAPI.hpp
        //  for details.
        /////////////////////////////////////////////////////////////////////////

        ///  Public endpoints ///

          errCode = bfxAPI.getTicker(response, "btcusd");
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
        return 0;

    }
#endif
}
