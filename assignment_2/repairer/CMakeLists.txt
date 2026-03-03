cmake_minimum_required(VERSION 3.16)

project(assignment_2_detector)

find_package(OpenCV REQUIRED)

add_executable(main ./src/main.cpp)

target_link_libraries(main ${OpenCV_LIBS})