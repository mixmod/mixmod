/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMAboutUs.cpp  description
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

#include "GUIMAboutUs.h"

GUIMAboutUs::GUIMAboutUs(QString & applicationName, QString & applicationVersion) : QDialog(), _applicationName(applicationName), _applicationVersion(applicationVersion) {
	setWindowTitle( tr("About Us") );

	setStyleSheet("background: white");
	setWindowIcon(QPixmap(":/logo.png"));

	setAttribute( Qt::WA_DeleteOnClose );
	setWindowModality (Qt::ApplicationModal);

	_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
	_buttonBox->setStyleSheet("QPushButton {background:white}");

	QVBoxLayout *mainLayout = new QVBoxLayout();
	layout = new QGridLayout();

	mainLayout->addLayout(layout);
	mainLayout->addWidget(_buttonBox);
	connect(_buttonBox, SIGNAL(accepted()), this, SLOT(ok()));
	fillLayout();

	setLayout(mainLayout);
}

GUIMAboutUs::~GUIMAboutUs() {
}

void GUIMAboutUs::ok() {
	close();
}

void GUIMAboutUs::fillLayout() {
	//--------
	//add Logo
	//--------
	QLabel * labelImage = new QLabel();
	QImage logo(":/logo.png");
	QSize size(_buttonBox->button(QDialogButtonBox::Ok)->sizeHint());
	logo = logo.scaledToHeight(_buttonBox->button(QDialogButtonBox::Ok)->height()*3, Qt::SmoothTransformation);

	labelImage->setPixmap(QPixmap::fromImage(logo));
	layout->addWidget(labelImage,0,0, 2,2);

	//--------
	//add Tex
	//--------
	QFont font;
	font.setBold( true );
	QLabel * descriptionLabel = new QLabel(_applicationName+" "+_applicationVersion);
	descriptionLabel->setFont(font);
	layout->addWidget(descriptionLabel, 0, 2);

	QLabel * descriptionLabel2 = new QLabel(tr("Mixmod software is a tool for fitting a mixture model of multivariate gaussian or multinomial components\nto a given data set with either a clustering, a density estimation or a discriminant analysis point of view.\n"));
	layout->addWidget(descriptionLabel2, 1, 2, 1, 2);

	QLabel * descriptionLabel3 = new QLabel(tr("MIXMODGUI license is described on Mixmod web site : www.mixmod.org.\n"));
	layout->addWidget(descriptionLabel3, 2, 2, 1, 2);

	QLabel * descriptionLabel4 = new QLabel("Copyright\nEmail\n");
	font.setBold( false );
	font.setUnderline(true);
	descriptionLabel4->setFont(font);
	QLabel * descriptionLabel5 = new QLabel("              (C) MIXMOD Team - 2001-2015\n              contact@mixmod.org\n");
	layout->addWidget(descriptionLabel4, 3, 2, 1, 1);
	layout->addWidget(descriptionLabel5, 3, 3, 1, 1);
}
