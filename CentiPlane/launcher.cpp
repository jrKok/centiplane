/*
 * this class launches X Plane.
 * It launches X Plane.exe at a default location, or one that it is told
 * can transmit command line options
 * launches as external independant process or as a traced process (to allow subsequent review of the instance)
 *
 * it resolves the customization as follows :
 *  finds which X Plane copy to use, default if not specified
 *  makes a symlink to prefences in the instances folder
 *  resolves the custom scenery to use, default is the
 *
 */
#include "launcher.h"
#include "CentiFileManager.h"

Launcher::Launcher():QObject()
{
StartXPlane();
}

Launcher::~Launcher(){

}

void Launcher::StartXPlane(){
    qDebug()<<"launch XP";
    QString xpName="file:///";
    xpName=xpName+CentiFileManager::GetMainXPlaneDir()+"/"+"X-Plane.exe";
    qDebug()<<xpName;
    QDesktopServices::openUrl(QUrl(xpName,QUrl::TolerantMode));
/*QProcess *proc=new QProcess(this);
proc->setWorkingDirectory(QString(CentiFileManager::GetMainXPlaneDir()+"/"));
proc->setProgram("X-Plane.exe");
proc->setArguments({""});
proc->setStandardOutputFile(QProcess::nullDevice());
proc->setStandardErrorFile(QProcess::nullDevice());
qint64 pid;
proc->startDetached(&pid);*/
}
