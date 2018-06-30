/* ---------------------------------------------------------------------
GenBox: stands for Generator of Box.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "gen_box.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

GenBox::GenBox()
{
  classname = make_classname(this);
  dataname = make_dataname(classname, this);
}

/* ------------------------------------------------------------------ */

const std::vector<bool> GenBox::get_periodic()
{
  return {
    data["periodic_x"], data["periodic_y"], data["periodic_z"]
  };
}

/* ------------------------------------------------------------------ */

const std::vector<bool> GenBox::get_periodic_py()
{
  hello();
  return get_periodic();
}

/* ------------------------------------------------------------------ */

const std::vector<std::unordered_map<std::string,double>> GenBox::get_edge()
{
  return {
    {{"min", data["min_x"]}, {"max", data["max_x"]}},
    {{"min", data["min_y"]}, {"max", data["max_y"]}},
    {{"min", data["min_z"]}, {"max", data["max_z"]}}
  };
}

/* ------------------------------------------------------------------ */

const std::vector<std::unordered_map<std::string,double>> GenBox::get_edge_py()
{
  hello();
  return get_edge();
}