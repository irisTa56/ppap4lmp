/* ---------------------------------------------------------------------
AddRename: stands for Adder to create new property by Renaming existing
property.

create: 2018/08/17 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_RENAME_H
#define ADD_RENAME_H

#include <adders/adder.h>

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