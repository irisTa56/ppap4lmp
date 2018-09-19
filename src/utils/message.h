/*!
  @file src/utils/message.h
  @brief This file has definitions of messaging functions.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#ifndef UTILS_MESSAGE_H
#define UTILS_MESSAGE_H

#include <alias/std.h>

//! Namespace for utility functions.
namespace utils
{
  /*!
    @brief Print to standard output.
    @param msg : A string to be printed.
    @return None.
  */
  void _message(
    const Str &msg);

  /*!
    @brief Logging a message.
    @param msg : A string to be printed.
    @return None.
  */
  void log(
    const Str &msg);

  /*!
    @brief Waning with a message.
    @param msg : A string to be printed.
    @return None.
  */
  void warning(
    const Str &msg);

  /*!
    @brief Switch on/off logging.
    @param input : Whether enable the logging or not.
    @return None.
    @details Note that logging is disabled by default.
  */
  void log_switch(
    bool input);
}

#endif