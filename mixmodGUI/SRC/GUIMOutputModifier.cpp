/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMOutputModifier.cpp  description
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
#include "GUIMOutputModifier.h"
#include "GUIMTreeModel.h"
#include <QCursor>

#include "mixmod/Utilities/Util.h"
#include "mixmod/Clustering/ClusteringModelOutput.h"
#include "GUIMMetaData.h"

GUIMOutputModifier::GUIMOutputModifier( XEM::MVC::RootTreeItem::ProjectType type, XEM::MVC::RootTreeItem::DataType dataType, XEM::MVC::TreeItem* treeOutput,const QModelIndex& index, QWidget* parent )
	: GUIMAbstractModifier( type, dataType, treeOutput, index, parent ), _bicButton( NULL ), _cvButton ( NULL ), _iclButton( NULL ), _necButton( NULL ), _dcvButton( NULL ), _hasBIC( false ), _posBIC(0), _hasNEC( false ), _posNEC(0), _hasICL( false ), _posICL(0), _hasDCV( false ), _posDCV(0), _hasCV ( false ),_posCV (0) {
	init();

	setWindowTitle( QObject::tr("Output : ") );
	move( QCursor::pos().x(), QCursor::pos().y() );

	_grid = new QGridLayout( this );
	int hPos = 0 ;

	_group = new QGroupBox( this );
	_group->setStyleSheet( "background-color:white" );

	QVBoxLayout *vbox = new QVBoxLayout;

	if( _projectType == XEM::MVC::RootTreeItem::Classification ) {
		if( _hasBIC  ) {
			_bicButton = new QRadioButton( QString::fromStdString(XEM::CriterionNameToString( XEM::BIC )), this );
			_bicButton->setChecked( hPos==0 );
			vbox->addWidget( _bicButton, hPos++, Qt::AlignLeft );
		}
		if( _hasICL ) {
			_iclButton = new QRadioButton( QString::fromStdString(XEM::CriterionNameToString( XEM::ICL )), this );
			_iclButton->setChecked( hPos==0 );
			vbox->addWidget( _iclButton, hPos++, Qt::AlignLeft );
		}
		if( _hasNEC ) {
			_necButton = new QRadioButton( QString::fromStdString(XEM::CriterionNameToString( XEM::NEC )), this );
			_necButton->setChecked( hPos==0 );
			vbox->addWidget( _necButton, hPos++, Qt::AlignLeft );
		}
	}
	else if( _projectType == XEM::MVC::RootTreeItem::DiscriminantAnalysis ) {
		//TODO
	}

	_group->setLayout( vbox );
	_grid->addWidget( _group, 0, 0, 1, 5 );

	_grid->addWidget( _ok, 1, 3 );

	_grid->addWidget( _cancel, 1, 4 );
}

GUIMOutputModifier::~GUIMOutputModifier() {
}

void GUIMOutputModifier::init() {
	int pos=_index.row();
	GUIMTreeModel * model=(GUIMTreeModel *)_index.model();
	//XEMMVCOutput * output = model->output(pos-1);
	int posProjet = 0;
//  XEMClusteringModelOutput * cMOuput = model->getClusteringMain(posProjet)->getClusteringOutput()->getClusteringModelOutput(pos-1);
	std::vector<XEM::CriterionName> const & criterionName = model->getClusteringMain(posProjet)->getInput()->getCriterionName();

	for (int i=0; i<criterionName.size(); ++i) {
		string criterionString = XEM::CriterionNameToString(criterionName[i]);
		if (criterionString=="BIC") {
			_hasBIC = true;
			_posBIC = i+1;
		}
		else if (criterionString=="ICL") {
			_hasICL = true;
			_posICL = i+1;
		}
		else if (criterionString=="NEC") {
			_hasNEC = true;
			_posNEC = i+1;
		}
		else if (criterionString=="CV") {
			_hasCV = true;
			_posCV = i+1;
		}
		else if (criterionString=="DCV") {
			_hasDCV = true;
			_posCV = i+1;
		}
	}
}

void GUIMOutputModifier::ok() {
	GUIMAction setAction;
	if( _projectType == XEM::MVC::RootTreeItem::Classification ) {
		if( _bicButton && _bicButton->isChecked() ) {
			QVariant value;
			value.setValue<XEM::CriterionName>(XEM::BIC);
			setAction = createSetAction(_index, value);
		}
		else if( _necButton && _necButton->isChecked() ) {
			QVariant value;
			value.setValue<XEM::CriterionName>(XEM::NEC);
			setAction = createSetAction(_index,  value);
		}
		else if( _iclButton && _iclButton->isChecked() ) {
			QVariant value;
			value.setValue<XEM::CriterionName>(XEM::ICL);
			setAction = createSetAction(_index,  value);
		}
		_processor->addAction(setAction);
	}
	else if( _projectType == XEM::MVC::RootTreeItem::DiscriminantAnalysis ) {
		// DCV

	}
	confirm();
}

void GUIMOutputModifier::discard() {
	cancel();
}
