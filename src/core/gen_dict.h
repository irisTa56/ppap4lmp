/*!
  @file src/core/gen_dict.h
  @brief This file has a definition of GenDict class.
  @author Takayuki Kobayashi
  @date 2018/07/03
*/

#ifndef GEN_DICT_H
#define GEN_DICT_H

#include <core/element.h>

/*!
  @brief GenDict is a dictionary (or map) of Generator objects.

  This class is a subclass of Generator class and stores
  an arbitrary number of Generator objects as a dictionary (map) of
  shared pointers of Generator class.
*/
class GenDict : public Generator {
  /*!
    Dictionary of shared pointers of Generator class (keys are
    strings and values are shared pointers). The values can be
    a pointer of Element, GenDict or GenList class up-casted to
    a shared pointer of Generator class.
  */
  Map<Str,ShPtr<Generator>> generator_dict;
 public:
  /*!
    @brief Constructor of GenDict class.

    @param generator_dict_
      Dictionary of shared pointers of Generator class.
      This parameter is assigned to #generator_dict.

    This constructor is thread-unsafe because it accesses
    its members thread-globally. Ensure this constructor is
    not called in a multithreading context.
  */
  GenDict(
    const Map<Str,ShPtr<Generator>> &generator_dict_);
  virtual ~GenDict() = default;
  /*!
    @brief Get a value in #generator_dict as a shared pointer of
    Element class.

    @param name
      A string key in #generator_dict.

    @return A value of #generator_dict up-casted to Element class.

    One needs to get a value of #generator_dict as Element
    when using its Element::data.
  */
  virtual ElPtr get_element(
    const Json &name = nullptr) override;
  /*!
    @brief Get a value in #generator_dict as a shared pointer of
    Generator class.

    @param name
      A string key in #generator_dict.

    @return A value of #generator_dict.

    One needs to get a value of #generator_dict as Generator
    when storing that object.
  */
  virtual ShPtr<Generator> get_generator(
    const Json &name = nullptr) override;
  //! @copydoc Generator::talk_with
  virtual void talk_with(
    const Str &classname) override;
  /*!
    @brief Get a set of the keys of #generator_dict.

    @return Set of strings.
  */
  Set<Str> get_keys();
};

#endif
