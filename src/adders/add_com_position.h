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
  please see pybind::py_add_com_position.
*/
class AddCoMPosition : public Adder {
  /*!
    Compute the center of mass with weighting factors. Note that
    the weighting factors are different from something like
    mass of atoms. Weighting factors are artificial values defined
    with some reason.

    @param data
      Mutable reference to Element::data where computed properties are
      added to.

    @param el_atoms
      Shared pointer of up-casted #ext_generator.

    @return None.
  */
  void compute_with_weights(
    Json &data,
    const ElPtr &el_atoms);
  /*!
    Compute the center of mass.

    @param data
      Mutable reference to Element::data where computed properties are
      added to.

    @param el_atoms
      Shared pointer of up-casted #ext_generator.

    @return None.
  */
  void compute_without_weights(
    Json &data,
    const ElPtr &el_atoms);
 protected:
  /*!
    @brief This method overrides Updater::compute_impl.

    <dl class="property added">
      <dt class="property added">Property to be added</dt>
      <dd class="property added">
        - \c mass : float
        - \c xu : float
        - \c yu : float
        - \c zu : float
      </dd>
    </dl>

    <dl class="property required">
      <dt class="property required">Required property</dt>
      <dd class="property required">
        - <c>atom-ids</c> : array of integers
      </dd>
    </dl>
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddCoMPosition class.

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
          - \c mass : float
          - \c xu : float
          - \c yu : float
          - \c zu : float
        </dd>
      </dl>
    @endparblock
  */
  AddCoMPosition(
    const ElPtr &elem);
  virtual ~AddCoMPosition() = default;
};

#endif