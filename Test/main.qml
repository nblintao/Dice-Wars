/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0

Rectangle {
    id: box
    width: 1000; height: 600;
    color:"gray";
    Grid{
        id:grid
        rows:10;
        columns:20;
        spacing:1;
        Repeater{
            id:rep;
            model:200;
            Rectangle {
            //    var tid="rec"+index;
                id:rec;
                width: 40; height: 40
           //     x:(index%10)*10;y:(index/10)*10;
                color:"#a020f0";
                border.color:"white";
                property var name:index;
                property var lastColor:"#a020f0";
      //          Text { text: index; font.pixelSize: 15; anchors.centerIn: parent }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    property string buttonID

                    acceptedButtons: Qt.AllButtons
                    // Value 'All.Buttons' is eqivalent to:
                    // 'Qt::LeftButton | Qt::RightButton | Qt::MiddleButton  .... | Qt::ExtraButton24'

                    onEntered:{
                                    info.text = 'Entered '+index;
                                    rep.itemAt(index).color="#da70d6";
                              }
                    onExited: {
                                    info.text = 'Exited '+index+' (pressed=' + pressed + ')';
                                    rep.itemAt(index).color=lastColor;
                              }

                    onPressed: {
                        if (mouse.button == Qt.LeftButton)
                            buttonID = 'LeftButton'
                        else if (mouse.button == Qt.RightButton)
                            buttonID = 'RightButton'
                        else if (mouse.button == Qt.MidButton)
                            buttonID = 'MiddleButton'
                        else if (mouse.button == Qt.BackButton)
                            buttonID = 'BackButton'
                        else if (mouse.button == Qt.ForwardButton)
                            buttonID = 'ForwardButton'
                        else if (mouse.button == Qt.TaskButton)
                            buttonID = 'TaskButton';
                        info.text = 'Pressed (' + buttonID + ' shift='
                            + (mouse.modifiers & Qt.ShiftModifier ? 'true' : 'false') + ')'
                        var posInBox = rep.itemAt(index).mapToItem(box, mouse.x, mouse.y)
                        posInfo.text = + mouse.x + ',' + mouse.y + ' in square'
                                + ' (' + posInBox.x + ',' + posInBox.y + ' in window)'
                    }

                    onReleased: {
                        btn.text = 'Released (isClick=' + mouse.isClick + ' wasHeld=' + mouse.wasHeld + ')'
                        posInfo.text = ''
                    }

                    //! [clicks]
                    onPressAndHold: btn.text = 'Press and hold'
                    onClicked:{
                                btn.text = 'Clicked '+index+' (wasHeld=' + mouse.wasHeld + ')';
                                if (rep.itemAt(index).lastColor=="#a020f0")
                                {
                                    rep.itemAt(index).color="#ffffff";
                                    rep.itemAt(index).lastColor="#ffffff";
                                }
                                else
                                {
                                   rep.itemAt(index).lastColor="#a020f0";
                                   rep.itemAt(index).color="#da70d6";
                                }
                              }

                    onDoubleClicked: btn.text = 'Double clicked'
                    //! [clicks]
                }
            }
        }

    }

    Text {
        id: info
        anchors.bottom: btn.top; anchors.horizontalCenter: parent.horizontalCenter; anchors.margins: 20

        onTextChanged: console.log(text)
    }

    Text {
        id: btn
        anchors.bottom: posInfo.top; anchors.horizontalCenter: parent.horizontalCenter; anchors.margins: 20
    }

    Text {
        id: posInfo
        anchors.bottom: parent.bottom; anchors.horizontalCenter: parent.horizontalCenter; anchors.margins: 20
    }

}
