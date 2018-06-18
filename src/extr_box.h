/* ---------------------------------------------------------------------
This file is for ExtrBox class.

create: 2018/06/12 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef EXTR_BOX_H
#define EXTR_BOX_H

#include "extractor.h"
#include "data_box.h"

class ExtrBox : public Extractor {
 public:
  ExtrBox();
  virtual ~ExtrBox() = default;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_extr_box(py::module &m) {
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<ExtrBox, PyExtractor<ExtrBox>, Extractor>(m, "ExtrBox")
    .def(py::init<>());

}

#endif
