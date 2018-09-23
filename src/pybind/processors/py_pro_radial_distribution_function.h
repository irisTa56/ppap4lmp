#ifndef PYBIND_PRO_RADIAL_DISTRIBUTION_FUNCTION_H
#define PYBIND_PRO_RADIAL_DISTRIBUTION_FUNCTION_H

#include <processors/pro_radial_distribution_function.h>
#include <pybind/processors/py_processor.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  void py_pro_radial_distribution_function(py::module &m);
}

#endif
