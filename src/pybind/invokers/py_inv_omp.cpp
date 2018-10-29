/*!
  @file src/pybind/invokers/py_inv_omp.cpp
  @brief This file is for binding InvOMP class to Python.
  @author Takayuki Kobayashi
  @date 2018/09/23
*/

#include "py_inv_omp.h"

void pybind::py_inv_omp(py::module &m)
{
  m.def(
    "execute_omp",
    py::overload_cast<const ShPtr<Processor> &>(&pybind::execute_omp)
  );

  m.def(
    "execute_omp",
    py::overload_cast<const Vec<ShPtr<Processor>> &>(&pybind::execute_omp)
  );

  py::class_<
    InvOMP,PyInvoker<InvOMP>,Invoker,ShPtr<InvOMP>>(m, "InvOMP")
    .def(py::init<>());
}

void pybind::execute_omp(const ShPtr<Processor> &proc)
{
  ShPtr<Invoker>(new InvOMP())->execute({proc});
}

void pybind::execute_omp(const Vec<ShPtr<Processor>> &procs)
{
  ShPtr<Invoker>(new InvOMP())->execute(procs);
}
