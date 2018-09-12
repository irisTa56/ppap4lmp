/*!
  @file src/adders/add_gyration_radius.h
  @brief This file has a definition of the AddGyrationRadius class,
  which is a subclass of the Adder class.
  @author Takayuki Kobayashi
  @date 2018/07/15
*/

#ifndef ADD_GYRATION_RADIUS_H
#define ADD_GYRATION_RADIUS_H

#include <adders/adder.h>

/*!
  @brief \e AddGyrationRadius stands for Adder for Gyration Radius.
  @details This class inherits Adder class and overrides
  Adder::compute_impl. About usage in Python, please see
  src/pybind/adders/add_gyration_radius.h
*/
class AddGyrationRadius : public Adder, public EnShThis<AddGyrationRadius> {
  bool add_squared = false;
  bool add_sqrted = true;
 protected:
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  using Adder::Adder;
  virtual ~AddGyrationRadius() = default;
  ShPtr<AddGyrationRadius> with_squared(
    bool add_squared_ = true);
  ShPtr<AddGyrationRadius> without_sqrted(
    bool without_sqrted_ = true);
};

#endif