/* ---------------------------------------------------------------------
GenAtomsDump: stands for Generator of Atoms from lammps' Dump file.

create: 2018/06/23 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GEN_ATOMS_DUMP_H
#define GEN_ATOMS_DUMP_H

#include "gen_atoms.h"

class GenAtomsDump : public GenAtoms {
 public:
  GenAtomsDump(const std::string &, int);
  GenAtomsDump(const std::string &, int, const std::string &);
  virtual ~GenAtomsDump() = default;
 protected:
  int timestep;
  std::string filepath;
  const std::vector<bool> get_is_int_vector(const std::string &);
  virtual void generate() override;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_gen_atoms_dump(py::module &m) {
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<GenAtomsDump,PyGenerator<GenAtomsDump>,GenAtoms,Generator,std::shared_ptr<GenAtomsDump>>(m, "GenAtomsDump")
    .def(py::init<const std::string &, int>())
    .def(py::init<const std::string &, int, const std::string &>());

}

#endif