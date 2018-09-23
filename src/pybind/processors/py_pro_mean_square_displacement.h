#ifndef PYBIND_PRO_MEAN_SQUARE_DISPLACEMENT_H
#define PYBIND_PRO_MEAN_SQUARE_DISPLACEMENT_H

#include <processors/pro_mean_square_displacement.h>
#include <pybind/processors/py_processor.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  void py_pro_mean_square_displacement(py::module &m);
}

#endif
