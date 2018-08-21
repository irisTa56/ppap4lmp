/* ---------------------------------------------------------------------
AddWrappedPositions: stands for Adder for Wrapped Postisions.

create: 2018/07/07 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_wrapped_positions.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

AddWrappedPositions::AddWrappedPositions(
  ShPtr<GenElement> elem)
{
  ext_generator = elem;
}

/* ------------------------------------------------------------------ */

void AddWrappedPositions::compute_impl(
  Json &data,
  Set<Str> &datakeys)
{
  auto gen_box = ext_generator->get_element();

  check_keys(
    gen_box, {"lo_x", "lo_y", "lo_z", "hi_x", "hi_y", "hi_z"});
  check_keys(datakeys, {"xu", "yu", "zu"});

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

  datakeys.insert({"x", "y", "z"});
}
