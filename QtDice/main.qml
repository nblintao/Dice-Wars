/*import QtQuick 2.2
import QtQuick.Controls 1.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }

    Rectangle {
        id: redSquare
        width: 120; height: 120
        anchors.top: parent.top; anchors.left: parent.left; anchors.margins: 10
        color: "red"
    }

}*/

// UICtest.qml
import Qt 4.7
Rectangle {
    width: 640
    height: 480
    Text { text: "Person name:" + ps.name; }
    Text { y: 20; text: "Person age:" + ps.age; }
    Rectangle{ x: 20; y: 40;  width: 20; height: 20; color: ps.getColor();}
    MouseArea{
        anchors.fill: parent;
        // 当鼠标按下后改变名字和年龄
        onClicked: { ps.changeNameAndAge(); }
    }
}
