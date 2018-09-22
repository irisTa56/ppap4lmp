/*!
  @file src/adders/add_special_bonds.h
  @brief This file has a definition of AddSpecialBonds class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/08/19
*/

#ifndef ADD_SPECIAL_BONDS_H
#define ADD_SPECIAL_BONDS_H

#include <adders/adder.h>

/*!
  @brief AddSpecialBonds adds special bonds.
  @details The term <i>special bonds</i> is somewhat confusing
  because one of special bonds is not a bond but, for example,
  an atom connected with special bond. If an atom has another atom as
  one of its special bonds, the two atoms are considered to
  interact with each other  through some kind of bonded potential(s).

  An object of this class has a molecular Element object as
  #ext_generator, and is appended to an atomic (or bead) Element
  object. The object of this class owns schemes for special bonds
  for each type of molecule; a scheme is something like a list of
  special bonds of atoms in one molecule.

  About usage in Python,
  please see src/pybind/adders/py_add_special_bonds.h.
*/
class AddSpecialBonds : public Adder {
  /*!
    @brief Schemes of special bonds for each molecular type.
    @details Description of special bonds is stored as a map
    (dictionary) from molecular type to vector of vectors
    (list of lists) of zero-based index of atoms <i>in a molecule</i>
    of that type. The first vector corresponds atoms in a molecule,
    and the second vector corresponds special bonds of each atom.
  */
  Map<int,Vec<Vec<int>>> mol_type_to_sbondses_in_mol;
 protected:
  /*!
    @copydoc Updater::compute_impl
    @details
    <table class="py_table2">
      <caption>
        AddSpecialBonds related properties
      </caption>
      <tr class="py_tr">
        <th class="py_th2">Key for property to be added</th>
        <th class="py_th2">Key for required property</th>
        <th class="py_th2">Key for externally required property</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">
          - <c>special-bonds</c> : array of integers
        </td>
        <td class="py_td">
          None.
        </td>
        <td class="py_td">
          - \c atom-ids : array of integers
        </td>
      </tr>
    </table>
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddSpecialBonds class for
    one molecular type.
    @param el_mols : Shared pointer to a molecular Element object
    consisting of an atomic (or bead) Element object where the
    constructed object is appended to.
    This argument is assigned to #ext_generator.
    @param scheme : ::Vec of ::Vec of zero-based index of atoms in
    a molecule.
    This argument is stored in #mol_type_to_sbondses_in_mol as a scheme
    for molecular type 1.
  */
  AddSpecialBonds(
    const ElPtr &el_mols,
    const Vec<Vec<int>> &scheme);
  /*!
    @brief Constructor of AddSpecialBonds class for
    multiple molecular types.
    @param el_mols : Shared pointer to a molecular Element object
    consisting of an atomic (or bead) Element object where the
    constructed object is appended to.
    This argument is assigned to #ext_generator.
    @param schemes : ::Map from molecular type to ::Vec of ::Vec of
    zero-based index of atoms in a molecule.
    This argument is assigned to #mol_type_to_sbondses_in_mol.
  */
  AddSpecialBonds(
    const ElPtr &el_mols,
    const Map<int,Vec<Vec<int>>> &schemes);
  virtual ~AddSpecialBonds() = default;
};

#endif