#ifndef DATA_KEYS_H
#define DATA_KEYS_H

#include <alias/std.h>

class DataKeys {
  Set<Str> _keys;
 public:
  DataKeys() = default;
  virtual ~DataKeys() = default;
  void clear();
  void set(
    const Set<Str> &keys);
  void add(
    const Str &key);
  void add(
    const Set<Str> &keys);
  void add(
    const std::initializer_list<Str> &keys);
  void remove(
    const Str &key);
  void remove(
    const Set<Str> &keys);
  void remove(
    const std::initializer_list<Str> &keys);
  void required(
    const Str &key);
  void required(
    const Set<Str> &keys);
  void required(
    const std::initializer_list<Str> &keys);
  bool optional(
    const Str &key);
  bool optional(
    const Set<Str> &keys);
  bool optional(
    const std::initializer_list<Str> &keys);
  const Set<Str> &get();
};

#endif