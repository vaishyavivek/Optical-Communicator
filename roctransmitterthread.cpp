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

#include "roctransmitterthread.h"

rocTransmitterThread::rocTransmitterThread(QObject *parent)
    :QObject(parent){
    port = new QextSerialPort("/dev/ttyACM1");
    port->setBaudRate(BAUD9600);
    isComLinkUp = port->open(QIODevice::WriteOnly);
    if(!isComLinkUp)
        emit sendDebugMessages("Can't communicate with the module for Transmission.\n");
    else
        emit sendDebugMessages("Connection successfully established for Transmission.\n");
    for(int i  = 1; i < 10; i++)
        port->write("" + (i/2));
    QThread::msleep(10);
}

void rocTransmitterThread::sendData(QString data){
    QByteArray stringReceived = data.toLocal8Bit();
    port->write("1");
    int length = stringReceived.length();
    for(int i = 0; i < length; i++) {
        char ch = stringReceived.at(i);
        for(int i = 7; i >= 0; i--){
            if(((ch >> i) & 1) == 1)
                port->write("1");
            QThread::msleep(10);
        }
        if(!port->isOpen()){
            isComLinkUp = false;
            emit sendDebugMessages("Lost the connection from transmission thread.\n");
            break;
        }
        if(((i + 1) % 30) == 0)
            data = data.insert(i, "<p>");
    }
    emit dataSentReceipt(data);
}
