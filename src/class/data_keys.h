/*!
  @file src/class/data_keys.h
  @brief This file has a definition of the DataKeys class, which is
  owned by Element class.
  @author Takayuki Kobayashi
  @date 2018/09/09
*/

#ifndef DATA_KEYS_H
#define DATA_KEYS_H

#include <alias/std.h>
#include <alias/json.h>

/*!
  @brief \e DataKeys is a small class owning a set of string keys for
  Element::data.
  @details An object of this class is owned by an Element object to
  check whether keys for property of the data exists quickly. Checking
  against the Element::data itself is a very time consuming process if
  it is an array data.
*/
class DataKeys {
  /*!
    @brief A set of string key for Element::data.
    @details Do not forget to add key(s) to this member manually when
    new value(s) is added to Element::data in Updater::compute_impl.
  */
  Set<Str> _keys;
 public:
  /*!
    @brief Constructor of DataKeys class (default).
  */
  DataKeys() = default;
  virtual ~DataKeys() = default;
  /*!
    @brief Clear the #_keys.
    @return None.
  */
  void clear();
  /*!
    @brief Set a given set of keys as the #_keys.
    @param keys : A set of string keys to be assigned to #_keys.
    @return None.
  */
  void set(
    const Set<Str> &keys);
  /*!
    @brief Add a key or keys in an array to the #_keys.
    @param key_ : ::Json for either a key or an array of keys to be
    added.
    @return None.
  */
  void add(
    const Json &key_);
  /*!
    @brief Remove a key or keys in an array from the #_keys.
    @param key_ : ::Json for either a key or an array of keys to be
    removed.
    @return None.
  */
  void remove(
    const Json &key_);
  /*!
    @brief Check if this object has required key(s).
    @param key_ : ::Json for either a key or an array of keys to be
    required.
    @return None.
    @details If this object does not have the given required key(s),
    a runtime error is thrown in C++ (and also raised in Python).
  */
  void required(
    const Json &key_);
  /*!
    @brief Check if this object has optional key(s).
    @param key_ : ::Json for either a key or an array of keys to be
    checked.
    @return Boolean.
    @details If this object has the given key(s), it returns true. If
    not, it returns false.
  */
  bool optional(
    const Json &key_);
  /*!
    @brief Get a constant reference to the #_keys.
    @return A constant reference to ::Set<#Str>.
  */
  const Set<Str> &get();
};

#endif