/*!
  @file src/core/gen_list.h
  @brief This file has a definition of the GenList class.
  @author Takayuki Kobayashi
  @date 2018/07/03
  @details \e GenList stands for Generator List (or vector).
*/

#ifndef GEN_LIST_H
#define GEN_LIST_H

#include <core/element.h>

/*!
  @brief The GenList class is a subclass of the Generator class.
  @details This class can stores an arbitrary number of Generator
  instance as a list (vector) of shared pointers.
*/
class GenList : public Generator {
  /*!
    @brief List of shared pointers of Generator. The core of the
    GenList class.
    @details The element can be a pointer to Element up-casted to a
    shared pointer of Generator.
  */
  Vec<ShPtr<Generator>> generator_list;
 public:
  /*!
    @brief Constructor of the GenList class.
    @param const Vec<ShPtr<Generator>> &generator_list_.
    @return Instance of the class.
    @details The argument is stored to the \e generator_list as it is.
    This constructor is thread-unsafe because it accesses its members
    thread-globally. Ensure this constructor is called from (via)
    Python (such as constructors of Updater, Processor and their
    subclasses) and not called in a multithreads context.
  */
  GenList(
    const Vec<ShPtr<Generator>> &generator_list_);
  virtual ~GenList() = default;
  /*!
    @brief Get an element of \e generator_list as a shared pointer of
    the Element class.
    @param const Json &name = nullptr.
    @return Shared pointer to an element of the \e generator_list.
    @details One needs get as the Element when accessing the data. The
    \e name must be an integer, that is an index of the
    \e generator_list.
  */
  virtual ElPtr get_element(
    const Json &name = nullptr) override;
  /*!
    @brief Get an element of \e generator_list as a shared pointer of
    the Generator class.
    @param const Json &name = nullptr.
    @return Shared pointer to an element of the \e generator_list.
    @details One needs get as the Generator when storing the instance.
    The \e name must be an integer, that is an index of the
    \e generator_list.
  */
  virtual ShPtr<Generator> get_generator(
    const Json &name = nullptr) override;
  /*!
    @brief Get the length of the \e generator_list.
    @param None.
    @return Integer.
  */
  int get_length();
};

#endif
