/*!
  @file src/pybind/invokers/py_inv_omp.cpp
  @brief This file is for binding InvOMP class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_inv_omp.h"

void pybind::py_inv_omp(py::module &m)
{
  py::class_<InvOMP,PyInvoker<InvOMP>,Invoker,ShPtr<InvOMP>>(m, "InvOMP")
    .def(py::init<ShPtr<Processor>>())
    .def(py::init<Vec<ShPtr<Processor>>>());
}
