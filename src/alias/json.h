/*!
  @file src/alias/json.h
  @brief This file includes \e nlohmann/json and defines an alias for
  the JSON type.
  @author Takayuki Kobayashi
  @date 2018/09/09
*/

#ifndef ALIAS_JSON_H
#define ALIAS_JSON_H

#include <nlohmann/json.hpp>

/*!
  @brief \e Json is an alias for the JSON type.
  @details For more details, please see the
  <a href="https://github.com/nlohmann/json">repository</a> and
  <a href="https://nlohmann.github.io/json/">documents</a> of
  \e nlohmann/json.
*/
using Json = nlohmann::json;

#ifdef ALIAS_PYBIND_H
#include <alias/pybind_json.h>
#endif

#endif