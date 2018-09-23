#ifndef PYBIND_PRO_RADIAL_DISTRIBUTION_FUNCTION_WITH_DEFORMATION_H
#define PYBIND_PRO_RADIAL_DISTRIBUTION_FUNCTION_WITH_DEFORMATION_H

#include <processors/pro_radial_distribution_function_with_deformation.h>
#include <pybind/processors/py_processor.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  void py_pro_radial_distribution_function_with_deformation(py::module &m);
}

#endif
