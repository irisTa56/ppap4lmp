cmake_minimum_required(VERSION 3.11.0)
project(ppap4lmp)

find_package(pybind11 REQUIRED)

FILE(GLOB CPPFILES src/*.cpp)
pybind11_add_module(_ppap4lmp ${CPPFILES})
