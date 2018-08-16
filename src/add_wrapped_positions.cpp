/* ---------------------------------------------------------------------
AddWrappedPositions: stands for Adder for Wrapped Postisions.

create: 2018/07/07 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_wrapped_positions.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

AddWrappedPositions::AddWrappedPositions(ShPtr<GenElement> elem)
{
  ext_generator = elem;
}

/* ------------------------------------------------------------------ */

void AddWrappedPositions::compute_impl(Json &data, Set<Str> &datakeys)
{
  auto gen_box = ext_generator->get_element();

  if (!check_containment<Str>(
    gen_box->get_keys(),
    {"lo_x", "lo_y", "lo_z", "hi_x", "hi_y", "hi_z"}))
  {
    runtime_error(
      "AddWrappedPositions needs 'lo_*' and 'hi_*' (x/y/z) externally");
    return;
  }

  auto &box = gen_box->get_data();

  if (!check_containment<Str>(datakeys, {"xu", "yu", "zu"}))
  {
    runtime_error("AddWrappedPositions needs 'xu', 'yu' and 'zu'");
    return;
  }

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
