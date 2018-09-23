/*!
  @file src/processors/pro_distance_in_molecule.h
  @brief This file has a definition of ProDistanceInMolecule class,
  which is a subclass of Processor class.
  @author Takayuki Kobayashi
  @date 2018/08/25
*/

/* ---------------------------------------------------------------------
ProDistanceInMolecule: stands for Processor which computes
atom to atom Distance In each Molecule (also computes squared
distance).

create: 2018/08/25 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PRO_DISTANCE_IN_MOLECULE_H
#define PRO_DISTANCE_IN_MOLECULE_H

#include <processors/processor.h>

/*!
  @brief ProDistanceInMolecule computes atom-to-atom distance
  in each molecule (also computes square of the distance).
  @details An object of this class ...

  About usage in Python,
  please see src/pybind/processors/py_pro_distance_in_molecule.h
*/
class ProDistanceInMolecule : public Processor {
  /*!
    @brief Zero-based index for an atom in a molecule.
    @details Distance between two atoms specified by #index1_in_mol
    and #index2_in_mol is calculated for each molecule.
  */
  int index1_in_mol = 0;
  //! @copydoc #index1_in_mol
  int index2_in_mol = 0;
  /*!
    @brief Specify a type of molecules to be analyzed.
    @details Only molecules whose type is #target_moltype are analyzed.
  */
  int target_moltype = 1;
  /*!
    @brief List in which ::RowArrayXd of computed distances are stored.
    @details Index in this member corresponds that in #generators.
  */
  Vec<RowArrayXd> distance2_traj;
  /*!
    @brief Array of computed distances.
    @details Each column corresponds to
    a sequence of computed distance of one molecule,
    and each rows corresponds to each element of #generators.
  */
  ArrayXXd distance2_array;
 protected:
  //! @copydoc Processor::run_impl
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
