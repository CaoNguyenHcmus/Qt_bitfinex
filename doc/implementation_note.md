Note
take care: *baseValues* is a extern struct value
====
currencyinfo
^
|
currencypairitem, *main.h*, depthitem.h, iniengine.h
^
|
exchange (setupApi is important)
^
|
exchange_bitfinex (constructor will fill to *struct BaseValues* in main.h)

----
[?] How to use socket to display value ????
20171108: Implement julyHttp in exchange_bitfinex.cpp
sendToApi() for secondSlot() get public slot
TODO: private key will fill here getApiKey() hard-code now
isReplayPending()?

sencondSlot() will be execute in void Exchange::run() in thread

connectToHostEncrypted() will connect to the secure SSL
----
https://stackoverflow.com/questions/39302049/connecting-qsslsocket-with-openssl-server

```
qt.network.ssl: QSslSocket: cannot resolve SSLv2_client_method
qt.network.ssl: QSslSocket: cannot resolve SSLv2_server_method
```

Tat ca nhung request se dc dua vao requestList
===
Done:
connect(julyHttp, SIGNAL(dataReceived(QByteArray, int)), this, SLOT(dataReceivedAuth(QByteArray, int)));
Connection b/w data receive from network and analyze result

Check price lien tuc (1 thread)
====
Input: Check price lien tuc ?? secondSlot() dc goi qua Exchange::run()
--Using thread. Done

Output: lien quan den indicatorengine.cpp de set va get price
Khi lay du lieu ve dua du lieu vao IndicatorEngine & ben ngoai se get gia nay


Currency menu (1 thread dung iniengine de luu vao currency menu)
=====
1 button ket noi voi 1 menu, menu nay lai chua nhieu cell
TODO
Input: Set gia tri ban dau cho menu list qua ham setCurrencyPairsList();
QMap<QString, CurrencyPairItem> currencyPairMap;
Muon co currencyPairMap ta phai down tu trang chu ve hoac luu tu local
Ta luu o local: dung iniengine.cpp file
main: IniEngine::global(); //run thread for get pair list from exchange
Know-how using QThread