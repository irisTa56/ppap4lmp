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
  virtual ~GenAtoms() = default;
  const bool is_unscaled();
  const bool is_unscaled_py();
  const bool is_scaled();
  const bool is_scaled_py();
  const bool is_unwrapped();
  const bool is_unwrapped_py();
  const bool is_scaled_unwrapped();
  const bool is_scaled_unwrapped_py();
  const Eigen::ArrayXXd get_positions(const std::string &);
  const Eigen::ArrayXXd get_positions_py(const std::string &);
 private:
  void assign_positions(
    Eigen::ArrayXXd &, const std::vector<std::string> &);
};

/* ------------------------------------------------------------------ */
// for pubind11

static void pybind_gen_atoms(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<GenAtoms,PyGenerator<GenAtoms>,Generator,std::shared_ptr<GenAtoms>>(m, "GenAtoms")
    .def(py::init<>())
    .def("is_unscaled", &GenAtoms::is_unscaled_py)
    .def("is_scaled", &GenAtoms::is_scaled_py)
    .def("is_unwrapped", &GenAtoms::is_unwrapped_py)
    .def("is_scaled_unwrapped", &GenAtoms::is_scaled_unwrapped_py)
    .def("get_positions", &GenAtoms::get_positions_py,
      py::return_value_policy::reference_internal);
}

#endif