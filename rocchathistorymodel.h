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

#ifndef ROCCHATHISTORYMODEL_H
#define ROCCHATHISTORYMODEL_H

#include<QObject>

class rocChatHistoryModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ChatData READ ChatData NOTIFY ChatDataChanged)
    Q_PROPERTY(bool SentOrReceived READ SentOrReceived NOTIFY SentOrReceivedChanged)
    Q_PROPERTY(QString TimeOfDefinition READ TimeOfDefinition NOTIFY TimeOfDefinitionChanged)

public:
    rocChatHistoryModel(QObject *parent = nullptr)
        :QObject(parent){}
    rocChatHistoryModel(QString &ChatData, bool SentOrReceived, QString &TimeOfDefinition, QObject *parent = nullptr)
        :QObject(parent), chatData(ChatData), sentOrReceived(SentOrReceived), timeOfDefinition(TimeOfDefinition) {}

    QString ChatData() const{ return chatData; }
    bool SentOrReceived() const{ return sentOrReceived; }
    QString TimeOfDefinition() const{ return timeOfDefinition; }

signals:
    void ChatDataChanged();
    void SentOrReceivedChanged();
    void TimeOfDefinitionChanged();

private:
    QString chatData;
    bool sentOrReceived;
    QString timeOfDefinition;
};

#endif // ROCCHATHISTORYMODEL_H
