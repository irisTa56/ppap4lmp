#ifndef ALIAS_STD_H
#define ALIAS_STD_H

#include <memory>

template <typename T>
using ShPtr = std::shared_ptr<T>;

template <typename T>
using EnShThis = std::enable_shared_from_this<T>;

#include <string>

using Str = std::string;

#include <vector>

template <typename T>
using Vec = std::vector<T>;

#include <unordered_map>

template <typename T, typename U>
using Map = std::unordered_map<T,U>;

#include <unordered_set>

template <typename T>
using Set = std::unordered_set<T>;

#ifdef ALIAS_PYBIND_H
#include <alias/pybind_std.h>
#endif

#endif