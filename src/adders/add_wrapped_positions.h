/* ---------------------------------------------------------------------
AddWrappedPositions: stands for Adder for Wrapped Postisions.

create: 2018/07/07 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_WRAPPED_POSITIONS_H
#define ADD_WRAPPED_POSITIONS_H

#include <adders/adder.h>

class AddWrappedPositions : public Adder {
 protected:
  virtual void compute_impl(
    Json &data,
    Set<Str> &datakeys) override;
 public:
  AddWrappedPositions(
    ShPtr<Element> elem);
  virtual ~AddWrappedPositions() = default;
};

#endif