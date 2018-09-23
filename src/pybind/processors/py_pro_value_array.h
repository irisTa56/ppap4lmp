#ifndef PYBIND_PRO_VALUE_ARRAY_H
#define PYBIND_PRO_VALUE_ARRAY_H

#include <processors/pro_value_array.h>
#include <pybind/processors/py_processor.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  void py_pro_value_array(py::module &m);
}

#endif
