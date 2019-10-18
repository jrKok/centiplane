#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include "CentiFileManager.h"
#include "launcher.h"
#include "jsonparser.h"
#include <QCoreApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
private:
    CentiFileManager files;
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *lowerButtonLayout;
    QPushButton *quit,*launchXP;
    JsonParser json;

    void BuildContent();
    void GetMainXPLocation();

    QMenu *FileMenu,*EditMenu,*ParametersMenu,*InstanceMenu;
    QAction *actExit;
    QAction *actLaunchXP;
    QAction *actEditInstance;
    QAction *actSceneryPackEditor;
    QAction *actNewInstance;
    QAction *actDeleteInstance;
    QAction *actCreateGroup;
    QAction *actSelectActiveXP;
    QAction *actSetParamIcon;
    QAction *actSetParamAdvanced;//Determines if advanced Instance settings should be active on create/modify
    QAction *actSetParamXPlocs;
    void CreateMenus();
    void CreateActions();
};

#endif // MAINWINDOW_H
