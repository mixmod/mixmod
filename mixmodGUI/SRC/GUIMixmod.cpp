/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMixmod.cpp  description
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
#include "GUIMixmod.h"

#include <iostream>
#include <cstdlib> // include NULL

#include <QtGui>
#include <QDir>
#include <QStringList>
#include <QString>
#include <QDataStream>
#include <algorithm>

#include "GUIMProjectCreator.h"
#include "GUIMTreeView.h"
#include "mixmod/Utilities/Random.h"

const QString GUIMixmod::languagesDir = QString( ":/" );

GUIMixmod::GUIMixmod( QWidget* parent , Qt::WindowFlags flags )
	: QMainWindow( parent, flags ),
	  _treeView( NULL ), _treeModel( NULL ), _treeDelegate( NULL ), /*_modelTest(NULL),*/
	  _projectCreator( NULL ), _managerGraphics(this),
	  _currentProject( NULL ), _projectRun( false ),
	  _xWindowPosition( 0 ), _yWindowPosition( 0 ), _windowWidth( 800 ), _windowHeight( 600 ),
	  _organisationName( "???" ), _applicationName( "MixmodGUI" ), _applicationVersion("1.2.1"),
	  _translator( NULL ),
	  _currentInputFileName( "" ) {

	setWindowTitle( _currentInputFileName + _applicationName );
	_locale = QLocale::system().name();
	_defaultLanguage = _locale ;
	_currentLanguage = _defaultLanguage ;

	_translator = new QTranslator( this );
	_translator->load( QString( "mixmod_" ) + _currentLanguage, languagesDir );
	qApp->installTranslator( _translator );

	createActions();
	createMenus();
	createStatusBar();
	createToolBars();

	createBackground();

	readSettings();
	setStyleSheet("QMainWindow {background: white ; }");

	setWindowIcon(QPixmap(":/logo.png"));
}

GUIMixmod::~GUIMixmod() {
}

GUIMGraphic* GUIMixmod::getGraphic(int index) {
	if (_managerGraphics.hasGraphics()) {
		return _managerGraphics.getGraphic(index);
	}
	else {
		return NULL;
	}
}

void GUIMixmod::createBackground() {
	widgetBackground = new QWidget();
	QHBoxLayout * grille = new QHBoxLayout(widgetBackground);
	QPixmap back=QPixmap(":/logo.png");
	//back=back.scaledToWidth (_windowWidth, Qt::SmoothTransformation);
	QLabel * presentation = new QLabel();
	presentation->setWindowState(Qt::WindowMaximized);

	presentation->setPixmap(back);
	grille->addWidget(new QLabel());
	grille->addWidget(presentation);
	grille->addWidget(new QLabel());
	setCentralWidget( widgetBackground);
}

void GUIMixmod::changeEvent( QEvent *event ) {
	if( event->type() == QEvent::LanguageChange ) {
// 		_file_saveInput->setText( tr( "&Save input" ) );
// 		_file_saveInputAs->setText( tr( "Sa&ve input as" ) );
		_file_quit->setText( tr( "&Quit" ) );

		_project_newProject_fromInput->setText( tr( "&Project from input" ) );
		_project_newProject_classification->setText( tr( "&Classification" ) );

		_project_newProject_discriminantAnalysis->setText( tr( "&Discriminant analysis" ) );
		_project_newProject_other->setText( tr( "&Other" ) );

		_project_openProject->setText( tr( "&Open project" ) );
		_project_saveProject->setText( tr( "&Save project" ) );
		_project_saveProjectAs->setText( tr( "Sa&ve project as" ) );

		_project_projectOption->setText( tr( "&Project options" ) );
		_project_closeProject->setText( tr( "&Close project" ) );

		_graphics_create->setText( tr( "&Create" ) );

		_preferences_graphicsSettings->setText( tr( "&Graphics settings" ) );
		_preferences_workDirectory->setText( tr(  "Change &working directory" ) );

		_execute_execute->setText( tr( "E&xecute" ) );
		_execute_executeCurrentStep->setText( tr( "Execute current &step" ) );
		_execute_cleanOutput ->setText(  tr("&Clean output") );

		_converter->setText( tr( "&Converter" ) );

		_help_mixmodHelp->setText( tr( "&Mixmod help" ) );
		_help_aboutUs->setText( tr( "&About us" ) );

		_fileMenu->setTitle( tr( "&File" ) );
		//_projectMenu->setTitle( tr( "&Project" ) );
		_project_newProject->setTitle( tr( "&New project" ) );
		_graphicsMenu ->setTitle(  tr( "&Graphics")  );
		_preferencesMenu->setTitle( tr( "P&references" ) );
		_preferences_language->setTitle( tr( "&Language" ) );
		_toolsMenu->setTitle( tr( "&Tools" ) );

		_executeMenu->setTitle( tr( "E&xecute" ) );
		_helpMenu->setTitle( tr( "&Help" ) );

	}
	else {
		QWidget::changeEvent( event );
	}
}

// creates a new default projectCreator
void GUIMixmod::reinitCreator( XEM::MVC::RootTreeItem::ProjectType type ) {
	if( _projectCreator ) {
		disconnect( _projectCreator, SIGNAL( itemCreated() ), this, SLOT( fillTree() ) );
		delete _projectCreator ;
	}
	_projectCreator = new GUIMProjectCreator( type ) ;
	connect( _projectCreator, SIGNAL( itemCreated() ), this, SLOT( fillTree() ) );
}

// When closing Widget
void GUIMixmod::closeEvent ( QCloseEvent* event ) {
	if( maybeSave() ) {
		writeSettings();
		event->accept();
	}
	else {
		event->ignore();
	}
}

void GUIMixmod::readSettings() {
	//FIXME
	QSettings settings( _organisationName, _applicationName );
	QPoint pos = settings.value( "pos", QPoint ( _xWindowPosition, _yWindowPosition ) ).toPoint();
	QSize size = settings.value( "size", QSize ( _windowWidth, _windowHeight ) ).toSize();
	resize( size );
	move( pos );

	//current Directory
	QString pathWorkDirectory = settings.value( "workDirectory").toString();
	GUISettings::workDirectory.setPath(pathWorkDirectory);

	if ( !GUISettings::workDirectory.exists() ) {
		GUISettings::workDirectory.setPath(".");
	}
}

void GUIMixmod::writeSettings() {
	QSettings settings( _organisationName, _applicationName ); // must be the same
	settings.setValue( "pos", pos() );
	settings.setValue( "size", size() );
	settings.setValue( "workDirectory", GUISettings::workDirectory.absolutePath());
}

bool GUIMixmod::maybeSave() {
	if( _currentInputFileName.isEmpty() && _treeModel) { // TODO when XML done
		// TODO when ViewTree done
		QMessageBox::StandardButton ret ;
		ret = QMessageBox::warning( this, tr( "WARNING" ), // change name ?
		                            tr( "The document has been modified.\n"
		                                "Do you want to save your changes?" ),
		                            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel );
		if( ret == QMessageBox::Save ) {
			return fileSaveProject();
		}
		else if( ret == QMessageBox::Cancel ) {
			return false ;
		}
		else if (ret == QMessageBox::Discard) {
			close();
		}
	}
	return true ;
}

bool GUIMixmod::loadInput() {
	//load .mixmod file
	QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), GUISettings::workDirectory.absolutePath(), tr("Mixmod Files (*.mixmod);;All Files (*)"));

	if (!filename.isEmpty()) {
		try {

			XEM::ClusteringMain * cMain = XEM::IStream(filename.toStdString(), XEM::IOStreamFormat::XML, true);
			projectCloseProject();
			fillTree(cMain);
			QFileInfo info( filename );
			_currentInputFileName = info.canonicalPath() + QDir::separator() + info.baseName() ;
			setWindowTitle( _currentInputFileName + " - "+  _applicationName );

			return true;
		}
		catch(XEM::Exception* e) {
			QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Warning"), QObject::tr( e->what()),QMessageBox::Ok );
			msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);} QPushButton{background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");
			msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
			msgBox.exec();
		}
		catch(XEM::IOStreamErrorType errorType) {
			QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Warning"), QObject::tr( XEM::IOStreamErrorTypeToString(errorType).c_str() ),QMessageBox::Ok );
			msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);} QPushButton{background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");
			msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
			msgBox.exec();
		}
	}
}

bool GUIMixmod::loadProjectFile( ) {
	//load .mixmod file
	QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), GUISettings::workDirectory.absolutePath(), tr("Mixmod Files (*.mixmod);;All Files (*)"));

	if (!filename.isEmpty()) {
		try {

			XEM::ClusteringMain * cMain = XEM::IStream(filename.toStdString(), XEM::IOStreamFormat::XML);
			projectCloseProject();
			fillTree(cMain);
			_projectRun = false ;
			QFileInfo info( filename );
			_currentInputFileName = info.canonicalPath() + QDir::separator() + info.completeBaseName() ;
			setWindowTitle( _currentInputFileName  + " - "+  _applicationName );

			if (cMain->getOutput()) {
				_execute_execute->setEnabled(false);
				GUISettings::outputIsPresent = true;
				_execute_cleanOutput->setVisible(true);
				_graphics_create->setEnabled(true);
				_projectRun = true ;
				_execute_cleanOutput->setVisible(true);
			}
			return true;
		}
		catch(XEM::Exception* e) {
			QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Warning"), QObject::tr( e->what() ),QMessageBox::Ok );
			msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);} QPushButton{background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");
			msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
			msgBox.exec();
		}
		catch(XEM::IOStreamErrorType errorType) {
			QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Warning"), QObject::tr( XEM::IOStreamErrorTypeToString(errorType).c_str() ),QMessageBox::Ok );
			msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);} QPushButton{background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");
			msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
			msgBox.exec();
		}
	}
	else {
		return false ;
	}
}

bool GUIMixmod::saveProject( const QString& s ) {
	try {
		XEM::ClusteringMain * cMain = _treeModel->getClusteringMain(0);
		XEM::OStream(s.toStdString(), XEM::IOStreamFormat::XML, cMain);
	}
	catch(XEM::Exception* e) {
		QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Warning"), QObject::tr( e->what() ),QMessageBox::Ok );
		msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);} QPushButton{background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");
		msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
		msgBox.exec();
	}
	catch(XEM::IOStreamErrorType errorType) {
		QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Warning"), QObject::tr( XEM::IOStreamErrorTypeToString(errorType).c_str() ),QMessageBox::Ok );
		msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);} QPushButton{background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");
		msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
		msgBox.exec();
	}
	return true;
}


/*******************/
/****** SLOTS ******/
/*******************/

void GUIMixmod::fillTree(XEM::ClusteringMain * cMain) {
	projectCloseProject();
	if (cMain) {
		_treeModel = new GUIMTreeModel( _projectCreator, cMain , this );
	}
	else {
		_treeModel = new GUIMTreeModel( _projectCreator, this );
	}

	_treeDelegate = new GUIMTreeDelegate( this );
	_treeView = new GUIMTreeView( this );
	_treeView->setUniformRowHeights(true);
	_treeView->setModel( _treeModel );
	_treeView->setItemDelegate( _treeDelegate );
	_treeView->setStyleSheet(" QTreeView::branch:has-siblings:!adjoins-item { border-image: url(:/vline.png) 0; } QTreeView::branch:has-siblings:adjoins-item {border-image: url(:/branch-more.png) 0; } QTreeView::branch:!has-children:!has-siblings:adjoins-item {border-image: url(:/branch-end.png) 0;} QTreeView::branch:has-children:!has-siblings:closed, QTreeView::branch:closed:has-children:has-siblings {border-image: none; image: url(:/branch-closed.png); } QTreeView::branch:open:has-children:!has-siblings,QTreeView::branch:open:has-children:has-siblings  { border-image: none;  image: url(:/branch-open.png);} QTreeView::branch:open:has-children:!has-siblings,QTreeView::branch:open:has-children:has-siblings  { border-image: none;  image: url(:/branch-open.png); }");

	_currentProject = _treeModel->root() ;
	_treeView->close();
	//if
	_treeView->expandToDepth(2);
	_treeView->header()->setResizeMode(0,QHeaderView::ResizeToContents);
	_treeView->header()->setStyleSheet("QHeaderView:section {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:0 white, stop:1 #a0c8fa);}");
	//_treeView->setFocus();
	//setCentralWidget( _treeView );

	_project_saveProject->setEnabled(true);
	_project_saveProjectAs->setEnabled(true);

	QWidget* widget= new QWidget();
	QHBoxLayout * layout=new QHBoxLayout(widget);
	layout->addWidget(_treeView);

	widget->setFocus();
	setCentralWidget( widget );
	connect(_treeView, SIGNAL( cleanOutput() ), this, SLOT(choiceOutputToClean()));
	connect(_treeView, SIGNAL( addGraphic( int , int)), this, SLOT( addGraphicInView(int, int) ));
	connect(_treeView, SIGNAL( deleteGraphic( int )), this, SLOT( deleteGraphicInView(int) ));
}


bool GUIMixmod::fileSaveProject() {
	if (_treeModel) {
		if( _currentInputFileName.isEmpty() ) {
			return fileSaveProjectAs();
		}
		else {
			return saveProject( _currentInputFileName );
		}
	}
	return false;
}

bool GUIMixmod::fileSaveProjectAs() {
	if (_treeModel) {

		QString saveName = GUISettings::workDirectory.absolutePath()+QDir::separator()+ "Project";
		QFileInfo infoSave(saveName + ".mixmod");
		if (infoSave.exists()) {
			int suffixSaveName = 2;
			QString saveNameTmp = saveName + QString::number(suffixSaveName);
			infoSave.setFile(saveNameTmp + ".mixmod");
			while (infoSave.exists()) {
				suffixSaveName++;
				saveNameTmp = saveName + QString::number(suffixSaveName);
				infoSave.setFile(saveNameTmp + ".mixmod");
			}
			saveName = saveNameTmp;
		}

		QString fileName = QFileDialog::getSaveFileName( this , tr("Mixmod Files"), saveName, tr("Mixmod Files (*.mixmod);;All Files (*)"));
		if( fileName.isEmpty() )
			return false;
		QFileInfo info( fileName );
		if (info.exists()) {
			_currentInputFileName = info.canonicalPath() + QDir::separator() + info.completeBaseName() ;//to remove the suffix
			setWindowTitle( _currentInputFileName  + " - "+  _applicationName );
			return saveProject( _currentInputFileName);
		}
		else {
			_currentInputFileName = fileName;
			_currentInputFileName.replace(".mixmod", "");
			setWindowTitle( _currentInputFileName  + " - "+  _applicationName );
			return saveProject(_currentInputFileName);
		}
	}
	return false;
}

void GUIMixmod::fileQuit() {
	close();

}

void GUIMixmod::newProjectFromInput() {
	// to create a tree
	// TODO when TreeView done
}

void GUIMixmod::newProjectClassification() {
	// TODO change ?
	reinitCreator( XEM::MVC::RootTreeItem::Classification );
	qDebug("In Classification creator");
	_projectCreator->show();
}

void GUIMixmod::newProjectDiscriminantAnalysis() {

	reinitCreator( XEM::MVC::RootTreeItem::DiscriminantAnalysis );
	qDebug("In Discriminant Analysis creator");
	_projectCreator->show();
}

void GUIMixmod::newProjectOther() {
	// to create a tree
	// TODO when TreeView done
	// TODO when I know what it is
}


void GUIMixmod::projectProjectOption() {
	// TODO when TreeView done
	// TODO when XML classes done
}

void GUIMixmod::projectCloseProject() {
	if( _treeModel )
		delete _treeModel ;
	_treeModel = NULL ;

	if( _treeView ) {
		//_treeView->close();
		delete _treeView ;
	}
	_treeView = NULL ;
	_currentInputFileName="";
	setWindowTitle( _currentInputFileName + _applicationName );
	_currentProject=NULL;
	_projectRun = false ;
	_managerGraphics.close();
	setCentralWidget( NULL );
	GUISettings::outputIsPresent = false;
	createBackground();
	_project_saveProject->setEnabled(false);
	_project_saveProjectAs->setEnabled(false);
	_graphics_create->setEnabled(false);
	_execute_execute->setEnabled(true);
	_execute_cleanOutput->setVisible(false);

}

void GUIMixmod::preferencesLanguage() {
	int iPos ;
	for( iPos = 0 ; iPos < _preferences_language_all.size() ; ++iPos ) {
		if( _preferences_language_all[iPos]->isChecked() )
			break ;
	}
	_currentLanguage = _preferences_language_all[iPos]->text();

	qApp->removeTranslator( _translator );
	_translator = new QTranslator( this );
	_translator->load( QString( "mixmod_" ) + _currentLanguage, ":/");
	qApp->installTranslator( _translator );

	changeEvent( new QEvent( QEvent::LanguageChange ) );
}

void GUIMixmod::preferencesGraphicsSettings() {
	// TODO when Graphics done
}

void GUIMixmod::convert() {
	GUIMConverter * converter = new GUIMConverter();
	converter->show();
}

void GUIMixmod::aboutUs() {
	GUIMAboutUs * aboutUs = new GUIMAboutUs(_applicationName, _applicationVersion);
	aboutUs->show();
}


void GUIMixmod::executeExecute() {

	if( _currentProject ) {
		if( _projectRun ) {
			try {
				_treeModel->removeOutput( 0 );
			}
			catch(XEM::Exception* e) {
				QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Warning"), QObject::tr( e->what() ),QMessageBox::Ok );
				msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);} QPushButton{background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");
				msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
				msgBox.exec();
			}

			_projectRun = false ;
			GUISettings::outputIsPresent = false;
		}

		// 0 : 1rst input
		try {
			_treeModel->setOutput(0);  // insert Output (and run kernel)
			GUISettings::outputIsPresent = true;
			_execute_cleanOutput->setVisible(true);
			_graphics_create->setEnabled(true);
			_treeView->expandToDepth(1);
			_execute_execute->setEnabled(false);
			_projectRun = true ;
		}
		catch(XEM::Exception* e) {
			QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Warning"), QObject::tr( e->what() ),QMessageBox::Ok );
			msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);} QPushButton{background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");
			msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
			msgBox.exec();
		}
	}
	else { // else display a warning

		QMessageBox msgBox(QMessageBox::Information, tr("Information"), tr("you have to create a input before running Mixmod"),QMessageBox::Ok );
		msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);}  QPushButton:default{background-color:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");

		msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
		msgBox.exec();
	}
}

void GUIMixmod::executeCleanOutput() {
	if( _projectRun ) {
		try {
			_treeModel->removeOutput( 0 );
			_projectRun=false;

			GUISettings::outputIsPresent = false;
			_execute_cleanOutput->setVisible(false);
			_managerGraphics.close();
			_graphics_create->setEnabled(false);
			_execute_execute->setEnabled(true);
		}
		catch(XEM::Exception* e) {
			QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Warning"), QObject::tr( e->what() ),QMessageBox::Ok );
			msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);} QPushButton{background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");
			msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
			msgBox.exec();
		}
	}
}

void GUIMixmod::choiceOutputToClean() {
	if( _projectRun ) {
		executeCleanOutput();
	}
}

void GUIMixmod::addGraphicInView(int indexGraphic, int indexVariable) {
	if (_projectRun && _treeModel->getClusteringMain(0)->getOutput()->atLeastOneEstimationNoError()) {
		if (!_managerGraphics.hasMain()) {
			_managerGraphics.setClusteringMain(_treeModel->getClusteringMain(0));
		}
		_managerGraphics.create(_currentProject->getDataType(), indexGraphic, indexVariable);
	}
}

void GUIMixmod::deleteGraphicInView(int indexGraphic) {
	_managerGraphics.deleteGraphic(indexGraphic);
}


void GUIMixmod::executeExecuteCurrentStep() {
	// TODO when Executable done
}

void GUIMixmod::graphicsCreate() {
	if( _projectRun && _treeModel->getClusteringMain(0)->getOutput()->atLeastOneEstimationNoError()) {
		_managerGraphics.close();
		_managerGraphics.setClusteringMain(_treeModel->getClusteringMain(0));
		_managerGraphics.createAll(_currentProject->getDataType());
	}
}

void GUIMixmod::changeWorkDirectory() {
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), GUISettings::workDirectory.absolutePath(), QFileDialog::ShowDirsOnly);
	if (!dir.isEmpty()) {
		GUISettings::workDirectory.setPath(dir);
		QMessageBox::information(this, tr("Working Directory"),
		                         tr("The working directory is \n") + GUISettings::workDirectory.absolutePath());
	}
}


void GUIMixmod::helpMixmodHelp() {
	// TODO if Mixmod have one
}
void GUIMixmod::helpAboutUs() {
	// TODO when you have the time
}
/*******************/

void GUIMixmod::loadAllLanguages() {
	// go to ./languages
	QDir dir( languagesDir );

//qDebug( QDir::currentPath().toStdString().c_str() );

	// load all .qm files, normaly the files begin with "mixmod_"
	QStringList list = dir.entryList( QStringList( QString("*.qm") ) );

	// only 1 language is checked
	language_group = new QActionGroup(this);

	// load the translations of each files
	for( int i = 0 ; i < list.size() ; ++i ) {
		// begin with "mixmod_"
		if( list[i].startsWith("mixmod_") ) {
			// display only the country in the Menu
			QString s = list[i].remove( "mixmod_" );
			s = s.remove( ".qm" );

			QAction* act = new QAction( QIcon(":/"+s+".png"),s, this );
			act->setIconVisibleInMenu(true);
			act->setCheckable( true );

			language_group->addAction( act );
			_preferences_language_all.append( act );

			if( _locale.contains(s) ) {
				act->setChecked( true );
				_currentLanguage = s ;
			}
			connect( act, SIGNAL( triggered() ), this, SLOT( preferencesLanguage() ) );
		}
	}
}

void GUIMixmod::createActions() {
	//_file_saveInput = new QAction( QIcon(":/save.png"),tr( "&Save input" ), this );
	//_file_saveInputAs = new QAction( QIcon(":/saveas.png"),tr( "Sa&ve input as" ), this );
	_file_quit = new QAction( QIcon(":/quit.png"), tr( "&Quit" ), this );
	_file_quit->setShortcut(Qt::CTRL + Qt::Key_Q);
	_file_quit->setIconVisibleInMenu(true);
	connect( _file_quit, SIGNAL( triggered() ), this, SLOT( fileQuit() ) );

	_project_newProject_fromInput = new QAction( QIcon(":/toenter.png"), tr( "&Project from input" ), this );
	_project_newProject_fromInput->setIconVisibleInMenu(true);
	_project_newProject_fromInput->setShortcut(Qt::CTRL + Qt::Key_I);
	connect( _project_newProject_fromInput, SIGNAL( triggered() ), this, SLOT( loadInput() ) );
	_project_newProject_classification = new QAction( QIcon(":/classification.png"), tr( "&Classification" ), this );
	_project_newProject_classification->setShortcut(Qt::CTRL + Qt::Key_F2);
	_project_newProject_classification->setIconVisibleInMenu(true);
	connect( _project_newProject_classification, SIGNAL( triggered() ), this, SLOT( newProjectClassification() ) );
	_project_newProject_discriminantAnalysis = new QAction( QIcon(":/AD.png"), tr( "&Discriminant analysis" ), this );
	_project_newProject_discriminantAnalysis->setShortcut(Qt::CTRL + Qt::Key_F3);
	_project_newProject_discriminantAnalysis->setIconVisibleInMenu(true);
	connect( _project_newProject_discriminantAnalysis, SIGNAL( triggered() ), this, SLOT( newProjectDiscriminantAnalysis() ) );
	_project_newProject_other = new QAction( QIcon(":/other.png"), tr( "&Other" ), this );
	_project_newProject_other->setIconVisibleInMenu(true);

	_project_openProject = new QAction( QIcon(":/open.png"), tr( "&Open project" ), this );
	_project_openProject->setShortcut(Qt::CTRL + Qt::Key_O);
	_project_openProject->setIconVisibleInMenu(true);
	connect( _project_openProject, SIGNAL( triggered() ), this, SLOT( loadProjectFile() ) );
	_project_saveProject = new QAction( QIcon(":/save.png"), tr( "&Save project" ), this );
	_project_saveProject->setShortcut(Qt::CTRL + Qt::Key_S);
	_project_saveProject->setIconVisibleInMenu(true);
	connect( _project_saveProject, SIGNAL( triggered() ), this, SLOT( fileSaveProject() ) );
	_project_saveProjectAs = new QAction( QIcon(":/saveas.png"), tr( "Sa&ve project as" ), this );
	_project_saveProjectAs->setShortcut(Qt::CTRL + Qt::Key_S + Qt::ALT);
	_project_saveProjectAs->setIconVisibleInMenu(true);
	connect( _project_saveProjectAs, SIGNAL( triggered() ), this, SLOT( fileSaveProjectAs() ) );
	_project_projectOption = new QAction( QIcon(":/settings.png"), tr( "&Project options" ), this );
	_project_projectOption->setIconVisibleInMenu(true);
	_project_closeProject = new QAction( QIcon(":/close.png"), tr( "&Close project" ), this );
	_project_closeProject->setShortcut(Qt::CTRL + Qt::Key_W);
	_project_closeProject->setIconVisibleInMenu(true);
	connect( _project_closeProject, SIGNAL( triggered() ), this, SLOT( projectCloseProject() ) );

	_execute_execute = new QAction( QIcon(":/go.png"), tr( "E&xecute" ), this );
	_execute_execute->setShortcut(Qt::Key_Return + Qt::CTRL);
	_execute_execute->setIconVisibleInMenu(true);
	connect( _execute_execute, SIGNAL( triggered() ), this, SLOT( executeExecute() ) );
	_execute_cleanOutput = new QAction(  tr("&Clean output"), this );
	connect( _execute_cleanOutput, SIGNAL( triggered() ), this, SLOT( executeCleanOutput() ) );
	_execute_executeCurrentStep = new QAction( tr( "Execute current &step" ), this );

	_graphics_create = new QAction( QIcon(":/stats.png"), tr( "&Create" ), this );
	_graphics_create->setIconVisibleInMenu(true);
	connect( _graphics_create, SIGNAL( triggered() ), this,  SLOT( graphicsCreate() ) );

	loadAllLanguages();

	_preferences_graphicsSettings = new QAction( QIcon(":/settings.png"), tr( "&Graphics settings" ), this );
	_preferences_graphicsSettings->setIconVisibleInMenu(true);
	_preferences_workDirectory = new QAction( QIcon(":/settings.png"), tr( "Change &working directory" ), this );
	_preferences_workDirectory->setIconVisibleInMenu(true);
	connect( _preferences_workDirectory, SIGNAL( triggered() ), this,  SLOT( changeWorkDirectory() ) );

	_converter = new QAction( QIcon(":/settings.png"), tr( "&Converter" ), this );
	_converter->setIconVisibleInMenu(true);
	connect( _converter, SIGNAL( triggered() ), this, SLOT( convert() ));

	_help_mixmodHelp = new QAction( QIcon(":/help.png"), tr( "&Mixmod help" ), this );
	_help_mixmodHelp->setEnabled(false);
	_help_mixmodHelp->setIconVisibleInMenu(true);
	_help_aboutUs = new QAction( QIcon(":/info.png"), tr( "&About us" ), this );
	_help_aboutUs->setIconVisibleInMenu(true);
	connect( _help_aboutUs, SIGNAL( triggered() ), this, SLOT( aboutUs() ));
}

void GUIMixmod::createMenus() {
	_fileMenu = menuBar()->addMenu( tr( "&File" ) );
	//_projectMenu = menuBar()->addMenu( tr( "&Project" ) );
	_project_newProject = _fileMenu->addMenu( tr( "&New project" ) );
	_project_newProject->addAction( _project_newProject_fromInput );
	_project_newProject->addAction( _project_newProject_classification );
	_project_newProject->addAction( _project_newProject_discriminantAnalysis );
	_project_newProject_discriminantAnalysis->setEnabled(false);
	_project_newProject->addAction( _project_newProject_other );
	_project_newProject_other->setEnabled(false);

	_fileMenu->addAction( _project_openProject );

	//_project_OpenRecentProject = _projectMenu->addMenu( tr("Open &Recent Project") );
	_fileMenu->addSeparator();
	_fileMenu->addAction( _project_saveProject );
	_fileMenu->addAction( _project_saveProjectAs );
	_project_saveProject->setEnabled(false);
	_project_saveProjectAs->setEnabled(false);
	_fileMenu->addAction( _project_projectOption );
	_project_projectOption->setEnabled(false);
	_fileMenu->addSeparator();
	//_editMenu = menuBar()->addMenu( tr("&Edit") );
	_fileMenu->addAction( _project_closeProject );
	_fileMenu->addAction( _file_quit );

	_executeMenu = menuBar()->addMenu( tr( "E&xecute" ) );
	_executeMenu->addAction( _execute_execute );
	_executeMenu->addAction( _execute_executeCurrentStep );
	_execute_executeCurrentStep->setEnabled(false);
	_executeMenu->addAction( _execute_cleanOutput );
	_execute_cleanOutput->setVisible(false);
	_graphicsMenu = menuBar()->addMenu( tr( "&Graphics")  );
	_graphicsMenu->addAction( _graphics_create );
	_graphics_create->setEnabled(false);
	_preferencesMenu = menuBar()->addMenu( tr( "P&references" ) );
	_preferences_language = _preferencesMenu->addMenu( tr( "&Language" ) );
	for( int i = 0 ; i < _preferences_language_all.size() ; ++i ) {
		_preferences_language->addAction( _preferences_language_all[i] );
	}
	_preferencesMenu->addAction( _preferences_graphicsSettings );
	_preferencesMenu->addAction( _preferences_workDirectory );

	_preferences_graphicsSettings->setEnabled(false);

	//Tools Menu
	_toolsMenu = menuBar()->addMenu( tr( "&Tools" ) );
	_toolsMenu->addAction( _converter );

	//helpMenu
	_helpMenu = menuBar()->addMenu( tr( "&Help" ) );
	_helpMenu->addAction( _help_mixmodHelp );
	_helpMenu->addAction( _help_aboutUs );

	menuBar()->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 white, stop:1 #a0c8fa);");//
}

void GUIMixmod::createToolBars() {
	fileToolBar=new QToolBar;
	fileToolBar->addAction(_project_newProject_classification);
	fileToolBar->addAction(_project_newProject_discriminantAnalysis);
	fileToolBar->addSeparator();
	fileToolBar->addAction(_project_openProject);
	fileToolBar->addAction(_project_saveProject);
	fileToolBar->addAction(_execute_execute);
	fileToolBar->addAction(_graphics_create);
	fileToolBar->addAction(_converter);
	//fileToolBar->setMovable(true);
	fileToolBar->setStyleSheet(" QToolBar {border-bottom:none; background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);}");
	//fileToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	addToolBar(Qt::TopToolBarArea,fileToolBar);
}

void GUIMixmod::createStatusBar() {
	QLabel * label = new QLabel(_applicationName);
	label->setAlignment(Qt::AlignLeft);
	statusBar()->insertPermanentWidget(0,label);
	QLinearGradient gradient(QPointF(0,200), QPointF(400,300));
	gradient.setColorAt(0, QColor(140,180,250,240));
	gradient.setColorAt(1, Qt::white);
	QBrush back = QBrush(gradient);
	statusBar()->setStyleSheet("QStatusBar::item {  border: none; } QStatusBar {border : none; background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:0 white, stop:1 #a0c8fa);}");//#a0c8fa
}
