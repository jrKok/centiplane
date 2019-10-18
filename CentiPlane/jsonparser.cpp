/*
 * this class reads the json application data
 * reads all initial variables from json file for centiplane
 * this json contains :

 *  a list of x plane copies
 *  a list of custom sceneries locations
 *  a list of aircraft locations
 *  a list of known plugins on users system
 *
 * finds all instances of XPlane.exe
 * compares with list in json file, if it finds a new one asks if it is copy or default.
 * Examins ressources/plugins to spot a new plugin
 */
#include "jsonparser.h"
#include "CentiFileManager.h"

JsonParser::JsonParser():
    instances(),
    isInstance(true),
    //objects for instance
    xpLocation(""),custAircrat(""),custScenery(""),commandLineOptions(""),
    //objects for appData
    appData(),
    instanceData(),
    optReloadXPLocsAtStart(false)

{
ReadAppData();
}

//Application Data Json Retrieve/Store

void JsonParser::SaveAppData(){
    if (xpLocation=="") return;
    QFile dataFile;
    QString dataFileName=QString(CentiFileManager::GetMyDir()+("/appData.json"));
    dataFile.setFileName(dataFileName);

    if (dataFile.open(QIODevice::WriteOnly)){
        //all data is already in appData object
        QJsonDocument data(appData);
        dataFile.write(data.toJson());
        qDebug()<<"wrote json to "<<dataFileName;
    }
}

void JsonParser::ReadAppData()
{
    QFile dataFile;
    QString dataFileName=QString(CentiFileManager::GetMyDir()+("/appData.json"));
    qDebug()<<dataFileName;
    dataFile.setFileName(dataFileName);

    if (dataFile.open(QIODevice::ReadOnly|QIODevice::ExistingOnly)){
       QByteArray fromFile=dataFile.readAll();
       QJsonDocument jFile(QJsonDocument::fromJson(fromFile));
       appData=jFile.object();
       //parse data
       optReloadXPLocsAtStart=appData["readXPLocs"].toBool();
       xpLocation=appData["XPDefault"].toString();
       xpLocations=appData["allXP"].toArray();
       qDebug()<<"read json as : "<<optReloadXPLocsAtStart;
       dataFile.close();
    }
    else {
        qDebug()<<"create new json file";
        BuildDataObject();
        SaveAppData();}

}

void JsonParser::BuildDataObject(){
    QVector<QString> locs=CentiFileManager::readXPlaneLocations();
    BuildXPArrayFromList(locs);
    xpLocation=CentiFileManager::GetMainXPlaneDir();
    if (xpLocation=="") return;
    appData["readXPLocs"]=optReloadXPLocsAtStart;
    appData["XPDefault"]=xpLocation;
    appData["allXP"]=xpLocations;
}


void JsonParser::BuildXPArrayFromList(const QVector<QString> &list){
        while(xpLocations.count()) {
             xpLocations.pop_back();
         }
    for (auto xploc: list){
              xpLocations.append(xploc);
    }
}
//AppData READ/WRITE

bool JsonParser::GetOptReload(){return optReloadXPLocsAtStart;}

void JsonParser::SetOptReload(bool opt){
    optReloadXPLocsAtStart=opt;
    appData["readXPLocs"]=optReloadXPLocsAtStart;
    SaveAppData();}

QStringList JsonParser::GetXPLocations(){
    QStringList locs;
    for (auto loc:xpLocations){
        locs.append(loc.toString());
    }
    return locs;
}

QString JsonParser::GetMainXPDir(){

    return xpLocation;
}

void JsonParser::SetMainXPDir(const QString &md){
    xpLocation=md;
    appData["XPDefault"]=xpLocation;
    SaveAppData();
}

void JsonParser::AddXPLocation(QString newLoc){
    xpLocations.append(newLoc);
    SaveAppData();
    appData["allXP"]=xpLocations;
}

//Other functions



