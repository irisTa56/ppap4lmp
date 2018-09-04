/* ---------------------------------------------------------------------
AddWrappedPosition: stands for Adder for Wrapped Postisions.

create: 2018/07/07 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_WRAPPED_POSITION_H
#define ADD_WRAPPED_POSITION_H

#include <adders/adder.h>

class AddWrappedPosition : public Adder {
 protected:
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  AddWrappedPosition(
    const ElPtr &elem);
  virtual ~AddWrappedPosition() = default;
};

#endif