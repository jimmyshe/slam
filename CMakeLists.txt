cmake_minimum_required(VERSION 3.1)
project(slam)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package( OpenCV REQUIRED )
set(SOURCE_FILES
    Features.cpp
    Features.h
    MainLoop.cpp
    MainLoop.h
    ReadRGBD.cpp
    ReadRGBD.h
    源.cpp)

add_executable(slam ${SOURCE_FILES})
target_link_libraries( slam ${OpenCV_LIBS} )