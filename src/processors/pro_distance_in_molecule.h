/*!
  @file src/processors/pro_distance_in_molecule.h
  @brief This file has a definition of ProDistanceInMolecule class,
  which is a subclass of Processor class.
  @author Takayuki Kobayashi
  @date 2018/08/25
*/

#ifndef PRO_DISTANCE_IN_MOLECULE_H
#define PRO_DISTANCE_IN_MOLECULE_H

#include <processors/processor.h>

/*!
  @brief ProDistanceInMolecule computes atom-to-atom distance
  in each molecule (also computes square of the distance).

  An object of this class makes a two-dimensional array of distances
  between two atoms belonging to the same molecule.
  Each row of the array corresponds to each snapshot of a simulation,
  and each column of the array corresponds to each molecule.

  About usage in Python,
  please see pybind::py_pro_distance_in_molecule.
*/
class ProDistanceInMolecule : public Processor {
  /*!
    Zero-based index for an atom in a molecule.
    Distance between two atoms specified by #index1_in_mol
    and #index2_in_mol is calculated for each molecule.
  */
  int index1_in_mol = 0;
  /*!
    Zero-based index for an atom in a molecule.
    Distance between two atoms specified by #index1_in_mol
    and #index2_in_mol is calculated for each molecule.
  */
  int index2_in_mol = 0;
  /*!
    Specify a type of molecules to be analyzed (default is 1).
    Only molecules whose type is #target_moltype are analyzed.
    Note that if molecules do not have \c type property,
    1 is used as their types.
  */
  int target_moltype = 1;
  /*!
    List in which ::RowArrayXd objects of computed distances
    of each molecule are stored.
    Indices in this list corresponds those in #generators.
  */
  Vec<RowArrayXd> distance2_traj;
  /*!
    A two-dimensional array of computed distances. Each column
    corresponds to a sequence of the distance for each molecule,
    and each row corresponds to each element of #generators.
  */
  ArrayXXd distance2_array;
 protected:
  /*!
    @copydoc Processor::run_impl

    I am sorry to say that the best documentation for this method
    is its source code...
  */
  virtual void run_impl(
    const int index) override;
 public:
  /*!
    @brief Constructor of ProDistanceInMolecule class
    for a snapshot of simulation.

    @param mols
    @parblock
      An Element object for molecules.
      <dl class="property required_ext">
        <dt class="property required_ext">Required property</dt>
        <dd class="property required_ext">
          - \c id : integer
          - \c atom-ids : array of integers
        </dd>
      </dl>

    @param atoms
      An Element object for atoms.
      <dl class="property required_ext">
        <dt class="property required_ext">Required property</dt>
        <dd class="property required_ext">
          - \c id : integer
          - \c xu : float
          - \c yu : float
          - \c zu : float
        </dd>
      </dl>
    @endparblock

    <span class="remove_in_table">
      A GenDict object is constructed taking the \c mols and \c atoms,
      and then put into #generators by #register_generator.
    </span>
  */
  ProDistanceInMolecule(
    const ElPtr &mols,
    const ElPtr &atoms);
  /*!
    @brief Constructor of ProDistanceInMolecule class
    for multiple snapshots of simulation.

    @param pairs
      List of pairs of two Element objects: the first object is
      for molecules and the second object is for atoms.
      If each Element object has an array data, all the array should have
      the same length.
      <dl class="property required_ext">
        <dt class="property required_ext">Required property (first)</dt>
        <dd class="property required_ext">
          - \c atom-ids : array of integers
        </dd>
      </dl>
      <dl class="property required_ext">
        <dt class="property required_ext">Required property (second)</dt>
        <dd class="property required_ext">
          - \c id : integer
          - \c xu : float
          - \c yu : float
          - \c zu : float
        </dd>
      </dl>

    <span class="remove_in_table">
      GenDict objects are constructed
      taking each element of the \c pairs,
      and then put into #generators by #register_generators.
    </span>
  */
  ProDistanceInMolecule(
    const Vec<std::pair<ElPtr,ElPtr>> &pairs);
  virtual ~ProDistanceInMolecule() = default;
  /*!
    @brief Resize #distance2_traj.
    @return None.
  */
  virtual void prepare() override;
  /*!
    @brief Fill #distance2_array with values of #distance2_traj.

    @return None.

    Each row of #distance2_array corresponds to
    each element of #distance2_traj.
  */
  virtual void finish() override;
  /*!
    @brief Specify two atoms in a molecule by zero-based index.
    Distance between the two atoms is computed for each molecule.

    @param index1_in_mol_
      A zero-based index in a molecule specifying a target atom.
      <span class="remove_in_table">
        This parameter is assigned to #index1_in_mol.
      </span>

    @param index2_in_mol_
      A zero-based index in a molecule
      specifying the other target atom.
      <span class="remove_in_table">
        This parameter is assigned to #index2_in_mol.
      </span>

    @return None.
  */
  void set_indices(
    int index1_in_mol_,
    int index2_in_mol_);
  /*!
    @brief Specify a molecular type. Only molecules whose \c type
    property is the specified type are analyzed. If molecules have
    no \c type property, you do not need to use this method.

    @param target_moltype_
      An integer for molecular type.
      <span class="remove_in_table">
        This parameter is assigned to #target_moltype.
      </span>

    @return None.
  */
  void set_moltype(
    int target_moltype_);
  /*!
    @brief Get computed distances between two atoms in each molecule
    as a two-dimensional array: each row corresponds to each snapshot
    of a simulation and each column corresponds to each molecule.

    @return Square rooted #distance2_array.
  */
  ArrayXXd get_distance_array();
  /*!
    @brief Get computed squared distances between two atoms
    in each molecule as a two-dimensional array:
    each row corresponds to each snapshot of a simulation
    and each column corresponds to each molecule.

    @return #distance2_array.
  */
  const ArrayXXd &get_distance2_array();
};

#endif
