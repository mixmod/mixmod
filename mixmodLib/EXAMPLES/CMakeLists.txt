
#sources
file(GLOB sources main.cpp clustering/*.cpp discriminant_analysis/*.cpp)
add_executable(mixmod_example ${sources})
target_link_libraries(mixmod_example mixmod)
#On install:

option(MIXMOD_INSTALL_EXAMPLES "install examples" OFF)
if (MIXMOD_INSTALL_EXAMPLES)
  install(TARGETS mixmod_example DESTINATION bin COMPONENT dev)
endif ()

macro(mixmodlib_add_test code)
  add_test(NAME ${code}_example COMMAND mixmod_example ${code} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endmacro()

foreach(num RANGE 1 14)
  mixmodlib_add_test(c${num})
endforeach()

foreach(num RANGE 1 5)
  mixmodlib_add_test(da${num})
endforeach()
