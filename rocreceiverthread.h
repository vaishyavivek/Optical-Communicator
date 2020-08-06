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

#ifndef ROCRECEIVERTHREAD_H
#define ROCRECEIVERTHREAD_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include "qextserialport.h"

class rocReceiverThread : public QObject
{
    Q_OBJECT
public:
    rocReceiverThread(QObject *parent = nullptr);

signals:
    void sendDebugMessages(QString message);
    void submitReceivedData(QString data);

public slots:
    void startReceivingData();

private:
    bool isComLinkUp;
    QextSerialPort *port;
};

#endif // ROCRECEIVERTHREAD_H
