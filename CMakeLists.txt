cmake_minimum_required(VERSION 3.11.0)
project(ppap4lmp)

add_subdirectory(json)
include_directories(json/include)

add_subdirectory(pybind11)
include_directories(pybind11/include)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

FILE(GLOB CPPFILES src/*.cpp)
pybind11_add_module(_ppap4lmp ${CPPFILES})
