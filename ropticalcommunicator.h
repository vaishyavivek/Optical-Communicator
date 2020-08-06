/*
This file is part of r-optical-communicator.

    r-optical-communicator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    r-optical-communicator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with r-optical-communicator. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ROPTICALCOMMUNICATOR_H
#define ROPTICALCOMMUNICATOR_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QTime>
#include "rocreceiverthread.h"
#include "roctransmitterthread.h"
#include "rocchathistorymodel.h"

class ROpticalCommunicator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> ChatHistoryList READ ChatHistoryList NOTIFY ChatHistoryListChanged)
    Q_PROPERTY(QString CurrentMessage READ CurrentMessage NOTIFY CurrentMessageChanged)

public:
    ROpticalCommunicator(QObject *parent = nullptr);

    QList<QObject*> ChatHistoryList() const{ return chatHistoryList;}
    QString CurrentMessage() const{ return currentMessage;}

    ~ROpticalCommunicator(){
        receiverThread.quit();
        //receiverThread.wait();
        transmitterThread.quit();
        //transmitterThread.wait();
    }

signals:
    void ChatHistoryListChanged();
    void CurrentMessageChanged();

    void askThreadToStartReceivingSignal();
    void provideDataForSending(QString data);

public slots:
    Q_INVOKABLE void sendDataFromUI(QString data);

    void debugMessagesFromThread(QString message);

    void dataReceived(QString newData);
    void getDataSentReceipt(QString dataSent);

private:
    QList<QObject*> chatHistoryList;
    QString currentMessage;

    QThread receiverThread;
    QThread transmitterThread;
};

#endif // ROPTICALCOMMUNICATOR_H
