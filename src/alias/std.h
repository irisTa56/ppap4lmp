/*!
  @file src/alias/std.h
  @brief ...
  @author Takayuki Kobayashi
  @date 2018/09/09
  @details ...
*/

#ifndef ALIAS_STD_H
#define ALIAS_STD_H

#include <memory>

/*!
  @brief ...
*/
template <typename T>
using ShPtr = std::shared_ptr<T>;

/*!
  @brief ...
*/
template <typename T>
using EnShThis = std::enable_shared_from_this<T>;

#include <string>

/*!
  @brief ...
*/
using Str = std::string;

#include <vector>

/*!
  @brief ...
*/
template <typename T>
using Vec = std::vector<T>;

#include <unordered_map>

/*!
  @brief ...
*/
template <typename T, typename U>
using Map = std::unordered_map<T,U>;

#include <unordered_set>

/*!
  @brief ...
*/
template <typename T>
using Set = std::unordered_set<T>;

#ifdef ALIAS_PYBIND_H
#include <alias/pybind_std.h>
#endif

#endif