/* ---------------------------------------------------------------------
AddChildPositions: stands for Adder for Child Positions relative to the
parent position (such as atoms' positions in a coarse-grained bead).

create: 2018/09/03 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_CHILD_POSITIONS_H
#define ADD_CHILD_POSITIONS_H

#include <adders/adder.h>

class AddChildPositions : public Adder {
  Str child_name;
 protected:
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  AddChildPositions(
    const ElPtr &elem,
    const Str &child_name_);
  virtual ~AddChildPositions() = default;
};

#endif