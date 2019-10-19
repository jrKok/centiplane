#ifndef INSTANCE_H
#define INSTANCE_H

#include <QString>
#include <QVector>
#include "jsoninstance.h"

class instance
{
public:
    instance();
    ~instance();
    static QString xpLocation,lineArguments,sceneryLocation,aircraftLocation;
    static QVector<QString> addPlugins,removePlugins;
    bool SelectInstance(QString instanceName);
    bool SelectGroup(QString groupName);
    void MakeMainGroup();
    void MakeDefaultInstance();
    bool ExecuteInstance();
private:

    JsonInstance *jsonGroup,*jsonInstance;
    bool hasSelectedInstance;
    QString currentGroupName,currentInstanceName;

};

#endif // INSTANCE_H
