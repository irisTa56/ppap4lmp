/*!
  @file src/core/gen_list.h
  @brief This file has a definition of GenList class.
  @author Takayuki Kobayashi
  @date 2018/07/03
*/

#ifndef GEN_LIST_H
#define GEN_LIST_H

#include <core/element.h>

/*!
  @brief GenList is a list (or vector) of Generator objects.

  This class is a subclass of Generator class and stores
  an arbitrary number of Generator object as a list (vector) of
  shared pointers of Generator class.
*/
class GenList : public Generator {
  /*!
    List of shared pointers of Generator class. The element can be
    a pointer of Element, GenDict or GenList class up-casted to
    a shared pointer of Generator class.
  */
  Vec<ShPtr<Generator>> generator_list;
 public:
  /*!
    @brief Constructor of GenList class.

    @param generator_list_
      List of shared pointers of Generator class.
      This parameter is assigned to #generator_list.

    This constructor is thread-unsafe because it accesses
    its members thread-globally. Ensure this constructor is
    not called in a multithreading context.
  */
  GenList(
    const Vec<ShPtr<Generator>> &generator_list_);
  virtual ~GenList() = default;
  /*!
    @brief Get an element of #generator_list as a shared pointer of
    Element class.

    @param name
      An index in #generator_list.

    @return An element of #generator_list up-casted to Element class.

    One needs to get an element of #generator_list as Element
    when using its Element::data.
  */
  virtual ElPtr get_element(
    const Json &name = nullptr) override;
  /*!
    @brief Get an element of #generator_list as a shared pointer of
    Generator class.

    @param name
      An index in #generator_list.

    @return An element of #generator_list.

    One needs to get an element of #generator_list as Generator
    when storing that object.
  */
  virtual ShPtr<Generator> get_generator(
    const Json &name = nullptr) override;
  //! @copydoc Generator::accessed_by_instance_of
  virtual void accessed_by_instance_of(
    const Str &classname) override;
  /*!
    @brief Get a length of #generator_list.

    @return An integer.
  */
  int get_length();
};

#endif
