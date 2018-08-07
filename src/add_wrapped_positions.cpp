/* ---------------------------------------------------------------------
AddWrappedPositions: stands for Adder for Wrapped Postisions.

create: 2018/07/07 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_wrapped_positions.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

AddWrappedPositions::AddWrappedPositions(std::shared_ptr<Generator> gen)
{
  check_reference_generator(gen, "Box");
  callable_datatypes = {"Atoms", "Molecules", "Beads"};
}

/* ------------------------------------------------------------------ */

void AddWrappedPositions::compute_impl(json &data)
{
  if (!check_key(data, {"xu", "yu", "zu"}))
  {
    runtime_error("AddWrappedPositions needs the unwrapped positions");
  }

  auto &box = reference_generator->get_data();

  ArrayXd offset(3);
  offset << box["min_x"], box["min_y"], box["min_z"];

  ArrayXd length(3);
  length << box["max_x"], box["max_y"], box["max_z"];
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
