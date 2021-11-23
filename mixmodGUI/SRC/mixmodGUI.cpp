/***************************************************************************
                             SRC/mixmodGUI.cpp  description
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
#include <QApplication>
#include <QVariant>
#include "mixmod_mvc/Util.h"


#include "GUIMixmod.h"

int main( int argc, char** argv )
{
  
  
  // Test date
  QDate currentDate = QDate::currentDate();
  QDate limitDate(2035,12,31);
  if (currentDate > limitDate){
    QApplication app( argc, argv );
    QPixmap pixmap(":/beginMixmod.png");
    QWidget window;
    QString message("\nThis testing mixmodGUI version is obsolete.\n Please go to www.mixmod.org to download a new one\n");
    QLabel * label1 = new QLabel(message);
    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(label1);
    QLabel * label2 = new QLabel();
    label2->setPixmap(pixmap);
    layout->addWidget(label2);
    window.setLayout(layout);
    window.show();
    return app.exec();
  }
  else{
    QApplication::setStyle("cleanlooks");
    QApplication app( argc, argv );
    QPixmap pixmap(":/beginMixmod.png");
    QSplashScreen splash(pixmap);
    splash.show();
	
    GUIMixmod mixmod ;

    QTimer::singleShot(1000, &splash, SLOT(close()));
    QTimer::singleShot(1100, &mixmod, SLOT(show()));
	
    mixmod.show();	
    return app.exec();
  }
}
