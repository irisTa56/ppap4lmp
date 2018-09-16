/*!
  @file src/core/updater.h
  @brief This file has a definition of the Updater class, which is
  one of the cores of this program.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef UPDATER_H
#define UPDATER_H

#include <omp.h>

#include <core/generators.h>

/*!
  @brief \e Updater is an abstract class to update data held by
  Element class.
  @details This class is a superclass of the Starter, Adder and Filter
  class. An instance of this class is append to an Element instance by
  Element::append_updater and stored as ::UpdatePair (where the first
  item is the Element instance and the second item is the instance of
  this class). For more details about ::UpdatePair, please see the
  Generator class.
*/
class Updater {
  /*!
    @brief Set of Element::dataid updated by this Updater instance.
    @details If this Updater instance is called from an Element
    instance for the first time, this instance stores Element::dataid
    in the #dataid_blacklist and updates Element::data. From the second
    time on, this instance can skip the updating computation.
  */
  Set<int> dataid_blacklist;
  /*!
    @brief A variable used for OpenMP.
    @details This member is used to update the #dataid_blacklist
    exclusively in a multithread context. To prevent the
    #dataid_blacklist from being updated from multiple threads at the
    same time, this member must be locked in the #check_blacklist and
    #remove_from_blacklist.
  */
  omp_lock_t omp_lock;
 protected:
  /*!
    @brief Shared pointer to an instance of Generator class used in
    updating process. It is different from the Element instance to be
    updated.
    @details To compute some properties of the data, external instance
    of Generator (can be Element/GenDict/GenList) might be required.
    For example, to compute the center of mass of molecules, an Element
    instance holding the data of positions of atoms in the molecules is
    required.
  */
  ShPtr<Generator> ext_generator;
  /*!
    @brief Implementation of computation to update the data.
    @details This is a pure virtual function, please see the subclasses
    for more details.
  */
  virtual void compute_impl(Json &, DataKeys &) = 0;
  /*!
    @brief Look for Element::dataid in #dataid_blacklist.
    @param dataid : Element::dataid to be checked.
    @return Boolean.
    @details If \c dataid is found in #dataid_blacklist, this
    method returns false, that is, rejects the Element instance of
    the \c dataid.
  */
  bool check_blacklist(
    const int dataid);
 public:
  /*!
    @brief Constructor of Updater class.
    @details This constructor is thread-unsafe because it accesses its
    members thread-globally. Ensure this constructor is called
    (indirectly) from Python and not called in a multithreads context.
  */
  Updater();
  virtual ~Updater() = default;
  /*!
    @brief Managing computation to update the data.
    @details This is a pure virtual function, please see the subclasses
    for more details.
  */
  virtual void compute(Json &, DataKeys &, const int) = 0;
  /*!
    @brief Remove Element::dataid from #dataid_blacklist.
    @param dataid : Element::dataid to be removed.
    @return None.
    @details Removing \c dataid from #dataid_blacklist is necessary in
    case that this instance updates the Element instance of the
    \c dataid again after its data being cleared.
  */
  void remove_from_blacklist(
    const int dataid);
  /*!
    @brief Get the #ext_generator of this instance.
    @return Constance reference to ::ShPtr<#Generator>.
    @details This method is mainly used in Element::update_chain.
  */
  const ShPtr<Generator> &get_ext_generator();
};

#endif