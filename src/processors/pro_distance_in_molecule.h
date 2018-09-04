/* ---------------------------------------------------------------------
ProDistanceInMolecule: stands for Processor which computes
atom to atom Distance In each Molecule (also computes squared
distance).

create: 2018/08/25 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PRO_DISTANCE_IN_MOLECULE_H
#define PRO_DISTANCE_IN_MOLECULE_H

#include <processors/processor.h>

class ProDistanceInMolecule : public Processor {
  int index1_in_mol = 0;
  int index2_in_mol = 0;
  int target_moltype = 1;
  Vec<RowArrayXd> distance2_traj;
  ArrayXXd distance2_array;
 protected:
  virtual void run_impl(
    const int index) override;
 public:
  ProDistanceInMolecule(
    const ElPtr &mols,
    const ElPtr &atoms);
  ProDistanceInMolecule(
    const Vec<std::pair<ElPtr,ElPtr>> &pairs);
  virtual ~ProDistanceInMolecule() = default;
  virtual void prepare() override;
  virtual void finish() override;
  void set_indices(
    int index1_in_mol_,
    int index2_in_mol_);
  void set_moltype(
    int target_moltype_);
  ArrayXXd get_distance_array();
  const ArrayXXd &get_distance2_array();
};

#endif
