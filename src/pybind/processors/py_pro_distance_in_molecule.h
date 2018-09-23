#ifndef PYBIND_PRO_DISTANCE_IN_MOLECULE_H
#define PYBIND_PRO_DISTANCE_IN_MOLECULE_H

#include <processors/pro_distance_in_molecule.h>
#include <pybind/processors/py_processor.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  void py_pro_distance_in_molecule(py::module &m);
}

#endif
