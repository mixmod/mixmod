/***************************************************************************
                             SRC/mixmod/Kernel/Criterion/BICCriterion.cpp  description
    copyright            : (C) MIXMOD Team - 2001-2016
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
#include "mixmod/Kernel/Criterion/BICCriterion.h"
#include "mixmod/Kernel/Criterion/CriterionOutput.h"
#include "mixmod/Kernel/Model/Model.h"

namespace XEM
{

//-----------
// Constructor
//-----------
BICCriterion::BICCriterion(Model *model) : Criterion(model) {}

//----------
// Destructor
//----------
BICCriterion::~BICCriterion() {}

//---
// run
//---
void BICCriterion::run(CriterionOutput &output)
{
	// initialize value
	double value = 0.0;
	// initialize error
	Exception *error = &NOERROR;
	try {
		// false : to not compute fik because already done
		const double loglikelihood = _model->getLogLikelihood(false);
		const int64_t freeParameter = _model->getFreeParameter();
		const double logN = _model->getLogN();
		value = (-2 * loglikelihood) + (freeParameter * logN);
	} catch (Exception &e) {
		// add name to criterion output
		output.setCriterionName(BIC);
		// add error to criterion output
		output.setError(e);
		throw;
	}
	// add name to criterion output
	output.setCriterionName(BIC);
	// add value to criterion output
	output.setValue(value);
	// add error to criterion output
	output.setError(*error);
}

}
