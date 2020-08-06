set (CMAKE_CXX_STANDARD 11)

cmake_minimum_required(VERSION 2.8)
project(main)
find_package(OpenCV REQUIRED)
add_executable(main 
               img_processing.h
               img_processing.cpp
               clustering.h
               clustering.cpp
               main.cpp)

target_link_libraries(main ${OpenCV_LIBS})
