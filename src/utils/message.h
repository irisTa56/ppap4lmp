#ifndef UTILS_MESSAGE_H
#define UTILS_MESSAGE_H

#include <alias/std.h>

namespace utils
{
  void _message(
    const Str &msg);

  void log(
    const Str &msg);

  void warning(
    const Str &msg);

  void log_switch(
    bool input);
}

#endif