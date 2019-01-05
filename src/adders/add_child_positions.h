/*!
  @file src/adders/add_child_positions.h
  @brief This file has a definition of AddChildPositions class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#ifndef ADD_CHILD_POSITIONS_H
#define ADD_CHILD_POSITIONS_H

#include <adders/adder.h>

/*!
  @brief AddChildPositions adds relative positions of a child Element
  object to a parent Element object.

  An object of this class owns a *child* object
  as #ext_generator, and is appended to a *parent* object
  using its Element::append_updater. The object of this class
  computes positions for the *child* object relative to a position
  for the *parent* object, and tehn appends them to an array
  belonging to the *parent* object. An example of *child* is
  an Element object containing data for atoms, and an example of
  *parent* is an Element object containing data for molecules.

  The terms *child* and *parent* are used because a *parent* object
  consists of a *child* object. In terms of time series, however,
  the *child* is created earlier than the *parent*.

  About usage in Python,
  please see pybind::py_add_child_positions.
*/
class AddChildPositions : public Adder {
  /*!
    Name of *child* object stored as #ext_generator. Key for property
    added to a *parent* object by this class is named
    as `[child_name]-xs`, `[child_name]-ys`
    and `[child_name]-zs`. The *parent* object is also required
    to have `[child_name]-ids` property.
  */
  Str child_name;
 protected:
  /*!
    @brief This method overrides Updater::compute_impl.

    <dl class="property added">
      <dt class="property added">Property to be added</dt>
      <dd class="property added">
        - `[child_name]-xs` : array of floats
        - `[child_name]-ys` : array of floats
        - `[child_name]-zs` : array of floats
      </dd>
    </dl>

    <dl class="property required">
      <dt class="property required">Required property</dt>
      <dd class="property required">
        - `[child_name]-ids` : array of integers
        - `xu` : float
        - `yu` : float
        - `zu` : float
      </dd>
    </dl>
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddChildPositions class.

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
          - `xu` : float
          - `yu` : float
          - `zu` : float
        </dd>
      </dl>

    @param child_name_
      A string for naming the *child* object.
      <span class="remove_in_table">
        This parameter is assigned to #child_name.
      </span>
    @endparblock
  */
  AddChildPositions(
    const ElPtr &elem,
    const Str &child_name_);
  virtual ~AddChildPositions() = default;
};

#endif