/*!
  @file src/adders/add_wrapped_position.cpp
  @brief This file has an implementation of AddWrappedPosition class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/07/07
*/

#include "add_wrapped_position.h"

/* ------------------------------------------------------------------ */

AddWrappedPosition::AddWrappedPosition(
  const ElPtr &elem)
{
  ext_generator = elem;
}

/* ------------------------------------------------------------------ */

void AddWrappedPosition::compute_impl(
  Json &data)
{
  required_keys({"xu", "yu", "zu"});

  auto el_box = ext_generator->get_element();

  el_box->required_keys({"lo_x", "lo_y", "lo_z", "hi_x", "hi_y", "hi_z"});

  auto &box = el_box->get_data();

  ArrayXd offset(3);
  offset << box["lo_x"], box["lo_y"], box["lo_z"];

  ArrayXd length(3);
  length << box["hi_x"], box["hi_y"], box["hi_z"];
  length -= offset;

  for (auto &d : data)
  {
    ArrayXd unwrapped(3);
    unwrapped << d["xu"], d["yu"], d["zu"];

    ArrayXd tmp = unwrapped;

    tmp -= offset;
    tmp /= length;

    tmp = -tmp.floor();
    tmp *= length;
    tmp += unwrapped;

    d["x"] = tmp(0);
    d["y"] = tmp(1);
    d["z"] = tmp(2);
  }
}

/* ------------------------------------------------------------------ */
