/*!
  @file src/adders/add_wrapped_position.h
  @brief This file has a definition of AddWrappedPosition class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/07/07
*/

#ifndef ADD_WRAPPED_POSITION_H
#define ADD_WRAPPED_POSITION_H

#include <adders/adder.h>

/*!
  @brief AddWrappedPosition adds wrapped positions of an Element object.
  @details Wrapping is a process to resolve periodic boundary condition;
  wrapped positions are in the original simulation box.

  About usage in Python,
  please see src/pybind/adders/py_add_wrapped_position.h.

  Key of property to be added:
    - \c x (float)
    - \c y (float)
    - \c z (float)

  Key of required property:
    - \c xu (float)
    - \c yu (float)
    - \c zu (float)

  Key of required property in #ext_generator:
    - \c lo_x (float)
    - \c lo_y (float)
    - \c lo_z (float)
    - \c hi_x (float)
    - \c hi_y (float)
    - \c hi_z (float)
*/
class AddWrappedPosition : public Adder {
 protected:
  /*!
    @copydoc Updater::compute_impl
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddWrappedPosition class.
    @param elem : Shared pointer to an Element object representing
    the simulation box.
    This argument is assigned to #ext_generator.
  */
  AddWrappedPosition(
    const ElPtr &elem);
  virtual ~AddWrappedPosition() = default;
};

#endif