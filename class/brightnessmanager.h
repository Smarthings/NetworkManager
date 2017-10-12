#ifndef BRIGHTNESSMANAGER_H
#define BRIGHTNESSMANAGER_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QFile>

class BrightnessManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 brightness READ brightness WRITE setBrightness NOTIFY brightnessChanged)

public:
    explicit BrightnessManager(QObject *parent = nullptr);

public slots:
    void setBrightness(quint16 value);

Q_SIGNALS:
    void brightnessChanged();

protected:
    quint16 brightness();
};

#endif // BRIGHTNESSMANAGER_H
