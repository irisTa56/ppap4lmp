/* ---------------------------------------------------------------------
This file is for DataBox class.

create: 2018/06/12 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef DATA_BOX_H
#define DATA_BOX_H

#include "data.h"

class DataBox : public Data {
 public:
  DataBox();
  virtual ~DataBox() = default;
  const Eigen::VectorXi &get_periodicity();
  const Eigen::ArrayXXd &get_edge();
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_data_box(py::module &m) {
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<DataBox, Data>(m, "DataBox")
    .def(py::init<>())
    .def(
      "get_periodicity", &DataBox::get_periodicity,
      py::return_value_policy::reference_internal)
    .def(
      "get_edge", &DataBox::get_edge,
      py::return_value_policy::reference_internal);

}

#endif
