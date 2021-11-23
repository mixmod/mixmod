/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMStopRuleModifier.cpp  description
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
#include "GUIMStopRuleModifier.h"
#include <QCursor>
#include <qmessagebox.h>

#include "mixmod/Utilities/Util.h"
#include "GUIMMetaData.h"

GUIMStopRuleModifier::GUIMStopRuleModifier( XEM::MVC::RootTreeItem::ProjectType type, XEM::MVC::RootTreeItem::DataType dataType, XEM::MVC::TreeItem* treeStopRule,const QModelIndex& index, QWidget* parent )
	: GUIMAbstractModifier( type, dataType, treeStopRule, index, parent ),
	  _epsilonButton( NULL ),
	  _nbIterationButton ( NULL ),
	  _isEpsilon( false ),
	  _isNbIteration( false ) {
	string algoName = _item->getParent()->getChild(0)->toString();
	if ( algoName == XEM::AlgoNameToString(XEM::SEM)  ) { // || algoName == M || algoName == MAP){
		QMessageBox msgBox(QMessageBox::Warning, tr("Inappropriate method"), tr("Impossible to modify the Stop Rule with this algorithm."),QMessageBox::Ok );
		msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);} QPushButton{background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");
		msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
		msgBox.exec();
		close();
	}
	else {
		init();

		setWindowTitle( QObject::tr("Stop Rule : ") );
		move( QCursor::pos().x(), QCursor::pos().y() );

		_grid = new QGridLayout( this );
		int hPos = 0 ;

		_group = new QGroupBox( this );
		_group->setStyleSheet( "background-color:white" );

		QVBoxLayout *vbox = new QVBoxLayout;

		_nbIterationButton = new QCheckBox( QString::fromStdString(XEM::AlgoStopNameToString(XEM::NBITERATION)), this );
		connect( _nbIterationButton, SIGNAL( released() ), this, SLOT( canConfirm() ) );
		vbox->addWidget( _nbIterationButton, hPos++, Qt::AlignLeft );
		_nbIterationButton->setChecked( _isNbIteration );

		_epsilonButton = new QCheckBox( QString::fromStdString(XEM::AlgoStopNameToString(XEM::EPSILON)), this );
		connect( _epsilonButton, SIGNAL( released() ), this, SLOT( canConfirm() ) );
		vbox->addWidget( _epsilonButton, hPos++, Qt::AlignLeft );
		_epsilonButton->setChecked( _isEpsilon );

		_group->setLayout( vbox );
		_grid->addWidget( _group, 0, 0, 1, 5 );

		_grid->addWidget( _ok, 1, 3 );

		_grid->addWidget( _cancel, 1, 4 );
	}
}

GUIMStopRuleModifier::~GUIMStopRuleModifier() {
}

void GUIMStopRuleModifier::canConfirm() {
	bool finish = false ;

	finish = ( _epsilonButton->isChecked() || _nbIterationButton->isChecked() );

	_ok->setEnabled( finish );
}

void GUIMStopRuleModifier::init() {
	unsigned int _nbChild = _item->getNbChild();
	if ( _nbChild == 2 ) {

		_isEpsilon = true ;
		_isNbIteration = true ;
		if ( _item->getChild(0)->getKeyword() == XEM::MVC::TreeEpsilon || _item->getChild(0)->getKeyword() == XEM::MVC::TreeInitEpsilon) {
			_posEpsilon = 0;
			_posNbIteration = 1;
		}
		else if ( _item->getChild(0)->getKeyword() == XEM::MVC::TreeNbIteration || _item->getChild(0)->getKeyword() == XEM::MVC::TreeInitNbIteration) {
			_posEpsilon = 1;
			_posNbIteration = 0;
		}
	}
	else if (_nbChild == 1) {
		switch ( _item->getChild(0)->getKeyword() ) {
		case XEM::MVC::TreeInitEpsilon :
		case XEM::MVC::TreeEpsilon :
			_isEpsilon = true ;
			_posEpsilon = 0;
			break;
		case XEM::MVC::TreeInitNbIteration :
		case XEM::MVC::TreeNbIteration :
			_isNbIteration = true ;
			_posNbIteration = 0;
			break;
		default :
			break;
		}
	}
}


void GUIMStopRuleModifier::ok() {
	unsigned int _nbChild = _item->getNbChild();
	int bothChecked = _epsilonButton->isChecked() && _nbIterationButton->isChecked();
	if (_item->getKeyword() == XEM::MVC::TreeStopRuleValue) {
		if ( _nbChild == 2 && !bothChecked ) { //only one is checked
			int positionChildToRemove = 1;
			if ( _epsilonButton->isChecked() ) {
				positionChildToRemove = 0;
			}
			GUIMAction removeAction = createRemoveAction(_index, positionChildToRemove);
			_processor->addAction(removeAction);

		}
		else if ( _nbChild == 1 && !bothChecked ) {//switch stoprule
			QVariant v ;
			if ( _isNbIteration && _epsilonButton->isChecked() ) { //switch child nbiteration->epsilon
				// insert
				GUIMAction insertAction = createInsertAction(_index, 1);
				_processor->addAction(insertAction);
				//remove
				GUIMAction removeAction = createRemoveAction(_index, 0);
				_processor->addAction(removeAction);
			}
			else if ( _isEpsilon && _nbIterationButton->isChecked() ) {//switch child nbiteration->epsilon
				// insert
				GUIMAction insertAction = createInsertAction(_index, 0);
				_processor->addAction(insertAction);
				//remove
				GUIMAction removeAction = createRemoveAction(_index, 1);
				_processor->addAction(removeAction);
			}
		}
		else if ( _nbChild == 1 && bothChecked ) {//change to NBITERATION_EPSILON
			if ( _isNbIteration ) { //epsilon to insert
				// insert
				GUIMAction insertAction = createInsertAction(_index, 1);
				_processor->addAction(insertAction);
			}
			else if( _isEpsilon ) {// insert
				GUIMAction insertAction = createInsertAction(_index, 0);
				_processor->addAction(insertAction);
			}
		}
	}
	else {
		QVariant v ;
		if (bothChecked) {
			v.setValue<XEM::AlgoStopName>( XEM::NBITERATION_EPSILON );
		}
		else if (_epsilonButton->isChecked()) {
			v.setValue<XEM::AlgoStopName>( XEM::EPSILON );
		}
		else if (_nbIterationButton->isChecked()) {
			v.setValue<XEM::AlgoStopName>( XEM::NBITERATION );
		}
		GUIMAction setAction = createSetAction(_index, v);
		_processor->addAction(setAction);
	}
	confirm();
}

void GUIMStopRuleModifier::discard() {
	cancel();
}
