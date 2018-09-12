/*!
  @file src/adders/add_child_ids.h
  @brief This file has a definition of the AddChildIDs class, which is
  a subclass of the Adder class.
  @author Takayuki Kobayashi
  @date 2018/08/19
*/

#ifndef ADD_CHILD_IDS_H
#define ADD_CHILD_IDS_H

#include <adders/adder.h>

/*!
  @brief \e AddChildIDs stands for Adder for Child IDs (such as
  \c atom-ids for molecules).
  @details This class inherits Adder class and overrides
  Adder::compute_impl. About usage in Python, please see
  src/pybind/adders/add_child_ids.h
*/
class AddChildIDs : public Adder {
  Str child_name;
  Str key_for_parent_id;
 protected:
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  AddChildIDs(
    const ElPtr &elem,
    const Str &child_name_,
    const Str &key_for_parent_id_);
  virtual ~AddChildIDs() = default;
};

#endif