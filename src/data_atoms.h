/* ---------------------------------------------------------------------
This file is for DataAtoms class.

create: 2018/06/19 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef DATA_ATOMS_H
#define DATA_ATOMS_H

#include "data.h"

class DataAtoms : public Data {
 public:
  DataAtoms() = default;
  virtual ~DataAtoms() = default;
  const Eigen::VectorXi &get_types();
  Eigen::ArrayXXd get_positions(const std::string &);
  bool is_unscaled();
  bool is_scaled();
  bool is_unwrapped();
  bool is_scaled_unwrapped();
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_data_atoms(py::module &m) {
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<DataAtoms, Data>(m, "DataAtoms")
    .def(py::init<>())
    .def(
      "get_types", &DataAtoms::get_types,
      py::return_value_policy::reference_internal)
    .def(
      "get_positions", &DataAtoms::get_positions,
      py::return_value_policy::reference_internal)
    .def(
      "is_unscaled", &DataAtoms::is_unscaled,
      py::return_value_policy::reference_internal)
    .def(
      "is_scaled", &DataAtoms::is_scaled,
      py::return_value_policy::reference_internal)
    .def(
      "is_unwrapped", &DataAtoms::is_unwrapped,
      py::return_value_policy::reference_internal)
    .def(
      "is_scaled_unwrapped", &DataAtoms::is_scaled_unwrapped,
      py::return_value_policy::reference_internal);

}

#endif
