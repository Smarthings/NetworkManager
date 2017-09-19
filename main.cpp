#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QCoreApplication>
#include <QNetworkConfiguration>
#include <QNetworkConfigurationManager>
#include <QNetworkSession>
#include <QList>
#include <QDebug>
#include <QProcess>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QString command = "iw wlp3s0 scan dump";
    QProcess scan_wifi;
    scan_wifi.start(command);

    if (!scan_wifi.waitForFinished())
        return -1;

    QByteArray result_scan = scan_wifi.readAll();


//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

    return app.exec();
}
