/* ---------------------------------------------------------------------
GenBox: stands for Generator of Box.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <sstream>

#include "gen_box.h"

/* ------------------------------------------------------------------ */

GenBox::GenBox()
{
  std::stringstream ss;
  ss << this;
  dataname = "Box_" + ss.str();
}

/* ------------------------------------------------------------------ */

GenBox::GenBox(const std::string &suffix)
{
  dataname = "Box_" + suffix;
}

/* ------------------------------------------------------------------ */

const std::vector<bool> GenBox::get_periodic()
{
  check_data();

  return {
    data["periodic_x"], data["periodic_y"], data["periodic_z"]
  };
}

/* ------------------------------------------------------------------ */

const std::vector<std::unordered_map<std::string,double>> GenBox::get_edge()
{
  check_data();

  return {
    {{"min", data["min_x"]}, {"max", data["max_x"]}},
    {{"min", data["min_y"]}, {"max", data["max_y"]}},
    {{"min", data["min_z"]}, {"max", data["max_z"]}}
  };
}