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
  @details This class inherits Adder class and overrides
  Adder::compute_impl.

  An object of this class owns a \e child Element object
  as the #ext_generator, and is appended to a \e parent object
  using its Element::append_updater. An example of \e child is
  an Element object containing data for atoms, and an example of
  \e parent is an Element object containing data for molecules.
  \c id property of the \e child is appended to an array belonging
  to the \e parent.

  The terms \e child and \e parent are used because a \e parent object
  consists of a \e child object. In terms of time series, however,
  the \e child is created earlier than the \e parent.

  About usage in Python,
  please see src/pybind/adders/py_add_child_ids.h.

  Key of property to be added:
    - <c>[child_name]-ids</c> (array of integer)

  Key of required property:
    - \c id (integer)

  Key of required property in #ext_generator:
    - \c id (integer)
    - <c>[key_for_parent_id]</c> (integer)
*/
class AddChildIDs : public Adder {
  /*!
    @brief Name of \e child object stored as #ext_generator.
    @details The key of property added by this class is named as
    <c>[child_name]-ids</c>.
  */
  Str child_name;
  /*!
    @brief Key in #ext_generator corresponding to \c id of \e parent
    object.
  */
  Str key_for_parent_id;
 protected:
  /*!
    @copydoc AddMap::compute_impl
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddChildIDs class.
    @param elem : Shared pointer to a \e child object.
    This argument is assigned to #ext_generator.
    @param child_name_ : A string for naming the \e child object.
    This argument is assigned to #child_name.
    @param key_for_parent_id_ : A string for key in the \e child object
    corresponding to \c id of \e parent object.
    This argument is assigned to #key_for_parent_id.
  */
  AddChildIDs(
    const ElPtr &elem,
    const Str &child_name_,
    const Str &key_for_parent_id_);
  virtual ~AddChildIDs() = default;
};

#endif