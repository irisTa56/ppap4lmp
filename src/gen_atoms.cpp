/* ---------------------------------------------------------------------
GenAtoms: stands for Generator of Atoms.

create: 2018/06/23 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "gen_atoms.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

GenAtoms::GenAtoms()
{
  classname = make_classname(this);
  dataname = make_dataname(classname, this);
}

/* ------------------------------------------------------------------ */

const Eigen::ArrayXXd GenAtoms::get_positions(const std::string &type)
{
  check_data();

  Eigen::ArrayXXd r(data.size(), 3);

  if (type == "unscaled")
  {
    assign_positions(r, {"x", "y", "z"});
  }
  else if (type == "scaled")
  {
    assign_positions(r, {"xs", "ys", "zs"});
  }
  else if (type == "unwrapped")
  {
    assign_positions(r, {"xu", "yu", "zu"});
  }
  else if (type == "scaled unwrapped")
  {
    assign_positions(r, {"xsu", "ysu", "zsu"});
  }
  else
  {
    runtime_error("Only 'unscaled', 'scaled', 'unwrapped' and 'scaled unwrapped' are supported");
  }

  return r;
}

/* ------------------------------------------------------------------ */

const bool GenAtoms::is_unscaled()
{
  auto check = check_keys({"x", "y", "z"});

  if (check == std::vector<bool>({true, true, true}))
  {
    return true;
  }
  else if (check == std::vector<bool>({false, false, false}))
  {
    return false;
  }
  else
  {
    runtime_error("Invalid 'unscaled' positions");
  }
}

/* ------------------------------------------------------------------ */

const bool GenAtoms::is_scaled()
{
  auto check = check_keys({"xs", "ys", "zs"});

  if (check == std::vector<bool>({true, true, true}))
  {
    return true;
  }
  else if (check == std::vector<bool>({false, false, false}))
  {
    return false;
  }
  else
  {
    runtime_error("Invalid 'scaled' positions");
  }
}

/* ------------------------------------------------------------------ */

const bool GenAtoms::is_unwrapped()
{
  auto check = check_keys({"xu", "yu", "zu"});

  if (check == std::vector<bool>({true, true, true}))
  {
    return true;
  }
  else if (check == std::vector<bool>({false, false, false}))
  {
    return false;
  }
  else
  {
    runtime_error("Invalid 'unwrapped' positions");
  }
}

/* ------------------------------------------------------------------ */

const bool GenAtoms::is_scaled_unwrapped()
{
  auto check = check_keys({"xsu", "ysu", "zsu"});

  if (check == std::vector<bool>({true, true, true}))
  {
    return true;
  }
  else if (check == std::vector<bool>({false, false, false}))
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
