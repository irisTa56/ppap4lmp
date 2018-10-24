/*!
  @file src/pybind/processors/py_pro_time_correlation_in_molecule.cpp
  @brief This file is for binding ProTimeCorrelationInMolecule class to Python.
  @author Takayuki Kobayashi
  @date 2018/10/24
*/

#include "py_pro_time_correlation_in_molecule.h"

void pybind::py_pro_time_correlation_in_molecule(py::module &m)
{
  py::class_<ProTimeCorrelationInMolecule,PyProcessor<ProTimeCorrelationInMolecule>,Processor,ShPtr<ProTimeCorrelationInMolecule>>(m, "ProTimeCorrelationInMolecule")
    .def(py::init<const Vec<std::pair<ElPtr,ElPtr>> &>())
    .def("set_indices", &ProTimeCorrelationInMolecule::set_indices)
    .def("set_moltype", &ProTimeCorrelationInMolecule::set_moltype)
    .def(
      "get_coefficients_array",
      &ProTimeCorrelationInMolecule::get_coefficients_array)
    .def(
      "get_time_correlation",
      &ProTimeCorrelationInMolecule::get_time_correlation);
}
