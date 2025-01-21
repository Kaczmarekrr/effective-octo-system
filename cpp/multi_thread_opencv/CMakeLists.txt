cmake_minimum_required(VERSION 3.15)
project(Display CXX)

find_package(tensorflowlite REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(Display src/upcoming_ver.cpp)

target_link_libraries(Display PRIVATE tensorflow::tensorflowlite opencv::opencv)
