cmake_minimum_required(VERSION 3.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
include_directories(include "./include" "./src")
project( face2yaml )

include(~/GitHub/dlib/dlib/cmake)
find_package( OpenCV )
add_executable(${PROJECT_NAME} ./src/${PROJECT_NAME}.cpp)
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} dlib::dlib)

add_executable(delaunay ./src/delaunay.cpp)
target_link_libraries(delaunay  ${OpenCV_LIBS})

add_executable(meanShape ./src/meanShape.cpp)
target_link_libraries(meanShape  ${OpenCV_LIBS})

add_executable(delaunayMeanShape ./src/delaunayMeanShape.cpp)
target_link_libraries(delaunayMeanShape  ${OpenCV_LIBS})
