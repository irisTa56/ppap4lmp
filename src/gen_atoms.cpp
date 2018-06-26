/* ---------------------------------------------------------------------
GenAtoms: stands for Generator of Atoms.

create: 2018/06/23 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "gen_atoms.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

GenAtoms::GenAtoms()
{
  dataname = "Atoms";
}

/* ------------------------------------------------------------------ */

GenAtoms::GenAtoms(const std::string &suffix)
{
  dataname = "Atoms_" + suffix;
}

/* ------------------------------------------------------------------ */

const Eigen::ArrayXXd GenAtoms::get_positions(const std::string &type)
{
  check_data();

  Eigen::ArrayXXd r(data.size(), 3);

  if (type == "unscaled")
  {
    if (!is_unscaled())
    {
      runtime_error("'unscaled' positions have not been set yet");
    }

    assign_positions(r, {"x", "y", "z"});
  }
  else if (type == "scaled")
  {
    if (!is_scaled())
    {
      runtime_error("'scaled' positions have not been set yet");
    }

    assign_positions(r, {"xs", "ys", "zs"});
  }
  else if (type == "unwrapped")
  {
    if (!is_unwrapped())
    {
      runtime_error("'unwrapped' positions have not been set yet");
    }

    assign_positions(r, {"xu", "yu", "zu"});
  }
  else if (type == "scaled unwrapped")
  {
    if (!is_scaled_unwrapped())
    {
      runtime_error("'scaled unwrapped' positions have not been set yet");
    }

    assign_positions(r, {"xsu", "ysu", "zsu"});
  }
  else
  {
    runtime_error("Only 'unscaled', 'scaled', 'unwrapped' and 'scaled unwrapped' are supported");
  }

  return r;
}

/* ------------------------------------------------------------------ */

const bool GenAtoms::is_unscaled(bool check_only_front)
{
  auto count = count_keys({"x", "y", "z"}, check_only_front);

  if (count == std::vector<int>({1, 1, 1}))
  {
    return true;
  }
  else if (count == std::vector<int>({0, 0, 0}))
  {
    return false;
  }
  else
  {
    runtime_error("Invalid 'unscaled' positions");
  }
}

/* ------------------------------------------------------------------ */

const bool GenAtoms::is_scaled(bool check_only_front)
{
  auto count = count_keys({"xs", "ys", "zs"}, check_only_front);

  if (count == std::vector<int>({1, 1, 1}))
  {
    return true;
  }
  else if (count == std::vector<int>({0, 0, 0}))
  {
    return false;
  }
  else
  {
    runtime_error("Invalid 'scaled' positions");
  }
}

/* ------------------------------------------------------------------ */

const bool GenAtoms::is_unwrapped(bool check_only_front)
{
  auto count = count_keys({"xu", "yu", "zu"}, check_only_front);

  if (count == std::vector<int>({1, 1, 1}))
  {
    return true;
  }
  else if (count == std::vector<int>({0, 0, 0}))
  {
    return false;
  }
  else
  {
    runtime_error("Invalid 'unwrapped' positions");
  }
}

/* ------------------------------------------------------------------ */

const bool GenAtoms::is_scaled_unwrapped(bool check_only_front)
{
  auto count = count_keys({"xsu", "ysu", "zsu"}, check_only_front);

  if (count == std::vector<int>({1, 1, 1}))
  {
    return true;
  }
  else if (count == std::vector<int>({0, 0, 0}))
  {
    return false;
  }
  else
  {
    runtime_error("Invalid 'scaled unwrapped' positions");
  }
}

/* ------------------------------------------------------------------ */

void GenAtoms::assign_positions(
  Eigen::ArrayXXd &array, const std::vector<std::string> &keys)
{
  int length = data.size();

  for (int i = 0; i < length; ++i)
  {
    auto &d = data[i];
    array(i,0) = d[keys[0]];
    array(i,1) = d[keys[1]];
    array(i,2) = d[keys[2]];
  }
}
