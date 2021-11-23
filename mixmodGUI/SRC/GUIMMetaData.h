/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMMetaData.h  description
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
#ifndef __GUIM_METADATA_H__
#define __GUIM_METADATA_H__

#include "mixmod/Kernel/IO/Input.h"
#include "mixmod/Kernel/IO/Data.h"
#include "mixmod/Kernel/IO/Partition.h"
#include "mixmod/Utilities/Util.h"
#include "mixmod/Clustering/ClusteringStrategy.h"
#include "mixmod/Clustering/ClusteringStrategyInit.h"

#include "MVCMixmod.h"
#include <QSpinBox>
#include <QMetaType>

Q_DECLARE_METATYPE(QSpinBox*)

//Q_DECLARE_METATYPE(XEMInput)
Q_DECLARE_METATYPE(XEM::Input*)
Q_DECLARE_METATYPE(const XEM::Input*)
//qRegisterMetaType<XEMInput>("XEMInput");
//qRegisterMetaTypeStreamOperators<XEMInput *>()

Q_DECLARE_METATYPE(XEM::Data*)
Q_DECLARE_METATYPE(const XEM::Data*)

Q_DECLARE_METATYPE(XEM::Partition)
Q_DECLARE_METATYPE(XEM::Partition*)
Q_DECLARE_METATYPE(const XEM::Partition*)
Q_DECLARE_METATYPE(XEM::Partition**)
Q_DECLARE_METATYPE(const XEM::Partition**)

Q_DECLARE_METATYPE(XEM::ModelName)
Q_DECLARE_METATYPE(XEM::ModelName*)
Q_DECLARE_METATYPE(const XEM::ModelName*)

//Q_DECLARE_METATYPE(XEMModelType)
Q_DECLARE_METATYPE(XEM::ModelType*)
Q_DECLARE_METATYPE(const XEM::ModelType*)
Q_DECLARE_METATYPE(XEM::ModelType**)
Q_DECLARE_METATYPE(const XEM::ModelType**)

Q_DECLARE_METATYPE(XEM::AlgoName)
Q_DECLARE_METATYPE(XEM::StrategyInitName)

Q_DECLARE_METATYPE(XEM::AlgoStopName)

Q_DECLARE_METATYPE(XEM::ClusteringStrategyInit*)
Q_DECLARE_METATYPE(const XEM::ClusteringStrategyInit*)

Q_DECLARE_METATYPE(XEM::Parameter*)
Q_DECLARE_METATYPE(const XEM::Parameter*)
Q_DECLARE_METATYPE(XEM::Parameter**)
Q_DECLARE_METATYPE(const XEM::Parameter**)

Q_DECLARE_METATYPE(XEM::CriterionName)
Q_DECLARE_METATYPE(XEM::CriterionName*)
Q_DECLARE_METATYPE(const XEM::CriterionName*)

#endif // __GUIM_METADATA_H__
