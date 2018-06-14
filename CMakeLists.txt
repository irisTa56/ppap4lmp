cmake_minimum_required(VERSION 2.8.12)
project(ppap4lmp)

find_package(pybind11 REQUIRED)

FILE(GLOB CPPFILES src/*.cpp)

foreach(filepath ${CPPFILES})
  get_filename_component(basename ${filepath} NAME_WE)
  pybind11_add_module(${basename} ${filepath})
  set_target_properties(${basename} PROPERTIES OUTPUT_NAME ppap4lmp/${basename})
endforeach()
