#ifndef DATA_KEYS_H
#define DATA_KEYS_H

#include <alias/std.h>

class DataKeys {
  Set<Str> _keys;
 public:
  DataKeys() = default;
  virtual ~DataKeys() = default;
  const Set<Str> &get();
  void clear();
  void add(
    const Str &key);
  void add(
    const Set<Str> &keys);
  void remove(
    const Str &key);
  void remove(
    const Set<Str> &keys);
  void required(
    const Str &key);
  void required(
    const Set<Str> &keys);
  bool optional(
    const Str &key);
  bool optional(
    const Set<Str> &keys);
};

#endif