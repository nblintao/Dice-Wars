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
        id:imageGrid;
        z:100;
        rows:10;
        columns:20;
        anchors.top: parent.top; anchors.horizontalCenter: parent.horizontalCenter; anchors.margins: 10;
        Repeater{
            id:imageRep;
            model:200;
            Image{
                width:40;
                height:40;
                x:index*index%10;y:10-index*index%10;
                source:"./Dice_20.png";
            }
        }
    }

    Grid{
        id:grid
        rows:10;
        columns:20;
        anchors.top: parent.top; anchors.horizontalCenter: parent.horizontalCenter; anchors.margins: 10;
        Repeater{
            id:rep;
            model:200;
            Rectangle {
                width: 40; height: 40
                color:gameMap.getColor(index);
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    property string buttonID

                    onEntered:{
                        gameMap.enter(index);
                        for(var i=0;i<200;i++){rep.itemAt(i).color=gameMap.getColor(i);}
                    }
                    onExited:{
                        gameMap.exit(index);
                        for(var i=0;i<200;i++){rep.itemAt(i).color=gameMap.getColor(i);}
                    }
                    onClicked:{
                        gameMap.click(index);
                        for(var i=0;i<200;i++){
                            if(gameMap.getDice(i)==1)
                                imageRep.itemAt(i).source="Dice_20.png";
                            else
                                imageRep.itemAt(i).source="Transparent_20.png";
                        }
                        for(var i=0;i<200;i++){rep.itemAt(i).color=gameMap.getColor(i);}
                        playerfColor.color=gameMap.getAttackerColor();
                        playersColor.color=gameMap.getAttackedColor();
                        playerfPoint.text=gameMap.getAttackerDice();
                        playersPoint.text=gameMap.getAttackedDice();
                        playerColor.color=gameMap.getPlayerColor();
                    }
                }
            }
        }

    }
    Rectangle{
        id:realTimeStatus
        width: grid.width; height: 40;
        anchors.top: grid.bottom; anchors.left: grid.left; anchors.horizontalCenter: parent.horizontalCenter;
        Row{
            anchors.verticalCenter: parent.verticalCenter;anchors.horizontalCenter: parent.horizontalCenter;anchors.margins: realTimeStatus.border.width;
            Rectangle{
                id:playerfColor;
                width:30;
                height:30;
                color:"blue";
            }
            Text{
                id:playerfPoint;
                width:300;
                anchors.verticalCenter: parent.verticalCenter;
                horizontalAlignment:Text.AlignHCenter;
                text:"23";
                font.pixelSize: 25;
            }
            Rectangle{
                id:playersColor;
                width:30;
                height:30;
                color:"#00ee76";
            }
            Text{
                id:playersPoint;
                width:300;
                anchors.verticalCenter: parent.verticalCenter;
                horizontalAlignment:Text.AlignHCenter;
                text:"16";
                font.pixelSize: 25;
            }
        }
    }
    Rectangle{
        id:playerNotify
        width: grid.width; height: 40;
        anchors.top: realTimeStatus.bottom; anchors.left: grid.left; anchors.horizontalCenter: parent.horizontalCenter;
        Row{
            anchors.horizontalCenter: parent.horizontalCenter;anchors.verticalCenter: parent.verticalCenter;anchors.margins: 2;
            Text{
                anchors.verticalCenter: parent.verticalCenter;
                horizontalAlignment:Text.AlignHCenter;
                text:"1.Click your area.";
                font.pixelSize: 20;
            }
            Rectangle{
                id:playerColor;
                anchors.verticalCenter: parent.verticalCenter;
                width:30;
                height:30;
                color:"#7D9EC0";
            }
            Text{
                anchors.verticalCenter: parent.verticalCenter;
                horizontalAlignment:Text.AlignHCenter;
                text:"  2.Click neighbor to attack.";
                font.pixelSize: 20;
            }
            Rectangle{
                id:endTurn;
                width:150;
                height:37;
                radius: 4;
                color:"#737373";
                Text{
                    anchors.verticalCenter: parent.verticalCenter;
                    anchors.horizontalCenter: parent.horizontalCenter;
                    text:"END TURN";
                    font.pixelSize:23;
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        gameMap.endTurn();
                        for(var i=0;i<200;i++){
                            if(gameMap.getDice(i)==1)
                                imageRep.itemAt(i).source="Dice_20.png";
                            else
                                imageRep.itemAt(i).source="Transparent_20.png";
                        }
                        for(var i=0;i<200;i++){rep.itemAt(i).color=gameMap.getColor(i);}
                        playerfColor.color=gameMap.getAttackerColor();
                        playersColor.color=gameMap.getAttackedColor();
                        playerfPoint.text=gameMap.getAttackerDice();
                        playersPoint.text=gameMap.getAttackedDice();
                        playerColor.color=gameMap.getPlayerColor();
                    }
                }


            }
        }
    }
}
