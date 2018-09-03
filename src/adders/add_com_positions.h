/* ---------------------------------------------------------------------
AddCoMPositions: stands for Adder for Center of Mass added as Position.

create: 2018/07/13 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_COM_POSITIONS_H
#define ADD_COM_POSITIONS_H

#include <adders/adder.h>

class AddCoMPositions : public Adder {
  void compute_with_weights(
    Json &data,
    const ElPtr &el_atoms);
  void compute_without_weights(
    Json &data,
    const ElPtr &el_atoms);
 protected:
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  AddCoMPositions(
    const ElPtr &elem);
  virtual ~AddCoMPositions() = default;
};

#endif