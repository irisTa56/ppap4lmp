/*!
  @file src/pybind/starters/py_sta_custom.cpp
  @brief This file is for binding StaCustom class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_sta_custom.h"

void pybind::py_sta_custom(py::module &m)
{
  py::class_<StaCustom,PyUpdater<StaCustom>,Starter,Updater,ShPtr<StaCustom>>(m, "StaCustom")
    .def(py::init<const Json &>());
}
