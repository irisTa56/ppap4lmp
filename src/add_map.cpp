/* ---------------------------------------------------------------------
AddMap: stands for Adder Mapping an existing property to a new property.

create: 2018/06/24 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_map.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

AddMap::AddMap(
  const std::string &key_ref_, const std::string &key_new_,
  pybind11::dict dict)
{
  key_ref = key_ref_;
  key_new = key_new_;

  for (const auto &item : dict)
  {
    mapping[convert_py2json(item.first)] = convert_py2json(item.second);
  }
}

/* ------------------------------------------------------------------ */

void AddMap::compute(nlohmann::json &data)
{
  if (data.is_array())
  {
    for (auto &d : data)
    {
      d[key_new] = mapping[d[key_ref]];
    }
  }
  else
  {
    message("AddMap does not compute for non-array data");
  }
}

/* ------------------------------------------------------------------ */

const nlohmann::json AddMap::convert_py2json(
  const pybind11::handle &pyhdl)
{
  if (pybind11::isinstance<pybind11::bool_>(pyhdl))
  {
    return nlohmann::json(pyhdl.cast<bool>());
  }
  else if (pybind11::isinstance<pybind11::int_>(pyhdl))
  {
    return nlohmann::json(pyhdl.cast<int>());
  }
  else if (pybind11::isinstance<pybind11::float_>(pyhdl))
  {
    return nlohmann::json(pyhdl.cast<double>());
  }
  else if (pybind11::isinstance<pybind11::str>(pyhdl))
  {
    return nlohmann::json(pyhdl.cast<std::string>());
  }
  else
  {
    runtime_error("Only 'bool', 'int', 'float' and 'str' are supported");
  }
}
