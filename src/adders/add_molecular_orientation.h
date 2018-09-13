/*!
  @file src/adders/add_molecular_orientation.h
  @brief This file has a definition of the AddMolecularOrientation
  class, which is a subclass of the Adder class.
  @author Takayuki Kobayashi
  @date 2018/07/16
*/

#ifndef ADD_MOLECULAR_ORIENTATION_H
#define ADD_MOLECULAR_ORIENTATION_H

#include <adders/adder.h>

/*!
  @brief \e AddMolecularOrientation stands for Adder for Molecular
  Orientation.
  @details This class inherits Adder class and overrides
  Adder::compute_impl. About usage in Python, please see
  src/pybind/adders/add_molecular_orientation.h.
*/
class AddMolecularOrientation : public Adder {
 protected:
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  using Adder::Adder;
  virtual ~AddMolecularOrientation() = default;
};

#endif