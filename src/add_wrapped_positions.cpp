/* ---------------------------------------------------------------------
AddWrappedPositions: stands for Adder for Wrapped Postisions.

create: 2018/07/07 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_wrapped_positions.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

AddWrappedPositions::AddWrappedPositions(
  std::shared_ptr<Generator> gen)
{
  if (gen->get_datatype() == "Box")
  {
    reference_generator = gen;
  }
  else
  {
    runtime_error(
      "AddWrappedPositions cannot use " + gen->get_dataname());
  }

  callable_datatypes = {"Atoms", "Molecules", "Beads"};
}

/* ------------------------------------------------------------------ */

void AddWrappedPositions::compute_impl(json &data)
{
  if (!json_all(check_key(data, {"xu", "yu", "zu"})))
  {
    runtime_error("Unwrapped positions do not exist");
  }

  auto &box = reference_generator->get_data();

  Eigen::Array3d offset;
  offset << double(box["min_x"]),
            double(box["min_y"]),
            double(box["min_z"]);

  Eigen::Array3d length;
  length << double(box["max_x"]) - double(box["min_x"]),
            double(box["max_y"]) - double(box["min_y"]),
            double(box["max_z"]) - double(box["min_z"]);

  for (auto &d : data)
  {
    Eigen::Array3d unwrapped;
    unwrapped << d["xu"], d["yu"], d["zu"];

    auto tmp = unwrapped;

    tmp -= offset;
    tmp /= length;

    tmp = -tmp.floor();

    tmp *= length;

    auto wrapped = unwrapped + tmp;

    d["x"] = wrapped(0);
    d["y"] = wrapped(1);
    d["z"] = wrapped(2);
  }
}
