/* ---------------------------------------------------------------------
This file is for GenBox class.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "gen_box.h"

/* ------------------------------------------------------------------ */

GenBox::GenBox() {

  dataname = "Box";

}

/* ------------------------------------------------------------------ */

const std::vector<bool> GenBox::get_periodic() {

  check_data();

  return std::vector<bool>({
    data["periodic_x"], data["periodic_y"], data["periodic_z"]
  });

}

/* ------------------------------------------------------------------ */

const std::vector<std::map<std::string,double>> GenBox::get_edge() {

  check_data();

  return std::vector<std::map<std::string,double>>({
    {{"min", data["min_x"]}, {"max", data["max_x"]}},
    {{"min", data["min_y"]}, {"max", data["max_y"]}},
    {{"min", data["min_z"]}, {"max", data["max_z"]}}
  });

}