cmake_minimum_required(VERSION 3.15)
project(Tree)

set(CMAKE_CXX_STANDARD 14)

add_executable(Tree main.cpp)

add_library(TreeLib Tree.cpp)

target_link_libraries(Tree TreeLib)