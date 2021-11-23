/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMChoiceColumnConverter.h  description
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

#ifndef GUIMCHOICECOLUMNCONVERTER_H
#define GUIMCHOICECOLUMNCONVERTER_H

#include <QtGui>
#include <vector>

using namespace std;

class GUIMLabel : public QLabel {

	Q_OBJECT

public :

	GUIMLabel( QWidget* = NULL );
	GUIMLabel( const QString & text, QWidget * = NULL, Qt::WindowFlags f = 0 );
	virtual ~GUIMLabel();

	void setId(int num);

private :

	int _id;

protected :

	virtual void mousePressEvent ( QMouseEvent * event);

signals :

	void clickedOn(int id);
};


class GUIMChoiceColumnConverter : public QWidget {
	Q_OBJECT

public :

	GUIMChoiceColumnConverter();
	virtual ~GUIMChoiceColumnConverter();

	void updateChoiceColumnConverter(int64_t nbColumn);

	///selectors
	vector< QLabel *> getLabel() const {
		return _vLabel;
	};
	QVector< QButtonGroup * > getVButtonGroup() const {
		return _vButtonGroup;
	};
	QVector< QSpinBox *> getFactor() const {
		return _vFactor;
	};
	bool getAtLeastOneColumnIsUsed() const {
		return _atLeastOneColumnIsUsed;
	};
	bool goodColumnConfiguration() const;

public slots :

	void verifyButton(QAbstractButton* button);
	void oneColumnIsChanged(int);
	void checkAll(int num);

	///return the nb of factor for the i-nth-1 spinbox (index=[0.._vFactor.size()-1])
	int64_t getNbFactor(int64_t index);

private:

	vector< QLabel *> _vLabel;
	QVector< QButtonGroup * > _vButtonGroup;
	QVector< QSpinBox *> _vFactor;

	bool _atLeastOneColumnIsUsed;

	QGridLayout * _mainLayout;

	void addRow(int64_t row);
};

//matching to the ordering of column type
enum ColumnTypeForRadioButton {
    USELESS = 0,
    QUANTITATIVE = 1,
    QUALITATIVE = 2,
    WEIGHT = 3,
    NAME = 4,
    NBCOLUMNTYPE = 5
};

QString ColumnTypetoString(ColumnTypeForRadioButton columnType);

#endif // GUIMCHOICECOLUMNCONVERTER_H
