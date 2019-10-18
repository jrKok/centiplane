#ifndef INSTANCE_H
#define INSTANCE_H

#include <QString>
#include <QVector>

class instance
{
public:
    instance();
    static QString xpLocation,lineArguments,sceneryLocation,aircraftLocation;
    static QVector<QString> addPlugins,removePlugins;
private:

};

#endif // INSTANCE_H
