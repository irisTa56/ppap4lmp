/*!
  @file src/adders/add_inertia_moment.h
  @brief This file has a definition of AddInertiaMoment class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/07/15
*/

#ifndef ADD_INERTIA_MOMENT_H
#define ADD_INERTIA_MOMENT_H

#include <adders/adder.h>

/*!
  @brief AddInertiaMoment adds inertia moment to an Element object.

  An object of this class computes elements of 3x3 matrix
  of inertia moment (a.k.a. inertia matrix, inertia tensor) of
  a *parent* Element object from masses and positions of
  a *child* Element object, and adds it to the *parent* object.
  The object of this class owns the *child* object as #ext_generator,
  and is appended to the *parent* object using
  its Element::append_updater. An example of *child* is
  an Element object containing data for atoms, and an example of
  *parent* is an Element object containing data for molecules.

  The terms *child* and *parent* are used because a *parent* object
  consists of a *child* object. In terms of time series, however,
  the *child* is created earlier than the *parent*.

  About usage in Python,
  please see pybind::py_add_inertia_moment.
*/
class AddInertiaMoment : public Adder {
 protected:
  /*!
    @brief This method overrides Updater::compute_impl.

    <dl class="property added">
      <dt class="property added">Property to be added</dt>
      <dd class="property added">
        - `I_xx` : float
        - `I_yy` : float
        - `I_zz` : float
        - `I_xy` : float
        - `I_xz` : float
        - `I_yz` : float
      </dd>
    </dl>

    <dl class="property required">
      <dt class="property required">Required property</dt>
      <dd class="property required">
        - `atom-ids` : array of integers
        - `xu` : float
        - `yu` : float
        - `zu` : float
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
    @brief Constructor of AddInertiaMoment class.

    @param elem
    @parblock
      A *child* Element object.
      <span class="remove_in_table">
        This parameter is assigned to #ext_generator.
      </span>
      <dl class="property required_ext">
        <dt class="property required_ext">Required property</dt>
        <dd class="property required_ext">
          - `id` : int
          - `mass` : float
          - `xu` : float
          - `yu` : float
          - `zu` : float
        </dd>
      </dl>
    @endparblock
  */
  AddInertiaMoment(
    const ElPtr &elem);
  virtual ~AddInertiaMoment() = default;
};

#endif