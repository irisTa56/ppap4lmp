/* ---------------------------------------------------------------------
AddMap: stands for Adder for Mapping from existing properties to new
properties.

create: 2018/06/26 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_MAP_H
#define ADD_MAP_H

#include <adders/adder.h>

class AddMap : public Adder, public EnShThis<AddMap> {
  bool do_overwrite = false;
  Str key_ref;
  Str key_new;
  Dict<Json,Json> mapping;
 protected:
  virtual void compute_impl(
    Json &data,
    Set<Str> &datakeys) override;
 public:
  AddMap(
    const Str &key_ref_,
    const Str &key_new_,
    const Dict<Json,Json> &mapping_);
  virtual ~AddMap() = default;
  ShPtr<AddMap> overwrite(
    bool do_overwrite_ = true);
};

#endif