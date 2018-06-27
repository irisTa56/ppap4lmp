/* ---------------------------------------------------------------------
GenAtoms: stands for Generator of Atoms.

create: 2018/06/23 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GEN_ATOMS_H
#define GEN_ATOMS_H

#include "generator.h"

class GenAtoms : public Generator {
 public:
  GenAtoms();
  GenAtoms(const std::string &);
  virtual ~GenAtoms() = default;
  const bool is_unscaled();
  const bool is_scaled();
  const bool is_unwrapped();
  const bool is_scaled_unwrapped();
  const Eigen::ArrayXXd get_positions(const std::string &);
 protected:
  void assign_positions(
    Eigen::ArrayXXd &, const std::vector<std::string> &);
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

static void pybind_gen_atoms(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<GenAtoms,PyGenerator<GenAtoms>,Generator,std::shared_ptr<GenAtoms>>(m, "GenAtoms")
    .def(py::init<>())
    .def(py::init<const std::string &>())
    .def("is_unscaled", &GenAtoms::is_unscaled)
    .def("is_scaled", &GenAtoms::is_scaled)
    .def("is_unwrapped", &GenAtoms::is_unwrapped)
    .def("is_scaled_unwrapped", &GenAtoms::is_scaled_unwrapped)
    .def("get_positions", &GenAtoms::get_positions,
      py::return_value_policy::reference_internal);
}

#endif