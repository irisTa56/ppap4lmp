/*!
  @file src/core/gen_dict.h
  @brief This file has a definition of the GenDict class.
  @author Takayuki Kobayashi
  @date 2018/07/03
*/

#ifndef GEN_DICT_H
#define GEN_DICT_H

#include <core/element.h>

/*!
  @brief \e GenDict stands for Generator Dictionary (or map).
  @details This class is a subclass of the Generator class and stores
  an arbitrary number of Generator instance as a dictionary (map) of
  shared pointers.
*/
class GenDict : public Generator {
  /*!
    @brief Dictionary of shared pointers of Generator (keys are strings
    and values are shared pointers). The core of the GenDict class.
    @details The values can be a pointer to Element up-casted to a
    shared pointer of Generator.
  */
  Map<Str,ShPtr<Generator>> generator_dict;
 public:
  /*!
    @brief Constructor of GenDict class.
    @param generator_dict_ : A dictionary of shared pointers to
    Generator instance.
    @details The argument is stored to the #generator_dict as it is.
    This constructor is thread-unsafe because it accesses its members
    thread-globally. Ensure this constructor is called (indirectly)
    from Python (such as constructors of Updater, Processor and their
    subclasses) and not called in a multithreads context.
  */
  GenDict(
    const Map<Str,ShPtr<Generator>> &generator_dict_);
  virtual ~GenDict() = default;
  /*!
    @brief Get a value of #generator_dict as a shared pointer of
    Element class.
    @param name : A string key in the #generator_dict.
    @return A value of the #generator_dict up-casted to Element class.
    @details One needs to get as Element when accessing the data. The
    argument \c name must be a string, which is a key for the value in
    #generator_dict.
  */
  virtual ElPtr get_element(
    const Json &name = nullptr) override;
  /*!
    @brief Get a value of #generator_dict as a shared pointer of
    Generator class.
    @param name : A string key in the #generator_dict.
    @return A value of the #generator_dict.
    @details One needs to get as Generator when storing the instance.
    The argument \c name must be a string, which is a key for the value
    in #generator_dict.
  */
  virtual ShPtr<Generator> get_generator(
    const Json &name = nullptr) override;
  /*!
    @brief Get a set of the keys in the #generator_list.
    @return Set of strings.
  */
  Set<Str> get_keys();
};

#endif
