/* ---------------------------------------------------------------------
GenBoxDump: stands for Generator of Box from lammps' Dump file.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GEN_BOX_DUMP_H
#define GEN_BOX_DUMP_H

#include "gen_box.h"

class GenBoxDump : public GenBox {
 public:
  GenBoxDump(const std::string &, int);
  GenBoxDump(const std::string &, int, const std::string &);
  virtual ~GenBoxDump() = default;
 protected:
  int timestep;
  std::string filepath;
  virtual void generate() override;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_gen_box_dump(py::module &m) {
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<GenBoxDump,PyGenerator<GenBoxDump>,GenBox,Generator,std::shared_ptr<GenBoxDump>>(m, "GenBoxDump")
    .def(py::init<const std::string &, int>())
    .def(py::init<const std::string &, int, const std::string &>());

}

#endif