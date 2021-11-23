/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMTreeModel.cpp  description
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
#include "GUIMTreeModel.h"
#include <QtGui/QtGui>

#include "mixmod/Kernel/IO/GaussianData.h"
#include "mixmod/Kernel/IO/BinaryData.h"

GUIMTreeModel::GUIMTreeModel( GUIMProjectCreator* creator, QObject* parent )
	: QAbstractItemModel(parent), _rootItem(NULL), _data( ), _creator(creator) {
	_rootItem = new XEM::MVC::RootTreeItem( " ", XEM::MVC::TreeProject );
	_rootItem->setProjectType( creator->getProjectType() );
	_rootItem->setDataType( creator->getDataType() );
	generateTree();
}

GUIMTreeModel::GUIMTreeModel( GUIMProjectCreator* creator, XEM::ClusteringMain * cMain, QObject* parent )
	: QAbstractItemModel(parent), _rootItem(NULL), _data( ), _creator(creator) {
	_rootItem = new XEM::MVC::RootTreeItem( " ", XEM::MVC::TreeProject );

	//case
// 	if (dynamic_cast<XEMClusteringInput *>(input)){
// 	  _rootItem->setProjectType( MVCRootTreeItem::Classification );
// 	}else if (0){
// 	  _rootItem->setProjectType( MVCRootTreeItem::DiscriminantAnalysis );
// 	}
	_rootItem->setProjectType( XEM::MVC::RootTreeItem::Classification );

	XEM::ClusteringInput * input = cMain->getInput();
	//Data type
	if (!input->getDataType()==XEM::QualitativeData) {
		_rootItem->setDataType( XEM::MVC::RootTreeItem::Quantitative );
	}
	else {
		_rootItem->setDataType( XEM::MVC::RootTreeItem::Qualitative );
	}
	generateTree(cMain);
}

GUIMTreeModel::~GUIMTreeModel() {
	qDeleteAll( _data );
	_data.clear();

	if( _rootItem ) {
		delete _rootItem ;
	}
}

int GUIMTreeModel::columnCount( const QModelIndex& /*parent*/ ) const {
	return 2 ;
}

QVariant GUIMTreeModel::data( const QModelIndex& index, int role ) const {
	if( !index.isValid() )
		return QVariant();

	if( role != Qt::DisplayRole && role != Qt::EditRole )
		return QVariant();

	XEM::MVC::TreeItem* item = getItem( index );
	if( item->getKeyword() <= XEM::MVC::NoKeyword || item->getKeyword() >= XEM::MVC::TreeSize)
		return QVariant();

	std::ostringstream sRow;
	sRow << index.row()+1;
	switch( index.column() ) {
	case 0 :
		switch(item->getKeyword()) {
		case XEM::MVC::TreeLabelSample :
		case XEM::MVC::TreeModelChild :
		case XEM::MVC::TreeNbAlgoChild :
		case XEM::MVC::TreeResult :
		case XEM::MVC::TreeCriterionChild :
		case XEM::MVC::TreeInitParameterStrategy :
		case XEM::MVC::TreeInitPartition :
		case XEM::MVC::TreeKnownPartitionSample :
		case XEM::MVC::TreeDataWeightChild :
		case XEM::MVC::TreeNbCluster :
		case XEM::MVC::TreeInitProportionChild :
		case XEM::MVC::TreeInitCenterChild :
		case XEM::MVC::TreeInitDispersionChild :
		case XEM::MVC::TreeInitScatterChild :
		case XEM::MVC::TreeInitDispersionData :
		case XEM::MVC::TreeOutputProportionChild :
		case XEM::MVC::TreeOutputCenterChild :
		case XEM::MVC::TreeOutputDispersionChild :
		case XEM::MVC::TreeOutputScatterChild :
		case XEM::MVC::TreeOutputDispersionData :
			return getName(item) + QString::fromStdString(sRow.str()) ;
		default:
			return getName(item) ;
		}
	case 1 :
		return QString::fromStdString( item->toString() );
	default :
		break ;
	}
	return QVariant();
}

Qt::ItemFlags GUIMTreeModel::flags( const QModelIndex& index ) const {
	if( !index.isValid() )
		return 0 ;

	return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable ;
}

QVariant GUIMTreeModel::headerData( int section, Qt::Orientation orientation, int role ) const {
	if( orientation == Qt::Horizontal && role == Qt::DisplayRole ) {
		switch( section ) {
		case 0 :
			return tr("Project") ;
		case 1 :
			return tr("Value") ;
		default :
			break ;
		}
	}

	return QVariant();
}

QModelIndex GUIMTreeModel::index( int row, int column, const QModelIndex& parent ) const {
	if( parent.isValid() && parent.column() != 0 )
		return QModelIndex();

	if( row < 0 || column < 0 || column >= columnCount(parent) )
		return QModelIndex();

//FIXME
	if( parent == QModelIndex() )
		return createIndex( row, column, _rootItem );

	XEM::MVC::TreeItem* parentItem = getItem( parent );
	if( !parentItem )
		throw ;

	if( row > static_cast<int>( parentItem->getNbChild() ) )

		return QModelIndex();

	XEM::MVC::TreeItem* childItem = parentItem->getChild( row );

	if( childItem )
		return createIndex( row, column, childItem );
	else
		return QModelIndex();
}

bool GUIMTreeModel::insertColumns( int /*position*/, int /*columns*/, const QModelIndex& /*parent*/ ) {
	bool success = false ;

	return success ;
}
//
bool GUIMTreeModel::insertRows( int position, int rows, const QModelIndex& parent ) { //rows is the lines number to insert
	XEM::MVC::TreeItem* parentItem = getItem( parent );
	bool success = false ;

	//beginInsertRows( parent, position, position + rows - 1 );

	// only to insert Output
// 	if( parentItem == _rootItem ){
// 		parentItem->insertChild( _data[ (position - 1)/2 ]->getOutput()->getViewOutput()->getRoot(),
// 					position
// 				);
// 		success = true ;
// 	}else {
// 		success = true ;
// 		MVCMixmod* mvc = NULL ;
// 		foreach( MVCMixmod* tmp, _data ){
// 			if( tmp->find( parentItem ) ){
// 				mvc = tmp ;
// 				break ;
// 			}
// 		}
// 		for( int i = 0 ; i < rows ; ++i ){
// 			success &= mvc->insertChild( parentItem, position );
// 		}
// 	}
	XEM::MVC::Mixmod* mvc = _data[0] ;
	success = true ;

//   if (parentItem != _rootItem){
//
//
//     foreach( MVCMixmod* tmp, _data ){
//       if( tmp->find( parentItem ) ){
//         mvc = tmp ;
//         break ;
//       }
//     }
//   }else{//only to insert output
//     foreach( MVCMixmod* tmp, _data ){
//       if( tmp && tmp->getView()->getRoot() == parentItem ){
// 	success = true ;
//         mvc = tmp ;
//         break ;
//       }
//     }
//   }

	for( int i = 0 ; i < rows ; ++i ) {
		success &= mvc->insertChild( parentItem, position );
	}

	//endInsertRows();
	layoutChanged ();
	return success ;
}

QModelIndex GUIMTreeModel::parent( const QModelIndex& index ) const {
	if( !index.isValid() )
		return QModelIndex();

	XEM::MVC::TreeItem* childItem = getItem( index );

	if( childItem->getKeyword() <= XEM::MVC::NoKeyword || childItem->getKeyword() >= XEM::MVC::TreeSize )
		return QModelIndex();

	XEM::MVC::TreeItem* parentItem = NULL ;

	if( childItem ) {
		if( childItem == _rootItem )
			return QModelIndex();
		parentItem = childItem->getParent();
	}
	else {
		return QModelIndex();
	}

	return createIndex( parentItem->getPosition(), 0, parentItem );
}

bool GUIMTreeModel::removeColumns( int /*position*/, int /*columns*/, const QModelIndex& /*parent*/ ) {
	bool success = false ;

	return success ;
}

bool GUIMTreeModel::removeRows( int position, int rows, const QModelIndex& parent ) {
	XEM::MVC::TreeItem* parentItem = getItem( parent );
	bool success = false ;

	// only to remove Output
	if( parentItem == _rootItem ) {
		_rootItem->removeChild( position );
		_data[ 0 ]->setOutputNULL();

		// success = false ;
// 	}else {
		/*
				MVCMixmod* mvc = NULL ;
				if (parentItem != _rootItem){
				  success = true ;

				  foreach( MVCMixmod* tmp, _data ){
				    if( tmp->find( parentItem ) ){
				      mvc = tmp ;
				      break ;
				    }
				  }
				}else{//only to insert output
				  foreach( MVCMixmod* tmp, _data ){
				    if( tmp && tmp->getView()->getRoot() == parentItem ){
				      success = true ;
				      mvc = tmp ;
				      break ;
				    }
				  }
				}*/
	}
	else {
		XEM::MVC::Mixmod* mvc = _data[0] ;
		success = true ;
		for( int i = 0 ; i < rows ; ++i ) {

			success &= mvc->removeChild( parentItem, position );

		}
	}

	layoutChanged ();
	return success ;
}

int GUIMTreeModel::rowCount( const QModelIndex& parent ) const {
	if( parent.column() > 0 ) return 0 ;

	if( parent == QModelIndex() ) return 1 ;

	XEM::MVC::TreeItem* parentItem = getItem( parent );

	if( parentItem )
		return parentItem->getNbChild();

	return 0 ;
}

bool GUIMTreeModel::setData( const QModelIndex& index, const QVariant& value, int role ) {

	if( role != Qt::EditRole )
		return false ;

	bool success = false ;
	XEM::MVC::TreeItem* item = getItem( index );

	/*if  (item == _rootItem ){
		int position = value.value<int>();
		_rootItem->setChild( _data[ 0 ]->getOutput()->getViewOutput()->getRoot(),
					position+1);
		QModelIndex topLeft = this->index( position+1, 0, index );
		XEMMVCTreeItem* itemL = getItem( topLeft );
		QModelIndex bottomRight = this->index( itemL->getNbChild()-1, 1, topLeft );

		emit dataChanged( topLeft,  bottomRight) ;

		beginRemoveRows( index, 0, 0);
		endRemoveRows();
		beginInsertRows( index, 0, 0);
		endInsertRows();
		success = true ;
	}else{*/

	XEM::MVC::Mixmod* mvc = NULL ;
	foreach( XEM::MVC::Mixmod* tmp, _data ) {
		if( tmp->find( item ) ) {
			mvc = tmp ;
			break ;
		}
	}
	try {
		success = mvc->setValue( item, value );
	}
	catch(XEM::Exception* e) {
		layoutChanged ();
		throw e;
	}
	catch(XEM::IOStreamErrorType& e) {
		layoutChanged();
		throw e;
	}
	layoutChanged ();
	return success ;
}

bool GUIMTreeModel::setHeaderData( int /*section*/, Qt::Orientation /*orientation*/, const QVariant& /*value*/, int /*role*/ ) {
	return false ;
}

XEM::MVC::TreeItem* GUIMTreeModel::getItem( const QModelIndex& index ) const {
	if( index.isValid() ) {
		XEM::MVC::TreeItem* item = reinterpret_cast<XEM::MVC::TreeItem*>( index.internalPointer() );
		if( item ) {
			return item ;
		}
	}
	return _rootItem ;
}

void GUIMTreeModel::generateTree(XEM::ClusteringMain * cMain) {
	if (cMain) {
		generateMixmod(0, cMain);
	}
	else {
		generateMixmod(0);
	}
}

void GUIMTreeModel::generateMixmod( int pos ) {
	// data
	XEM::DataDescription * dataDescription = _creator->getDataDescription();

	vector<int64_t> nbCluster = _creator->getNbClusters().toStdVector();

	//first access to _data
	if (_data.isEmpty())
		_data.resize(1);

	_data.insert( pos, new XEM::MVC::Mixmod() );


	_data[pos]->constructClusteringMain(nbCluster, dataDescription);

	_rootItem->insertChild( _data[pos]->getView()->getInput(), /* when more than one step : (2*) */pos );

}

void GUIMTreeModel::generateMixmod( int pos, XEM::ClusteringMain * cMain ) {
	//first access to _data
	if (_data.isEmpty())
		_data.resize(1);

	_data.insert( pos, new XEM::MVC::Mixmod(cMain) );
	_rootItem->insertChild( _data[pos]->getView()->getInput(), /* when more than one step : (2*) */pos );
	if (cMain->getOutput()) {
		_rootItem->insertChild(_data[pos]->getView()->getOutput(), pos+1);
	}

}

void GUIMTreeModel::setOutput( int pos) {
	insertRows(pos+1, 1, createIndex(0,0,_rootItem).parent() );
	_rootItem->insertChild(_data[pos]->getView()->getOutput(), pos+1);
}

void GUIMTreeModel::sortOutput(int pos, XEM::CriterionName criterionName ) {
	_data[pos]->sortOutput(criterionName);
	layoutChanged ();
}

void GUIMTreeModel::removeOutput( int pos ) {
	bool test = _rootItem->getNbChild() > unsigned(pos) ;

	if( test ) {
		//_rootItem->removeChild(pos+1);
		removeRows( pos+1, 1, createIndex(0,0,_rootItem).parent() );
	}
}

/*bool GUIMTreeModel::saveInputXML(const QString& s)
{
	bool res = true;
	QFile file(s); // Ouverture du fichier en écriture et en texte.
	file.open(QFile::WriteOnly | QFile::Text);
	QXmlStreamWriter writer(&file);
	writer.setAutoFormatting(true);
	writer.writeStartDocument();
	writer.writeStartElement("Project");

	writer.writeStartElement("Options");
	if ( _rootItem->getProjectType() == MVCRootTreeItem::Classification ){
		writer.writeTextElement("Project_Type", "Classification");
	}else if ( _rootItem->getProjectType() == MVCRootTreeItem::DiscriminantAnalysis ){
		writer.writeTextElement("Project_Type", "DiscriminantAnalysis");
	}
	if ( _rootItem->getDataType() == MVCRootTreeItem::Qualitative ){
		writer.writeTextElement("Data_Type", "Qualitative");
	}else if ( _rootItem->getDataType() == MVCRootTreeItem::Quantitative ){
		writer.writeTextElement("Data_Type", "Quantitative");
	}
	writer.writeEndElement();//ferme l'élément Options

	writer.writeStartElement("Input");

	writer.writeTextElement("Variables", QString().setNum(input(0)->getPbDimension()));

	writer.writeStartElement("NbNbCluster");//Clusters
	writer.writeAttribute("Value", QString().setNum(input(0)->getNbNbCluster()));
	for (int i = 0; i < input(0)->getNbNbCluster(); ++i){
		writer.writeStartElement("NbCluster");
		writer.writeAttribute("Rank", QString().setNum(i+1));
		writer.writeCharacters(QString().setNum(input(0)->getTabNbCluster()[i]));
		writer.writeEndElement();
	}
	writer.writeEndElement();//ferme l'élément NbNbCluster


	writer.writeStartElement("Data");//Data
	writer.writeTextElement("Samples", QString().setNum(input(0)->getNbSample()));//Samples
	writer.writeTextElement("File",QString::fromStdString (input(0)->getXEMData()->getDataFile()._fileName));
	if( isBinary( input(0)->getTabModelTypeI(0)->getModelName() ) ){
		writer.writeStartElement("Factor");
		for(int i=0; i<input(0)->getPbDimension(); ++i){
			writer.writeTextElement("Modality", QString().setNum(static_cast<const XEMBinaryData* >( input(0)->getXEMData() )->getTabNbModality()[i]));//Modality
		}
		writer.writeEndElement();//ferme Factor
	}
	writer.writeTextElement("Weight", QString::fromStdString (input(0)->getXEMData()->getFileNameWeight()));
	writer.writeEndElement();//ferme Data

	writer.writeStartElement("Model");//Model
	for (int i=0; i<input(0)->getNbModelType(); ++i){
		writer.writeTextElement("Model", QString::fromStdString (XEMModelNameToString( input(0)->getTabModelTypeI(i)->getModelName() )));
	}
	writer.writeEndElement();//ferme l'élément model

	writer.writeStartElement("Strategy");//Strategy
	writer.writeTextElement("NbTry", QString().setNum(input(0)->getStrategy(0)->getNbTry()));
	writer.writeStartElement("Type");//Type de strategie
	XEMStrategyInitName typeName = input(0)->getStrategy(0)->getStrategyInit()->getStrategyInitName();
	writer.writeTextElement("Name", QString::fromStdString (XEMStrategyInitNameToString(typeName)));
	switch (typeName){
		case RANDOM :
      		case SMALL_EM :
      		case CEM_INIT :
      		case SEM_MAX :
        		break ;
      		case USER :
        	{
			writer.writeStartElement("Parameters");//parameters
			if (_rootItem->getDataType() == MVCRootTreeItem::Qualitative){
				writer.writeAttribute("Type", "Binary");
			}else if (_rootItem->getDataType() == MVCRootTreeItem::Quantitative){
				writer.writeAttribute("Type", "EDDA");
			}
			writer.writeAttribute("NbCluster", QString().setNum(input(0)->getTabNbCluster()[0]));
			writer.writeEndElement();//ferme l'élément parameters
			break;
		}
		case USER_PARTITION :
        	{
			writer.writeTextElement("Parameters","");
			break;
        	}
        	break ;
      		default :
        	break ;
    	}
	writer.writeEndElement();//ferme l'élément type de strategie
	writer.writeStartElement("Algorithm");//algo
	writer.writeAttribute("Number", QString().setNum(input(0)->getStrategy(0)->getNbAlgo()));
	for (int i=0; i<input(0)->getStrategy(0)->getNbAlgo(); ++i){
		writer.writeStartElement("Algo");
		writer.writeAttribute("Rank", QString().setNum(i+1));
		writer.writeTextElement("AlgoName", QString::fromStdString (XEMAlgoNameToString( input(0)->getStrategy(0)->getAlgo(i)->getAlgoName() )));
		writer.writeStartElement("Rule");
		writer.writeTextElement("NbIteration", QString().setNum(input(0)->getStrategy(0)->getAlgo(i)->getNbIteration()));
		writer.writeTextElement("Epsilon", QString().setNum(input(0)->getStrategy(0)->getAlgo(i)->getEpsilon()));
		writer.writeEndElement();//ferme l'élément Rule
		writer.writeEndElement();//ferme l'élément Algo
	}
	writer.writeEndElement();//ferme l'élément Algorithm
	writer.writeEndElement();//ferme l'élément Strategy

	writer.writeStartElement("Criterion");
	writer.writeAttribute("Number",QString().setNum(input(0)->getNbCriterionName()));
	for (int i=0; i<input(0)->getNbCriterionName(); ++i){
		writer.writeTextElement("CriterionName", QString::fromStdString (XEMCriterionNameToString(input(0)->getCriterionName(i))));
	}
	writer.writeEndElement();//ferme l'élément Criterion

	if (input(0)->getTabPartition()){
		writer.writeTextElement("Partition", QString::fromStdString (input(0)->getTabPartitionI(0)->getPartitionFile()._fileName ));
	}else{
		writer.writeTextElement("Partition", QString::fromStdString (XEMMVCModel::DEFAULTFILENAME));
	}
	writer.writeEndElement();//ferme l'élément Input

	writer.writeEndDocument();
	file.close();

	return res;

}*/
