#ifndef ALIAS_PYBIND_H
#define ALIAS_PYBIND_H

#include <pybind11/pybind11.h>

namespace py = pybind11;

#ifdef ALIAS_STD_H
#include <alias/pybind_std.h>
#endif

#ifdef ALIAS_JSON_H
#include <alias/pybind_json.h>
#endif

#ifdef ALIAS_EIGEN_H
#include <alias/pybind_eigen.h>
#endif

#endif