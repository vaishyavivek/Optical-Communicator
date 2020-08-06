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


#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "ropticalcommunicator.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    ROpticalCommunicator rObject;

    /*QextSerialPort *port = new QextSerialPort("/dev/ttyACM0");
     * port->setBaudRate(BAUD9600);
    QByteArray data = 0;

    bool open = false;
    open = port->open(QIODevice::ReadOnly | QIODevice::Unbuffered);

    if(open)
        qDebug("Resources are ready to be fetched");
    else
        qDebug("Couldn't read resources.");

    while(data >= 0){
        port->flush();
        data = port->read(6);
        qDebug(data);
    }*/

    QQmlContext *ctxt = engine.rootContext();
    ctxt->setContextProperty("rObject", &rObject);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
