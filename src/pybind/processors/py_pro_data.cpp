/*!
  @file src/pybind/processors/py_pro_data.cpp
  @brief This file is for binding ProData class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_pro_data.h"

void pybind::py_pro_data(py::module &m)
{
  py::class_<ProData,PyProcessor<ProData>,Processor,ShPtr<ProData>>(m, "ProData")
    .def(py::init<const ElPtr &>())
    .def(py::init<const Vec<ElPtr> &>())
    .def("select", &ProData::select)
    .def("get_results", &ProData::get_results);
}
