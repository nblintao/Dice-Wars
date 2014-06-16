#include <QDir>
#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlFileSelector>
#include <QQuickView>
#include <QQmlContext>
#include "gamemap.h"
int main(int argc, char* argv[])
{
    QGuiApplication app(argc,argv);
    QQuickView view;

    GameMap gameMap;
    view.rootContext()->setContextProperty("gameMap",&gameMap);

    view.setSource(QUrl("qrc:///main.qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    if (QGuiApplication::platformName() == QLatin1String("qnx") ||
          QGuiApplication::platformName() == QLatin1String("eglfs")) {
        view.showFullScreen();
    } else {
        view.show();
    }
    return app.exec();
}
