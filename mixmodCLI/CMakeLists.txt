cmake_minimum_required(VERSION 2.8.5)
PROJECT(mixmodCLI)

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
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wno-deprecated")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -Wno-deprecated")
find_package(OpenMP)
if (OPENMP_FOUND)
 set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OpenMP_CXX_FLAGS}")
 set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OpenMP_CXX_FLAGS}")
endif()
message("CMAKE_CXX_FLAGS_RELEASE : " ${CMAKE_CXX_FLAGS_RELEASE})
message("CMAKE_CXX_FLAGS_DEBUG : " ${CMAKE_CXX_FLAGS_DEBUG})
message("CMAKE_CXX_FLAGS : " ${CMAKE_CXX_FLAGS})

#find Mixmod libraries
find_library(libmixmod mixmod PATHS ${CPACK_PACKAGING_INSTALL_PREFIX}/lib ${CMAKE_INSTALL_PREFIX}/lib NO_DEFAULT_PATH)
message("libmixmod found here : "  ${libmixmod})
find_library(libmixmod_iostream mixmod_iostream PATHS ${CPACK_PACKAGING_INSTALL_PREFIX}/lib ${CMAKE_INSTALL_PREFIX}/lib NO_DEFAULT_PATH)
message("libmixmod_iostream found here : "  ${libmixmod_iostream})


#include_directories
include_directories(${CMAKE_INSTALL_PREFIX}/include)
#include_directories(${CMAKE_INSTALL_PREFIX}/include/mixmod_iostream)
#Include Eigen files
include_directories(${CMAKE_SOURCE_DIR}/../../../../dev/components/mixmodLib/trunk/SRC/Eigen)

# libxml++ stuff
message("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../../../dev/UTIL/cmake")
find_package(LibXML++ REQUIRED)
include_directories(${LibXML++_INCLUDE_DIRS})
set(LIBS ${LIBS} ${LibXML++_LIBRARIES})
message("-DXEM_RESOURCES_PATH=\"${CMAKE_INSTALL_PREFIX}/share/mixmod/resources/\"")
add_definitions("-DXEM_RESOURCES_PATH=\"${CMAKE_INSTALL_PREFIX}/share/mixmod/resources/\"")

SET(Mixmod_cli_src SRC/mixmodCli.cpp)
ADD_EXECUTABLE("mixmod-cli" ${Mixmod_cli_src})

#GSL stuff
find_package(GSL)
find_package(BLAS)
IF(GSL_FOUND AND BLAS_FOUND)
  include_directories(${GSL_INCLUDES})
  include_directories(${BLAS_INCLUDES})
  message("libgsl found here : "  ${GSL_INCLUDES})
  set(LIBS ${LIBS} ${GSL_LIBRARIES})
  set(LIBS ${LIBS} ${BLAS_LIBRARIES})
ELSEIF(NOT GSL_FOUND AND BLAS_FOUND)
  message("libgsl not found")
ELSEIF(NOT BLAS_FOUND)
  message("libblas not found")
ENDIF()

#Armadillo stuff
find_package(Armadillo)
IF(ARMADILLO_FOUND)
  include_directories(${ARMADILLO_INCLUDE_DIRS})
  message("libarmadillo found here : "  ${ARMADILLO_INCLUDE_DIRS})
  set(LIBS ${LIBS} ${ARMADILLO_LIBRARIES})
ELSEIF(NOT ARMADILLO_FOUND)
  message("libarmadillo not found")
ENDIF()

#ITpp stuff
find_package(ITpp)
IF(ITPP_FOUND)
  include_directories(${ITPP_INCLUDE_DIR})
  message("libitpp found here : "  ${ITPP_INCLUDE_DIR})
  set(LIBS ${LIBS} ${ITPP_LIBRARY})
ELSEIF(NOT ITPP_FOUND)
  message("libitpp not found")
ENDIF()


TARGET_LINK_LIBRARIES("mixmod-cli" ${libmixmod} ${libmixmod_iostream} ${LIBS})

INSTALL(TARGETS "mixmod-cli" DESTINATION bin)
