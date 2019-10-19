  /*
 * This class can read text files to vector,
 * write string vector to textfile, manages file names
 * stores all needed files for running centiplane,
 * returns directories, file names through static functions
 * evokes file browsers for dirs, names with presets as required
 *
 * The constructor
 *  looks for all xplane folders,
 *  loads aircraft folder locations
 *  loads custom scenery locations,
 *
 * Functions :
 *  maintain lists of those xplane folders, aircraft and custom scenery locations,
 *  stores them in arrays in global json file with the help of jsonparser
 *
 *  generates symlinks (checks if developer mode is on, elsewhere generates an error)
 *
 *  knows about groups and instances, checks integrity of structure of instances, groups
 *
 *  able to rename directories,
 */
#include "CentiFileManager.h"

QDir CentiFileManager::applicationDir=QDir();
QDir CentiFileManager::mainXPlaneDir=QDir();
QDir CentiFileManager::customACDir=QDir();
QDir CentiFileManager::customSceneryDir=QDir();


//Constructor

CentiFileManager::CentiFileManager()
{
applicationDir=QDir::current();
qDebug()<<applicationDir.path();
qDebug()<<"developer mode : "<<IsDeveloperModeEnabled();
qDebug()<<"Administrator  : "<<IsRunInAdmin();
}


// Use QDirIterator to find X Plane.exes

QVector<QString> CentiFileManager::readXPlaneLocations(){
    QVector<QString> XPLocs;
    qDebug()<<"Begin reading XPlane locations";
    QStringList xpName;
    xpName.append("X-Plane.exe");
    QFileInfoList roots=QDir::drives();
    bool found=false;

    for (auto drive:roots){
        qDebug()<<"searching on drive "<<drive.dir().path();
        QDirIterator findFile(drive.dir().path(),xpName,QDir::NoFilter,QDirIterator::Subdirectories);
        qDebug()<<"begin searching";
        while (findFile.hasNext()){
            findFile.next();
            if (findFile.fileName()=="X-Plane.exe")
            {
                found=true;
                QDir xpD(findFile.filePath());
                xpD.cdUp();
                XPLocs.append(xpD.path());
            }
        }
    }

    if (!found)
    {
        XPLocs.append("X-Plane is not installed on this drive");
        mainXPlaneDir=QDir();
        qDebug()<<"haven't found XPlane.exe";
    }

    return XPLocs;
}

QString CentiFileManager::GetMyDir(){
    return CentiFileManager::applicationDir.absolutePath();
}

QString CentiFileManager::GetMainXPlaneDir(){
    return mainXPlaneDir.path();
}

bool CentiFileManager::IsDeveloperModeEnabled() {
  HKEY hKey;
  auto err = RegOpenKeyExW(HKEY_LOCAL_MACHINE,LR"(SOFTWARE\Microsoft\Windows\CurrentVersion\AppModelUnlock)",0,KEY_READ,&hKey);
  if (err!=ERROR_SUCCESS)
     return false;
  DWORD value{};
  DWORD dwordSize = sizeof(DWORD);
  err = RegQueryValueExW(hKey,L"AllowDevelopmentWithoutDevLicense",nullptr,nullptr,reinterpret_cast<LPBYTE>(&value),&dwordSize);
  RegCloseKey(hKey);
  if (err!=ERROR_SUCCESS)
    return false;
  return value != 0;
}

bool CentiFileManager::IsRunInAdmin(){
    BOOL fRet = FALSE;
    HANDLE hToken = nullptr;
    if( OpenProcessToken( GetCurrentProcess( ),TOKEN_QUERY,&hToken ) ) {
        TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof( TOKEN_ELEVATION );
        if( GetTokenInformation( hToken, TokenElevation, &Elevation, sizeof( Elevation ), &cbSize ) ) {
            fRet = Elevation.TokenIsElevated;
        }
    }
    if( hToken ) {
        CloseHandle( hToken );
    }
    return fRet;
}

void CentiFileManager::SetMainXPDir(const QString &md){
    mainXPlaneDir=md;
}
