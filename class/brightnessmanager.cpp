#include "brightnessmanager.h"

BrightnessManager::BrightnessManager(QObject *parent) : QObject(parent)
{

}

quint16 BrightnessManager::brightness()
{
    QFile readBrightness("/sys/class/backlight/rpi_backlight/brightness");
    if (!readBrightness.open(QIODevice::ReadOnly))
        return 0;

    QString line = readBrightness.readLine();
    return line.toUInt();
}

void BrightnessManager::setBrightness(quint16 value)
{
    QString command = QString("/bin/sh -c \"echo %1 > /sys/class/backlight/rpi_backlight/brightness\"").arg(value);
    QProcess _brightness;
    _brightness.start(command);

    if (!_brightness.waitForFinished())
        qDebug() << "Error" << _brightness.errorString();
}
