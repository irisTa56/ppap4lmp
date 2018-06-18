/* ---------------------------------------------------------------------
This file is for ExtrBox class.

create: 2018/06/12 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef EXTR_BOX_H
#define EXTR_BOX_H

#include "extractor.h"
#include "data_box.h"

class ExtrBox : public Extractor <class DataBox> {
 public:
  ExtrBox();
  virtual ~ExtrBox() = default;
};

// implementation of get_data_()
template class Extractor<DataBox>;
template<> const DataBox &Extractor<DataBox>::get_data_() {

  if (!is_extracted) {
    extract();
    is_extracted = true;
  }

  return *data;

}

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

// trampoline class to bind Python
template <class EXTR = ExtrBox>
class PyExtrBox : public EXTR {
 public:
  using EXTR::EXTR;
 protected:
  void extract() override {
    PYBIND11_OVERLOAD_PURE(void, EXTR, extract, );
  }
};

static void pybind_extr_box(py::module &m) {

  py::class_<ExtrBox, PyExtrBox<>>(m, "ExtrBox")
    .def(py::init<>())
    .def(
      "get_data", &ExtrBox::get_data_,
      py::return_value_policy::reference_internal);

}

#endif
