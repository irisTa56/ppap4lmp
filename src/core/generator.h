/*!
  @file src/core/generator.h
  @brief This file has a definition of Generator class, which is
  one of the cores of this program.
  @author Takayuki Kobayashi
  @date 2018/06/21
*/

#ifndef GENERATOR_H
#define GENERATOR_H

#include <alias/std.h>
#include <alias/json.h>

class Element;
class Updater;

/*!
  @brief *UpdatePair* is a pair of shared pointer of Element class
  and Updater class.

  The Updater object updates Element::data of the Element object
  (in other words, the Element object calls Element::update_data
  taking the Updater object as its parameter).
  An UpdatePair object is created only in Element::append_updater.
*/
using UpdatePair = std::pair<ShPtr<Element>,ShPtr<Updater>>;

/*!
  @brief Generator is an abstract class to generate data.

  This class is a superclass of Element class.

  This class stores a chain (sequence) of ::UpdatePair objects
  which describes a process how Element::data will be generated
  and updated. In addition, by using GenDict and GenList class,
  which are subclasses of this class, one can group Element objects
  in one Generator object and control all updating processes
  associated with the Element objects.
*/
class Generator {
 protected:
  /*!
    Chain (sequence) of ::UpdatePair objects. It describes a process
    how Element::data is generated and updated. This chain of
    ::UpdatePair objects is executed one by one using #generate_data.
    In this updating process, the Element objects (the first items of
    ::UpdatePair) uses the Updater objects (the second items of
    ::UpdatePair) to update their Element::data.
    This member can be extended only in Element::append_updater.
  */
  Vec<UpdatePair> update_chain;
  /*!
    Merge a given chain of ::UpdatePair objects to #update_chain.

    @param new_chain
      List of ::UpdatePair objects to be merged.

    @return None.

    In merging a chain of ::UpdatePair objects, relative
    orders of ::UpdatePair objects in the `new_chain` and
    #update_chain are retained so that dependency order of
    the updating process will be preserved. During the merging,
    duplication of ::UpdatePair objects will be removed. If there is
    no explicit preference, elements in the `new_chain` will be
    appended to the end of #update_chain. This method is thread-unsafe
    because it accesses #update_chain thread-globally. Ensure this
    method is not called in a multithreading context.
  */
  void merge_update_chain(
    const Vec<UpdatePair> &new_chain);
 public:
  Generator() = default;
  virtual ~Generator() = default;
  //! Get a shared pointer of Element class.
  virtual ShPtr<Element> get_element(
    const Json &name = nullptr) = 0;
  //! Get a shared pointer of Generator class.
  virtual ShPtr<Generator> get_generator(
    const Json &name = nullptr) = 0;
  /*!
    @brief Set class name of an instance calling Element::required.

    @param classname
      A string to be assigned to Element::checking_classname.

    @return None.
  */
  virtual void accessed_by_instance_of(
    const Str &classname) = 0;
  /*!
    @brief Appoint to this Generator object.

    @return None.
  */
  void book_to_generate_data();
  /*!
    @brief Hello to this Generator object.

    @return None.

    This method calls Element::update_data for
    all the ::UpdatePair objects in #update_chain, that is,
    executing whole updating process associated with this object.
    By executing this method, Element::data in this Element object
    (or Element objects in this GenDict or GenList object) is ready
    to be used (filled with values).
  */
  void generate_data();
  /*!
    @brief Goodbye to this object.

    @return None.
  */
  void finish_using_generated_data();
  /*!
    @brief Get #update_chain of this object.

    @return Constant reference to ::Vec<#UpdatePair>.

    This method is mainly used in Element::append_updater to
    access #update_chain of Updater::ext_generator.
  */
  const Vec<UpdatePair> &get_update_chain();
};

#endif
