/*!
  @file src/core/generator.h
  @brief This file has a definition of the Generator class, which is
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
  @brief \e UpdatePair is a pair of shared pointer of Element class and
  Updater class. The Updater object updates Element::data of the
  Element object (in other words, the Element object calls
  Element::update_data taking the Updater object as its argument).
  An UpdatePair object is created only in Element::append_updater.
*/
using UpdatePair = std::pair<ShPtr<Element>,ShPtr<Updater>>;

/*!
  @brief \e Generator is an abstract class to generate data.
  @details This class is a superclass of Element class. This class
  stores a chain (sequence) of ::UpdatePair objects which represents
  the process how Element::data will be generated and updated. By using
  subclasses, GenDict and GenList class, one can group Element objects
  in one Generator object and control all the updating process.
*/
class Generator {
 protected:
  /*!
    @brief Chain (sequence) of ::UpdatePair objects. It represents
    the process how the data is generated and updated.
    @details This chain of ::UpdatePair objects is executed one by
    one by the #hello. In this updating process, the Element objects
    (the first items of ::UpdatePair) uses the Updater objects (the
    second items of ::UpdatePair) to update the Element::data. An
    element of this sequence is added only in Element::append_updater.
  */
  Vec<UpdatePair> update_chain;
  /*!
    @brief Merge a given chain of ::UpdatePair objects to
    #update_chain.
    @param new_chain : A chain of ::UpdatePair objects to be merged.
    @return None.
    @details In merging a chain of ::UpdatePair objects, relative
    orders of the chain taken as \c new_chain and the #update_chain
    are retained so that dependency order of the updating process will
    not be broken. During the merging, duplication of ::UpdatePair
    objects will be removed. If there is no explicit preference,
    elements in the \c new_chain will be appended to the end of
    #update_chain. This method is thread-unsafe because it accesses the
    #update_chain thread-globally. Ensure this method is called
    (indirectly) from Python (via Element::append_updater) and not
    called in a multithreads context.
  */
  void merge_update_chain(
    const Vec<UpdatePair> &new_chain);
 public:
  Generator() = default;
  virtual ~Generator() = default;
  /*!
    @brief Get a shared pointer of Element class.
    @details This is a pure virtual function, please see the subclasses
    for more details.
  */
  virtual ShPtr<Element> get_element(
    const Json &name = nullptr) = 0;
  /*!
    @brief Get a shared pointer of Generator class.
    @details This is a pure virtual function, please see the subclasses
    for more details.
  */
  virtual ShPtr<Generator> get_generator(
    const Json &name = nullptr) = 0;
  /*!
    @brief Appoint to this object.
    @return None.
    @details Appointing means calling Element::increment_remain of all
    the Element objects contained in the #update_chain.
  */
  void appoint();
  /*!
    @brief Hello to this object.
    @return None.
    @details Greeting means calling Element::update_data for all
    the ::UpdatePair objects in the #update_chain, that is, executing
    the updating process associated with this object. By executing
    this method, Element::data in this Element object (or Element
    objects in this GenDict or GenList object) is set (filled with
    values).
  */
  void hello();
  /*!
    @brief Goodbye to this object.
    @return None.
    @details Saying goodbye means calling Element::decrement_remain of
    all the Element objects contained in the #update_chain.
  */
  void goodbye();
  /*!
    @brief Get the #update_chain of this object.
    @return Constance reference to ::Vec<#UpdatePair>.
    @details This method is mainly used in Element::append_updater to
    access #update_chain of Updater::ext_generator.
  */
  const Vec<UpdatePair> &get_update_chain();
};

#endif
