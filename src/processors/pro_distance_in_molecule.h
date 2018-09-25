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
  @details An object of this class makes an array of distances
  between two atoms belonging to the same molecule.
  Each row of the array corresponds to each snapshot of a simulation,
  and each column of the array corresponds to each molecule.

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
  /*!
    @copydoc Processor::run_impl
    @details
    <table class="py_table3">
      <caption>
        Properties required by StaMolecules
      </caption>
      <tr class="py_tr">
        <th class="py_th3">Generator</th>
        <th class="py_th3">Key for required property</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">

        </td>
        <td class="py_td">
          None.
        </td>
        <td class="py_td">
          - \c id : integer
          - \c mol : integer
        </td>
      </tr>
    </table>
  */
  virtual void run_impl(
    const int index) override;
 public:
  /*!
    @brief Constructor of ProDistanceInMolecule class
    for a pair of two Element objects.
    @param mols : An Element object for molecules.
    @param atoms : An Element object for atoms.
    @details A GenDict object is constructed
    taking the \c mols and \c atoms,
    and then put into #generators by #register_generator.
  */
  ProDistanceInMolecule(
    const ElPtr &mols,
    const ElPtr &atoms);
  /*!
    @brief Constructor of ProDistanceInMolecule class
    for multiple pairs of two Element objects.
    @param pairs : ::Vec of pairs of two Element objects:
    the first object is for molecules
    and the second object is for atoms.
    @details GenDict objects are constructed
    taking each element of the \c pairs,
    and then put into #generators by #register_generators.
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
    @details Each row of #distance2_array corresponds to
    each element of #distance2_traj.
  */
  virtual void finish() override;
  /*!
    @brief Specify two atoms in a molecule by zero-based index.
    Distance between the two atoms is computed for each molecule.
    @param index1_in_mol_ : A zero-based index in a molecule
    specifying a target atom.
    @param index2_in_mol_ : A zero-based index in a molecule
    specifying the other target atom.
    @return None.
  */
  void set_indices(
    int index1_in_mol_,
    int index2_in_mol_);
  /*!
    @brief Specify a molecular type. Only molecules whose \c type
    property is the specified type are analyzed.
    @param target_moltype_ : An integer for molecular type.
    @return None.
  */
  void set_moltype(
    int target_moltype_);
  /*!
    @brief Get computed distances as a two-dimensional array:
    each row corresponds to each snapshot of a simulation
    and each column corresponds to each molecule.
    @return Square rooted #distance2_array.
  */
  ArrayXXd get_distance_array();
  /*!
    @brief Get computed squared distances as a two-dimensional array:
    each row corresponds to each snapshot of a simulation
    and each column corresponds to each molecule.
    @return #distance2_array.
  */
  const ArrayXXd &get_distance2_array();
};

#endif
