/*!
  @file src/pybind/processors/py_pro_value_array.cpp
  @brief This file is for binding ProValueArray class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_pro_value_array.h"

void pybind::py_pro_value_array(py::module &m)
{
  py::class_<ProValueArray,PyProcessor<ProValueArray>,Processor,ShPtr<ProValueArray>>(m, "ProValueArray")
    .def(py::init<const ElPtr &>())
    .def(py::init<const Vec<ElPtr> &>())
    .def("select", &ProValueArray::select)
    .def("get_results", &ProValueArray::get_results);
}
