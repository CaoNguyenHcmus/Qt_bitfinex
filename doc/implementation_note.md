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