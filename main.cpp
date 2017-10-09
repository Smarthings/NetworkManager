#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickStyle>
#include <QtQuick>
#include <QDebug>

#include "./class/networkwireless.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<NetworkWireless>("NetworkWireless", 1, 0, "NetworkWireless");
    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
