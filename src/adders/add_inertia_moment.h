/* ---------------------------------------------------------------------
AddInertiaMoment: stands for Adder for Inertia Moment (of molecules).

create: 2018/07/15 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_INERTIA_MOMENT_H
#define ADD_INERTIA_MOMENT_H

#include <adders/adder.h>

class AddInertiaMoment : public Adder {
  void compute_with_weights(
    Json &data,
    ShPtr<GenElement> gen_atoms);
  void compute_without_weights(
    Json &data,
    ShPtr<GenElement> gen_atoms);
 protected:
  virtual void compute_impl(
    Json &data,
    Set<Str> &datakeys) override;
 public:
  AddInertiaMoment(
    ShPtr<GenElement> elem);
  virtual ~AddInertiaMoment() = default;
};

#endif