/*!
  @file src/adders/add_map.h
  @brief This file has a definition of the AddMap class, which is a
  subclass of the Adder class.
  @author Takayuki Kobayashi
  @date 2018/06/26
*/

#ifndef ADD_MAP_H
#define ADD_MAP_H

#include <adders/adder.h>

/*!
  @brief \e AddMap stands for Adder for Mapping from existing property
  to new property.
  @details This class inherits Adder class and overrides
  Adder::compute_impl. About usage in Python, please see
  src/pybind/adders/add_map.h.
*/
class AddMap : public Adder, public EnShThis<AddMap> {
  bool do_overwrite = false;
  Str key_ref;
  Str key_new;
  Map<Json,Json> mapping;
 protected:
  /*!
    @brief Compute properties and add them to Element::data given as a
    reference.
    @param data : Mutable reference to Element::data where computed
    properties are added to.
    @param datakeys : Mutable reference to Element::datakeys where keys
    of computed properties are added to.
    @return None.
    @details I'm sorry to say that source code is the best
    documentation for this method...
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  AddMap(
    const Str &key_ref_,
    const Str &key_new_,
    const Map<Json,Json> &mapping_);
  virtual ~AddMap() = default;
  ShPtr<AddMap> overwrite(
    bool do_overwrite_ = true);
};

#endif