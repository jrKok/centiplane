#ifndef CENTIFILEMANAGER_H
#define CENTIFILEMANAGER_H


#include "Windows.h"
#include <QDebug>
#include <QVector>
#include <QString>
#include <QDir>
#include <QDirIterator>
#include <stdio.h>
#include <lmcons.h>
#include "winreg.h"
#include "processthreadsapi.h"
#pragma comment(lib, "advapi32")

class CentiFileManager
{
public:
    CentiFileManager();
    static QVector<QString> readXPlaneLocations();
    static QString GetMainXPlaneDir();
    static QString GetMyDir();
    static QDir applicationDir,mainXPlaneDir, customACDir,customSceneryDir;
    bool IsDeveloperModeEnabled();
    bool IsRunInAdmin();
    void SetMainXPDir(const QString &md);
};

#endif // CENTIFILEREADER_H
