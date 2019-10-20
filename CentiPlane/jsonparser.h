#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <QInputDialog>
class JsonParser
{
public:
    JsonParser();
    bool    GetOptReload();
    void    SetOptReload(bool opt);
    QString GetMainXPDir();
    void    SetMainXPDir(const QString &md);
    bool    GetRestartOption();
    void    SetRestartOption(bool opt);
    void    AddXPLocation(QString newLoc);
    void    ChooseDefaultXPLocation();
    QStringList GetXPLocations();

private:
    //objects for instance as group
    QJsonArray instances;
    QJsonArray xpLocations;
    bool isInstance;
    //objects for instance
    QString xpLocation,custAircrat,custScenery,commandLineOptions;
    //objects for appData
    QJsonObject appData;
    QJsonObject instanceData;
    bool optReloadXPLocsAtStart,restartAtPrevious;
    //functions
    void SaveAppData();
    void ReadAppData();
    void BuildDataObject();
    void BuildXPArrayFromList(const QVector<QString> &list);


};

#endif // JSONPARSER_H
