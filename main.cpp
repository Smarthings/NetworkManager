#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickStyle>
#include <QtQuick>
#include <QDebug>

#include "./class/networkmanager.h"
#include "./class/networkwireless.h"
#include "./class/networkwired.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<NetworkManager>("NetworkManager", 1, 0, "NetworkManager");
    qmlRegisterType<NetworkWireless>("NetworkWireless", 1, 0, "NetworkWireless");
    qmlRegisterType<NetworkWired>("NetworkWired", 1, 0, "NetworkWired");

    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
