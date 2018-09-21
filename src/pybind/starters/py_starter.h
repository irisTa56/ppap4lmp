/*!
  @file src/pybind/starters/py_starter.h
  @brief This file is for binding Starter class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef PYBIND_STARTER_H
#define PYBIND_STARTER_H

#include <starters/starter.h>
#include <pybind/py_updater.h>

/*!
  @brief Function to bind Starter class to Python.
  @details Constructor of Starter class is hidden from Python,
  because the class is an abstract one.
*/
static void pybind_starter(py::module &m)
{
  py::class_<
    Starter,PyUpdater<Starter>,Updater,ShPtr<Starter>>(m, "Starter")
    .def(py::init<>());
}

#endif