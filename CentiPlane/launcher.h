#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QProcess>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QString>
#include <QDebug>

class Launcher: public QObject
{
 Q_OBJECT

public:
    Launcher();
    ~Launcher();
private:
    void StartXPlane();
};

#endif // LAUNCHER_H
