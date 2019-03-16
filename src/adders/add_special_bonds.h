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
  @brief AddSpecialBonds adds *special bonds*.

  The term *special bonds* is somewhat confusing
  because one of special bonds is not a bond but, for example,
  an atom connected with a special bond. If an atom has another atom
  as one of its special bonds, the two atoms are considered to
  interact with each other through some kind of bonded potential(s).

  An object of this class has a molecular Element object as
  #ext_generator, and is appended to an atomic (or bead) Element
  object. The object of this class owns schemes for special bonds
  for each type of molecule; a scheme is something like a list of
  special bonds of each atom in one molecule.

  About usage in Python,
  please see pybind::py_add_special_bonds.
*/
class AddSpecialBonds : public Adder {
  /*!
    Schemes of special bonds for each molecular type contained
    in a ::Map (dictionary) object from molecular type
    to a list of lists of zero-based indices of atoms
    in a molecule of that type. The first list corresponds atoms
    in a molecule, and the second lists corresponds special bonds
    of each atom.
  */
  Map<int,Vec<Vec<int>>> mol_type_to_sbondses_in_mol;
 protected:
  /*!
    @brief This method overrides Updater::compute_impl.

    <dl class="property added">
      <dt class="property added">Property to be added</dt>
      <dd class="property added">
        - `special-bonds` : array of integers
      </dd>
    </dl>
  */
  virtual void compute_impl(
    Json &data) override;
 public:
  /*!
    @brief Constructor of AddSpecialBonds class for
    molecules all of whose `type` property are 1,
    or molecules all of which do not have the property.

    @param el_mols
    @parblock
      A molecular Element object consisting of an atomic (or bead)
      Element object where the constructed object is appended to.
      <span class="remove_in_table">
        This parameter is assigned to #ext_generator.
      </span>
      <dl class="property required_ext">
        <dt class="property required_ext">Required property</dt>
        <dd class="property required_ext">
          - `atom-ids` : array of integers
        </dd>
      </dl>

    @param scheme
      List of lists of zero-based indices of atoms in a molecule.
      The first list corresponds atoms in a molecule,
      and the second lists corresponds special bonds of each atom.
      <span class="remove_in_table">
        This parameter is stored in #mol_type_to_sbondses_in_mol
        as a scheme for molecular type 1.
      </span>
    @endparblock
  */
  AddSpecialBonds(
    const ElPtr &el_mols,
    const Vec<Vec<int>> &scheme);
  /*!
    @brief Constructor of AddSpecialBonds class for
    multiple molecular types.

    @param el_mols
    @parblock
      A molecular Element object consisting of an atomic (or bead)
      Element object where the constructed object is appended to.
      <span class="remove_in_table">
        This parameter is assigned to #ext_generator.
      </span>
      <dl class="property required_ext">
        <dt class="property required_ext">Required property</dt>
        <dd class="property required_ext">
          - `atom-ids` : array of integers
        </dd>
      </dl>

    @param schemes
      Dictionary from molecular type to list of lists of
      zero-based indices of atoms in a molecule.
      The first list corresponds atoms in a molecule,
      and the second lists corresponds special bonds of each atom.
      <span class="remove_in_table">
        This parameter is assigned to #mol_type_to_sbondses_in_mol.
      </span>
    @endparblock
  */
  AddSpecialBonds(
    const ElPtr &el_mols,
    const Map<int,Vec<Vec<int>>> &schemes);
  virtual ~AddSpecialBonds() = default;
};

#endif