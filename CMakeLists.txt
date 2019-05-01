cmake_minimum_required(VERSION 3.11.0)
project(ppap4lmp)

find_package(nlohmann_json)
IF(NOT nlohmann_json_FOUND)
  add_subdirectory(json)
  include_directories(json/single_include)
ENDIF()

find_package(pybind11)
IF(NOT pybind11_FOUND)
  add_subdirectory(pybind11)
  include_directories(pybind11/include)
ENDIF()

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

include_directories(src)

FILE(GLOB CPPFILES src/*.cpp src/*/*.cpp src/*/*/*.cpp)

pybind11_add_module(_ppap4lmp ${CPPFILES})

#target_link_libraries(_ppap4lmp PRIVATE profiler)
