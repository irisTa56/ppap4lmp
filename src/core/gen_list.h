/*!
  @file src/core/gen_list.h
  @brief This file has a definition of the GenList class.
  @author Takayuki Kobayashi
  @date 2018/07/03
*/

#ifndef GEN_LIST_H
#define GEN_LIST_H

#include <core/element.h>

/*!
  @brief \e GenList stands for Generator List (or vector).
  @details This class is a subclass of the Generator class and stores
  an arbitrary number of Generator object as a list (vector) of
  shared pointers.
*/
class GenList : public Generator {
  /*!
    @brief List of shared pointers of Generator. The core of GenList
    class.
    @details The element can be a pointer to Element up-casted to a
    shared pointer of Generator.
  */
  Vec<ShPtr<Generator>> generator_list;
 public:
  /*!
    @brief Constructor of GenList class.
    @param generator_list_ : A list of shared pointers to
    Generator object.
    @details The argument is stored to the #generator_list as it is.
    This constructor is thread-unsafe because it accesses its members
    thread-globally. Ensure this constructor is called (indirectly)
    from Python (such as constructors of Updater, Processor and their
    subclasses) and not called in a multithreads context.
  */
  GenList(
    const Vec<ShPtr<Generator>> &generator_list_);
  virtual ~GenList() = default;
  /*!
    @brief Get an element of #generator_list as a shared pointer of
    Element class.
    @param name : An index in the #generator_list.
    @return A value of the #generator_list up-casted to Element class.
    @details One needs to get as Element when accessing the data. The
    argument \c name must be an integer, which is an index of the
    #generator_list.
  */
  virtual ElPtr get_element(
    const Json &name = nullptr) override;
  /*!
    @brief Get an element of #generator_list as a shared pointer of
    Generator class.
    @param name : An index in the #generator_list.
    @return A value of the #generator_list.
    @details One needs to get as Generator when storing the object.
    The argument \c name must be an integer, which is an index of the
    #generator_list.
  */
  virtual ShPtr<Generator> get_generator(
    const Json &name = nullptr) override;
  /*!
    @brief Get the length of the #generator_list.
    @return Integer.
  */
  int get_length();
};

#endif
