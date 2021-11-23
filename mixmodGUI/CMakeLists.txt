# Configuration
#--------------
cmake_minimum_required(VERSION 2.8.5)
project(mixmodGUI)
#include(${CMAKE_SOURCE_DIR}/../../../../cmake_shared_config.txt)


# Installation prefix, packaging prefix
#--------------------------------------
if (NOT DEFINED CMAKE_INSTALL_PREFIX)
	set(CMAKE_INSTALL_PREFIX "/usr/local")
endif ()
message("CMAKE_INSTALL_PREFIX :"  ${CMAKE_INSTALL_PREFIX})
if (NOT DEFINED CPACK_PACKAGING_INSTALL_PREFIX)
	set(CPACK_PACKAGING_INSTALL_PREFIX "/usr")
endif ()
message("CPACK_PACKAGING_INSTALL_PREFIX : " ${CPACK_PACKAGING_INSTALL_PREFIX})


# Release/Debug
#--------------
IF(NOT  CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_BUILD_TYPE "Release")
endif ()
message("CMAKE_BUILD_TYPE : " ${CMAKE_BUILD_TYPE})

# Compiler settings
#-------------------
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
message("CMAKE_CXX_FLAGS_RELEASE : " ${CMAKE_CXX_FLAGS_RELEASE})
set(CMAKE_CXX_FLAGS_DEBUG "-g3")
message("CMAKE_CXX_FLAGS_DEBUG : " ${CMAKE_CXX_FLAGS_DEBUG})
message("CMAKE_CXX_FLAGS : " ${CMAKE_CXX_FLAGS})



#-----
#CPack
#-----
INCLUDE(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "2")
set(CPACK_PACKAGE_VERSION_PATCH "2")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Mixmod Graphical User Interface")
set(CPACK_PACKAGE_VENDOR "mixmodGUI")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/ReadMe.txt")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/license.txt")
set(CPACK_PACKAGE_CONTACT "contact@mixmod.org")
set(CPACK_PACKAGE_FILE_NAME 
	"mixmodGUI_${CPACK_PACKAGE_VERSION_MAJOR}-${CPACK_PACKAGE_VERSION_MINOR}-${CPACK_PACKAGE_VERSION_PATCH}_${CMAKE_SYSTEM_PROCESSOR}") 

# pakages .deb and .rpm
#----------------------
IF(UNIX)
	SET(CPACK_GENERATOR "DEB;RPM;TGZ" )
	SET(SUBDIR_LIB_INSTALL "mixmodGUI")
	#SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.15), libstdc++6 (>= 4.6.3), libgcc1 (>=1:4.6.3)") les dépendances sont gérées automatiquement avec la ligne set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
	set(CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "MixmodGUI")
	set(CPACK_COMPONENT_APPLICATIONS_DESCRIPTION "Mixmod Graphical User Interface")
	#set(CPACK_COMPONENT_HEADERS_DEPENDS libraries) #doesn't work! 
	#set(CPACK_COMPONENT_LIBRARIES_GROUP "lib")
	set(CPACK_COMPONENTS_ALL applications)
	set(CPACK_DEB_COMPONENT_INSTALL ON)
	set(CPACK_RPM_COMPONENT_INSTALL ON)
ENDIF(UNIX)

#other files included in the package
#-----------------------------------
# INSTALL(PROGRAMS ${CMAKE_SOURCE_DIR}/BIN/mixmodGUI 
# 	DESTINATION bin
# 	COMPONENT applications
# )

#TODO: LIB/ is empty => fill it
# mixmod sub-directory : mixmodLib, mixmodIO, mixmodMVC, mixmod_qt, mixmod_newmat
# thridparty sub-directory : all QT ans Qwr dependencies
FILE(GLOB_RECURSE mixmodlibs 
	${CMAKE_SOURCE_DIR}/LIB/mixmod/*.so*
)

INSTALL(FILES ${mixmodlibs}
	DESTINATION lib/${SUBDIR_LIB_INSTALL}/mixmod
	COMPONENT applications
)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
# FILE(GLOB_RECURSE thirdpartylibs 
# 	${CMAKE_SOURCE_DIR}/LIB/thirdparty/*.so*
# )
# 
# INSTALL(FILES ${thirdpartylibs}
# 	DESTINATION lib/${SUBDIR_LIB_INSTALL}/thirdparty
# 	COMPONENT applications
# )


#projects examples
FILE(GLOB examples 
	${CMAKE_SOURCE_DIR}/mxd/*.mixmod
	${CMAKE_SOURCE_DIR}/mxd/*.dat
	${CMAKE_SOURCE_DIR}/mxd/*.mxd)
INSTALL(FILES ${examples}
	DESTINATION share/mixmodGUI/examples
	COMPONENT applications)

#TODO: also install documentation in share/mixmod/doc...


include(CPack)


# "Recurse" in SRC/
#------------------
ADD_SUBDIRECTORY(SRC)
