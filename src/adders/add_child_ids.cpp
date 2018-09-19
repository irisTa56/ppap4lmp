/*!
  @file src/adders/add_child_ids.cpp
  @brief This file has an implementation of AddChildIDs class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/08/19
  @details For more details, please see the header file,
  src/adders/add_child_ids.h.
*/

#include "add_child_ids.h"
#include "../utils/map_to_index.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

AddChildIDs::AddChildIDs(
  const ElPtr &elem,
  const Str &child_name_,
  const Str &key_for_parent_id_)
{
  ext_generator = elem;
  child_name = child_name_;
  key_for_parent_id = key_for_parent_id_;
}

/* ------------------------------------------------------------------ */

void AddChildIDs::compute_impl(
  Json &data,
  DataKeys &datakeys)
{
  datakeys.required("id");

  auto el_children = ext_generator->get_element();

  el_children->required({"id", key_for_parent_id});

  auto key_for_child_ids = child_name + "-ids";

  if (datakeys.optional(key_for_child_ids))
  {
    ut::runtime_error("Key '" + key_for_child_ids + "' already exists");
  }

  auto id2index = ut::map_to_index(data, "id");

  for (const auto &child : el_children->get_data())
  {
    auto mol_index = id2index[child[key_for_parent_id]];
    data[mol_index][key_for_child_ids].push_back(child["id"]);
  }

  datakeys.add(key_for_child_ids);
}

/* ------------------------------------------------------------------ */
