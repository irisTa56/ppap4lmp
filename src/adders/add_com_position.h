/*!
  @file src/adders/add_com_position.h
  @brief This file has a definition of AddCoMPosition class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/07/13
*/

#ifndef ADD_COM_POSITION_H
#define ADD_COM_POSITION_H

#include <adders/adder.h>

/*!
  @brief AddCoMPosition adds center of mass to an Element object
  as its unwrapped position.
  @details An object of this class computes center of mass of a parent
  Element object from unwrapped positions of a child Element object,
  and adds it to the parent object as its unwrapped position.
  The object of this class owns the \e child object
  as #ext_generator, and is appended to the \e parent object
  using its Element::append_updater. An example of \e child is
  an Element object containing data for atoms, and an example of
  \e parent is an Element object containing data for molecules.

  The terms \e child and \e parent are used because a \e parent object
  consists of a \e child object. In terms of time series, however,
  the \e child is created earlier than the \e parent.

  About usage in Python,
  please see src/pybind/adders/py_add_com_position.h.
*/
class AddCoMPosition : public Adder {
  /*!
    @brief Compute the center of mass with weighting factors.
    @param data : Mutable reference to Element::data where computed
    properties are added to.
    @param el_atoms : Shared pointer of up-casted #ext_generator.
    @return None.
    @details Note that the weighting factors are different from
    something like mass of atoms. Weighting factors are
    artificial values defined with some reason.
  */
  void compute_with_weights(
    Json &data,
    const ElPtr &el_atoms);
  /*!
    @brief Compute the center of mass.
    @param data : Mutable reference to Element::data where computed
    properties are added to.
    @param el_atoms : Shared pointer of up-casted #ext_generator.
    @return None.
  */
  void compute_without_weights(
    Json &data,
    const ElPtr &el_atoms);
 protected:
  /*!
    @copydoc Updater::compute_impl
    @details
    <table class="py_table2">
      <caption>
        AddCoMPosition related properties
      </caption>
      <tr class="py_tr">
        <th class="py_th2">Key for property to be added</th>
        <th class="py_th2">Key for required property</th>
        <th class="py_th2">Key for externally required property</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">
          - \c mass : float
          - \c xu : float
          - \c yu : float
          - \c zu : float
        </td>
        <td class="py_td">
          - <c>atom-ids</c> : array of integers
        </td>
        <td class="py_td">
          - \c id : integer
          - \c mass : float
          - \c xu : float
          - \c yu : float
          - \c zu : float
        </td>
      </tr>
    </table>
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddCoMPosition class.
    @param elem : Shared pointer to a \e child object.
    This argument is assigned to #ext_generator.
  */
  AddCoMPosition(
    const ElPtr &elem);
  virtual ~AddCoMPosition() = default;
};

#endif