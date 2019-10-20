#ifndef JSONINSTANCE_H
#define JSONINSTANCE_H

#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QByteArray>
#include <QDebug>

class JsonInstance
{
public:
    JsonInstance();
    void SetMyFileName(QString name);
    bool loadInstance (QString instanceName);
    bool NewInstance (bool mkGroup);
    void ReadInstanceData();
    void WriteInstanceData();
    void AddToInstanceList(QString name,int line, int col);
    void ReplaceItem(QString name, int line, int col);
    void AddToPluginList(QString pluginName);
    void RetrieveFromPluginList (QString pluginName);
    void HasSceneryPacks(bool scenery);
    void SetCommandLineOptions(QString options);
    void SetXPlaneToLaunch(QString XPDir);
    void SetSceneryLoc(QString scLoc);
    void SetAircraftLoc(QString acLoc);
    QString GetCommandLineOptions();
    QString GetXPlaneToLaunch();
    QString GetSceneryLoc();
    QString GetAircraftLoc();

private:
    QString myFileName;
    QJsonObject instanceItem; //an object with name of instance, col and line integers
    QJsonObject container;
    QJsonArray instanceList,pluginsList;
    bool isGroup,hasSceneryPacks;
    QString name,commandLineOptions,xpLoc,sceneryLocation,acLocation;
    QStringList *instances;
    bool MakeGroupObject();
    bool MakeInstanceObject();
};

#endif // JSONINSTANCE_H
