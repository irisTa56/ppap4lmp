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
    ShPtr<Element> gen_atoms);
  void compute_without_weights(
    Json &data,
    ShPtr<Element> gen_atoms);
 protected:
  virtual void compute_impl(
    Json &data,
    Set<Str> &datakeys) override;
 public:
  AddCoMPositions(
    ShPtr<Element> elem);
  virtual ~AddCoMPositions() = default;
};

#endif