/*!
  @file src/alias/json.h
  @brief This file includes *nlohmann/json* and defines an alias for
  a JSON class.
  @author Takayuki Kobayashi
  @date 2018/09/09
*/

#ifndef ALIAS_JSON_H
#define ALIAS_JSON_H

#include <nlohmann/json.hpp>

/*!
  @brief *Json* is an alias for *nlohmann::json*.

  For more details, please see the
  <a href="https://github.com/nlohmann/json">repository</a> and
  <a href="https://nlohmann.github.io/json/">documents</a> of
  *JSON for Modern C++*.
*/
using Json = nlohmann::json;

#ifdef ALIAS_PYBIND_H
#include <alias/pybind_json.h>
#endif

#endif