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
*/
class AddWrappedPosition : public Adder {
 protected:
  /*!
    @copydoc Updater::compute_impl
    @details
    <table class="py_table2">
      <caption>
        AddWrappedPosition related properties
      </caption>
      <tr class="py_tr">
        <th class="py_th2">Key for property to be added</th>
        <th class="py_th2">Key for required property</th>
        <th class="py_th2">Key for externally required property</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">
          - \c x : float
          - \c y : float
          - \c z : float
        </td>
        <td class="py_td">
          - \c xu : float
          - \c yu : float
          - \c zu : float
        </td>
        <td class="py_td">
          - \c lo_x : float
          - \c lo_y : float
          - \c lo_z : float
          - \c hi_x : float
          - \c hi_y : float
          - \c hi_z : float
        </td>
      </tr>
    </table>
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