/*!
  @file src/adders/add_inertia_moment.h
  @brief This file has a definition of the AddInertiaMoment class,
  which is a subclass of the Adder class.
  @author Takayuki Kobayashi
  @date 2018/07/15
*/

#ifndef ADD_INERTIA_MOMENT_H
#define ADD_INERTIA_MOMENT_H

#include <adders/adder.h>

/*!
  @brief \e AddInertiaMoment stands for Adder for Inertia Moment.
  @details This class inherits Adder class and overrides
  Adder::compute_impl. About usage in Python, please see
  src/pybind/adders/add_inertia_moment.h.
*/
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