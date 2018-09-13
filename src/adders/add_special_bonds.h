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
  Adder::compute_impl. About usage in Python, please see
  src/pybind/adders/add_special_bonds.h. About special bonds, please see
  https://lammps.sandia.gov/doc/special_bonds.html.
*/
class AddSpecialBonds : public Adder {
  Map<int,Vec<Vec<int>>> mol_type_to_sbondses_in_mol;
 protected:
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  AddSpecialBonds(
    const ElPtr &el_mols,
    const Vec<Vec<int>> &scheme);
  AddSpecialBonds(
    const ElPtr &el_mols,
    const Map<int,Vec<Vec<int>>> &schemes);
  virtual ~AddSpecialBonds() = default;
};

#endif