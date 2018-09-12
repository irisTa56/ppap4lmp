/*!
  @file src/adders/add_com_position.h
  @brief This file has a definition of the AddCoMPosition class, which
  is a subclass of the Adder class.
  @author Takayuki Kobayashi
  @date 2018/07/13
*/

#ifndef ADD_COM_POSITION_H
#define ADD_COM_POSITION_H

#include <adders/adder.h>

/*!
  @brief \e AddCoMPosition stands for Adder for Center of Mass added as
  Position, \c xu, \c yu and \c zu.
  @details This class inherits Adder class and overrides
  Adder::compute_impl. About usage in Python, please see
  src/pybind/adders/add_com_position.h
*/
class AddCoMPosition : public Adder {
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
  AddCoMPosition(
    const ElPtr &elem);
  virtual ~AddCoMPosition() = default;
};

#endif