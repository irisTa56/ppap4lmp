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

  An object of this class simply renames an existing property of
  an Element object; that is, copies values for the existing property,
  store the values with a new user-defined name, and then
  deletes the old property.

  About usage in Python,
  please see pybind::py_add_rename.
*/
class AddRename : public Adder, public EnShThis<AddRename> {
  /*!
    Whether overwriting an existing property whose name is
    the same as #key_new (default is `false`).
  */
  bool do_overwrite = false;
  /*!
    Key for an existing property to be renamed.
  */
  Str key_old;
  /*!
    New key by which the existing property is renamed.
  */
  Str key_new;
 protected:
  /*!
    @brief This method overrides Updater::compute_impl.
  */
  virtual void compute_impl(
    Json &data) override;
 public:
  /*!
    @brief Constructor of AddRename class.

    @param key_old_
    @parblock
      A string key for an existing property to be renamed.
      <span class="remove_in_table">
        This parameter is assigned to #key_old.
      </span>

    @param key_new_
      A string key by which the old key for the existing property is
      renamed.
      <span class="remove_in_table">
        This parameter is assigned to #key_new.
      </span>
    @endparblock
  */
  AddRename(
    const Str &key_old_,
    const Str &key_new_);
  virtual ~AddRename() = default;
  /*!
    @brief Allow overwriting an existing property by a renamed property
    with the same name.

    @param do_overwrite_
      A boolean, whether an existing property can be overwritten
      by a renamed property (default is `true`).
      <span class="remove_in_table">
        This parameter is assigned to #do_overwrite.
      </span>

    @return Shared pointer to this object.

    <span class="remove_in_table">
      Please be careful not to call this method
      in a multithreading context because it is thread-unsafe.
    </span>
  */
  ShPtr<AddRename> overwrite(
    bool do_overwrite_ = true);
};

#endif