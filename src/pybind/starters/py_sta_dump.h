/*!
  @file src/pybind/starters/py_sta_dump.h
  @brief This file is for binding StaDump class to Python.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef PYBIND_STA_DUMP_H
#define PYBIND_STA_DUMP_H

#include <starters/sta_dump.h>
#include <pybind/starters/py_starter.h>

/*!
  @brief Function to bind StaDump class to Python.
  @details Constructor of StaDump class is hidden from Python,
  because the class is an abstract one.
*/
static void pybind_sta_dump(py::module &m)
{
  py::class_<
    StaDump,PyUpdater<StaDump>,Starter,Updater,ShPtr<StaDump>>(m, "StaDump")
    .def(py::init<const Str &, int>());
}

#endif