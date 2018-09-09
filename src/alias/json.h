/*!
  @file src/alias/json.h
  @brief ...
  @author Takayuki Kobayashi
  @date 2018/09/09
  @details ...
*/

#ifndef ALIAS_JSON_H
#define ALIAS_JSON_H

#include <nlohmann/json.hpp>

/*!
  @brief ...
*/
using Json = nlohmann::json;

#ifdef ALIAS_PYBIND_H
#include <alias/pybind_json.h>
#endif

#endif