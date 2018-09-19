/*!
  @file src/core/element.h
  @brief This file has a definition of Element class,
  which is one of the cores of this program.
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
  @brief Element is a Generator containing data \e element (or
  \e entity) as a ::Json object.
  @details This class inherits Generator class and ::EnShThis<#Element>.

  Element class is different from Generator, GenDict and GenList by
  owning data (or \e entity). The data is stored as a #data member,
  and a set of keys of properties in the data is stored
  as a #datakeys member. An object of this class can update its own
  #data and #datakeys by calling its #update_data where mutable
  references of #data and #datakeys are passed to an Updater object
  paired as ::UpdatePair.

  About usage in Python,
  please see src/pybind/py_element.h.
*/
class Element : public Generator, public EnShThis<Element> {
  /*!
    @brief The number of created objects (a.k.a. instances) of
    Element class.
    @details This member is only used for setting #dataid.
  */
  static int instance_count;
  /*!
    @brief The number of times this object will be used in the
    future.
    @details This member can be incremented by #increment_remain and
    decremented by #decrement_remain. If this member becomes 0 in
    #decrement_remain, the #data is cleared to save memory.
  */
  int n_remain = 0;
  /*!
    @brief Unique ID for an object of Element class.
    @details This member is used to prevent duplication of updating
    process of the #data. For more details, please see Updater class.
  */
  int dataid;
  /*!
    @brief Data \e element (or \e entity) itself.
    @details This member is an object of ::Json, which is a very
    flexible data container consisting of hierarchically organized
    items: pairs of a string key and int/bool/double/string/array value.
    Thanks to this flexibility, this class can store data for box,
    atoms, molecules, beads, cube, ... and more!!
  */
  Json data;
  /*!
    @brief Set of keys of the data.
    @details This member stores string keys the #data has. For more
    details, please see DataKeys class. Note that after updating the
    data, the set of keys must be manually updated (add/remove keys)
    in Updater or its subclasses.
  */
  DataKeys datakeys;
  /*!
    @brief A variable used by OpenMP.
    @details In this program, #data is updated in a multithread context.
    To prevent the #data from being updated from multiple threads
    at the same time, this member must be locked in the #update_data,
    #increment_remain and #decrement_remain.
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
    @details If one increments #n_remain of this object before using
    the #data and then decrements it after using it, the #data is
    cleared to save memory. This system is convenient to access #data
    multiple times while saving memory.
  */
  void decrement_remain();
  /*!
    @brief This method updates #data of this object.
    @param upd : Shared pointer to an Updater object updating the
    #data.
    @return None.
    @details This method updates the #data using an object of Updater
    taken as \c upd. This object and the Updater object are paired
    as ::UpdatePair by #append_updater in advance. In this method,
    mutable references of the #data and #datakeys are passed to
    Updater::compute of the Updater object. The #dataid is also passed
    to the Updater object.
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
    members thread-globally. Ensure this constructor is not called
    in a multithreads context.
  */
  Element();
  virtual ~Element() = default;
  /*!
    @brief Get this object as a shared pointer of Element class.
    @param name : ::Json (default is \c nullptr).
    @return Shared pointer to this Element object.
    @details One needs to get as Element when using this #data.
    The argument \c name must be left as default.
  */
  virtual ShPtr<Element> get_element(
    const Json &name = nullptr) override;
  /*!
    @brief Get this object as a shared pointer of Generator class.
    @param name : ::Json (default is \c nullptr).
    @return Shared pointer to this object up-casted to Generator.
    @details One needs to get as Generator when storing this object.
    The argument \c name must be left as default.
  */
  virtual ShPtr<Generator> get_generator(
    const Json &name = nullptr) override;
  /*!
    @brief Append an Updater object to this Element object.
    @param upd : Shared pointer to an Updater object.
    @return Shared pointer of this Element object.
    @details To update the data, one needs to create an Updater object
    and then appends it to an Element object using this method.
    In this method, Generator::update_chain stored in
    Updater::ext_generator of the \c upd is merged to
    Generator::update_chain of this object; then an ::UpdatePair
    consisting of this object and the \c upd is appended to
    Generator::update_chain of this object.
  */
  ShPtr<Element> append_updater(
    const ShPtr<Updater> &upd);
  /*!
    @brief Get the reference to #data of this object.
    @return Constant reference to ::Json.
    @details One can refer the whole data stored in this object
    by this method.
  */
  const Json &get_data();
  /*!
    @brief Get the partial data of this object.
    @param key_ : ::Json for either a key or an array of keys.
    @return ::Json (not a reference).
    @details One can get the partial data stored in this object by
    this method. To select which property is included in returned
    ::Json, pass a string key of the property as \c key_.
  */
  Json get_data(
    const Json &key_);
  /*!
    @brief Get keys of the data of this object.
    @return Constant reference to DataKeys.
    @details One can refer the keys (property names) in the data
    by this method.
  */
  const DataKeys &get_keys();
  /*!
    @brief Extract values of a property in #data as an one-dimensional
    Eigen-Array.
    @param array : Mutable reference to ::ArrayXi or ::ArrayXd.
    @param key : A string key of a property to be extracted.
    @return None.
    @details If one passed ::ArrayXi or ::ArrayXd as a reference, this
    method fills it by values of a property specified by \c key.
  */
  template <typename T>
  void array1d(
    T &array,
    const Str &key);
  /*!
    @brief Extract values of properties in #data as a two-dimensional
    Eigen-Array.
    @param array : Mutable reference to ::ArrayXXi or ::ArrayXXd.
    @param keys : A vector of string keys of properties to be extracted.
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
    @details It is convenient if DataKeys::required can be called
    without getting DataKeys object from this Element object. For more
    details, please see DataKeys class.
  */
  void required(
    const Json &key_);
  /*!
    @brief Wrapper for DataKeys::optional.
    @param key_ : ::Json for either a key or an array of keys.
    @return bool.
    @details It is convenient if DataKeys::optional can be called
    without getting DataKeys object from this Element object. For more
    details, please see DataKeys class.
  */
  bool optional(
    const Json &key_);
  /*!
    @brief Wrapper for the #get_data method, which returns a reference.
    @return Constant reference to ::Json.
    @details This method provides a functionality to access the #data
    directly from Python. An updating process associated with this
    object is executed before getting the data.
  */
  const Json &get_data_py();
  /*!
    @brief Wrapper for the #get_keys method.
    @return Constant reference to ::Set<#Str>.
    @details This method provides a functionality to access
    the #datakeys directly from Python. An updating process associated
    with this object is executed before getting the set of keys.
  */
  const Set<Str> &get_keys_py();
  /*!
    @brief Wrapper for the #array1d method for integer values.
    @param key : A string key specifying a property.
    @return ::ArrayXi (Numpy-Array in Python).
    @details This method provides a functionality to access values
    stored in the #data directly from Python as
    an one-dimensional array. An updating process associated with
    this object is executed before getting the array.
  */
  ArrayXi get_1d_int_py(
    const Str &key);
  /*!
    @brief Wrapper for the #array1d method for float (double in C++)
    values.
    @param key : A string key specifying a property.
    @return ::ArrayXd (Numpy-Array in Python).
    @details This method provides a functionality to access values
    stored in the #data directly from Python as
    an one-dimensional array. An updating process associated with
    this object is executed before getting the array.
  */
  ArrayXd get_1d_float_py(
    const Str &key);
  /*!
    @brief Wrapper for the #array2d method for integer values.
    @param args : An ordered list of keys specifying properties
    (\c *args in Python).
    @return ::ArrayXXi (Numpy-Array in Python).
    @details This method provides a functionality to access values
    stored in the #data directly from Python as a two-dimensional array.
    An updating process associated with this object is executed
    before getting the array.
  */
  ArrayXXi get_2d_int_py(
    const py::args &args);
  /*!
    @brief Wrapper for the #array2d method for float (double in C++)
    values.
    @param args : An ordered list of keys specifying properties
    (\c *args in Python).
    @return ::ArrayXXd (Numpy-Array in Python).
    @details This method provides a functionality to access values
    stored in the #data directly from Python as a two-dimensional array.
    An updating process associated with this object is executed
    before getting the array.
  */
  ArrayXXd get_2d_float_py(
    const py::args &args);
 private:
  /*!
    @brief Routines to be conducted when a wrapper of getter is called
    from Python.
    @return None.
    @details This method runs updating process associated with this
    object so that a wrapper of getter can access the filled #data.
  */
  void init_for_python();
};

//! \e ElPtr is an alias for a shared pointer of Element class.
using ElPtr = ShPtr<Element>;

#endif
