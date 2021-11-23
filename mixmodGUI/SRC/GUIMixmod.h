/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMixmod.h  description
    copyright            : (C) MIXMOD Team - 2001-2015
    email                : contact@mixmod.org
 ***************************************************************************/

/***************************************************************************
    This file is part of MIXMOD

    MIXMOD is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MIXMOD is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MIXMOD.  If not, see <http://www.gnu.org/licenses/>.

    All informations available on : http://www.mixmod.org
***************************************************************************/
#ifndef __GUIMIXMOD_H__
#define __GUIMIXMOD_H__

#include <QtGui>
#include <QTranslator>
#include <QTreeView>

#include "GUIUtil.h"
#include "GUIMTreeModel.h"
#include "GUIMTreeDelegate.h"
#include "mixmod_mvc/TreeItem.h"
#include "mixmod_iostream/IOStreamUtil.h"

#include "GUIMProjectCreator.h"
#include "GUIMMetaData.h"
#include "GUIMConverter.h"
#include "GUIMAboutUs.h"
#include "GUIMGraphicManager.h"

//#include "modeltest.h"
//class GUITreeItem ;

class GUIMixmod : public QMainWindow {
	Q_OBJECT

public :

	// Coplien
	explicit GUIMixmod( QWidget* = 0, Qt::WindowFlags = 0 );
	//GUIMixmod( const GUIMixmod & );
	virtual ~GUIMixmod();
	//const GUIMixmod& operator=( const GUIMixmod& );

	GUIMGraphic * getGraphic(int index);

protected :

	virtual void changeEvent( QEvent* );

private slots :

	void fillTree(XEM::ClusteringMain * cMain = NULL);

	// call by menu
	bool fileSaveProject();
	bool loadInput();
	bool loadProjectFile(  );
	bool fileSaveProjectAs();
	void fileQuit();

	void newProjectFromInput();
	void newProjectClassification();
	void newProjectDiscriminantAnalysis();
	void newProjectOther();

	void projectProjectOption();
	void projectCloseProject();

	void executeExecute();
	void executeCleanOutput();
	void executeExecuteCurrentStep();

	void graphicsCreate();

	void changeWorkDirectory();

	void preferencesLanguage();
	void preferencesGraphicsSettings();

	void convert();
	void aboutUs();

	void helpMixmodHelp();
	void helpAboutUs();

	void choiceOutputToClean();
	void addGraphicInView(int indexGraphic, int indexVariable );
	void deleteGraphicInView(int);

private : // functions

	void reinitCreator( XEM::MVC::RootTreeItem::ProjectType ) ;

	void closeEvent( QCloseEvent* );

	void readSettings();
	void writeSettings();

	bool maybeSave();

	///save File in XML
	bool saveProject( const QString& );

	void loadAllLanguages();

	void createActions();
	void createMenus();
	void createStatusBar();
	void createBackground();
	void createToolBars();

private : // parameters

	/****** For MV Prog ******/
	// _treeView is the QT View
	QTreeView* _treeView ;

	// _treeModel contains MIXMOD data
	GUIMTreeModel* _treeModel ;

	GUIMTreeDelegate* _treeDelegate ;

//TODO testing
	//ModelTest* _modelTest ;

	/*************************/

	/****** Creators ******/
	GUIMProjectCreator* _projectCreator ;
	GUIMGraphicManager _managerGraphics;
	/**********************/

	// the current project
	XEM::MVC::RootTreeItem* _currentProject ;
	bool _projectRun ;

	// for Settings
	int _xWindowPosition ;
	int _yWindowPosition ;
	int _windowWidth ;
	int _windowHeight ;

	QString _organisationName ;
	QString _applicationName ;
	QString _applicationVersion ;

	// for translation
	QString _currentLanguage ;
	QString _defaultLanguage ;
	QString _locale ;
	QTranslator* _translator ;

	QString _currentInputFileName ;

	/****** All Menus ******/
	QMenu* _fileMenu ;
	//QMenu* _editMenu ;
	QMenu* _project_newProject ;
	//QMenu* _project_OpenRecentProject ; // it is a sub menu of project menu
	QMenu* _executeMenu ;
	QMenu* _graphicsMenu ;
	QMenu* _preferencesMenu ;
	QMenu* _preferences_language ;
	QMenu* _toolsMenu ;
	QMenu* _helpMenu ;
	QToolBar *fileToolBar;
	QToolBar *editToolBar;
	/***********************/
	/****** All menus Actions ******/
	// in Project menu
	// in new Project submenu
	QAction* _project_newProject_fromInput ;
	QAction* _project_newProject_classification ;
	QAction* _project_newProject_discriminantAnalysis ;
	QAction* _project_newProject_other ;
	// end of submenu
	QAction* _project_openProject ;
	QAction* _project_saveProject ;
	QAction* _project_saveProjectAs ;
	QAction* _project_projectOption ;
	QAction* _project_closeProject ;
	QAction* _file_quit ;
	// in Execute menu
	QAction* _execute_execute ;
	QAction* _execute_cleanOutput ;
	QAction* _execute_executeCurrentStep ;
	// in Graphics
	QAction* _graphics_create ;
	// in Preferences menu
	QActionGroup* language_group ;
	QVector<QAction*> _preferences_language_all ;
	QAction* _preferences_graphicsSettings ;
	QAction * _preferences_workDirectory;
	// in Tool Menu
	QAction * _converter ;
	// in Help menu
	QAction* _help_mixmodHelp ;
	QAction* _help_aboutUs ;
	/******************************/
	//background
	QWidget *widgetBackground;
	QLabel * presentation;

	static const QString languagesDir ;
};

#endif // __GUIMIXMOD_H__
