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
  @brief AddChildIDs adds `id` property of a child Element object to
  a parent Element object.

  An object of this class owns a *child* Element object
  as #ext_generator, and is appended to a *parent* object
  using its Element::append_updater. The object of this class
  appends values for `id` property of the *child* object to an array
  belonging to the *parent* object. An example of *child* is
  an Element object containing data for atoms, and an example of
  *parent* is an Element object containing data for molecules.

  The terms *child* and *parent* are used because a *parent* object
  consists of a *child* object. In terms of time series, however,
  the *child* is created earlier than the *parent*.

  About usage in Python,
  please see pybind::py_add_child_ids.
*/
class AddChildIDs : public Adder {
  /*!
    Name of *child* object stored as #ext_generator. Key for property
    added by this class is named as `[child_name]-ids`.
  */
  Str child_name;
  /*!
    Key in #ext_generator corresponding to `id` of *parent* object.
  */
  Str key_for_parent_id;
 protected:
  /*!
    @brief This method overrides Updater::compute_impl.

    <dl class="property added">
      <dt class="property added">Property to be added</dt>
      <dd class="property added">
        - `[child_name]-ids` : array of integers
      </dd>
    </dl>

    <dl class="property required">
      <dt class="property required">Required property</dt>
      <dd class="property required">
        - `id` : integer
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
      A *child* Element object.
      <span class="remove_in_table">
        This parameter is assigned to #ext_generator.
      </span>
      <dl class="property required_ext">
        <dt class="property required_ext">Required property</dt>
        <dd class="property required_ext">
          - `id` : integer
          - `[key_for_parent_id]` : integer
        </dd>
      </dl>

    @param child_name_
      A string for naming the *child* object.
      <span class="remove_in_table">
        This parameter is assigned to #child_name.
      </span>

    @param key_for_parent_id_
      A string for key in the *child* object
      corresponding to `id` of *parent* object.
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