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
  @brief AddWrappedPosition adds wrapped positions for
  an Element object.

  Wrapping is a process to resolve periodic boundary condition;
  wrapped positions are in the original simulation box.

  About usage in Python,
  please see pybind::py_add_wrapped_position.
*/
class AddWrappedPosition : public Adder {
 protected:
  /*!
    @brief This method overrides Updater::compute_impl.

    <dl class="property added">
      <dt class="property added">Property to be added</dt>
      <dd class="property added">
        - \c x : float
        - \c y : float
        - \c z : float
      </dd>
    </dl>

    <dl class="property required">
      <dt class="property required">Required property</dt>
      <dd class="property required">
        - \c xu : float
        - \c yu : float
        - \c zu : float
      </dd>
    </dl>
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddWrappedPosition class.

    @param elem
    @parblock
       An Element object for a simulation box.
      <span class="remove_in_table">
        This parameter is assigned to #ext_generator.
      </span>

      <dl class="property required_ext">
        <dt class="property required_ext">Required property</dt>
        <dd class="property required_ext">
          - \c lo_x : float
          - \c lo_y : float
          - \c lo_z : float
          - \c hi_x : float
          - \c hi_y : float
          - \c hi_z : float
        </dd>
      </dl>
    @endparblock
  */
  AddWrappedPosition(
    const ElPtr &elem);
  virtual ~AddWrappedPosition() = default;
};

#endif