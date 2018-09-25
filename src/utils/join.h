/*!
  @file src/utils/join.h
  @brief This file has a definition of ::utils::join.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#ifndef UTILS_JOIN_H
#define UTILS_JOIN_H

#include <alias/std.h>

//! Namespace for utility functions.
namespace utils
{
  /*!
    @brief Mimicking Python's \c join.

    @param strs
      Vector (list) of strings to be joined.

    @param jointer
      A string used for jointing elements of the \c strs.

    @return A string.
  */
  Str join(
    const Vec<Str> &strs,
    const Str &jointer);
}

#endif