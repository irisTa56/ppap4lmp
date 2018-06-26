/* ---------------------------------------------------------------------
ModMap: stands for Modifier adding new properties by Mapping an
existing properties.

create: 2018/06/24 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <iostream>

#include "mod_map.h"

/* ------------------------------------------------------------------ */

ModMap::ModMap(
  const std::string &key_ref, const std::string &key_new, pybind11::dict map) {

  std::cout << map << std::endl;

}

/* ------------------------------------------------------------------ */

void ModMap::modify(nlohmann::json &data) {

}
