/* ---------------------------------------------------------------------
AddGyrationRadius: stands for Adder for Gyration Radius (of molecules).

create: 2018/07/15 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_GYRATION_RADIUS_H
#define ADD_GYRATION_RADIUS_H

#include <adders/adder.h>

class AddGyrationRadius : public Adder, public EnShThis<AddGyrationRadius> {
  bool add_squared = false;
  bool add_sqrted = true;
 protected:
  virtual void compute_impl(
    Json &data,
    Set<Str> &datakeys) override;
 public:
  using Adder::Adder;
  virtual ~AddGyrationRadius() = default;
  ShPtr<AddGyrationRadius> with_squared(
    bool add_squared_ = true);
  ShPtr<AddGyrationRadius> without_sqrted(
    bool without_sqrted_ = true);
};

#endif