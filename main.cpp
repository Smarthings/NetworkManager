#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QCoreApplication>
#include <QNetworkConfiguration>
#include <QNetworkConfigurationManager>
#include <QNetworkSession>
#include <QList>
#include <QDebug>
#include <QProcess>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QString command = "iw wlp3s0 scan dump";
    QProcess scan_wifi;
    scan_wifi.start(command);

    if (!scan_wifi.waitForFinished())
        return -1;

    QRegularExpression reg_SIGNAL("(signal: .*)");
    QRegularExpression reg_SSID("(SSID: .*)");
    QRegularExpression reg_AUTHTYPE("(Authentication suites: .*)");
    QRegularExpression reg_FINAL("BSS .*\)$");

    QList<QStringList> list;
    QStringList str_list;

    while (!scan_wifi.atEnd()) {
        QString line = scan_wifi.readLine();

        QRegularExpressionMatch match_SIGNAL = reg_SIGNAL.match(line);
        if (match_SIGNAL.hasMatch())
            str_list.append(match_SIGNAL.captured());

        QRegularExpressionMatch match_SSID = reg_SSID.match(line);
        if (match_SSID.hasMatch())
            str_list.append(match_SSID.captured());

        QRegularExpressionMatch match_AUTHTYPE = reg_AUTHTYPE.match(line);
        if (match_AUTHTYPE.hasMatch()) {
            str_list.append(match_AUTHTYPE.captured());
            list.append(str_list);
            str_list.clear();
        }
    }

    for (auto &it : list) {
        qDebug() << it;
    }

    /*QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;*/

    return 0;
    //return app.exec();
}
