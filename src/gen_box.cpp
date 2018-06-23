/* ---------------------------------------------------------------------
GenBox: stands for Generator of Box.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "gen_box.h"

/* ------------------------------------------------------------------ */

GenBox::GenBox() {

  dataname = "Box";

}

/* ------------------------------------------------------------------ */

GenBox::GenBox(const std::string &suffix) {

  dataname = "Box_" + suffix;

}

/* ------------------------------------------------------------------ */

const std::vector<bool> GenBox::get_periodic() {

  check_data();

  return {
    data["periodic_x"], data["periodic_y"], data["periodic_z"]
  };

}

/* ------------------------------------------------------------------ */

const std::vector<std::map<std::string,double>> GenBox::get_edge() {

  check_data();

  return {
    {{"min", data["min_x"]}, {"max", data["max_x"]}},
    {{"min", data["min_y"]}, {"max", data["max_y"]}},
    {{"min", data["min_z"]}, {"max", data["max_z"]}}
  };

}