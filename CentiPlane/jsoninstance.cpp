/*
 * this json contains :
 *  a tag if it is a group of instances or an instance
 *   if it is a group it contains :
 *    an ordered list of instances in the form of a tree, completed by a place holder tag,x,y
 *     (the instances being a record of a dirname, a name, a category, x, y)
 *   if it is an instance it contains :
 *      XP location to use (variable contains Dir name or main)
 *      custom scenery to use (variable stores Dir name or main)
 *      aircraft directory to use (variable stores Dir name or main)
 *      special options yet to be defined
 *      the edited scenerypack.ini, stores it via the centifilemanager  (variable : main/)
 *      the command line options
 *      the plugins to be used
 */
#include "jsoninstance.h"

JsonInstance::JsonInstance():

  instanceItem(), //an object with name of instance(), col and line integers
  container(),
  instanceList(),
  pluginsList(),
  isGroup(false),
  hasSceneryPacks(false),
  name(""),
  commandLineOptions(""),
  xpLoc(""),
  sceneryLocation(""),
  acLocation(""),
  instances(nullptr)

{

}

void JsonInstance::ReadInstanceData(){
    QFile instanceFile;
    instanceFile.setFileName(myFileName);
    if (instanceFile.open(QIODevice::ReadOnly|QIODevice::ExistingOnly)){
       QByteArray fromFile=instanceFile.readAll();
       QJsonDocument jFile(QJsonDocument::fromJson(fromFile));
       container=jFile.object();
       isGroup=container["IsGroup"].toBool();
       if (isGroup){
           instanceList=container["ItemList"].toArray();
       }
       else{

       }
    }

}

void JsonInstance::WriteInstanceData(){
   QFile instanceFile;
   if (instanceFile.open(QIODevice::WriteOnly)){
       QJsonDocument jFile(container);
       instanceFile.write(jFile.toJson());
   }
}

void JsonInstance::SetMyFileName(QString name){
    myFileName=name;
}

bool JsonInstance::NewInstance(bool mkGroup){
    if (myFileName=="") return false;
    isGroup=mkGroup;
    if (isGroup) MakeGroupObject();
    else MakeInstanceObject();
    WriteInstanceData();
    return true;
}

bool JsonInstance::MakeGroupObject(){
    container["IsGroup"]=true;
    container["ItemList"]=instanceList;
}

bool JsonInstance::MakeInstanceObject(){
    container["IsGroup"]=false;
    container["HasSceneryPack"]=hasSceneryPacks;
    container["XPlaneToUse"]=xpLoc;
    container["CommandLineOptions"]=commandLineOptions;
    container["SceneryToUse"]=sceneryLocation;
    container["AircraftLocation"]=acLocation;
    container["PluginList"]=pluginsList;

}

void JsonInstance::AddToInstanceList(QString name,int line, int col){
     QJsonObject newInst;
     newInst["InstanceName"]=name;
     newInst["Line"]=line;
     newInst["col"]=col;
     instanceList.append(newInst);
}

void JsonInstance::ReplaceItem(QString name, int line, int col){

}

void JsonInstance::AddToPluginList(QString pluginName){

}
void JsonInstance::RetrieveFromPluginList (QString pluginName){}

void JsonInstance::HasSceneryPacks(bool scenery){}
void JsonInstance::SetCommandLineOptions(QString options){}
void JsonInstance::SetXPlaneToLaunch(QString XPDir){}
void JsonInstance::SetSceneryLoc(QString scLoc){}
void JsonInstance::SetAircraftLoc(QString acLoc){}
QString JsonInstance::GetCommandLineOptions(){}
QString JsonInstance::GetXPlaneToLaunch(){}
QString JsonInstance::GetSceneryLoc(){}
QString JsonInstance::GetAircraftLoc(){}

