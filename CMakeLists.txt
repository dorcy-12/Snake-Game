cmake_minimum_required(VERSION 3.29)
project(untitled1)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})


set(CMAKE_CXX_STANDARD 20)

add_executable(untitled1 main.cpp)


target_link_libraries(untitled1 ${CURSES_LIBRARIES})