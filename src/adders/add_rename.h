/*!
  @file src/adders/add_rename.h
  @brief This file has a definition of the AddRename class, which is a
  subclass of the Adder class.
  @author Takayuki Kobayashi
  @date 2018/08/17
*/

#ifndef ADD_RENAME_H
#define ADD_RENAME_H

#include <adders/adder.h>

/*!
  @brief \e AddRename stands for Adder creating new property by Renaming
  existing property.
  @details This class inherits Adder class and ::EnShThis<#AddRename>,
  and overrides Adder::compute_impl. This class simply renames an
  existing property; copies values of the existing property with a new
  arbitrary name, then deletes the old property. About usage in Python,
  please see src/pybind/adders/add_rename.h.
  <p>
  Name (key) of property to be added:
    - \c <c>[key_new]</c> (any type)
  </p>
  <p>
  Name (key) of property to be required:
    - <c>[key_old]</c> (any type)
  </p>
*/
class AddRename : public Adder, public EnShThis<AddRename> {
  /*!
    @brief Whether overwriting an existing property whose name is the
    same as new property to be added (default is false).
  */
  bool do_overwrite = false;
  /*!
    @brief Name (key) of an existing property.
  */
  Str key_old;
  /*!
    @brief Name (key) of a new property to be added (codomain of the
    mapping).
  */
  Str key_new;
 protected:
  /*!
    @copydoc AddMap::compute_impl
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddRename class.
    @param key_old_ : A string key for an old property to be renamed.
    @param key_new_ : A string key for a new property to be added.
    @details The \c key_old_ and \c key_new_ are assigned to the
    #key_old and #key_new, respectively.
  */
  AddRename(
    const Str &key_old_,
    const Str &key_new_);
  virtual ~AddRename() = default;
  /*!
    @brief Switch #do_overwrite (to true by default).
    @param do_overwrite_ : A boolean to be assigned to #do_overwrite.
    @return Shared pointer to this object.
  */
  ShPtr<AddRename> overwrite(
    bool do_overwrite_ = true);
};

#endif