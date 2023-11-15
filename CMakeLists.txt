# Configuration
#--------------
cmake_minimum_required(VERSION 3.5)
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type")
PROJECT(mixmod)

list (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/UTIL/cmake/")

option (BUILD_SHARED_LIBS "shared/static libs" ON)

#Eigen stuff
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
include_directories(${EIGEN3_INCLUDE_DIRS})
message(STATUS "libeigen found here : "  ${EIGEN3_INCLUDE_DIRS})

#GSL stuff
# find_package(GSL)
# find_package(BLAS)
# IF(GSL_FOUND AND BLAS_FOUND)
#   include_directories(${GSL_INCLUDES})
#   include_directories(${BLAS_INCLUDES})
#   message(STATUS "libgsl found here : "  ${GSL_INCLUDES})
# ELSEIF(NOT GSL_FOUND AND BLAS_FOUND)
#   message(STATUS "libgsl not found")
# ELSEIF(NOT BLAS_FOUND)
#   message(STATUS "libblas not found")
# ENDIF()
#
# #Armadillo stuff
# find_package(Armadillo)
# IF(ARMADILLO_FOUND)
#   include_directories(${ARMADILLO_INCLUDE_DIRS})
#   message(STATUS "libarmadillo found here : "  ${ARMADILLO_INCLUDE_DIRS})
# ELSEIF(NOT ARMADILLO_FOUND)
#   message(STATUS "libarmadillo not found")
# ENDIF()
#
# #ITpp stuff
# find_package(ITpp)
# IF(ITPP_FOUND)
#   include_directories(${ITPP_INCLUDE_DIR})
#   message(STATUS "libitpp found here : "  ${ITPP_INCLUDE_DIR})
# ELSEIF(NOT ITPP_FOUND)
#   message(STATUS "libitpp not found")
# ENDIF()

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
message(STATUS "CMAKE_INSTALL_PREFIX :"  ${CMAKE_INSTALL_PREFIX})

if (NOT DEFINED CPACK_PACKAGING_INSTALL_PREFIX)
	set(CPACK_PACKAGING_INSTALL_PREFIX "/usr")
endif ()
message(STATUS "CPACK_PACKAGING_INSTALL_PREFIX : " ${CPACK_PACKAGING_INSTALL_PREFIX})

# Release/Debug
#--------------
message(STATUS "CMAKE_BUILD_TYPE : " ${CMAKE_BUILD_TYPE})

# Compiler settings
#-------------------
set (CMAKE_CXX_STANDARD 17)
find_package(OpenMP)
if (OPENMP_FOUND)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()
message(STATUS "CMAKE_CXX_FLAGS : " ${CMAKE_CXX_FLAGS})

#fix related to CMP0009. See cmake --help-policy CMP0009
#NOTE: we should not need it if required cmake VERSION >= 2.8.X... (?!)
if(POLICY CMP0009)
	cmake_policy(SET CMP0009 NEW)
endif(POLICY CMP0009)

enable_testing()

add_subdirectory(mixmodLib)

option (MIXMOD_BUILD_IOSTREAM "build iostream" OFF)
if (MIXMOD_BUILD_IOSTREAM)
  add_subdirectory (mixmodIOStream)
endif ()

option (MIXMOD_BUILD_CLI "build cli" OFF)
if (MIXMOD_BUILD_CLI AND MIXMOD_BUILD_IOSTREAM)
  add_subdirectory (mixmodCLI)
endif ()
