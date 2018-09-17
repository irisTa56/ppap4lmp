/*!
  @file src/adders/add_special_bonds.h
  @brief This file has a definition of the AddSpecialBonds class, which
  is a subclass of the Adder class.
  @author Takayuki Kobayashi
  @date 2018/08/19
*/

#ifndef ADD_SPECIAL_BONDS_H
#define ADD_SPECIAL_BONDS_H

#include <adders/adder.h>

/*!
  @brief \e AddSpecialBonds stands for Adder for Special Bonds.
  @details This class inherits Adder class and overrides
  Adder::compute_impl. Special bonds is a property for atoms (or beads)
  belonging to the same molecule; if an atom has another atom as one of
  its special bonds, the two atoms are considered to interact with each
  other through bonded potential(s) (bond-length, bond-angle ...). For
  more details about special bonds, please see Lammps documentation:
  https://lammps.sandia.gov/doc/special_bonds.html. About usage in
  Python, please see src/pybind/adders_py/add_special_bonds.h.
  <p>
    Name (key) of property to be added:
      - \c <c>special-bonds</c> (array of integer)
  </p>
  <p>
    Name (key) of property in #ext_generator to be required:
      - \c atom-ids (array of integer)
  </p>
*/
class AddSpecialBonds : public Adder {
  /*!
    @brief Blueprints of special bonds for each type of molecule.
    @details Definition of special bonds is stored as a map (dictionary)
    from types of molecule to vector of vector (list of list) of index
    of atoms <i>in a molecule</i> of the type. The first vector
    corresponds atoms in a molecule, and the second vector corresponds
    special bonds of the each atom.
  */
  Map<int,Vec<Vec<int>>> mol_type_to_sbondses_in_mol;
 protected:
  /*!
    @copydoc AddMap::compute_impl
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddSpecialBonds class for one type of
    molecule.
    @param el_mols : Shared pointer to an Element object created from
    another Element object where the constructed object is appended
    to.
    @param scheme : Vector of vector of index of atoms in a molecule
    representing special bonds.
    @details The \c el_mols is assigned to #ext_generator. The
    \c scheme is stored in #mol_type_to_sbondses_in_mol as a blueprint
    of special bonds for molecular type 1.
  */
  AddSpecialBonds(
    const ElPtr &el_mols,
    const Vec<Vec<int>> &scheme);
  /*!
    @brief Constructor of AddSpecialBonds class for multiple types of
    molecule.
    @param el_mols : Shared pointer to an Element object created from
    another Element object where the constructed object is appended
    to.
    @param schemes : Map from types of molecule to vector of vector of
    index of atoms in a molecule representing special bonds for the
    each molecular type.
    @details The \c el_mols is assigned to #ext_generator. The
    \c schemes is assigned to #mol_type_to_sbondses_in_mol.
  */
  AddSpecialBonds(
    const ElPtr &el_mols,
    const Map<int,Vec<Vec<int>>> &schemes);
  virtual ~AddSpecialBonds() = default;
};

#endif