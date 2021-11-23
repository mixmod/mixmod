#for headers from mixmodIOStream
include_directories(${CMAKE_SOURCE_DIR}/SRC)
#for headers from other modules
include_directories(${CMAKE_INSTALL_PREFIX}/include)
#NEWMAT (current mathematical library)
#TODO: shouldn't be needed, since mixmodIOStream doesn't call its methods
include_directories(${CMAKE_INSTALL_PREFIX}/include/NEWMAT)

#Include Eigen files
include_directories(${CMAKE_SOURCE_DIR}/../../mixmodLib/trunk/SRC/Eigen)

# libxml++ stuff
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
find_package(LibXML++ REQUIRED)
include_directories(${LibXML++_INCLUDE_DIRS})
set(LIBS ${LIBS} ${LibXML++_LIBRARIES})
add_definitions("-DXEM_RESOURCES_PATH=\"${CMAKE_INSTALL_PREFIX}/share/mixmod/resources/\"")
# that is because of auto_ptr deprecation warnings in libxml++2.6. To be removed ASAP
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")

#find libraries from other modules
find_library(libmixmod mixmod PATHS ${CPACK_PACKAGING_INSTALL_PREFIX}/lib ${CMAKE_INSTALL_PREFIX}/lib NO_DEFAULT_PATH)
message("libmixmod found here : "  ${libmixmod})

#QT
#FIND_PACKAGE( Qt4 REQUIRED )
#SET(QT_USE_QTXML TRUE)
#SET(QT_USE_QTXMLPATTERNS TRUE)
#SET(QT_USE_QTNETWORK TRUE)
#INCLUDE( ${QT_USE_FILE} )
#SET(QT_LIBRARIES ${QT_LIBRARIES} ${QT_QTXML_LIBRARY} ${QT_QTXMLPATTERNS_LIBRARY} ${QT_QTNETWORK_LIBRARY})
#QT4_ADD_RESOURCES(resource_schemas ${CMAKE_SOURCE_DIR}/SRC/XML_specs/schema.qrc)


#set(XML_resource ${resource_schemas})

#Generation de la liste des fichiers sources
FILE(GLOB mixmod_iostream_src ${CMAKE_SOURCE_DIR}/SRC/mixmod_iostream/*.cpp)
FILE(GLOB mixmod_iostream_h ${CMAKE_SOURCE_DIR}/SRC/mixmod_iostream/*.h)

ADD_LIBRARY(mixmod_iostream SHARED ${mixmod_iostream_src}) # ${XML_resource})
#TARGET_LINK_LIBRARIES(mixmod_iostream ${QT_LIBRARIES} ${mixmodLib})
TARGET_LINK_LIBRARIES(mixmod_iostream ${LibXML++_LIBRARIES}  ${libmixmod})

SET_TARGET_PROPERTIES(mixmod_iostream 
	PROPERTIES VERSION "2.4.0")

INSTALL(TARGETS mixmod_iostream
	LIBRARY DESTINATION lib
	COMPONENT libraries)

INSTALL(FILES ${mixmod_iostream_h}        
	DESTINATION include/mixmod_iostream
	COMPONENT headers)
