/*!
  @file src/adders/add_rename.h
  @brief This file has a definition of AddRename class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/08/17
*/

#ifndef ADD_RENAME_H
#define ADD_RENAME_H

#include <adders/adder.h>

/*!
  @brief AddRename renames an existing property.
  @details This class inherits Adder class
  and ::EnShThis<#AddRename>, and overrides Adder::compute_impl.

  An object of this class simply renames an existing property; that is,
  copies values of the existing property, names the values as
  a new user-defined name, and then deletes the old property.

  About usage in Python,
  please see src/pybind/adders/py_add_rename.h.

  Key of property to be added:
    - \c <c>[key_new]</c> (any type)

  Key of required property:
    - <c>[key_old]</c> (any type)
*/
class AddRename : public Adder, public EnShThis<AddRename> {
  /*!
    @brief Whether overwriting an existing property whose name is the
    same as new property to be added (default is false).
  */
  bool do_overwrite = false;
  /*!
    @brief Key of an existing property to be renamed.
  */
  Str key_old;
  /*!
    @brief New key by which the existing property is renamed.
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
    @param key_old_ : A string key of an existing property to be
    renamed.
    This argument is assigned to #key_old.
    @param key_new_ : A string key by which the old key of the existing
    property is renamed.
    This argument is assigned to #key_new.
  */
  AddRename(
    const Str &key_old_,
    const Str &key_new_);
  virtual ~AddRename() = default;
  /*!
    @brief Switch #do_overwrite (to true by default).
    @param do_overwrite_ : A boolean to be assigned to #do_overwrite.
    @return Shared pointer to this object.
    @details Please be careful not to call this method in
    a multithreads context because it is thread-unsafe.
  */
  ShPtr<AddRename> overwrite(
    bool do_overwrite_ = true);
};

#endif