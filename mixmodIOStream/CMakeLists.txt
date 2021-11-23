# Configuration
#--------------
cmake_minimum_required(VERSION 2.8.5)
project(mixmod_iostream)

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

#include(${CMAKE_SOURCE_DIR}/../../../../cmake_shared_config.txt)

#
# Resources without QT
#

FILE(GLOB xml_resources 
  ${CMAKE_SOURCE_DIR}/SRC/XML_specs/*.xsd)
INSTALL(FILES ${xml_resources}
	DESTINATION share/mixmod/resources
	COMPONENT applications)


#-----
#CPack
#-----
# INCLUDE(InstallRequiredSystemLibraries)
# set(CPACK_PACKAGE_VERSION_MAJOR "2")
# set(CPACK_PACKAGE_VERSION_MINOR "4")
# set(CPACK_PACKAGE_VERSION_PATCH "0")
# set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Mixmod IOStream Library")
# set(CPACK_PACKAGE_VENDOR "MIXMOD")
# set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/ReadMe.txt")
# set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/license.txt")
# set(CPACK_PACKAGE_CONTACT "contact@mixmod.org")
# set(CPACK_PACKAGE_FILE_NAME "mixmodiostream_${CPACK_PACKAGE_VERSION_MAJOR}-${CPACK_PACKAGE_VERSION_MINOR}-${CPACK_PACKAGE_VERSION_PATCH}_${CMAKE_SYSTEM_PROCESSOR}") 

# pakages .deb and .rpm
#----------------------
# IF(UNIX)
# 	SET(CPACK_GENERATOR "DEB;RPM" )
# 	SET(SUBDIR_LIB_INSTALL "${CMAKE_SYSTEM_PROCESSOR}-linux-gnu")
# 	#SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.15), libstdc++6 (>= 4.6.3), libgcc1 (>=1:4.6.3)")
# 	SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6, libstdc++6, libgcc1 ")
# 	set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Mixmod IOStream librarie")
# 	set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "MixmodIOStream Headers")
# 	set(CPACK_COMPONENT_LIBRARIES_DESCRIPTION "MixmodIOstream shared library")
# 	set(CPACK_COMPONENT_HEADERS_DESCRIPTION "MixmodIOStream header files")
# 	set(CPACK_COMPONENT_HEADERS_DEPENDS libraries) #doesn't work! 
# 	set(CPACK_COMPONENT_LIBRARIES_GROUP "lib")
# 	set(CPACK_COMPONENT_HEADERS_GROUP "dev")
# 	set(CPACK_COMPONENTS_ALL libraries headers)
# 	set(CPACK_DEB_COMPONENT_INSTALL ON)
# 	set(CPACK_RPM_COMPONENT_INSTALL ON)
# ENDIF(UNIX)
# 
# include(CPack)


# Directories
#-------------
ADD_SUBDIRECTORY(SRC)
