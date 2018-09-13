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
  @details This class inherits Adder class and overrides
  Adder::compute_impl. About usage in Python, please see
  src/pybind/adders/add_rename.h.
*/
class AddRename : public Adder, public EnShThis<AddRename> {
  bool do_overwrite = false;
  Str key_old;
  Str key_new;
 protected:
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  AddRename(
    const Str &key_old_,
    const Str &key_new_);
  virtual ~AddRename() = default;
  ShPtr<AddRename> overwrite(
    bool do_overwrite_ = true);
};

#endif