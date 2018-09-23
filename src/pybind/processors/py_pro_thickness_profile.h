#ifndef PYBIND_PRO_THICKNESS_PROFILE_H
#define PYBIND_PRO_THICKNESS_PROFILE_H

#include <processors/pro_thickness_profile.h>
#include <pybind/processors/py_processor.h>

//! Namespace for functions to bind C++ classes to Python.
namespace pybind
{
  void py_pro_thickness_profile(py::module &m);
}

#endif
