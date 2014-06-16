#include <QApplication>
#include <QQmlApplicationEngine>
#include "person.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();

  /*
    Person tmpPerson;
    tmpPerson.setName("Tom");
    tmpPerson.setAge(25);
    QDeclarativeView qmlView;
    qmlView.rootContext()->setContextProperty("ps",&tmpPerson);
    //qmlView.setSource(QUrl::fromLocalFile("../UICtest/UICtest.qml"));
    qmlView.setSource(QUrl::fromLocalFile("../main.qml"));
    qmlView.show();
    return a.exec();

    */

}
