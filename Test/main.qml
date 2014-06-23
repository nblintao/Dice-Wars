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
    width: 850; height: 500;
    color:"gray";
    Grid{
        id:imageGrid;
        z:20;
        rows:gameMap.row();
        columns:gameMap.column();
        anchors.top: parent.top; anchors.horizontalCenter: parent.horizontalCenter; anchors.margins: 10;
        Repeater{
            id:imageRep;
            model:gameMap.row()*gameMap.column();
            Image{
//                width:40;
//                height:40;
                width:800/gameMap.column();
                height:400/gameMap.row();
                x:index*index%gameMap.row();y:gameMap.row()-index*index%gameMap.row();
                source:"./Dice_20.png";
            }
        }
    }

    Grid{
        id:grid
        rows:gameMap.row();
        columns:gameMap.column();
        anchors.top: parent.top; anchors.horizontalCenter: parent.horizontalCenter; anchors.margins: 10;
        Repeater{
            id:rep;
            model:gameMap.row()*gameMap.column();
            Rectangle {
//                width: 40; height: 40
                width:800/gameMap.column();
                height:400/gameMap.row();
                color:gameMap.getColor(index);
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    property string buttonID
                    onEntered:{
                        if(gameMap.getStatus()===1){
                            gameMap.enter(index);
                            for(var i=0;i<rep.model;i++){rep.itemAt(i).color=gameMap.getColor(i);}
                        }
                    }
                    onExited:{
                        if(gameMap.getStatus()===1){
                            gameMap.exit(index);
                            for(var i=0;i<rep.model;i++){rep.itemAt(i).color=gameMap.getColor(i);}
                        }
                    }
                    onClicked:{
                        if(gameMap.getStatus()===1){
                            gameMap.click(index);
                            if(gameMap.getStatus()===2){
                                winnerColor.color=gameMap.getWinnerColor();
                                finalWindow.z=22;
                            }else{
                                for(var i=0;i<rep.model;i++){
                                    if(gameMap.getDice(i)==1)
                                        imageRep.itemAt(i).source="Dice_20.png";
                                    else
                                        imageRep.itemAt(i).source="Transparent_20.png";
                                }
                                for(i=0;i<rep.model;i++){rep.itemAt(i).color=gameMap.getColor(i);}
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
                radius: 5;
                color:"white";
            }
            Text{
                id:playerfPoint;
                width:300;
                anchors.verticalCenter: parent.verticalCenter;
                horizontalAlignment:Text.AlignHCenter;
                font.family: "Helvetica [Cronyx]";
                text:"";
                font.pixelSize: 25;
            }
            Rectangle{
                id:playersColor;
                width:30;
                height:30;
                radius: 5;
                color:"white";
            }
            Text{
                id:playersPoint;
                width:300;
                anchors.verticalCenter: parent.verticalCenter;
                horizontalAlignment:Text.AlignHCenter;
                font.family: "Helvetica [Cronyx]";
                text:"";
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
                font.family: "Helvetica [Cronyx]";
                font.pixelSize: 20;
            }
            Rectangle{
                id:playerColor;
                anchors.verticalCenter: parent.verticalCenter;
                width:30;
                height:30;
                radius: 5;
                color:"white";
            }
            Text{
                anchors.verticalCenter: parent.verticalCenter;
                horizontalAlignment:Text.AlignHCenter;
                text:" 2.Click neighbor to attack.      ";
                font.family: "Helvetica [Cronyx]";
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
                    text:"End Turn";
                    font.family: "Helvetica [Cronyx]";
                    font.pixelSize:23;
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        gameMap.endTurn();
                        for(var i=0;i<rep.model;i++){
                            if(gameMap.getDice(i)==1)
                                imageRep.itemAt(i).source="Dice_20.png";
                            else
                                imageRep.itemAt(i).source="Transparent_20.png";
                        }
                        for(i=0;i<rep.model;i++){rep.itemAt(i).color=gameMap.getColor(i);}
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
        id:welcomeWindow
        z:21;
        color:"white";
        anchors.top: parent.top; anchors.horizontalCenter: parent.horizontalCenter; anchors.margins: 10;
        width:grid.width;
        height:grid.height+realTimeStatus.height+playerNotify.height;
        Rectangle{
            id:firstSubwelcomeWindow;
            anchors.left: parent.left;
            width:grid.width/3;
            height:welcomeWindow.height;
            Grid {
                id:welcomePicture;
                y:firstSubwelcomeWindow.height/3.8;
                anchors.horizontalCenter: parent.horizontalCenter;
                columns: 3
                spacing: 2
                Rectangle { color: "#FF6666"; width: 50*1.5; height: 50*1.5 }
                Rectangle { color: "#FFFF66"; width: 20*1.5; height: 50*1.5 }
                Rectangle { color: "#99CC66"; width: 50*1.5; height: 20*1.5 }
                Rectangle { color: "#99CCFF"; width: 50*1.5; height: 50*1.5 }
                Rectangle { color: "#CCFFFF"; width: 10*1.5; height: 10*1.5 }
            }
            Rectangle{
                id:startRectangle;
                y:firstSubwelcomeWindow.height/1.46;
                height:40;
                anchors.horizontalCenter: parent.horizontalCenter;
                Row{
                    height:40;
                    anchors.horizontalCenter: parent.horizontalCenter;
                    Image{
                        source:"Dice_40.png";
                    }
                    Rectangle{
                        id:startButton;
                        height:40;
                        width:150;
                        radius: 5;
                        border.color: "white"
                        color:"#6699CC";
                        Rectangle{
                            anchors.verticalCenter: parent.verticalCenter;
                            anchors.horizontalCenter: parent.horizontalCenter;
                            height:32;
                            width:142;
                            radius:3;
                            color:"#99CCFF";
                        }
                        Text{
                            id:startText
                            anchors.verticalCenter: parent.verticalCenter;
                            anchors.horizontalCenter: parent.horizontalCenter;
                            text:"Start";
                            font.pixelSize: 25;
                            font.family: "Helvetica [Cronyx]";
                            color:"#666699";
                            font.bold: true;
                        }
                        MouseArea{
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: {
                                startButton.color = "#330066";
//                                startText.font.pixelSize = 30;
                                startText.font.italic = true;
                            }
                            onExited: {
                                startButton.color = "#6699CC";
//                                startText.font.pixelSize = 25;
                                startText.font.italic = false;
                            }
                            onClicked:{
                                if(gameMap.getStatus()===0){
                                    gameMap.initialize();
                                    for(var i=0;i<rep.model;i++){
                                        if(gameMap.getDice(i)==1)
                                            imageRep.itemAt(i).source="Dice_20.png";
                                        else
                                            imageRep.itemAt(i).source="Transparent_20.png";
                                    }
                                    for(i=0;i<rep.model;i++){rep.itemAt(i).color=gameMap.getColor(i);}
                                    playerColor.color=gameMap.getPlayerColor();
                                    welcomeWindow.z=-5;
                                }
                            }
                        }
                    }
                }
            }
       }
       Rectangle{
           id:secondSubwelcomeWindow;
           anchors.left:firstSubwelcomeWindow.right;
           width:welcomeWindow.width-firstSubwelcomeWindow.width;
           height:welcomeWindow.height;
           Column{
               anchors.verticalCenter: parent.verticalCenter;
               anchors.horizontalCenter: parent.horizontalCenter;
               Image{
                   width:secondSubwelcomeWindow.width;
                   height:secondSubwelcomeWindow.width*0.4;
                   source:"Header.png"
               }
               Rectangle{
                   width:secondSubwelcomeWindow.width;
                   height:50;
                   Row{
                       anchors.horizontalCenter: parent.horizontalCenter
                       Repeater{
                           id :selectNumber
                           model:5;
                           Rectangle{
                               height:50;
                               width:50;
                               border.color: "white";
                               color:"#CC9933";
                               radius: 5;
                               Rectangle{
                                   id:playerAmountRec
                                   anchors.verticalCenter: parent.verticalCenter;
                                   anchors.horizontalCenter: parent.horizontalCenter;
                                   height:40;
                                   width:40;
                                   radius: 20;
                                   color:"#FFFF99";
                               }
                               Text{
                                   id:playerAmount
                                   anchors.verticalCenter: parent.verticalCenter;
                                   anchors.horizontalCenter: parent.horizontalCenter;
                                   text:index+2;
                                   font.family: "Helvetica [Cronyx]";
                                   font.pixelSize: 20;
                                   font.bold: true
                                   color:"#000000";
                               }
                               MouseArea{
                                   anchors.fill: parent
                                   hoverEnabled: true
                                   onEntered: {
                                       playerAmountRec.color="#CC9933";
                                   }
                                   onExited: {
                                       playerAmountRec.color="#FFFF99";
                                   }

                                   onClicked: {
                                       gameMap.setPlayer(index+2);
                                       for(var i=0;i<selectNumber.model;i++)
                                       selectNumber.itemAt(i).color = "#CC9933";
                                       color = "#FFFF99";
                                   }
                               }
                           }
                       }
                       Rectangle{
                           height:50;
                           width:200;
                           radius: 5;
                           border.color: "white";
                           color:"#CCCC00";
                           Text{
                               anchors.verticalCenter: parent.verticalCenter;
                               anchors.horizontalCenter: parent.horizontalCenter;
                               text:"Players";
                               font.family: "Helvetica [Cronyx]";
                               font.pixelSize: 30;
                               font.bold: true;
                               color:"#666600";
                           }
                       }
                   }
               }
           }
       }
    }
    Rectangle{
        z:-10;
        id:finalWindow;
//        color:"white";
        anchors.top: parent.top; anchors.horizontalCenter: parent.horizontalCenter; anchors.margins: 10;
        width:welcomeWindow.width;
        height:welcomeWindow.height;
        color:"#FFFF00";
        Rectangle{
            height:finalWindow.height/1.1;
            width:finalWindow.width/1.1;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.horizontalCenter: parent.horizontalCenter;
            radius:50;
            color:"#FFFF99";
            Column{
                anchors.verticalCenter: parent.verticalCenter;
                anchors.horizontalCenter: parent.horizontalCenter;
                width:parent.width;
                Row{
                    Text{
                        anchors.verticalCenter: parent.verticalCenter;
                        id:finnalMessage;
                        font.family: "Helvetica [Cronyx]";
                        text:"  Winner :  ";
                        font.pixelSize: 70;
                        font.bold: true;
                        color:"#009966";
                    }
                    Rectangle{
                        id:winnerColor;
                        anchors.verticalCenter: parent.verticalCenter;
                        width:50;
                        height:50;
                        radius: 10;
                        border.color: "white";
                        border.width: 5;
                        color:"black";
                    }
                }
                Text{
                    text:"  Congratulations!";
                    font.family: "Helvetica [Cronyx]";
                    font.pixelSize: 70;
                    font.bold: true;
                    color:"#009966";
                }
                Rectangle{

                    height:100;
                    width:parent.width;
                    color:"#FFFF99";
              //      ColorAnimation on color{ from: "white"; to: "black"; duration: 20000 }
                    Row{

                        anchors.verticalCenter: parent.verticalCenter;
                        anchors.horizontalCenter: parent.horizontalCenter;
                       // width:parent.width;
                      //  height:100;
                        Rectangle{
                            id:restartButton;
                            width:200;
                            height:50;
                            radius:10;
                            border.color: "white";
                            color:"#FF9933";
                            Text{
                                anchors.verticalCenter: parent.verticalCenter;
                                anchors.horizontalCenter: parent.horizontalCenter;
                                text:"Restart";
                                font.family: "Helvetica [Cronyx]";
                                font.bold: true;
                                font.pixelSize: 20;
                            }
                            MouseArea{
                                anchors.fill: parent
                                hoverEnabled: true
                                onEntered: {
                                    restartButton.color = "#FFFF00";
                                }
                                onExited: {
                                    restartButton.color = "#FF9933";
                                }
                                onClicked: {
                                    if(gameMap.getStatus()===2){
                                        gameMap.initialize();
                                        for(var i=0;i<rep.model;i++){
                                            if(gameMap.getDice(i)==1)
                                                imageRep.itemAt(i).source="Dice_20.png";
                                            else
                                                imageRep.itemAt(i).source="Transparent_20.png";
                                        }
                                        for(i=0;i<rep.model;i++){rep.itemAt(i).color=gameMap.getColor(i);}
                                        finalWindow.z=-10;
                                    }
                                }
                            }
                        }
                        Rectangle{
                            width:100;
                            height:50;
                            color:"#FFFF99";
                        }
                        Rectangle{
                            id:quitButton;
                            width:200;
                            height:50;
                            radius:10;
                            border.color: "white";
                            color:"#FF9933";
                            Text{
                                anchors.verticalCenter: parent.verticalCenter;
                                anchors.horizontalCenter: parent.horizontalCenter;
                                font.family: "Helvetica [Cronyx]";
                                text:"Quit";
                                font.bold: true;
                                font.pixelSize: 20;
                            }
                            MouseArea{
                                anchors.fill: parent
                            }
                        }
                    }
                }
            }


        }
    }
}
