/*!
  @file src/adders/add_child_positions.h
  @brief This file has a definition of the AddChildPositions class,
  which is a subclass of the Adder class.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#ifndef ADD_CHILD_POSITIONS_H
#define ADD_CHILD_POSITIONS_H

#include <adders/adder.h>

/*!
  @brief \e AddChildPositions stands for Adder for Child Positions
  (such as \c atom-xs, \c atom-ys and \c atom-zs for molecules).
  @details This class inherits Adder class and overrides
  Adder::compute_impl. An instance of this class is supposed to own a
  \e children instance (such as atoms) as the #ext_generator and be
  appended to \e parent instance (such as molecules). A position of a
  \e child is computed relative to a position of its \e parent and
  appended to an array belonging to the \e parent. About usage in
  Python, please see src/pybind/adders/add_child_positions.h.
  <p>
  Name (key) of property to be added:
    - <c>[child_name]-xs</c> (array of float)
    - <c>[child_name]-ys</c> (array of float)
    - <c>[child_name]-zs</c> (array of float)
  </p>
  <p>
  Name (key) of property to be required:
    - <c>[child_name]-ids</c> (array of integer)
    - \c xu (float)
    - \c yu (float)
    - \c zu (float)
  </p>
  <p>
  Name (key) of property in #ext_generator to be required:
    - \c id (integer)
    - \c xu (float)
    - \c yu (float)
    - \c zu (float)
  </p>
*/
class AddChildPositions : public Adder {
  /*!
    @brief Name of \e children instance stored as #ext_generator.
    @details The name (key) of property added to the \e parent instance
    by this class is named as <c>[child_name]-xs</c>,
    <c>[child_name]-ys</c> and <c>[child_name]-zs</c>. The \e parent
    instance is also required to have <c>[child_name]-ids</c> property.
  */
  Str child_name;
 protected:
  /*!
    @copydoc AddMap::compute_impl
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddChildPositions class.
    @param elem : Shared pointer to \e children instance.
    @param child_name_ : A string for name of the \e children instance.
    @return Instance of this class.
    @details The \c elem and \c child_name_ are assigned to the
    #ext_generator and #child_name respectively.
  */
  AddChildPositions(
    const ElPtr &elem,
    const Str &child_name_);
  virtual ~AddChildPositions() = default;
};

#endif