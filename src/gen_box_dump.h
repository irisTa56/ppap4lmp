/* ---------------------------------------------------------------------
This file is for GenBoxDump class.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GEN_BOX_DUMP_H
#define GEN_BOX_DUMP_H

#include "gen_box.h"

class GenBoxDump : public GenBox {
 public:
  GenBoxDump(const std::string &, int);
  virtual ~GenBoxDump() = default;
 protected:
  virtual void generate() override;
  std::string filepath;
  int timestep;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_gen_box_dump(py::module &m) {
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<GenBoxDump, PyGenerator<GenBoxDump>, GenBox, Generator>(m, "GenBoxDump")
    .def(py::init<const std::string &, int>());

}

#endif