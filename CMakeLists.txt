cmake_minimum_required(VERSION 3.25)
project(cppcraft)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

find_package(glew REQUIRED)
find_package(glfw3 REQUIRED)

add_subdirectory(src)
