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
    DataKeys &datakeys) override;
 public:
  AddWrappedPositions(
    const ElPtr &elem);
  virtual ~AddWrappedPositions() = default;
};

#endif