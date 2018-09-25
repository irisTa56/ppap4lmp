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

  An object of this class owns a \e child object
  as #ext_generator, and is appended to a \e parent object
  using its Element::append_updater. The object of this class
  computes positions for the \e child object relative to a position
  for the \e parent object, and tehn appends them to an array
  belonging to the \e parent object. An example of \e child is
  an Element object containing data for atoms, and an example of
  \e parent is an Element object containing data for molecules.

  The terms \e child and \e parent are used because a \e parent object
  consists of a \e child object. In terms of time series, however,
  the \e child is created earlier than the \e parent.

  About usage in Python,
  please see pybind::py_add_child_positions.
*/
class AddChildPositions : public Adder {
  /*!
    Name of \e child object stored as #ext_generator. Key for property
    added to a \e parent object by this class is named
    as <c>[child_name]-xs</c>, <c>[child_name]-ys</c>
    and <c>[child_name]-zs</c>. The \e parent object is also required
    to have <c>[child_name]-ids</c> property.
  */
  Str child_name;
 protected:
  /*!
    @brief This method overrides Updater::compute_impl.

    <dl class="property added">
      <dt class="property added">Property to be added</dt>
      <dd class="property added">
        - <c>[child_name]-xs</c> : array of floats
        - <c>[child_name]-ys</c> : array of floats
        - <c>[child_name]-zs</c> : array of floats
      </dd>
    </dl>

    <dl class="property required">
      <dt class="property required">Required property</dt>
      <dd class="property required">
        - <c>[child_name]-ids</c> : array of integers
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
    @brief Constructor of AddChildPositions class.

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

    @param child_name_
      A string for naming the \e child object.
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