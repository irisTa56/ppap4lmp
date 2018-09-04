/* ---------------------------------------------------------------------
AddCoMPosition: stands for Adder for Center of Mass added as Position.

create: 2018/07/13 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_COM_POSITION_H
#define ADD_COM_POSITION_H

#include <adders/adder.h>

class AddCoMPosition : public Adder {
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
  AddCoMPosition(
    const ElPtr &elem);
  virtual ~AddCoMPosition() = default;
};

#endif