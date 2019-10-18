/*
 * the launcher does the following :
 * maintains a list of global settings to launch x plane. Each set of settings define an instance (of X Plane).
 * for each setting the user can define :
 *  X Plane. exe directory to be used (or its folder) : XPDir
 *  preferences at the time X Plane was shut down, a simlink is created in the XPDir,
 *  a list of plugins to be used (or discarded), the plugins are moved to or removed from the ressources/plugins folder
 *  an instance of scenerypacks.ini, copied to the current custom scenery location
 *  for advanced users, different custom scenery locations can be defined, in that case a simlink will be created in X Plane's current folder
 *  for advances users, different aircraft locations can be defined, a simlink will be created if required
 *
 * The scenerypacks.ini can be directly edited, by disabling scenery. The program knows how to differentiate libs and sceneries.
 * The plugin list can be edited by telling what plugin to use (checkmarks), the others will be removed.
 *
 * The program is been told to store all parameters in one directory. For each instance created, a sub directory is created.
 * Each subdirectory is either an instance or encapsulates other subdirectories.
 * An instance sub directory contains :
 *  1 - a copy of output/preferences (to which a simlink will be created in the current X-Plane 11/output
 *  2 - a json file which describes :
 *    X Plane copy to use
 *    plugin list to use, to remove
 *    the custom scenery location to use
 *    the aircraft location to use
 *    command line options to use for x plane
 *  3 - a copy of scenerypacks.ini
 *
 * An instance weighes about 400ko.
 *
 * The first time the program is launched, the user will be asked for the X Plane directory if several are found.
 * The main directory for data (centiplane's data directory) will contain :
 *  a default instance (called default, cannot be removed), a copy of preferences when the
 *  a list of custom scenery directories
 *  a list of aircraft directories
 * All these parameters of the instance can be edited in a specialized window, where the advanced option puts known X Plane copies, Aircraft copies, scenery copies
 *
 * The program shows all instances as small icons, underscored by the name, the icon depicting the current plane model in use and its png (if it exists)
 * Functionality : new instance, remove instance, edit instance
 *
 * the window for editing an instance has :
 *  a list of active plugins,
 *  a list of discarded plugins
 *  the list of sceneries with their status, enabled or disabled. libraries are also highlighted
 *  a list of
 * buttons to validate, cancel, disable all scenery (first click disables only added scenery, next click libraries as well, next click all except global airport, next everything)
 *  enable all scenery
 *  advanced options :
 *   command line options for X Plane
 *   select scenery location
 *   select aircraft location
 *   select X Plane location
 *
 * a window for maintaining all X Plane copies : update a copy (with advanced options)
 * move a copy, eventually suppress a copy
 *  advanced options for
 *   launch plane maker
 *   launch airfoil maker
 *
 *
 */

#include "mainwindow.h"
#include <QtWidgets>

/*
 * This window is launched on start of the program. In the upper part are icons and the title of each instance.
 * A double click on the icon will launch X Plane by help of the launcher object.
 * A simple click will select it and highlight buttons.
 * Additional buttons allow to launch X Plane maintenance, Edit instance, create new instance, group instances
 * The code here essentially maintains display of the buttons and allows for grouping instances.
 * Grouping an instance is creating a group, then drag drop instances onto that group. Multiselect, then group should also be possible.
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      files(),
       centralWidget(new QWidget(parent)),
       mainLayout (new QVBoxLayout(parent)),
       lowerButtonLayout(new QHBoxLayout(parent)),
       quit (new QPushButton("quit",parent)),
       launchXP(new QPushButton("Launch X Plane",parent)),
       json()
{
    qDebug()<<"main Window";
    //Launcher startXP;
    QString xpD=json.GetMainXPDir();
    if (xpD=="") GetMainXPLocation();
    else files.SetMainXPDir(xpD);
    BuildContent();
    CreateActions();
    CreateMenus();
}

MainWindow::~MainWindow()
{

}

void MainWindow::BuildContent(){
    setCentralWidget(centralWidget);
    QString backgroundString="background-image:url";
    QString generalbackground=QString(backgroundString+"("+files.GetMainXPlaneDir()+"/Resources/bitmaps/def_file.png"+")");
    qDebug()<<generalbackground;
    centralWidget->setStyleSheet(generalbackground);
    mainLayout->addWidget(centralWidget);

    lowerButtonLayout->addWidget(quit);
    lowerButtonLayout->addWidget(launchXP);
    centralWidget->setLayout(lowerButtonLayout);

    connect(quit,SIGNAL(released()),this,SLOT(close()));
}

void MainWindow::GetMainXPLocation(){
    QInputDialog input(this);
    input.setInputMode(QInputDialog::TextInput);
    input.setOption(QInputDialog::UseListViewForComboBoxItems,true);
    input.setComboBoxItems(json.GetXPLocations());
    input.setWindowTitle("X-Plane locations");
    input.setLabelText("Select the main X Plane folder");

    bool okb=input.exec();
    QString xpDir=input.textValue();
    qDebug()<<"got this textValue"<<xpDir;
    input.done(okb);
    // QString xpDir=input.getItem(this,"X Plane Locations","Select the main X Plane Directory ;",json.GetXPLocations(),0,false,&okb);
    if (okb&&xpDir!=""){
        json.SetMainXPDir(xpDir);
        files.SetMainXPDir(xpDir);
    }
}
void MainWindow::CreateActions(){
 actExit=new QAction("Quit",this);
 actExit->setToolTip("doesn't launch X Plane and quits");
 connect(actExit,SIGNAL(triggered()),this,SLOT(close()));
}

void MainWindow::CreateMenus(){
    FileMenu=menuBar()->addMenu("File");
    FileMenu->addAction(actExit);
}
