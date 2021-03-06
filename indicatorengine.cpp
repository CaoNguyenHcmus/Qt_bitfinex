//  This file is part of Qt Bitcoin Trader
//      https://github.com/JulyIGHOR/QtBitcoinTrader
//  Copyright (C) 2013-2017 July IGHOR <julyighor@gmail.com>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  In addition, as a special exception, the copyright holders give
//  permission to link the code of portions of this program with the
//  OpenSSL library under certain conditions as described in each
//  individual source file, and distribute linked combinations including
//  the two.
//
//  You must obey the GNU General Public License in all respects for all
//  of the code used other than OpenSSL. If you modify file(s) with this
//  exception, you may extend this exception to your version of the
//  file(s), but you are not obligated to do so. If you do not wish to do
//  so, delete this exception statement from your version. If you delete
//  this exception statement from all source files in the program, then
//  also delete it here.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <QThread>
#include "indicatorengine.h"
#include "main.h"
#include "widget.h"
#include <QDebug>

IndicatorEngine::IndicatorEngine() : QObject()
{
    connect(this, &IndicatorEngine::indicatorChanged, this, &IndicatorEngine::setValueSlot);
    
    connect(this, &IndicatorEngine::indicatorHighChanged, baseValues.mainWindow_, &Widget::indicatorHighChanged);
    connect(this, &IndicatorEngine::indicatorLowChanged, baseValues.mainWindow_, &Widget::indicatorLowChanged);
    connect(this, &IndicatorEngine::indicatorSellChanged, baseValues.mainWindow_, &Widget::indicatorSellChanged);
    connect(this, &IndicatorEngine::indicatorBuyChanged, baseValues.mainWindow_, &Widget::indicatorBuyChanged);
    connect(this, &IndicatorEngine::indicatorLastChanged, baseValues.mainWindow_, &Widget::indicatorLastChanged);
    connect(this, &IndicatorEngine::indicatorVolumeChanged, baseValues.mainWindow_, &Widget::indicatorVolumeChanged);

    QThread* indicatorEngineThread = new QThread;
    connect(this, SIGNAL(finishThread()), indicatorEngineThread, SLOT(quit()));
    this->moveToThread(indicatorEngineThread);
    indicatorEngineThread->start();
}

IndicatorEngine::~IndicatorEngine()
{
    emit finishThread();
}

//---------------------------------------- Static ----------------------------------------
IndicatorEngine* IndicatorEngine::global()
{
    static IndicatorEngine instance; //mutex https://stackoverflow.com/questions/5006547/qt-best-practice-for-a-single-instance-app-protection
    return &instance;
}
/*setValue is call by receive data from bitfinex */
void IndicatorEngine::setValue(QString exchange, QString symbol, QString indicator, double value)
{
    qDebug() <<"Function trace: " << __func__ << "()\t" << "exchange: " << exchange << "\tsymbol: " << symbol << "\tindicator: " << indicator << "\tvalue:" << value;
    emit IndicatorEngine::global()->indicatorChanged(exchange, symbol, indicator, value);
}

double IndicatorEngine::getValue(QString index)
{
    qDebug() <<"Function trace: " << __func__ << "()\t" << index;
    IndicatorEngine::global()->locker.lock();
    double value = IndicatorEngine::global()->indicators[index.toLatin1()];
    IndicatorEngine::global()->locker.unlock();

    return value;
}
//---------------------------------------- Private ----------------------------------------
/* when receive from bifinex luu vao trong 1 cai mang indicators chua index va value sau do emit co su thay doi */
#if 1
void IndicatorEngine::setValueSlot(QString exchange, QString symbol, QString name, double value)
{
    if (exchange == baseValues.exchangeName && symbol == baseValues.currentPair.symbol)
    {
        QByteArray index = (exchange + '_' + symbol + '_' + name).toLatin1();

        if (indicators.contains(index))
        {
            if (indicators[index] == value)
                return;
            else
            {
                locker.lock();
                indicators[index] = value;
                locker.unlock();
            }
        }
        else
        {
            locker.lock();
            indicators.insert(index, value);
            locker.unlock();
        }

        if (name == "High"){
            qDebug() <<"Function trace: " << __func__ << "()\t" <<"indicatorHighChanged_____________________________";
            emit indicatorHighChanged(symbol, value);
        }
        else if (name == "Low")
        {
            qDebug() <<"Function trace: " << __func__ << "()\t" <<"indicatorLowChanged_____________________________";
            emit indicatorLowChanged(symbol, value);
        }
        else if (name == "Sell")
        {
            qDebug() <<"Function trace: " << __func__ << "()\t" <<"indicatorSellChanged_____________________________";
            emit indicatorSellChanged(symbol, value);
        }
        else if (name == "Buy")
            emit indicatorBuyChanged(symbol, value);
        else if (name == "Last")
        {
            qDebug() <<"Function trace: " << __func__ << "()\t" <<"indicatorLastChanged_____________________________";
            emit indicatorLastChanged(symbol, value);
        }
        else if (name == "Volume")
            emit indicatorVolumeChanged(symbol, value);
    }
}
#endif