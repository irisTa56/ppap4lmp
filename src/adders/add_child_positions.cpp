/*!
  @file src/adders/add_child_positions.cpp
  @brief This file has implementations of the AddChildPositions class,
  which is a subclass of the Adder class.
  @author Takayuki Kobayashi
  @date 2018/09/03
  @details For more details, please see the header file,
  src/adders/add_child_positions.h.
*/

#include "add_child_positions.h"
#include "../utils/map_to_index.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

/* ------------------------------------------------------------------ */

AddChildPositions::AddChildPositions(
  const ElPtr &elem,
  const Str &child_name_)
{
  ext_generator = elem;
  child_name = child_name_;
}

/* ------------------------------------------------------------------ */

void AddChildPositions::compute_impl(
  Json &data,
  DataKeys &datakeys)
{
  auto key_for_child_ids = child_name + "-ids";

  datakeys.required({key_for_child_ids, "xu", "yu", "zu"});

  auto el_children = ext_generator->get_element();

  el_children->required({"id", "xu", "yu", "zu"});

  auto &children = el_children->get_data();

  auto id2index_child = ut::map_to_index(children, "id");

  auto key_x = child_name + "-xs";
  auto key_y = child_name + "-ys";
  auto key_z = child_name + "-zs";

  for (auto &d : data)
  {
    double x = d["xu"];
    double y = d["yu"];
    double z = d["zu"];

    auto tmp_x = Json::array();
    auto tmp_y = Json::array();
    auto tmp_z = Json::array();

    for (const auto &child_id : d[key_for_child_ids])
    {
      auto &child = children[id2index_child[child_id]];

      tmp_x.push_back(child["xu"].get<double>() - x);
      tmp_y.push_back(child["yu"].get<double>() - y);
      tmp_z.push_back(child["zu"].get<double>() - z);
    }

    d[key_x].swap(tmp_x);
    d[key_y].swap(tmp_y);
    d[key_z].swap(tmp_z);
  }

  datakeys.add({key_x, key_y, key_z});
}

/* ------------------------------------------------------------------ */
