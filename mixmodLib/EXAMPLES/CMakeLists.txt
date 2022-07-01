
#sources
file(GLOB sources main.cpp clustering/*.cpp discriminant_analysis/*.cpp)
add_executable(mixmod_example ${sources})
target_include_directories(mixmod_example PRIVATE ${CMAKE_SOURCE_DIR}/SRC ${CMAKE_SOURCE_DIR}/SRC/mixmod/Utilities/)
target_link_libraries(mixmod_example mixmod)
#On install:
INSTALL(TARGETS mixmod_example DESTINATION bin COMPONENT dev)
