#ifndef ALIAS_JSON_H
#define ALIAS_JSON_H

#include <nlohmann/json.hpp>

using Json = nlohmann::json;

#ifdef ALIAS_PYBIND_H
#include <alias/pybind_json.h>
#endif

#endif