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
    const ElPtr &el_atoms);
  void compute_without_weights(
    Json &data,
    const ElPtr &el_atoms);
 protected:
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  AddInertiaMoment(
    const ElPtr &elem);
  virtual ~AddInertiaMoment() = default;
};

#endif