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

#include "ropticalcommunicator.h"

ROpticalCommunicator::ROpticalCommunicator(QObject *parent)
    : QObject(parent){
        rocReceiverThread *receiver = new rocReceiverThread();
        receiver->moveToThread(&receiverThread);

        connect(&receiverThread, &QThread::finished, receiver, &QObject::deleteLater);
        connect(this, &ROpticalCommunicator::askThreadToStartReceivingSignal, receiver, &rocReceiverThread::startReceivingData);
        connect(receiver, &rocReceiverThread::submitReceivedData, this, &ROpticalCommunicator::dataReceived);
        connect(receiver, &rocReceiverThread::sendDebugMessages, this, &ROpticalCommunicator::debugMessagesFromThread);

        rocTransmitterThread *transmitter = new rocTransmitterThread();
        transmitter->moveToThread(&transmitterThread);

        connect(&transmitterThread, &QThread::finished, transmitter, &QObject::deleteLater);
        connect(this, &ROpticalCommunicator::provideDataForSending, transmitter, &rocTransmitterThread::sendData);
        connect(transmitter, &rocTransmitterThread::dataSentReceipt, this, &ROpticalCommunicator::getDataSentReceipt);
        connect(transmitter, &rocTransmitterThread::sendDebugMessages, this, &ROpticalCommunicator::debugMessagesFromThread);

        receiverThread.start();
        transmitterThread.start();
        emit askThreadToStartReceivingSignal();
}

void ROpticalCommunicator::debugMessagesFromThread(QString message){
    currentMessage += message;
    emit CurrentMessageChanged();
}

void ROpticalCommunicator::sendDataFromUI(QString data){
    if(data != "")
        emit provideDataForSending(data);
}

void ROpticalCommunicator::dataReceived(QString newData){
    newData = newData.remove("\r");
    newData = newData.remove("\n");
    QString currentTime = QTime::currentTime().toString("HH:mm");
    rocChatHistoryModel *anotherChat = new rocChatHistoryModel(newData, false, currentTime);
    chatHistoryList.append(anotherChat);
    emit ChatHistoryListChanged();
}

void ROpticalCommunicator::getDataSentReceipt(QString dataSent){
    QString currentTime = QTime::currentTime().toString("HH:mm");
    rocChatHistoryModel *anotherChat = new rocChatHistoryModel(dataSent, true, currentTime);
    chatHistoryList.append(anotherChat);
    emit ChatHistoryListChanged();
}
