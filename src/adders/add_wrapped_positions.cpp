/* ---------------------------------------------------------------------
AddWrappedPositions: stands for Adder for Wrapped Postisions.

create: 2018/07/07 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_wrapped_positions.h"

/* ------------------------------------------------------------------ */

AddWrappedPositions::AddWrappedPositions(
  const ShPtr<Element> &elem)
{
  ext_generator = elem;
}

/* ------------------------------------------------------------------ */

void AddWrappedPositions::compute_impl(
  Json &data,
  DataKeys &datakeys)
{
  datakeys.required({"xu", "yu", "zu"});

  auto gen_box = ext_generator->get_element();

  gen_box->required({"lo_x", "lo_y", "lo_z", "hi_x", "hi_y", "hi_z"});

  auto &box = gen_box->get_data();

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

  datakeys.add({"x", "y", "z"});
}
