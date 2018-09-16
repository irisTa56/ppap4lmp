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
  Adder::compute_impl. Wrapping is a process to resolve periodic
  boundary condition; wrapped positions are in the original simulation
  box. About usage in Python, please see
  src/pybind/adders/add_wrapped_position.h.
  <p>
  Name (key) of property to be added:
    - \c x (float)
    - \c y (float)
    - \c z (float)
  </p>
  <p>
  Name (key) of property to be required:
    - \c xu (float)
    - \c yu (float)
    - \c zu (float)
  </p>
  <p>
  Name (key) of property in #ext_generator to be required:
    - \c lo_x (float)
    - \c lo_y (float)
    - \c lo_z (float)
    - \c hi_x (float)
    - \c hi_y (float)
    - \c hi_z (float)
  </p>
*/
class AddWrappedPosition : public Adder {
 protected:
  /*!
    @copydoc AddMap::compute_impl
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddWrappedPosition class.
    @param elem : Shared pointer to an Element instance representing
    the simulation box.
    @details The \c elem is assigned to the #ext_generator.
  */
  AddWrappedPosition(
    const ElPtr &elem);
  virtual ~AddWrappedPosition() = default;
};

#endif