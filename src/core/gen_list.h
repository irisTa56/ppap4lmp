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
  @details This class is a subclass of Generator class and stores
  an arbitrary number of Generator object as a list (vector) of
  shared pointers of Generator class.
*/
class GenList : public Generator {
  /*!
    @brief List of shared pointers of Generator class.
    @details The element can be a pointer to Element up-casted to a
    shared pointer of Generator.
  */
  Vec<ShPtr<Generator>> generator_list;
 public:
  /*!
    @brief Constructor of GenList class.
    @param generator_list_ : List of shared pointers of
    Generator class.
    This parameter is assigned to #generator_list.
    @details This constructor is thread-unsafe because it accesses
    its members thread-globally. Ensure this constructor is not called
    in a multithreading context.
  */
  GenList(
    const Vec<ShPtr<Generator>> &generator_list_);
  virtual ~GenList() = default;
  /*!
    @brief Get an element of #generator_list as a shared pointer of
    Element class.
    @param name : An index in #generator_list.
    @return An element of #generator_list up-casted to
    Element class.
    @details One needs to get an element of #generator_list as Element
    when using its Element::data.
    The argument \c name must be an integer, which is an index in the
    #generator_list.
  */
  virtual ElPtr get_element(
    const Json &name = nullptr) override;
  /*!
    @brief Get an element of #generator_list as a shared pointer of
    Generator class.
    @param name : An index in #generator_list.
    @return An element of #generator_list.
    @details One needs to get an element of #generator_list as Generator
    when storing that object.
    The argument \c name must be an integer, which is an index of the
    #generator_list.
  */
  virtual ShPtr<Generator> get_generator(
    const Json &name = nullptr) override;
  /*!
    @brief Get a length of #generator_list.
    @return Integer.
  */
  int get_length();
};

#endif
