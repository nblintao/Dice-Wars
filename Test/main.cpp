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
    view.setTitle("Dice War");
    view.setSource(QUrl("qrc:///main.qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    if (QGuiApplication::platformName() == QLatin1String("qnx") ||
          QGuiApplication::platformName() == QLatin1String("eglfs")) {
        view.showFullScreen();
    } else {
        view.setMaximumSize(QSize(850,500));
        view.setMinimumSize(QSize(850,500));
        view.show();
    }
    return app.exec();
}
