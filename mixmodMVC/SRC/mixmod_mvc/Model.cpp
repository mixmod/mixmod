/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/Model.cpp  description
    copyright            : (C) MIXMOD Team - 2001-2013
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
#include "mixmod_mvc/Model.h"
#include "mixmod/Kernel/IO/QuantitativeColumnDescription.h"
#include "mixmod/Kernel/IO/QualitativeColumnDescription.h"

namespace XEM {
namespace MVC {


const std::string Model::DEFAULTFILENAME ("NONE");

// destructor
Model::~Model() {
	clearItem();
	clearMain();
}


Model::Model(ClusteringMain * cMain) {
	_mItem = NULL ;
	_cMain = cMain;
}



/********************/
// construct
/********************/

// Clustering Main with gaussian Data
void Model::constructClusteringMain(int64_t iNbSample, int64_t iPbDimension, vector<int64_t> iNbCluster, const std::string & iDataFileName) {
	clearMain();

	vector<ColumnDescription *> columnDescription;
	columnDescription.resize(iPbDimension);
	for (int64_t j=0; j<iPbDimension; j++) {
		columnDescription[j] = new QuantitativeColumnDescription(j);
	}

	DataDescription dataDescription(iNbSample, iPbDimension, columnDescription, FormatNumeric::txt, iDataFileName);

	ClusteringInput * input = new ClusteringInput( iNbCluster , dataDescription);
	_cMain = new ClusteringMain(input);
}


// Clustering Main with binary Data
void Model::constructClusteringMain(int64_t iNbSample, int64_t iPbDimension, vector<int64_t> iNbCluster, const std::string & iDataFileName, vector<int64_t> iModality) {
	clearMain();
	vector<ColumnDescription *> columnDescription;
	columnDescription.resize(iPbDimension);
	for (int64_t j=0; j<iPbDimension; j++) {
		columnDescription[j] = new QualitativeColumnDescription(j, iModality[j]);
	}

	DataDescription dataDescription(iNbSample, iPbDimension, columnDescription, FormatNumeric::txt, iDataFileName);

	ClusteringInput * input = new ClusteringInput( iNbCluster , dataDescription);
	_cMain = new ClusteringMain(input);
}


// Clustering Main with dataDescription
void Model::constructClusteringMain(vector<int64_t> iNbCluster, DataDescription & dataDescription) {
	clearMain();

	ClusteringInput * input = new ClusteringInput( iNbCluster , dataDescription);
	_cMain = new ClusteringMain(input);
}

// DA Main with gaussian Data
void Model::constructDAMain(int64_t iNbSample, int64_t iPbDimension, int64_t iNbCluster, const std::string & iDataFileName, const string & iDataPartitionFileName, const string iDataFileNameToClassify) {
	// TODO

}


// DA Main with binary Data
void Model::constructDAMain(int64_t iNbSample, int64_t iPbDimension, int64_t iNbCluster, const std::string & iDataFileName, const string & iDataPartitionFileName, const string iDataFileNameToClassify, vector<int64_t> iModality) {
	//TODO
}

}
}
