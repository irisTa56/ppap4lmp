#ifndef PYBIND_INV_OMP_H
#define PYBIND_INV_OMP_H

#include <invokers/inv_omp.h>
#include <pybind/invokers_py/invoker.h>

static void pybind_inv_omp(py::module &m)
{
  py::class_<InvOMP,PyInvoker<InvOMP>,Invoker,ShPtr<InvOMP>>(m, "InvOMP")
    .def(py::init<ShPtr<Processor>>())
    .def(py::init<Vec<ShPtr<Processor>>>());
}

#endif
