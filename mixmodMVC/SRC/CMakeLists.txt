#for headers from mixmodMVC
include_directories(${CMAKE_SOURCE_DIR}/SRC)
#for headers from other modules
include_directories(${CMAKE_INSTALL_PREFIX}/include)
#NEWMAT (current mathematical library)
#TODO: shouldn't be needed, since mixmodMVC doesn't call its methods
include_directories(${CMAKE_INSTALL_PREFIX}/include/NEWMAT)


#find libraries from other modules
find_library(libmixmod mixmod PATHS ${CPACK_PACKAGING_INSTALL_PREFIX}/lib ${CMAKE_INSTALL_PREFIX}/lib NO_DEFAULT_PATH)
message("libmixmod found here : "  ${libmixmod})
FIND_LIBRARY(libmixmodiostream mixmod_iostream PATHS ${CPACK_PACKAGING_INSTALL_PREFIX}/lib ${CMAKE_INSTALL_PREFIX}/lib NO_DEFAULT_PATH)
message("libmixmodiostream found here : "  ${libmixmodiostream})

#QT
FIND_PACKAGE(Qt4 REQUIRED)
SET(QT_USE_QTXML FALSE)
SET(QT_USE_QTXMLPATTERNS FALSE)
SET(QT_USE_QTNETWORK TRUE)
INCLUDE( ${QT_USE_FILE} )
#SET(QT_LIBRARIES ${QT_LIBRARIES} ${QT_QTXML_LIBRARY} ${QT_QTXMLPATTERNS_LIBRARY} ${QT_QTNETWORK_LIBRARY})
SET(QT_LIBRARIES ${QT_LIBRARIES} ${QT_QTNETWORK_LIBRARY})
# libxml++ stuff
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")
find_package(LibXML++ REQUIRED)
include_directories(${LibXML++_INCLUDE_DIRS})
#set(LIBS ${LIBS} ${LibXML++_LIBRARIES})
add_definitions("-DXEM_RESOURCES_PATH=\"${CMAKE_INSTALL_PREFIX}/share/mixmod/resources/\"")
#SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fmax-errors=1 -Wno-deprecated")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
#mixmodMVC
FILE(GLOB mixmod_mvc_src ${CMAKE_SOURCE_DIR}/SRC/mixmod_mvc/*.cpp)

ADD_LIBRARY(mixmod_mvc SHARED ${mixmod_mvc_src})
TARGET_LINK_LIBRARIES(mixmod_mvc ${libmixmod} ${mixmod_iostream_lib})

SET_TARGET_PROPERTIES(mixmod_mvc
	PROPERTIES VERSION "1.2.0")

INSTALL(TARGETS mixmod_mvc 
	LIBRARY DESTINATION lib
	COMPONENT libraries)

FILE(GLOB headers ${CMAKE_SOURCE_DIR}/SRC/mixmod_mvc/*.h)
INSTALL(FILES ${headers} 
	DESTINATION include/mixmod_mvc
	COMPONENT headers)
