/*!
  @file src/adders/add_wrapped_position.h
  @brief This file has a definition of the AddWrappedPosition class,
  which is a subclass of the Adder class.
  @author Takayuki Kobayashi
  @date 2018/07/07
*/

#ifndef ADD_WRAPPED_POSITION_H
#define ADD_WRAPPED_POSITION_H

#include <adders/adder.h>

/*!
  @brief \e AddWrappedPosition stands for Adder for Wrapped Postisions,
  \c x, \c y and \c z.
  @details This class inherits Adder class and overrides
  Adder::compute_impl. About usage in Python, please see
  src/pybind/adders/add_wrapped_position.h.
*/
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