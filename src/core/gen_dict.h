/*!
  @file src/core/gen_dict.h
  @brief This file has a definition of the GenDict class.
  @author Takayuki Kobayashi
  @date 2018/07/03
  @details \e GenDict stands for Generator Dictionary (or map).
*/

#ifndef GEN_DICT_H
#define GEN_DICT_H

#include <core/element.h>

/*!
  @brief The GenDict class is a subclass of the Generator class.
  @details This class can stores an arbitrary number of Generator
  instance as a dictionary (map) of shared pointers.
*/
class GenDict : public Generator {
  /*!
    @brief Dictionary of shared pointers of Generator: keys are strings
    and values are shared pointers. The core of the GenDict class.
    @details The values can be a pointer to Element up-casted to a
    shared pointer of Generator.
  */
  Map<Str,ShPtr<Generator>> generator_dict;
 public:
  /*!
    @brief Constructor of the GenDict class.
    @param const Map<Str,ShPtr<Generator>> &generator_dict_.
    @return Instance of the class.
    @details The argument is stored to the \e generator_dict as it is.
    This constructor is thread-unsafe because it accesses its members
    thread-globally. Ensure this constructor is called from (via)
    Python (such as constructors of Updater, Processor and their
    subclasses) and not called in a multithreads context.
  */
  GenDict(
    const Map<Str,ShPtr<Generator>> &generator_dict_);
  virtual ~GenDict() = default;
  /*!
    @brief Get a value of \e generator_dict as a shared pointer of
    the Element class.
    @param const Json &name = nullptr.
    @return Shared pointer to a value of the \e generator_dict.
    @details One needs get as the Element when accessing the data. The
    \e name must be a string, that is a key for the value in
    \e generator_dict.
  */
  virtual ElPtr get_element(
    const Json &name = nullptr) override;
  /*!
    @brief Get a value of \e generator_dict as a shared pointer of
    the Generator class.
    @param const Json &name = nullptr.
    @return Shared pointer to a value of the \e generator_dict.
    @details One needs get as the Generator when storing the instance.
    The \e name must be a string, that is a key for the value in
    \e generator_dict.
  */
  virtual ShPtr<Generator> get_generator(
    const Json &name = nullptr) override;
  /*!
    @brief Get a set of the keys of the \e generator_list.
    @param None.
    @return Set of strings.
  */
  Set<Str> get_keys();
};

#endif
