/*!
  @file src/alias/std.h
  @brief This file includes a part of C++ Standard Template Library and
  defines aliases for them.
  @author Takayuki Kobayashi
  @date 2018/09/09
*/

#ifndef ALIAS_STD_H
#define ALIAS_STD_H

#include <memory>

/*!
  @brief \e ShPtr is an alias for shared pointer.
*/
template <typename T>
using ShPtr = std::shared_ptr<T>;

/*!
  @brief \e EnShThis is an alias for a class which can create shared
  pointer of itself by calling \c shared_from_this().
*/
template <typename T>
using EnShThis = std::enable_shared_from_this<T>;

#include <string>

/*!
  @brief \e Str is an alias for string.
*/
using Str = std::string;

#include <vector>

/*!
  @brief \e Vec is an alias for vector (same as list in Python).
*/
template <typename T>
using Vec = std::vector<T>;

#include <unordered_map>

/*!
  @brief \e Map is an alias for unordered map (same as dict in Python).
  @details Searching an item from unordered map is (considerably)
  faster than doing the same thing with ordered (regular in C++) map.
*/
template <typename T, typename U>
using Map = std::unordered_map<T,U>;

#include <unordered_set>

/*!
  @brief \e Set is an alias for unordered set (same as set in Python).
  @details Searching an element from unordered set is (considerably)
  faster than doing the same thing with ordered (regular in C++) set.
*/
template <typename T>
using Set = std::unordered_set<T>;

#ifdef ALIAS_PYBIND_H
#include <alias/pybind_std.h>
#endif

#endif