/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMConverter.h  description
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

#ifndef GUIMCONVERTER_H
#define GUIMCONVERTER_H

#include "GUIUtil.h"
#include "GUIMChoiceColumnConverter.h"

class GUIMConverter : public QDialog {

	Q_OBJECT

public :

	GUIMConverter();

	~GUIMConverter();

private slots :

	void ok() ;
	void discard() ;
	void setFilename();
	void setDirectoryNumericFile();
	void setDirectoryXMLFile();
	void verifyTextInput( QString text );
	void verifyTextNumericMixmod( QString text );
	void verifyTextXMLMixmod( QString text );
	void updateOutput( QString text );
	void updateChoiceColumn(int nbColumn);

private :

	void init();
	void createNbSampleBox();
	void createNbColumnBox();
	void createFilenameBox();
	void createFormatBox();
	void createChoiceColumn();
	void createMixmodFilenameBox();

	int64_t _hPos;
	int64_t _hPosInput;
	int64_t _hPosOutput;
	QString TEXT_VALIDATOR;
	QString FILE_VALIDATOR;
	QString DIR_VALIDATOR;
	bool _validateInput ;
	bool _validateNumericMixmod ;
	bool _validateXMLMixmod ;

	QValidator *_validatorXML;
	QValidator *_validatorNumeric;

	//main grid
	QGridLayout *layout;
	QGridLayout *_gridInput;
	QGridLayout *_gridOutput;
	QGroupBox *groupBoxInput;

	QDialogButtonBox *_buttonBox;

	//nbSample
	QSpinBox * _nbSampleSpinBox;

	//nbColumn
	QSpinBox * _nbColumnSpinBox;

	//ChoiceColumn
	QScrollArea * sa;
	GUIMChoiceColumnConverter * _choiceColumnConverter;

	//Filename
	QLineEdit * _filenameEdit;
	QPushButton * _filenameButton;
	QLabel * _validatorlabel;

	//Format
	vector<QString> _formatVector;
	QComboBox * _formatComboBox;
	int64_t _indexFormat;

	//Output
	QLineEdit* _filenameNumericMixmodEdit;
	QPushButton* _filenameNumericMixmodButton;
	QPushButton* _filenameXMLMixmodButton;
	QLineEdit* _filenameXMLMixmodEdit;
	QLabel* _validatorNumericlabel;
	QLabel* _validatorXMLlabel;
	QString _numericFilename;
	QString _XMLFilename;
};

#endif // GUIMCONVERTER_H
