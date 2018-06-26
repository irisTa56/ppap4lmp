/* ---------------------------------------------------------------------
AddMap: stands for Adder Mapping an existing property to a new property.

create: 2018/06/24 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <iostream>

#include "add_map.h"

/* ------------------------------------------------------------------ */

AddMap::AddMap(
  const std::string &key_ref, const std::string &key_new,
  pybind11::dict map)
{
  std::cout << map << std::endl;
}

/* ------------------------------------------------------------------ */

void AddMap::compute(nlohmann::json &data)
{

}
