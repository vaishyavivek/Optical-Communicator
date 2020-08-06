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

import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Window 2.2

Window {
    visible: true
    width: 400
    height: 560
    title: qsTr("Reverse Optical Communicator")
    Column{
        id: mainLayout
        anchors.fill: parent
        spacing: 10
        Rectangle{
            id: headerBar
            width: parent.width
            height: parent.height*0.1
            border.width: 2
            border.color: "red"
            Text{
                anchors.fill: parent
                text: rObject.CurrentMessage
                font.pointSize: 8
            }
        }

        Rectangle{
            id: listViewParentRect
            width: parent.width
            height: parent.height*0.8 - 15
            ListView{
                id: chatHistory
                anchors.fill: parent
                model: rObject.ChatHistoryList
                clip: true
                spacing: 5

                delegate: Rectangle{
                    id: chatHistoryDelegate
                    property string chatData: model.modelData.ChatData
                    width: chatHistory.width
                    height: 40
                    Loader{
                        width: parent.width
                        height: parent.height
                        sourceComponent: {
                            switch(model.modelData.SentOrReceived){
                            case true:
                                return sentChat;
                            case false:
                                return receivedChat;
                            }
                        }
                    }

                    Component{
                        id: sentChat
                        Rectangle{
                            anchors.fill: parent
                            Rectangle{
                                anchors.fill: parent
                                anchors.leftMargin: 32
                                border.color: "blue"
                                border.width: 2
                                Column{
                                    anchors.fill: parent
                                    anchors.margins: 4
                                    Rectangle{
                                        id: chatTextParentRect
                                        width: parent.width
                                        height: parent.height*0.9 - 4
                                        Text {
                                            id: chatText
                                            text: model.modelData.ChatData
                                            verticalAlignment: Text.AlignVCenter
                                            font.pointSize: 11
                                            anchors.fill: parent
                                        }
                                    }
                                    Rectangle{
                                        id: timeOfSubmissionParentRect
                                        width: parent.width
                                        height: parent.height*0.1
                                        Text {
                                            id: timeOfSubmission
                                            text: model.modelData.TimeOfDefinition
                                            font.pointSize: 6
                                            anchors.left: parent.left
                                        }
                                    }
                                }
                            }
                        }
                    }
                    Component{
                        id: receivedChat
                        Rectangle{
                            anchors.fill: parent
                            Rectangle{
                                anchors.fill: parent
                                anchors.rightMargin: 32
                                border.color: "green"
                                border.width: 2
                                Column{
                                    anchors.fill: parent
                                    anchors.margins: 4
                                    Rectangle{
                                        id: chatTextParentRect
                                        width: parent.width
                                        height: parent.height*0.90 - 4
                                        Text {
                                            id: chatText
                                            text: model.modelData.ChatData
                                            horizontalAlignment: Text.AlignHCenter
                                            font.pointSize: 11
                                            anchors.fill: parent
                                        }
                                    }
                                    Rectangle{
                                        id: timeOfSubmissionParentRect
                                        width: parent.width
                                        height: parent.height*0.1
                                        Text {
                                            id: timeOfSubmission
                                            text: model.modelData.TimeOfDefinition
                                            font.pointSize: 6
                                            anchors.left: parent.left
                                        }
                                    }
                                }
                            }
                        }
                    }

                    Component.onCompleted: {
                        chatHistoryDelegate.height = getChatBoxHeight(chatData.length)
                    }
                }
            }
        }

        Rectangle{
            id: textInputFieldParentRect
            property int charIsSpace: 0
            property bool readyToSend: false
            width: parent.width
            height: parent.height*0.1 - 5
            Row{
                anchors.fill: parent
                spacing: 5
                anchors.margins: 5
                TextField{
                    id: textInputField
                    width: parent.width - parent.height - 5
                    height: parent.height
                    visible: true
                    focus: true
                    placeholderText: "Enter your text here..."
                    onAccepted: {
                        if(textInputFieldParentRect.readyToSend){
                            rObject.sendDataFromUI(text)
                            text = ""
                            textInputFieldParentRect.charIsSpace = 0
                            textInputFieldParentRect.readyToSend = false
                        }
                    }
                    onTextChanged: {
                        if((text.charAt(textInputFieldParentRect.charIsSpace) === " ") && !textInputFieldParentRect.readyToSend)
                            textInputFieldParentRect.charIsSpace++
                        else
                            textInputFieldParentRect.readyToSend = true
                    }
                }
                RToolBarButton{
                    id: sendButton
                    buttonHeight: parent.height
                    hoverText: "Send Your Text"
                    iconSource: "/icons/SendBtn.png"
                    shortcutKey: "Enter"
                    active: true
                    onClicked: {
                        if(textInputFieldParentRect.readyToSend){
                            rObject.sendDataFromUI(textInputField.text)
                            textInputField.text = ""
                            textInputFieldParentRect.charIsSpace = 0
                            textInputFieldParentRect.readyToSend = false
                        }
                    }
                }
            }
        }
    }
    function getChatBoxHeight(textLength){
        var height = 0
        while(textLength > 0){
            height += 40
            textLength -= 30
        }
        return height
    }
}
