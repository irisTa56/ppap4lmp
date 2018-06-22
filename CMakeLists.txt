cmake_minimum_required(VERSION 3.11.0)
project(ppap4lmp)

find_package(nlohmann_json REQUIRED)

find_package(pybind11 REQUIRED)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

FILE(GLOB CPPFILES src/*.cpp)
pybind11_add_module(_ppap4lmp ${CPPFILES})
