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

//! *ShPtr* is an alias for shared pointer.
template <typename T>
using ShPtr = std::shared_ptr<T>;

/*!
  @brief *EnShThis* is an alias for a class which can create shared
  pointer of itself by calling `shared_from_this()`.
*/
template <typename T>
using EnShThis = std::enable_shared_from_this<T>;

#include <string>

//! *Str* is an alias for string.
using Str = std::string;

#include <vector>

//! *Vec* is an alias for vector (same as list in Python).
template <typename T>
using Vec = std::vector<T>;

#include <unordered_map>

/*!
  @brief *Map* is an alias for unordered map (same as dict in Python).

  Searching an item from unordered map takes shorter time
  than doing the same thing with ordered map (`std::map`).
*/
template <typename T, typename U>
using Map = std::unordered_map<T,U>;

#include <unordered_set>

/*!
  @brief *Set* is an alias for unordered set (same as set in Python).

  Searching an element from unordered set takes shorter time
  than doing the same thing with ordered set (`std::set`).
*/
template <typename T>
using Set = std::unordered_set<T>;

#ifdef ALIAS_PYBIND_H
#include <alias/pybind_std.h>
#endif

#endif