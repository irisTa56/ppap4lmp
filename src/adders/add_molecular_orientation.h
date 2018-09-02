/* ---------------------------------------------------------------------
AddMolecularOrientation: stands for Adder for Molecular Orientation.

create: 2018/07/16 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_MOLECULAR_ORIENTATION_H
#define ADD_MOLECULAR_ORIENTATION_H

#include <adders/adder.h>

class AddMolecularOrientation : public Adder {
 protected:
  virtual void compute_impl(
    Json &data,
    Set<Str> &datakeys) override;
 public:
  using Adder::Adder;
  virtual ~AddMolecularOrientation() = default;
};

#endif