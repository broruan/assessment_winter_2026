cmake_minimum_required(VERSION 3.16)
project(assignment_0_detector LANGUAGES CXX)

find_package(OpenCV REQUIRED)

add_executable(detector ./src/detector.cpp)
add_executable(test ./src/test.cpp)

target_include_directories(detector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(detector ${OpenCV_LIBS})
target_link_libraries(test ${OpenCV_LIBS})