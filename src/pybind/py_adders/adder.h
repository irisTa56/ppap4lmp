/*!
  @file src/pybind/py_adders/adder.h
  @brief This file has a function to bind Adder class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef PYBIND_ADDER_H
#define PYBIND_ADDER_H

#include <adders/adder.h>
#include <pybind/updater.h>

/*!
  @brief Function to bind Adder class to Python.
  @details Constructor of Adder class is hidden from Python, because
  the class is an abstract one.
*/
static void pybind_adder(py::module &m)
{
  py::class_<
    Adder,PyUpdater<Adder>,Updater,ShPtr<Adder>>(m, "Adder")
    .def(py::init<>());
}

#endif