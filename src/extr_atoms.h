/* ---------------------------------------------------------------------
This file is for ExtrAtoms class.

create: 2018/06/19 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef EXTR_ATOMS_H
#define EXTR_ATOMS_H

#include "extractor.h"
#include "data_atoms.h"

class ExtrAtoms : public Extractor {
 public:
  ExtrAtoms() = default;
  virtual ~ExtrAtoms() = default;
 protected:
  virtual void create() override;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_extr_atoms(py::module &m) {
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<ExtrAtoms, PyExtractor<ExtrAtoms>, Extractor>(m, "ExtrAtoms")
    .def(py::init<>());

}

#endif
