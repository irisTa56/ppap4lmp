/*!
  @file src/adders/add_child_ids.h
  @brief This file has a definition of AddChildIDs class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/08/19
*/

#ifndef ADD_CHILD_IDS_H
#define ADD_CHILD_IDS_H

#include <adders/adder.h>

/*!
  @brief AddChildIDs adds \c id property of a child Element object to
  a parent Element object.

  An object of this class owns a \e child Element object
  as #ext_generator, and is appended to a \e parent object
  using its Element::append_updater. The object of this class
  appends values for \c id property of the \e child object to an array
  belonging to the \e parent object. An example of \e child is
  an Element object containing data for atoms, and an example of
  \e parent is an Element object containing data for molecules.

  The terms \e child and \e parent are used because a \e parent object
  consists of a \e child object. In terms of time series, however,
  the \e child is created earlier than the \e parent.

  About usage in Python,
  please see pybind::py_add_child_ids.
*/
class AddChildIDs : public Adder {
  /*!
    Name of \e child object stored as #ext_generator. Key for property
    added by this class is named as <c>[child_name]-ids</c>.
  */
  Str child_name;
  /*!
    Key in #ext_generator corresponding to \c id of \e parent object.
  */
  Str key_for_parent_id;
 protected:
  /*!
    @brief This method overrides Updater::compute_impl.

    <dl class="property added">
      <dt class="property added">Property to be added</dt>
      <dd class="property added">
        - <c>[child_name]-ids</c> : array of integers
      </dd>
    </dl>

    <dl class="property required">
      <dt class="property required">Required property</dt>
      <dd class="property required">
        - \c id : integer
      </dd>
    </dl>
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddChildIDs class.

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
          - <c>[key_for_parent_id]</c> : integer
        </dd>
      </dl>

    @param child_name_
      A string for naming the \e child object.
      <span class="remove_in_table">
        This parameter is assigned to #child_name.
      </span>

    @param key_for_parent_id_
      A string for key in the \e child object
      corresponding to \c id of \e parent object.
      <span class="remove_in_table">
        This parameter is assigned to #key_for_parent_id.
      </span>
    @endparblock
  */
  AddChildIDs(
    const ElPtr &elem,
    const Str &child_name_,
    const Str &key_for_parent_id_);
  virtual ~AddChildIDs() = default;
};

#endif