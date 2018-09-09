/*!
  @file src/core/generator.h
  @brief This file has a definition of the Generator class, which is
  one of the cores of this program.
  @author Takayuki Kobayashi
  @date 2018/06/21
  @details \e Generator is an abstract class to generate data.
*/

#ifndef GENERATOR_H
#define GENERATOR_H

#include <alias/std.h>
#include <alias/json.h>

class Element;
class Updater;

/*!
  @brief \e UpdatePair is a pair of shared pointer of the Element class
  and the Updater class. The Updater instance updates \e data of the
  Element instance (in other words, the Element instance calls its
  \e update_data method taking the Updater instance as its argument).
  This is created in \e append_updater method of the Element class.
*/
using UpdatePair = std::pair<ShPtr<Element>,ShPtr<Updater>>;

/*!
  @brief The Generator class is one of the cores of this program.
  @details This class is superclass of the Element class and stores
  a sequence of UpdatePairs which represents the process how the data
  is generated. By using subclasses (the GenDict and GenList class),
  one can group the Element instances in one Generator and control all
  the updating process.
*/
class Generator {
 protected:
  /*!
    @brief Sequence of UpdatePairs. It represents the process how the
    data is updated (filled by keys and values).
    @details This sequence of UpdatePairs is executed one by one in the
    \e hello method. In this updating process, the Element instances
    (the first element of UpdatePair) uses the Updater instances (the
    second element of UpdatePair) to update its \e data. An element of
    this sequence is added in \e append_updater method of the Element
    class. In that method, \e update_chain stored in the external
    Generator in the Updater instance will be merged to the
    \e update_chain of this instance.
  */
  Vec<UpdatePair> update_chain;
  /*!
    @brief Merge a sequence of UpdatePairs to \e update_chain of this
    instance.
    @param const Vec<UpdatePair> &new_chain).
    @return None.
    @details In merging a sequence of UpdatePairs, relative orders of
    the sequence passed by the \e new_chain and the \e update_chain are
    retained so that dependency order of the updating process will not
    be broken. Duplication of UpdatePair will be removed. If there is
    no explicit preference, elements in the \e new_chain will be
    appended to the end of \e update_chain. This method is
    thread-unsafe because it accesses the \e update_chain
    thread-globally. Ensure this method is called from (via) Python
    (such as \e append_updater of the Element class) and not called in
    a multithreads context.
  */
  void merge_update_chain(
    const Vec<UpdatePair> &new_chain);
 public:
  Generator() = default;
  virtual ~Generator() = default;
  /*!
    @brief Get a shared pointer of the Element class.
    @details This is pure virtual function, please see the subclasses
    for more details.
  */
  virtual ShPtr<Element> get_element(
    const Json &name = nullptr) = 0;
  /*!
    @brief Get a shared pointer of the Generator class.
    @details This is pure virtual function, please see the subclasses
    for more details.
  */
  virtual ShPtr<Generator> get_generator(
    const Json &name = nullptr) = 0;
  /*!
    @brief Appoint to this Generator instance.
    @param None.
    @return None.
    @details Appointing is calling \e increment_remain method of all
    the Element instances contained in the \e update_chain.
  */
  void appoint();
  /*!
    @brief Hello to this Generator instance.
    @param None.
    @return None.
    @details Greeting is calling \e update_data method for all the
    UpdatePairs in the \e update_chain, that is, executing the update
    process. By executing this method, \e data in this Element instance
    (or Element instances in this GenDict or GenList instance) is set.
  */
  void hello();
  /*!
    @brief Goodbye to this Generator instance.
    @param None.
    @return None.
    @details Saying goodbye is calling \e decrement_remain method of
    all the Element instances contained in the \e update_chain.
  */
  void goodbye();
  /*!
    @brief Get the \e update_chain of this instance.
    @param None.
    @return Constance reference to Vec<UpdatePair>.
    @details This method is mainly used to access \e update_chain of
    external Generator instance of the Updater class.
  */
  const Vec<UpdatePair> &get_update_chain();
};

#endif
