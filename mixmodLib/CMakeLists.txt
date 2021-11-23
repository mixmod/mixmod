# Configuration
#--------------
cmake_minimum_required(VERSION 2.8.5)
PROJECT(mixmod)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../UTIL/cmake/")

#Eigen stuff
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
IF(EIGEN3_FOUND)
	include_directories(${EIGEN3_INCLUDE_DIRS})
	message("libeigen found here : "  ${EIGEN3_INCLUDE_DIRS})
ELSEIF(NOT EIGEN3_FOUND)
  message("libeigen not found")
ENDIF()

#GSL stuff
find_package(GSL)
find_package(BLAS)
IF(GSL_FOUND AND BLAS_FOUND)
  include_directories(${GSL_INCLUDES})
  include_directories(${BLAS_INCLUDES})
  message("libgsl found here : "  ${GSL_INCLUDES})
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
ELSEIF(NOT ARMADILLO_FOUND)
  message("libarmadillo not found")
ENDIF()

#ITpp stuff
find_package(ITpp)
IF(ITPP_FOUND)
  include_directories(${ITPP_INCLUDE_DIR})
  message("libitpp found here : "  ${ITPP_INCLUDE_DIR})
ELSEIF(NOT ITPP_FOUND)
  message("libitpp not found")
ENDIF()

#usage "cmake . " + Options :
#	-DCMAKE_INSTALL_PREFIX="<Path>" 
#		Default : /usr/local
#		-> /usr/local/lib : libmixmod.so
#		-> /usr/local/include/mixmod : *.h  + /usr/local/share/mixmod : EXAMPLES (module dev)
#	-DCMAKE_BUILD_TYPE="Debug" Default="Release"

# Switch: cmake .. -DCMAKE_INSTALL_PREFIX="/usr/" ou "C:\Windows\ProgramFiles\mixmod\" ou ...
# NOTE: should be copied in every individual source package

# cpack -G DEB

# version mumber
set(CPACK_PACKAGE_VERSION_MAJOR "3")
set(CPACK_PACKAGE_VERSION_MINOR "2")
set(CPACK_PACKAGE_VERSION_PATCH "2")

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

#fix related to CMP0009. See cmake --help-policy CMP0009
#NOTE: we should not need it if required cmake VERSION >= 2.8.X... (?!)
if(POLICY CMP0009)
	cmake_policy(SET CMP0009 NEW)
endif(POLICY CMP0009)


#------------------------
# Recurse in directories
#------------------------
ADD_SUBDIRECTORY(SRC)
#ADD_SUBDIRECTORY(EXAMPLES)

#install some extra files
install(FILES "README" "LICENSE" 
	DESTINATION share/mixmod
	COMPONENT dev)

#-----
#CPack
#-----
include(${CMAKE_SOURCE_DIR}/CPackLists.txt)
include(CPack)
