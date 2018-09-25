/*!
  @file src/core/updater.h
  @brief This file has a definition of Updater class,
  which is one of the cores of this program.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef UPDATER_H
#define UPDATER_H

#include <omp.h>

#include <core/generators.h>

/*!
  @brief Updater is an abstract class to update data held by
  an Element object.
  @details This class is a superclass of the Starter, Adder and Filter
  class.

  An object of this class is append to an Element object by
  Element::append_updater and stored as ::UpdatePair (where the first
  item is the Element object and the second item is the object of
  this class).
*/
class Updater {
  /*!
    @brief Set of Element::dataid updated by this Updater object.
    @details If this Updater object is called from an Element
    object for the first time, this object stores Element::dataid in
    #dataid_blacklist and updates Element::data. From the second
    time on, this object can skip the updating computation.
  */
  Set<int> dataid_blacklist;
  /*!
    @brief A variable used for OpenMP.
    @details In this program, #dataid_blacklist is modified
    in a multithreading context. To prevent #dataid_blacklist
    from being modified from multiple threads at the same time,
    this member must be locked in #check_blacklist
    and #remove_from_blacklist.
  */
  omp_lock_t omp_lock;
 protected:
  /*!
    @brief Shared pointer to a Generator object used in update process.
    @details To compute some properties for an Element object where
    this object is appended to, an external Generator object (can be
    Element/GenDict/GenList) might be required. For example, to compute
    the center of mass of molecules for a molecular Element object,
    an atomic Element object containing positions of the atoms is
    required.
  */
  ShPtr<Generator> ext_generator;
  /*!
    @brief Implementation of computation to update Element::data.
    @param data : Mutable reference to Element::data
    where computed properties are added to.
    @param datakeys : Mutable reference to Element::datakeys
    where keys for computed properties are added to.
    @return None.
  */
  virtual void compute_impl(Json &, DataKeys &) = 0;
  /*!
    @brief Look for Element::dataid in #dataid_blacklist.
    @param dataid : Element::dataid to be checked.
    @return Boolean.
    @details If \c dataid is found in #dataid_blacklist, this
    method returns false, that is, rejects the Element object of
    the \c dataid.
  */
  bool check_blacklist(
    const int dataid);
 public:
  /*!
    @brief Constructor of Updater class.

    This constructor is thread-unsafe because it accesses
    its members thread-globally. Ensure this constructor is
    not called in a multithreading context. Please be careful
    that constructors of subclasses of this class are
    also thread-unsafe.
  */
  Updater();
  virtual ~Updater() = default;
  /*!
    @brief Managing computation to update Element::data.
    @param data : Mutable reference to Element::data where computed
    properties are added to.
    @param datakeys : Mutable reference to Element::datakeys where keys
    for computed properties are added to.
    @param dataid : Constant integer copied from Element::dataid.
    @return None.
    @details This is a pure virtual function, please see the subclasses
    for more details.
  */
  virtual void compute(Json &, DataKeys &, const int) = 0;
  /*!
    @brief Remove Element::dataid from #dataid_blacklist.
    @param dataid : Element::dataid to be removed.
    @return None.
    @details Removing \c dataid from #dataid_blacklist is necessary
    so that this object can update the Element object of the \c dataid
    again after its Element::data being cleared.
  */
  void remove_from_blacklist(
    const int dataid);
  /*!
    @brief Get #ext_generator of this object.
    @return Constance reference to ::ShPtr<#Generator>.
    @details This method is mainly used in Element::update_chain.
  */
  const ShPtr<Generator> &get_ext_generator();
};

#endif