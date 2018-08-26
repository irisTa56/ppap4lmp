/* ---------------------------------------------------------------------
AddSpecialBonds: stands for Adder for Special Bonds.
See: https://lammps.sandia.gov/doc/special_bonds.html

create: 2018/08/19 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_SPECIAL_BONDS_H
#define ADD_SPECIAL_BONDS_H

#include <adders/adder.h>

class AddSpecialBonds : public Adder {
  Map<int,Vec<Vec<int>>> mol_type_to_sbondses_in_mol;
 protected:
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  AddSpecialBonds(
    const ShPtr<Element> &gen_mols,
    const Vec<Vec<int>> &scheme);
  AddSpecialBonds(
    const ShPtr<Element> &gen_mols,
    const Map<int,Vec<Vec<int>>> &schemes);
  virtual ~AddSpecialBonds() = default;
};

#endif