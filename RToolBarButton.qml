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
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

Rectangle{
    id: toolBarButtonParentRect
    property int buttonHeight: 45
    property int buttonWidth: buttonHeight
    property string hoverText: "Button"
    property bool hoverTextSafeMode: false
    property string iconSource: "/Library/Icons/Resources/FolderIcons/Document.png"
    property bool active: false
    property string shortcutKey: ""

    signal clicked

    width: buttonWidth; height: buttonHeight
    color: "transparent"
    //radius: 10
    Image {
        id: toolBarButtonIcon
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        sourceSize.height: parent.height*0.95
        sourceSize.width: parent.width*0.95
        source: iconSource
    }
    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            if(active)
                animationOnHoverEntered.start();
                hoverOverTextPopup.open()}
        onExited: {
            if(active)
                animationOnHoverExited.start();
                hoverOverTextPopup.close()}
        onClicked: {
            if(active){
                animationOnHoverExited.start();
                parent.clicked()}}
    }

    Keys.onPressed: {
        if(event.key === Qt.Key_Enter || event.key === Qt.Key_Return){
            if(active){
                animationOnHoverExited.start();
                toolBarButtonParentRect.clicked()
            }
        }
    }

    Popup{
        id: hoverOverTextPopup
        padding: 0
        y: parent.height + hoverOverText.height/2
        Rectangle{
            id: hoverOverTextParentRect
            color: "black"
            width: hoverOverText.width + 10
            height: hoverOverText.height + 10
            radius: 2
            Text {
                id: hoverOverText
                text: hoverText
                anchors.centerIn: parent
                color: "white"
            }
        }

        enter: Transition {
                NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; duration: 500 }
            }

        exit: Transition {
                NumberAnimation { property: "opacity"; from: 1.0; to: 0.0; duration: 500 }
            }
        Component.onCompleted: {
            if(((toolBarButtonParentRect.x + hoverOverText.width) > toolBarButtonParentRect.parent.width) && hoverTextSafeMode)
                hoverOverTextPopup.x = hoverOverText.width*(-1);
            if(shortcutKey !== "")
                hoverOverText.text += " (" + shortcutKey + ")"
        }
    }

    PropertyAnimation{
        id: animationOnHoverEntered
        target: toolBarButtonParentRect
        property: "color"
        to: "lightsteelblue"
        duration: 500
    }

    PropertyAnimation{
        id: animationOnHoverExited
        target: toolBarButtonParentRect
        property: "color"
        to: "transparent"
        duration: 500
    }

    onFocusChanged: {
        if(focus) {
            animationOnHoverEntered.start()
            hoverOverTextPopup.open()
        }
        else {
            animationOnHoverExited.start()
            hoverOverTextPopup.close()
        }
    }
}
