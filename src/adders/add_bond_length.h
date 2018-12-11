/*!
  @file src/adders/add_bond_length.h
  @brief This file has a definition of AddBondLength class,
  which is a subclass of Adder class.
  @author Yang Juntao & Kawai Kento
  @date 2018/12/06
*/

#ifndef ADD_BOND_LENGTH_H
#define ADD_BOND_LENGTH_H

#include <adders/adder.h>

/*!
  @brief AddBondLength adds center of mass to an Element object
  as its unwrapped position.

  An object of this class computes center of mass
  of a \e parent Element object from unwrapped positions
  for a \e child Element object, and adds it to the \e parent object
  as its unwrapped position. The object of this class owns
  the \e child object as #ext_generator, and is appended to
  the \e parent object using its Element::append_updater.
  An example of \e child is an Element object containing data
  for atoms, and an example of \e parent is an Element object
  containing data for molecules.

  The terms \e child and \e parent are used because a \e parent object
  consists of a \e child object. In terms of time series, however,
  the \e child is created earlier than the \e parent.

  About usage in Python,
  please see pybind::py_add_bond_length.
*/
class AddBondLength : public Adder {
  
 protected:
  /*!
    @brief This method overrides Updater::compute_impl.

    <dl class="property added">
      <dt class="property added">Property to be added</dt>
      <dd class="property added">
        - \c length : float
      </dd>
    </dl>

    <dl class="property required">
      <dt class="property required">Required property</dt>
      <dd class="property required">
        - <c>atom1-id</c> : integer
        - <c>atom2-id</c> : integer
      </dd>
    </dl>
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddBondLength class.

    @param elem
    @parblock
      A \e child Element object.
      <span class="remove_in_table">
        This parameter is assigned to #ext_generator.
      </span>
      <dl class="property required_ext">
        <dt class="property required_ext">Required property</dt>
        <dd class="property required_ext">
          - \c id : integer
          - \c xu : float
          - \c yu : float
          - \c zu : float
        </dd>
      </dl>
    @endparblock
  */
  AddBondLength(
    const ElPtr &elem);
  virtual ~AddBondLength() = default;
};

#endif