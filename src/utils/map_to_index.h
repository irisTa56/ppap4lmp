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
    @brief Create a ::Map object from values of selected property
    in an array ::Json object to corresponding index
    in the ::Json object.

    @param data
      An array ::Json object.

    @param key
      A string key specifying a property used as domain of the mapping.

    @return A ::Map object from elements of the `data`
    to corresponding index in the `data`.

    Note that the mapping must be bijection.
  */
  Map<Json,int> map_to_index(
    const Json &data,
    const Str &key);
}

#endif