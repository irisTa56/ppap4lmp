/* ---------------------------------------------------------------------
ProDistanceInMolecule: stands for Processor which computes
atom to atom Distance In each Molecule (also computes squared
distance).

create: 2018/08/25 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PRO_DISTANCE_IN_MOLECULE_H
#define PRO_DISTANCE_IN_MOLECULE_H

#include "processor.h"

class ProDistanceInMolecule : public Processor {
  int index1_in_mol = 0;
  int index2_in_mol = 0;
  int target_moltype = 1;
  bool do_sqrt = false;
  List<RowArrayXd> distance2_traj;
  ArrayXXd distance_array;
  ArrayXXd distance2_array;
 protected:
  virtual void run_impl(
    int index) override;
 public:
  ProDistanceInMolecule(
    ShPtr<GenElement> mols,
    ShPtr<GenElement> atoms);
  ProDistanceInMolecule(
    List<std::pair<ShPtr<GenElement>,ShPtr<GenElement>>> pairs);
  virtual ~ProDistanceInMolecule() = default;
  virtual void prepare() override;
  virtual void finish() override;
  void set_indices(
    int index1_in_mol_,
    int index2_in_mol_);
  void set_moltype(
    int target_moltype_);
  void compute_sqrt(
    bool do_sqrt_ = true);
  const ArrayXXd &get_distance_array();
  const ArrayXXd &get_distance2_array();
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_pro_distance_in_molecule(py::module &m)
{
  py::class_<ProDistanceInMolecule,PyProcessor<ProDistanceInMolecule>,Processor,ShPtr<ProDistanceInMolecule>>(m, "ProDistanceInMolecule")
    .def(py::init<ShPtr<GenElement>,ShPtr<GenElement>>())
    .def(py::init<List<std::pair<ShPtr<GenElement>,ShPtr<GenElement>>>>())
    .def("set_indices", &ProDistanceInMolecule::set_indices)
    .def("set_moltype", &ProDistanceInMolecule::set_moltype)
    .def(
      "compute_sqrt", &ProDistanceInMolecule::compute_sqrt,
      py::arg("do_sqrt_") = true)
    .def(
      "get_distance_array", &ProDistanceInMolecule::get_distance_array,
      py::return_value_policy::reference_internal)
    .def(
      "get_distance2_array", &ProDistanceInMolecule::get_distance2_array,
      py::return_value_policy::reference_internal);
}

#endif
