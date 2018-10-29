/*!
  @file src/pybind/invokers/py_invoker.cpp
  @brief This file is for binding Invoker class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_invoker.h"

void pybind::py_invoker(py::module &m)
{
  py::class_<
    Invoker,PyInvoker<>,ShPtr<Invoker>>(m, "Invoker")
    .def(py::init<>());
}
