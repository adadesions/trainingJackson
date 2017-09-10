cmake_minimum_required(VERSION 3.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
include_directories(include "./include" "./src")
project( aam )

include(~/GitHub/dlib/dlib/cmake)
find_package( OpenCV )
add_executable( ${PROJECT_NAME} ./src/${PROJECT_NAME}.cpp )
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )

add_executable( core_aam ./src/core_aam.cpp )
target_link_libraries( core_aam ${OpenCV_LIBS} )