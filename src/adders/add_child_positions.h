/*!
  @file src/adders/add_child_positions.h
  @brief This file has a definition of the AddChildPositions class,
  which is a subclass of the Adder class.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#ifndef ADD_CHILD_POSITIONS_H
#define ADD_CHILD_POSITIONS_H

#include <adders/adder.h>

/*!
  @brief \e AddChildPositions stands for Adder for Child Positions
  (such as \c atom-xs, \c atom-ys and \c atom-zs for molecules).
  @details This class inherits Adder class and overrides
  Adder::compute_impl. About usage in Python, please see
  src/pybind/adders/add_child_positions.h
*/
class AddChildPositions : public Adder {
  Str child_name;
 protected:
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  AddChildPositions(
    const ElPtr &elem,
    const Str &child_name_);
  virtual ~AddChildPositions() = default;
};

#endif