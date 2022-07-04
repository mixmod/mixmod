
#sources
file(GLOB sources main.cpp clustering/*.cpp discriminant_analysis/*.cpp)
add_executable(mixmod_example ${sources})
target_include_directories(mixmod_example PRIVATE ${CMAKE_SOURCE_DIR}/SRC ${CMAKE_SOURCE_DIR}/SRC/mixmod/Utilities/)
target_link_libraries(mixmod_example mixmod)
#On install:
INSTALL(TARGETS mixmod_example DESTINATION bin COMPONENT dev)

macro(mixmodlib_add_test code)
  add_test(NAME ${code}_example COMMAND mixmod_example ${code} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endmacro()

foreach(num RANGE 1 14)
  mixmodlib_add_test(c${num})
endforeach()

foreach(num RANGE 1 5)
  mixmodlib_add_test(da${num})
endforeach()
