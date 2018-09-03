#ifndef DATA_KEYS_H
#define DATA_KEYS_H

#include <alias/std.h>
#include <alias/json.h>

class DataKeys {
  Set<Str> _keys;
 public:
  DataKeys() = default;
  virtual ~DataKeys() = default;
  void clear();
  void set(
    const Set<Str> &keys);
  void add(
    const Json &key_);
  void remove(
    const Json &key_);
  void required(
    const Json &key_);
  bool optional(
    const Json &key_);
  const Set<Str> &get();
};

#endif