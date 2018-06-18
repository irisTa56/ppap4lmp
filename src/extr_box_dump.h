/* ---------------------------------------------------------------------
This file is for ExtrBoxDump class.

create: 2018/06/12 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef EXTR_BOX_DUMP_H
#define EXTR_BOX_DUMP_H

#include "extr_box.h"

class ExtrBoxDump : public ExtrBox {
 public:
  ExtrBoxDump(const std::string &, int);
  virtual ~ExtrBoxDump() = default;
 protected:
  virtual void extract() override;
  std::string filepath;
  int timestep;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_extr_box_dump(py::module &m) {

  py::class_<ExtrBoxDump, PyExtrBox<ExtrBoxDump>, ExtrBox>(m, "ExtrBoxDump")
    .def(py::init<const std::string &, int>());

}

#endif
