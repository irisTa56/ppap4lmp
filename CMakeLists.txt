cmake_minimum_required(VERSION 2.8.12)
project(ppap4lmp)

add_subdirectory(pybind11)
pybind11_add_module(ppap4lmp src/main.cpp)
