#ifndef PYBIND_PRO_VALUE_ARRAY_H
#define PYBIND_PRO_VALUE_ARRAY_H

#include <processors/pro_value_array.h>
#include <pybind/processor.h>

static void pybind_pro_value_array(py::module &m)
{
  py::class_<ProValueArray,PyProcessor<ProValueArray>,Processor,ShPtr<ProValueArray>>(m, "ProValueArray")
    .def(py::init<ShPtr<Element>>())
    .def(py::init<List<ShPtr<Element>>>())
    .def("select", &ProValueArray::select)
    .def(
      "get_results", &ProValueArray::get_results,
      py::return_value_policy::reference_internal);
}

#endif
