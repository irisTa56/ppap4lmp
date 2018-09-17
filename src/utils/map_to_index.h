/*!
  @file src/utils/map_to_index.h
  @brief This file has a definition of ::utils::map_to_index.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#ifndef UTILS_MAP_TO_INDEX_H
#define UTILS_MAP_TO_INDEX_H

#include <alias/std.h>
#include <alias/json.h>

//! Namespace for utility functions.
namespace utils
{
  /*!
    @brief Mainly used for creating a map from values of selected
    property in array Element::data to corresponding index in the array.
    @param data : Array ::Json.
    @param key : A string key specifying a property used as domain of
    the mapping.
    @return ::Map from elements of an array ::Json to corresponding
    index in the array.
    @details Note that the mapping must be bijection.
  */
  Map<Json,int> map_to_index(
    const Json &data,
    const Str &key);
}

#endif