/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMAlgoModifier.cpp  description
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

#include "GUIMAlgoModifier.h"
#include <mixmod_mvc/View.h>
#include "GUIMMetaData.h"
#include <QCursor>

#include "mixmod/Utilities/Util.h"
#include <QtGui/QtGui>

GUIMAlgoModifier::GUIMAlgoModifier( XEM::MVC::RootTreeItem::ProjectType type, XEM::MVC::RootTreeItem::DataType dataType, XEM::MVC::TreeItem* item, const QModelIndex& index, QWidget* parent )
	: GUIMAbstractModifier( type, dataType, item, index, parent ) {
	QFont font;
	font.setUnderline( true );
	move( QCursor::pos().x(), QCursor::pos().y() );

	_grid = new QGridLayout( this );

	QLabel* _labelTitle = new QLabel( QObject::tr("INSERT ALGORITHM"));
	_labelTitle->setFont( font );
	_grid->addWidget( _labelTitle, 0, 2 );

	_widget = new QWidget( this );
	_widgetBox = new QVBoxLayout( _widget );

	/*Position*/
	_gPosition = new QGroupBox(tr("Position"), _widget);
	_gPosition->setStyleSheet( "background-color:white" );

	_positionBox = new QHBoxLayout ;

	QLabel* _labelPosition = new QLabel( QObject::tr("POSITION"), _widget );
	_labelPosition->setFont( font );
	_positionBox->addWidget( _labelPosition );

	_valuePosition = new QSpinBox( _widget );
	_valuePosition->setMinimum( 1 );
	_valuePosition->setMaximum( item->getNbChild() + 1 );
	_valuePosition->setValue( item->getNbChild() + 1 );
	_positionBox->addWidget( _valuePosition);

	_gPosition->setLayout(_positionBox);
	_widgetBox->addWidget(_gPosition);
	/*end Position*/

	/*Algo Name*/
	_gAlgoName = new QGroupBox(tr("Algorithm"), _widget);
	_gAlgoName->setStyleSheet( "background-color:white" );
	_algoNameBox = new QHBoxLayout ;
	//label
	QLabel* _labelAlgoName = new QLabel( QObject::tr("ALGORITHM"), _widget );
	_labelAlgoName->setFont( font );
	_algoNameBox->addWidget( _labelAlgoName );

	//name
	_gName = new QGroupBox(tr("Name"), _widget);
	_nameBox = new QVBoxLayout;
	_algoNameGroup = new QButtonGroup( _nameBox );

	if ( type == XEM::MVC::RootTreeItem::Classification ) {
		_EMButton = new QRadioButton( tr("EM"));
		_CEMButton = new QRadioButton( tr("CEM"));
		_SEMButton = new QRadioButton( tr("SEM"));
		_algoNameGroup->addButton( _EMButton ) ;
		_algoNameGroup->addButton( _CEMButton ) ;
		_algoNameGroup->addButton( _SEMButton ) ;

		//faire un connect pour stop rule
		_nameBox->addWidget( _EMButton );
		_nameBox->addWidget( _CEMButton );
		_nameBox->addWidget( _SEMButton );
		connect( _EMButton, SIGNAL( released() ), this, SLOT( verifyAlgo() ) );
		connect( _CEMButton, SIGNAL( released() ), this, SLOT( verifyAlgo() ) );
		connect( _SEMButton, SIGNAL( released() ), this, SLOT( verifyAlgo() ) );
		_EMButton->setChecked (true );
	}
	else if ( type == XEM::MVC::RootTreeItem::DiscriminantAnalysis) {
		_MButton = new QRadioButton( tr("M"));
		_MAPButton = new QRadioButton( tr("MAP"));
		_algoNameGroup->addButton( _MButton ) ;
		_algoNameGroup->addButton( _MAPButton ) ;
		//TODO faire un connect pour stop rule et nbiteration
		_nameBox->addWidget( _MButton );
		_nameBox->addWidget( _MAPButton );
	}
	_gName->setLayout( _nameBox );
	_algoNameBox->addWidget( _gName );
	_gAlgoName->setLayout( _algoNameBox );
	_widgetBox->addWidget(_gAlgoName);
	/*end Algo Name*/


	/*Stop Rule*/
	_gStopRule = new QGroupBox(tr("Stop Rule"), _widget);
	_gStopRule->setStyleSheet( "background-color:white" );
	_stopRuleBox = new QHBoxLayout ;
	//label
	QLabel* _labelStopRule = new QLabel( QObject::tr("STOP RULE"), _widget );
	_labelStopRule->setFont( font );
	_stopRuleBox->addWidget( _labelStopRule ) ;

	//rule
	_gRule = new QGroupBox(tr("Rule"), _widget);
	_ruleBox = new QVBoxLayout;

	_nbIterationButton = new QCheckBox( QString::fromStdString(XEM::AlgoStopNameToString(XEM::NBITERATION)), this );
	connect( _nbIterationButton, SIGNAL( released() ), this, SLOT( canConfirm() ) );
	_ruleBox->addWidget( _nbIterationButton, 0, Qt::AlignLeft );
	_nbIterationButton->setChecked( true );

	_epsilonButton = new QCheckBox( QString::fromStdString(XEM::AlgoStopNameToString(XEM::EPSILON)), this );
	connect( _epsilonButton, SIGNAL( released() ), this, SLOT( canConfirm() ) );
	_ruleBox->addWidget( _epsilonButton, 0, Qt::AlignLeft );
	_epsilonButton->setChecked( true );

	_gRule->setLayout(_ruleBox);
	_stopRuleBox->addWidget(_gRule);

	//rule value
	_gRuleValue = new QGroupBox(tr("Values"), _widget);
	_gridStopRuleValue = new QGridLayout;

	//label
	QLabel * _labelEpsilon = new QLabel( QObject::tr("Epsilon"), _widget );
	QLabel * _labelNbIteration = new QLabel( QObject::tr("NbIteration"), _widget );
	_gridStopRuleValue->addWidget( _labelNbIteration, 0, 1);//label
	_gridStopRuleValue->addWidget( _labelEpsilon, 1, 1);//label
	_editValueEpsilon = new QLineEdit( _widget );
	_editValueNbIteration = new QLineEdit( _widget );


	std::ostringstream sEps, sNbIt;
	sEps << XEM::defaultEpsilon;
	sNbIt << XEM::defaultNbIteration;

	_editValueEpsilon->setText(QString::fromStdString(sEps.str()));
	_editValueNbIteration->setText(QString::fromStdString(sNbIt.str()));

	_validNbIteration = new QIntValidator(XEM::minNbIteration,XEM::maxNbIteration, _widget);//validity of nbiteration
	XEM::MVC::TreeItem * child = item->getChild(0);
	if( child->getChild(0)->toString() == XEM::AlgoNameToString( XEM::SEM ) ) {
		reinterpret_cast< QIntValidator *>(_validNbIteration)->setBottom(XEM::minNbIterationForSEM);
	}
	_editValueNbIteration->setMaxLength( 6 );

	_validEpsilon = new QDoubleValidator(XEM::minEpsilon, XEM::maxEpsilon, 6, _widget);//validity of epsilon
	_editValueEpsilon->setMaxLength( 8 );

	_editValueEpsilon->setValidator( _validEpsilon );
	_editValueNbIteration->setValidator( _validNbIteration );

	_gridStopRuleValue->addWidget(_editValueNbIteration, 0, 2);
	_gridStopRuleValue->addWidget(_editValueEpsilon, 1, 2);
	connect( _editValueEpsilon, SIGNAL( textChanged(const QString &) ), this, SLOT( canConfirm() ) );
	connect( _editValueNbIteration, SIGNAL( textChanged(const QString &) ), this, SLOT( canConfirm() ) );

	_gRuleValue->setLayout(_gridStopRuleValue);
	_stopRuleBox->addWidget(_gRuleValue);
	_gStopRule->setLayout(_stopRuleBox);
	_widgetBox->addWidget(_gStopRule);
	/*end StopRule*/

	_grid->addWidget( _widget, 1, 0, 1, 5 );
	_grid->addWidget( _ok, 2, 3 );
	_grid->addWidget( _cancel, 2, 4 );
}

GUIMAlgoModifier::~GUIMAlgoModifier() {
	/*
	  qDeleteAll( _vButtons );
	  _vButtons.clear();
	*/
}

void GUIMAlgoModifier::ok() {
	// insert default algo (with default stop rule)
	GUIMAction insertAction = createInsertAction(_index, _valuePosition->value()-1 );
	_processor->addAction(insertAction);

	//algoName
	QVariant algoName ;
	if ( _projectType == XEM::MVC::RootTreeItem::Classification ) {
		if ( _EMButton->isChecked())
			algoName.setValue<XEM::AlgoName>( XEM::EM );
		if ( _CEMButton->isChecked())
			algoName.setValue<XEM::AlgoName>( XEM::CEM );
		if ( _SEMButton->isChecked())
			algoName.setValue<XEM::AlgoName>( XEM::SEM );
	}
	else {
		if ( _MAPButton->isChecked())
			algoName.setValue<XEM::AlgoName>( XEM::MAP );
		if ( _MButton->isChecked())
			algoName.setValue<XEM::AlgoName>( XEM::M );
	}
	if (algoName.value<XEM::AlgoName>() != XEM::defaultAlgoName) {
		QList<int> positions;
		positions.append(_valuePosition->value()-1);
		positions.append(XEM::MVC::View::ALGO_NAME); //ALGO_NAME is the position of AlgoName child
		GUIMAction setAction = createSetAction(_index, positions, algoName);
		_processor->addAction(setAction);
	}

	//nb_iteration
	if (!_nbIterationButton->isChecked()) {
		QList<int> positions;
		positions.append(_valuePosition->value()-1);
		positions.append(XEM::MVC::View::STOP);
		positions.append(XEM::MVC::View::NB_ITERATION);
		GUIMAction removeAction = createRemoveAction(_index, positions);
		_processor->addAction(removeAction);
	}

	//epsilon
	if (!_epsilonButton->isChecked() && !_SEMButton->isChecked()) {
		QList<int> positions;
		positions.append(_valuePosition->value()-1);
		positions.append(XEM::MVC::View::STOP);
		positions.append(XEM::MVC::View::EPSILON);
		GUIMAction removeAction = createRemoveAction(_index, positions);
		_processor->addAction(removeAction);
	}
	//set nb_iteration
	if (_nbIterationButton->isChecked()) {
		QList<int> positions;
		positions.append(_valuePosition->value()-1);
		positions.append(XEM::MVC::View::STOP);
		positions.append(XEM::MVC::View::NB_ITERATION);
		QString valueString = _editValueNbIteration->text();
		QVariant value;
		value.setValue<int>( valueString.toInt() );
		GUIMAction setAction = createSetAction(_index, positions, value);
		_processor->addAction(setAction);
	}

	//set epsilon
	if (_epsilonButton->isChecked() && !_SEMButton->isChecked()) {
		QList<int> positions;
		positions.append(_valuePosition->value()-1);
		positions.append(XEM::MVC::View::STOP);
		if (_nbIterationButton->isChecked()) {
			positions.append(XEM::MVC::View::EPSILON);
		}
		else {
			positions.append(XEM::MVC::View::EPSILON-1);
		}
		QString valueString = _editValueEpsilon->text();
		QVariant value;
		value.setValue<double>( valueString.toDouble() );
		GUIMAction setAction = createSetAction(_index, positions, value);
		_processor->addAction(setAction);
	}
	confirm();
}


void GUIMAlgoModifier::discard() {
	cancel();
}


void GUIMAlgoModifier::verifyAlgo() {
	bool keepEpsilon = true ;
	if (_SEMButton->isChecked() ) {
		_editValueEpsilon->setEnabled( !keepEpsilon );
		_epsilonButton->setChecked( !keepEpsilon );
		_epsilonButton->setEnabled( !keepEpsilon );
		reinterpret_cast< QIntValidator *>(_validNbIteration)->setBottom(XEM::minNbIterationForSEM);
	}
	else {
		_editValueEpsilon->setEnabled( keepEpsilon );
		_epsilonButton->setEnabled( keepEpsilon );
		reinterpret_cast< QIntValidator *>(_validNbIteration)->setBottom(XEM::minNbIteration);
	}
	canConfirm() ;
}


void GUIMAlgoModifier::canConfirm() {
	bool finish = false;
	bool activateEpsilon = _epsilonButton->isChecked();
	bool activateNbIteration = _nbIterationButton->isChecked() ;
	bool epsilonValidity = true ;
	bool nbIterationValidity = true ;

	finish = ( activateEpsilon || activateNbIteration ) ;
	if (finish) {
		if (activateEpsilon) {
			epsilonValidity =  _editValueEpsilon->hasAcceptableInput() ;
		}
		if (activateNbIteration) {
			nbIterationValidity = _editValueNbIteration->hasAcceptableInput() ;
		}
	}
	_editValueEpsilon->setEnabled(activateEpsilon);
	_editValueNbIteration->setEnabled(activateNbIteration);

	_ok->setEnabled( finish & epsilonValidity & nbIterationValidity );
}
