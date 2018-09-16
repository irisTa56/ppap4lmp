/*!
  @file src/core/element.h
  @brief This file has a definition of the Element class, which is
  one of the cores of this program.
  @author Takayuki Kobayashi
  @date 2018/07/01
*/

#ifndef ELEMENT_H
#define ELEMENT_H

#include <omp.h>

#include <alias/eigen.h>
#include <alias/pybind.h>
#include <core/generator.h>
#include <class/data_keys.h>

/*!
  @brief \e Element is a Generator containing data \e element (or
  entity, object).
  @details This class inherits Generator class and
  ::EnShThis<#Element>. Element class is different from the Generator
  class and its subclasses (except for this class) by owning data
  \e element (or entity, object). The data is stored as a ::Json
  instance, #data, and a set of the keys (or property names, attributes)
  of the data is stored as a DataKeys instance, #datakeys. This class
  can update its own data by calling #update_data where a mutable
  reference of #data is passed to an Updater instance.
*/
class Element : public Generator, public EnShThis<Element> {
  /*!
    @brief The number of created instances of Element class.
    @details This member is only used for setting #dataid.
  */
  static int instance_count;
  /*!
    @brief The number of times this instance will be used in the
    future.
    @details This member can be incremented by #increment_remain and
    decremented by #decrement_remain. If this member becomes 0 in
    #decrement_remain, the #data is cleared to save memory.
  */
  int n_remain = 0;
  /*!
    @brief Unique ID for an instance of Element class.
    @details This member is used to prevent duplication of updating
    process of the data. For more details, please see Updater class.
  */
  int dataid;
  /*!
    @brief Data \e element (or entity, object) itself.
    @details This member is an instance of ::Json, which is a very
    flexible data container consisting of hierarchically organized
    pairs of a string key and int/bool/double/string/array value. This
    can store data of Box, Atoms, Molecules, Beads, Cube ... and more!!
  */
  Json data;
  /*!
    @brief Set of keys (or property names, attributes) of the data.
    @details This member stores string keys the #data has. For more
    details, please see DataKeys class. Note that after updating the
    data, the set of keys must be manually updated (add/remove keys) in
    Updater or its subclasses.
  */
  DataKeys datakeys;
  /*!
    @brief A variable used for OpenMP.
    @details This member is used to update the #data exclusively in a
    multithread context. To prevent the #data from being updated from
    multiple threads at the same time, this member must be locked in
    the #update_data, #increment_remain and #decrement_remain.
  */
  omp_lock_t omp_lock;
  /*!
    @brief This method increments #n_remain.
    @return None.
    @details Please see #decrement_remain.
  */
  void increment_remain();
  /*!
    @brief This method decrements #n_remain.
    @return None.
    @details If one increments #n_remain of this instance before using
    the #data and then decrements it after using the #data, the #data
    is cleared to save memory. This system is convenient to access
    #data multiple times and save memory at the same time.
  */
  void decrement_remain();
  /*!
    @brief This method updates #data of this instance.
    @param upd : Shared pointer to an Updater instance updating the
    #data.
    @return None.
    @details This method updates the #data using an instance of Updater
    taken as \c upd. This instance and the Updater instance are paired
    as ::UpdatePair by #append_updater in advance. In this method, the
    #data, #datakeys and #dataid are passed to the Updater instance.
  */
  void update_data(
    const ShPtr<Updater> &upd);
  /*!
    @brief To use the #increment_remain, #decrement_remain and
    #update_data, Generator needs to be a friend class.
  */
  friend class Generator;
 public:
  /*!
    @brief Constructor of Element class.
    @details This constructor is thread-unsafe because it accesses its
    members thread-globally. Ensure this constructor is called
    (indirectly) from Python and not called in a multithreads context.
  */
  Element();
  virtual ~Element() = default;
  /*!
    @brief Get this instance as a shared pointer of Element class.
    @param name : ::Json (default is \c nullptr).
    @return Shared pointer of this Element instance.
    @details One needs to get as Element when accessing the data. The
    argument \c name must be left as default.
  */
  virtual ShPtr<Element> get_element(
    const Json &name = nullptr) override;
  /*!
    @brief Get this instance as a shared pointer of Generator class.
    @param name : ::Json (default is \c nullptr).
    @return Shared pointer of this Generator instance.
    @details One needs to get as Generator when storing the instance.
    The argument \c name must be left as default.
  */
  virtual ShPtr<Generator> get_generator(
    const Json &name = nullptr) override;
  /*!
    @brief Append an instance of Updater class to this instance. <b>Can
    be called from Python</b>.
    @param upd : Shared pointer to an Updater instance to be appended
    to this instance.
    @return Shared pointer of this Element instance.
    @details To update the data, one creates an instance of Updater
    class in Python and appends it to an instance of Element class.
    Generator::update_chain stored in Updater::ext_generator of the
    Updater instance, which is taken as \c upd, will be merged to
    Generator::update_chain of this instance; then the pair consisting
    of this instance and the Updater instance will be added to
    Generator::update_chain of this instance. Please also see Generator
    and Updater class.
  */
  ShPtr<Element> append_updater(
    const ShPtr<Updater> &upd);
  /*!
    @brief Get the reference to #data of this instance.
    @return Constant reference to ::Json.
    @details One can refer the whole data stored in this instance by
    this method.
  */
  const Json &get_data();
  /*!
    @brief Get the partial data of this instance.
    @param key_ : ::Json for either a key or an array of keys.
    @return ::Json (not a reference).
    @details One can get the partial data stored in this instance by
    this method. To select which data is included, specify a key or an
    array of keys as \c key_.
  */
  Json get_data(
    const Json &key_);
  /*!
    @brief Get keys of the data of this instance.
    @return Constant reference to DataKeys.
    @details One can get the keys (property names) in the data by this
    method.
  */
  const DataKeys &get_keys();
  /*!
    @brief Extract values in #data as an one-dimensional Eigen-Array.
    @param array : Mutable reference to ::ArrayXi or ::ArrayXd.
    @param key : A string key for values to be extracted.
    @return None.
    @details If one passed ::ArrayXi or ::ArrayXd as a reference, this
    method fills it by values of a property specified by \c key.
  */
  template <typename T>
  void array1d(
    T &array,
    const Str &key);
  /*!
    @brief Extract values in #data as a two-dimensional Eigen-Array.
    @param array : Mutable reference to ::ArrayXXi or ::ArrayXXd.
    @param keys : A vector of string keys for values to be extracted.
    values to be extracted.
    @return None.
    @details If one passed ::ArrayXXi or ::ArrayXXd as a reference,
    this method fills it by values of some properties specified by \c
    keys.
  */
  template <typename T>
  void array2d(
    T &array,
    const Vec<Str> &keys);
  /*!
    @brief Wrapper for DataKeys::required.
    @param key_ : ::Json for either a key or an array of keys.
    @return None.
    @details It is convenient that the method can be called without
    getting DataKeys instance from this Element instance. For more
    details, please see DataKeys class.
  */
  void required(
    const Json &key_);
  /*!
    @brief Wrapper for DataKeys::optional.
    @param key_ : ::Json for either a key or an array of keys.
    @return bool.
    @details It is convenient that the method can be called without
    getting DataKeys instance from this Element instance. For more
    details, please see DataKeys class.
  */
  bool optional(
    const Json &key_);
  /*!
    @brief Wrapper for the #get_data method which returns a reference.
    <b>Can be called from Python as \e get_data</b>.
    @return Constant reference to ::Json.
    @details This method provides a functionality to access the #data
    directly from Python. An updating process associated with this
    instance is executed before getting the data.
  */
  const Json &get_data_py();
  /*!
    @brief Wrapper for the #get_keys method. <b>Can be called from
    Python as \e get_keys</b>.
    @return Constant reference to ::Set<#Str>.
    @details This method provides a functionality to access #datakeys
    directly from Python. An updating process associated with this
    instance is executed before getting the set of keys.
  */
  const Set<Str> &get_keys_py();
  /*!
    @brief Wrapper for the #array1d method for integer values. <b>Can
    be called from Python as \e get_1d_int</b>.
    @param key : A string key specifying a property.
    @return ::ArrayXi (Numpy-Array in Python).
    @details This method provides a functionality to access the data of
    this instance directly from Python as an one-dimensional array. An
    updating process associated with this instance is executed before
    getting the data.
  */
  ArrayXi get_1d_int_py(
    const Str &key);
  /*!
    @brief Wrapper for the #array1d method for float (double in C++)
    values. <b>Can be called from Python as \e get_1d_float</b>.
    @param key : A string key specifying a property.
    @return ::ArrayXd (Numpy-Array in Python).
    @details This method provides a functionality to access the data of
    this instance directly from Python as an one-dimensional array. An
    updating process associated with this instance is executed before
    getting the data.
  */
  ArrayXd get_1d_float_py(
    const Str &key);
  /*!
    @brief Wrapper for the #array2d method for integer values. <b>Can
    be called from Python as \e get_2d_int</b>.
    @param args : An ordered list of keys specifying properties (*args
    in Python).
    @return ::ArrayXXi (Numpy-Array in Python).
    @details This method provides a functionality to access the data of
    this instance directly from Python as a two-dimensional array. An
    updating process associated with this instance is executed before
    getting the data.
  */
  ArrayXXi get_2d_int_py(
    const py::args &args);
  /*!
    @brief Wrapper for the #array2d method for float (double in C++)
    values. <b>Can be called from Python as \e get_2d_float</b>.
    @param args : An ordered list of keys specifying properties (*args
    in Python).
    @return ::ArrayXXd (Numpy-Array in Python).
    @details This method provides a functionality to access the data of
    this instance directly from Python as a two-dimensional array. An
    updating process associated with this instance is executed before
    getting the data.
  */
  ArrayXXd get_2d_float_py(
    const py::args &args);
 private:
  /*!
    @brief Routines to be conducted when a wrapper of getter is called
    from Python.
    @return None.
    @details This method runs updating process associated with this
    instance so that a wrapper of getter can access the filled data.
  */
  void init_for_python();
};

/*!
  @brief \e ElPtr is an alias for a shared pointer of Element.
*/
using ElPtr = ShPtr<Element>;

#endif
