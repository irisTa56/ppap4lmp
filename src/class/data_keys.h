/*!
  @file src/class/data_keys.h
  @brief This file has a definition of DataKeys class,
  which is owned by Element class.
  @author Takayuki Kobayashi
  @date 2018/09/09
*/

#ifndef DATA_KEYS_H
#define DATA_KEYS_H

#include <alias/std.h>
#include <alias/json.h>

/*!
  @brief DataKeys is a small class owning a set of string keys
  in Element::data.

  An object of this class is owned by an Element object
  and used for checking existence of keys for properties in
  the Element::data quickly. Note that checking keys against
  the Element::data itself is a time consuming process if it is
  a large array ::Json object.
*/
class DataKeys {
  /*!
    A set of string keys in Element::data. Do not forget to add key(s)
    to this member manually when new item(s) is added to Element::data.
  */
  Set<Str> _keys;
  /*!
    Name of a class of which instance calls #required. Showing the class
    name in an error message raised by #required helps debugging.
  */
  Str checking_classname;
 public:
  //! Constructor of DataKeys class (default).
  DataKeys() = default;
  virtual ~DataKeys() = default;
  /*!
    @brief Clear #_keys.

    @return None.
  */
  void clear();
  /*!
    @brief Set a given set of keys as #_keys.

    @param keys
      Set of string keys to be assigned to #_keys.

    @return None.
  */
  void set(
    const Set<Str> &keys);
  /*!
    @brief Add key(s) in an array to #_keys.

    @param key_
      A ::Json object for either a key or an array of keys to be added.

    @return None.
  */
  void add(
    const Json &key_);
  /*!
    @brief Remove key(s) in an array from #_keys.

    @param key_
      A ::Json object for either a key or an array of keys
      to be removed.

    @return None.
  */
  void remove(
    const Json &key_);
  /*!
    @brief Set a name of class of which instance calls #required.

    @param classname
      A string to be assigned to #checking_classname.

    @return None.
  */
  void set_checking_classname(
    const Str &classname);
  /*!
    @brief Check if this object has required key(s).

    @param key_
      A ::Json object for either a key or an array of keys
      for required property.

    @return None.

    If this object does not have the given required key(s),
    a runtime error is thrown in C++ (and also raised in Python).
  */
  void required(
    const Json &key_);
  /*!
    @brief Check if this object has optional key(s).

    @param key_
      A ::Json object for either a key or an array of keys
      for optional property.

    @return A boolean.

    If this object has the given key(s), it returns true. If
    not, it returns false.
  */
  bool optional(
    const Json &key_);
  /*!
    @brief Get a constant reference to #_keys.

    @return Constant reference to ::Set<#Str>.
  */
  const Set<Str> &get();
};

#endif