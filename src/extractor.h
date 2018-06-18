/* ---------------------------------------------------------------------
This file is for Extractor class.

create: 2018/06/12 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include <string>

#include <pybind11/pybind11.h>

#include "data.h"

class Extractor {
 public:
  Extractor() = default;
  virtual ~Extractor() = default;
  void reserve();
  void cancel();
  bool del_data();
  Data *get_data();
  const Data *get_data_();  // for reference use from Python
  /*
  template <typename DATA>
  const DATA &get_data_();  // for reference use from Python
  */
 protected:
  virtual void extract() = 0;
  bool is_extracted = false;
  int reservation_count = 0;
  Data *data;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

// trampoline class to bind Python
template <class EXTR = Extractor>
class PyExtractor : public EXTR {
 public:
  using EXTR::EXTR;
 protected:
  void extract() override {
    PYBIND11_OVERLOAD_PURE(void, EXTR, extract, );
  }
};

static void pybind_extractor(py::module &m) {

  py::class_<Extractor, PyExtractor<>>(m, "Extractor")
    .def(py::init<>())
    .def(
      "get_data", &Extractor::get_data_,
      py::return_value_policy::reference_internal);

}

#endif
