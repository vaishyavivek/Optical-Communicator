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


#include "rocreceiverthread.h"

rocReceiverThread::rocReceiverThread(QObject *parent)
    : QObject(parent){
    port = new QextSerialPort("/dev/ttyACM1");
    port->setBaudRate(BAUD9600);
    isComLinkUp = port->open(QIODevice::ReadOnly);

    if(!isComLinkUp)
        emit sendDebugMessages("Can't communicate with the module for receiving.\n");
    else
        emit sendDebugMessages("Connection successfully established for receiving.\n");
}

void rocReceiverThread::startReceivingData(){
    QString currentData = "";
    while (isComLinkUp) {
        QByteArray charData = port->read(1);
        if((charData != "0") && (charData != "0\r") && (charData != "0\r\n"))
            currentData.append(charData);
        else if(currentData.length() > 0){
            emit submitReceivedData(currentData);
            currentData = "";
        }

        if (!port->isOpen() || !isComLinkUp)
            emit sendDebugMessages("Lost the connection from receiver thread.\n");
        QThread::msleep(10);
    }
}
