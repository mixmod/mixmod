#for headers from mixmodGUI
include_directories(${CMAKE_SOURCE_DIR}/SRC)
#for headers from other modules
include_directories(${CMAKE_INSTALL_PREFIX}/include)
#NEWMAT (current mathematical library)
#TODO: shouldn't be needed, since mixmodGUI doesn't call its methods
include_directories(${CMAKE_INSTALL_PREFIX}/include/NEWMAT)
# next line needed for FindQwt.cmake and FindLibXML++.cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")

#find libraries from other modules
find_library(libmixmod mixmod PATHS ${CPACK_PACKAGING_INSTALL_PREFIX}/lib ${CMAKE_INSTALL_PREFIX}/lib NO_DEFAULT_PATH)
message("libmixmod found here : "  ${libmixmod})
FIND_LIBRARY(libmixmodiostream mixmod_iostream PATHS ${CPACK_PACKAGING_INSTALL_PREFIX}/lib ${CMAKE_INSTALL_PREFIX}/lib NO_DEFAULT_PATH)
message("libmixmodiostream found here : "  ${libmixmodiostream})
FIND_LIBRARY(libmixmodmvc mixmod_mvc PATHS ${CPACK_PACKAGING_INSTALL_PREFIX}/lib ${CMAKE_INSTALL_PREFIX}/lib NO_DEFAULT_PATH)
message("libmixmodmvc found here : "  ${libmixmodmvc})

# libxml++ stuff
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
find_package(LibXML++ REQUIRED)
message("LibXML++_LIBRARIES : "  ${LibXML++_LIBRARIES})
include_directories(${LibXML++_INCLUDE_DIRS})
# Qwt
#TODO: fix this, which will not work on Windows/MacOS for the moment

if (APPLE)
	FIND_PATH(Qwt_INCLUDE_DIR qwt.h PATHS /usr/local/qwt-6.0.0/include)
	SET(QWT_LIBRARY ${CMAKE_SOURCE_DIR}/LIB/thirdparty/libqwt.dylib)
elseif (WIN32)
	SET(QWT_LIBRARY ${CMAKE_SOURCE_DIR}/LIB/thirdparty/qwt6.dll)
else ()
	#FIND_PATH(Qwt_INCLUDE_DIR qwt.h PATHS /usr/include/qwt)
#	FIND_LIBRARY(Qwt_LIBRARY NAMES qwt PATHS /usr/lib)
 	#SET(Qwt_LIBRARY /usr/lib/libqwt.so.6)   
    find_package(Qwt REQUIRED)
    # The module defines the following variables:
    #  QWT_FOUND - the system has Qwt
    #  QWT_INCLUDE_DIR - where to find qwt_plot.h
    #  QWT_INCLUDE_DIRS - qwt includes
    #  QWT_LIBRARY - where to find the Qwt library
    #  QWT_LIBRARIES - aditional libraries
    #  QWT_MAJOR_VERSION - major version
    #  QWT_MINOR_VERSION - minor version
    #  QWT_PATCH_VERSION - patch version
    #  QWT_VERSION_STRING - version (ex. 5.2.1)
    #  QWT_ROOT_DIR - root dir (ex. /usr/local)
    message("QWT_FOUND: ${QWT_FOUND}")
    message("QWT_INCLUDE_DIR : ${QWT_INCLUDE_DIR}")
    message("QWT_INCLUDE_DIRS : ${QWT_INCLUDE_DIRS}")
    message("QWT_LIBRARY : ${QWT_LIBRARY}")
    message("QWT_LIBRARIES : ${QWT_LIBRARIES}")
    message("QWT_MAJOR_VERSION : ${QWT_MAJOR_VERSION}")
    message("QWT_MINOR_VERSION : ${QWT_MINOR_VERSION}")
    message("QWT_PATCH_VERSION : ${QWT_PATCH_VERSION}")
    message("QWT_VERSION_STRING : ${QWT_VERSION_STRING}")
    message("QWT_ROOT_DIR : ${QWT_ROOT_DIR}")

endif ()
INCLUDE_DIRECTORIES(${QWT_INCLUDE_DIR})
#message(${Qwt_INCLUDE_DIR})

#QT
FIND_PACKAGE(Qt4 REQUIRED)
SET(QT_USE_QTXML FALSE)
SET(QT_USE_QTXMLPATTERNS FALSE)
SET(QT_USE_QTNETWORK TRUE)
INCLUDE( ${QT_USE_FILE} )
SET(QT_LIBRARIES ${QT_LIBRARIES} ${QT_QTNETWORK_LIBRARY})
message("QT_LIBRARIES : "  ${QT_LIBRARIES})
QT4_ADD_RESOURCES(resource_images ${CMAKE_SOURCE_DIR}/SRC/IMAGES/images.qrc)
QT4_ADD_RESOURCES(resource_languages ${CMAKE_SOURCE_DIR}/SRC/languages/languages.qrc)
set(resource ${resource_images} ${resource_languages})
# that is because of auto_ptr deprecation warnings in libxml++2.6. To be removed ASAP
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
# libxml++ stuff
find_package(LibXML++ REQUIRED)
include_directories(${LibXML++_INCLUDE_DIRS})
set(LIBS ${LIBS} ${LibXML++_LIBRARIES})
add_definitions("-DXEM_RESOURCES_PATH=\"${CMAKE_INSTALL_PREFIX}/share/mixmod/resources/\"")
if(${QWT_MINOR_VERSION})
  add_definitions(-DQWT_6_1_X=1)
endif ()

#Ajout dans une variable des fichiers headers contenant 
#des slots ou la macro Q_OBJECT
set(MOC_HEADERS 
	GUIMAboutUs.h
	GUIMAbstractModifier.h
#GUIMAction.h
	GUIMAlgoModifier.h
	GUIMAlgoNameModifier.h
	GUIMChoiceColumnConverter.h
	GUIMConverter.h
	GUIMCriteriaModifier.h
	GUIMCriterionChildModifier.h
	GUIMDataCreator.h
#GUIMFileNameValidator.h
	GUIMGraphic.h
	GUIMGraphic2DQuantitative.h
	GUIMGraphicDockWidget.h
	GUIMGraphicManager.h
	GUIMGraphicQualitativeDiagram.h
	GUIMGraphicQuantitativeClass.h
	GUIMGraphicQuantitativeHist.h
	GUIMGraphicQuantitativePoint.h
	GUIMInitModifier.h
	GUIMInitParameterModifier.h
	GUIMKnownPartitionModifier.h 
#GUIMMetaData.h
	GUIMModelModifier.h
	GUIMNbStrategyTryModifier.h
	GUIMOutputModifier.h
	GUIMParameterInInitModifier.h
	GUIMProcessModifier.h
	GUIMProjectCreator.h
	GUIMSpinBoxesWidget.h
	GUIMStopRuleModifier.h
	GUIMStopRuleValueModifier.h
	GUIMTextEntryWidget.h
	GUIMTreeDelegate.h
	GUIMTreeModel.h
	GUIMTreeView.h
	GUIMWeightModifier.h
	GUIMixmod.h #MVCMixmod.h ?!
#GUIUtil.h, and MVCxxx.h
)

#Creation du code moc avec les fichiers headers contenu
#dans la variable MOC_HEADERS
QT4_WRAP_CPP(
	src
	${MOC_HEADERS})

#Generation de la liste des fichiers sources
FILE(GLOB MixmodQT_src ${CMAKE_SOURCE_DIR}/SRC/*.cpp)

ADD_LIBRARY(mixmod_qt SHARED ${MixmodQT_src} ${src})
TARGET_LINK_LIBRARIES(mixmod_qt ${QT_LIBRARIES} ${libmixmodmvc} ${QWT_LIBRARY} ${LibXML++_LIBRARIES})

#Used by Cpack
install(TARGETS mixmod_qt
	LIBRARY
	DESTINATION lib
	COMPONENT applications)

#-----------------------------------------------------------------------------------------
# mixmodGUI
#----------------------------------------------------------------------------------------
SET(mixmodGUI_src mixmodGUI.cpp)
ADD_EXECUTABLE(mixmodGUI_exe ${mixmodGUI_src} ${resource})
TARGET_LINK_LIBRARIES(mixmodGUI_exe mixmod_qt ${libmixmodmvc} ${QT_LIBRARIES} ${QWT_LIBRARY} ${libmixmodiostream} ${libmixmod})

#Used by Cpack
install(TARGETS mixmodGUI_exe
	RUNTIME
	DESTINATION bin
	COMPONENT applications)
