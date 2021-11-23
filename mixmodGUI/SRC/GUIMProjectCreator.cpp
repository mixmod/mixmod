/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMProjectCreator.cpp  description
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
#include "GUIMProjectCreator.h"
#include <QFileInfo>
#include <QVariant>
#include <QMessageBox>

#include "GUIMDataCreator.h"
#include "GUIMMetaData.h"
#include "mixmod_iostream/DomData.h"

GUIMProjectCreator::GUIMProjectCreator( XEM::MVC::RootTreeItem::ProjectType type, QWidget* parent, Qt::WindowFlags flags )
	: QWizard(parent,flags), _projectType(type), _dataType(XEM::MVC::RootTreeItem::NoDataType), _dataDescription(NULL),
	  _vClusters( QVector<int64_t>() ) {
	setWindowTitle( QObject::tr("Create new Project") );
	setWindowIcon(QPixmap(":/logo.jpg"));
	addPage( new GUIMDataCreator(type, this) );

	connect( button(QWizard::FinishButton), SIGNAL(released()), this, SLOT(finished()) );
}

GUIMProjectCreator::~GUIMProjectCreator() {
}

void GUIMProjectCreator::finished() {
	// the first page contains all nbClusters & modalities (cannot use field() because of user widget)
	GUIMDataCreator* firstPage = static_cast<GUIMDataCreator*>( page( startId() ) );
	try {
// Nb Cluster
		if( _projectType == XEM::MVC::RootTreeItem::Classification ) {
			for( int64_t i = 0 ; i < field("nbNbCluster").toInt() ; ++i ) {
				if ( !_vClusters.contains(firstPage->_nbCluster->getSpinBoxValue(i)))
					_vClusters.append( firstPage->_nbCluster->getSpinBoxValue(i) );
			}
		}
		else {
			_vClusters.append(field("nbCluster").toInt());
		}

// Criteria
		if( _projectType == XEM::MVC::RootTreeItem::Classification ) {
			_vCriteria.append(XEM::BIC);
		}
		else if( _projectType == XEM::MVC::RootTreeItem::DiscriminantAnalysis ) {
			_vCriteria.append(XEM::CV);
		}

// Modality

		if (!field("dataFilename").toString().isNull()) {
			XEM::DomData domData;
			_dataDescription = domData.readDataFile(field("dataFilename").toString().toStdString());
		}


		if( _dataDescription->getDataType() ==XEM::QualitativeData ) {

			_dataType = XEM::MVC::RootTreeItem::Qualitative ;
		}
		else {
			_dataType = XEM::MVC::RootTreeItem::Quantitative ;
		}

// Creation of the Data
		//_nbSample = static_cast<long>( field("nbSample").toInt() );
		//_pbDimension = field("pbDimension").toInt();

		//_dataFilename = field("dataFilename").toString() ;
		//_weightFilename = "" ; // field("weightFilename").toString() ;
		if( _projectType == XEM::MVC::RootTreeItem::DiscriminantAnalysis ) {
			_dataPartition = field("dataPartition").toString() ;
			_dataFilenameReclassify = field("dataFilenameReclassify").toString() ;
		}


		emit( itemCreated() );

		close();
	}
	catch(XEM::IOStreamErrorType error) {
		QString errorString(XEM::IOStreamErrorTypeToString(error).c_str());
		QString message = tr( "An data error is occured. Please enter correct values for your project." )+" \nNote : "+errorString;
		close();
		QMessageBox msgBox(QMessageBox::Critical, tr("Data Error"), message );
		msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);} QPushButton{background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");
		msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
		msgBox.exec();
	}
	catch(...) {
		close();
		QMessageBox msgBox(QMessageBox::Critical, tr("Data Error"), tr( "An data error is occured. Please enter correct values for your project." ) );
		msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);} QPushButton{background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");
		msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
		msgBox.exec();
	}
}
