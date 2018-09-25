/*!
  @file src/utils/runtime_error.h
  @brief This file has a definition of ::utils::runtime_error.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#ifndef UTILS_RUNTIME_ERROR_H
#define UTILS_RUNTIME_ERROR_H

#include <alias/std.h>

//! Namespace for utility functions.
namespace utils
{
  /*!
    @brief Raise (for Python) and throw (for C++) a runtime error.

    @param msg
      A string message for the runtime error.

    @return None.
  */
  void runtime_error(
    const Str &msg);
}

#endif