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
  of a *parent* Element object from unwrapped positions
  for a *child* Element object, and adds it to the *parent* object
  as its unwrapped position. The object of this class owns
  the *child* object as #ext_generator, and is appended to
  the *parent* object using its Element::append_updater.
  An example of *child* is an Element object containing data
  for atoms, and an example of *parent* is an Element object
  containing data for molecules.

  The terms *child* and *parent* are used because a *parent* object
  consists of a *child* object. In terms of time series, however,
  the *child* is created earlier than the *parent*.

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
        - `mass` : float
        - `xu` : float
        - `yu` : float
        - `zu` : float
      </dd>
    </dl>

    <dl class="property required">
      <dt class="property required">Required property</dt>
      <dd class="property required">
        - `atom-ids` : array of integers
        - `atom-weights` : array of floats (optional)
      </dd>
    </dl>
  */
  virtual void compute_impl(
    Json &data,
    JsonToVoidFunc check_required_keys,
    JsonToBoolFunc check_optional_keys) override;
 public:
  /*!
    @brief Constructor of AddCoMPosition class.

    @param elem
    @parblock
      A *child* Element object.
      <span class="remove_in_table">
        This parameter is assigned to #ext_generator.
      </span>
      <dl class="property required_ext">
        <dt class="property required_ext">Required property</dt>
        <dd class="property required_ext">
          - `id` : integer
          - `mass` : float
          - `xu` : float
          - `yu` : float
          - `zu` : float
        </dd>
      </dl>
    @endparblock
  */
  AddCoMPosition(
    const ElPtr &elem);
  virtual ~AddCoMPosition() = default;
};

#endif