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
  @details An object of this class simply renames an existing property;
  that is, copies values of the existing property, names the values as
  a new user-defined name, and then deletes the old property.

  About usage in Python,
  please see src/pybind/adders/py_add_rename.h.
*/
class AddRename : public Adder, public EnShThis<AddRename> {
  /*!
    @brief Whether overwriting an existing property whose name is the
    same as new property to be added (default is false).
  */
  bool do_overwrite = false;
  /*!
    @brief Key for an existing property to be renamed.
  */
  Str key_old;
  /*!
    @brief New key by which the existing property is renamed.
  */
  Str key_new;
 protected:
  /*!
    @copydoc Updater::compute_impl
    @details
    <table class="py_table2">
      <caption>
        AddRename related properties
      </caption>
      <tr class="py_tr">
        <th class="py_th2">Key for property to be added</th>
        <th class="py_th2">Key for required property</th>
        <th class="py_th2">Key for externally required property</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">
          - <c>[key_new]</c> : any type
        </td>
        <td class="py_td">
          - <c>[key_old]</c> : any type
        </td>
        <td class="py_td">
          None.
        </td>
      </tr>
    </table>
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddRename class.
    @param key_old_ : A string key for an existing property to be
    renamed.
    This argument is assigned to #key_old.
    @param key_new_ : A string key by which the old key
    for the existing property is renamed.
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
    a multithreading context because it is thread-unsafe.
  */
  ShPtr<AddRename> overwrite(
    bool do_overwrite_ = true);
};

#endif