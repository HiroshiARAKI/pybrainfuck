cmake_minimum_required(VERSION 3.16)
project(pybrainfuck)

#set(CMAKE_CXX_STANDARD 11)
set(PYBIND11_CPP_STANDARD -std=c++11)
add_subdirectory(pybind11)

set(CMAKE_CXX_FLAGS "-Wall -O3")
set(CPLUS_INCLUDE_PATH "/usr/local/Cellar/python/3.7.7/Frameworks/Python.framework/Versions/3.7/include/python3.7m/")

pybind11_add_module(pybrainfuck pybf.cpp)
