cmake_minimum_required(VERSION 3.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
include_directories(include "./include" "./src")
project( trainingJackson )

include(~/GitHub/testDlib/dlib-19.5/dlib/cmake)
find_package( OpenCV )
add_executable(${PROJECT_NAME} ./src/app.cpp)
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} dlib::dlib)
