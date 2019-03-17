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

/*!
  @brief Element inherits Generator class and contains data *element*
  (or *entity*) as a ::Json object.

  This class inherits Generator class and ::EnShThis<#Element>.

  Element class is different from Generator, GenDict and GenList by
  owning data *element* (or *entity*). The data is stored as #data,
  and a set of keys for properties in the data is stored as #datakeys.
  Note that #data can be either an array ::Json object or
  a non-array ::Json object. A non-array ::Json object consists of
  items: pairs of a string key and int/bool/double/string/array value.
  The key represents a property name. For array #data, it contains
  non-array ::Json objects. Each non-array ::Json object should have
  the same set of keys; this set is the one stored as #datakeys.

  An object of this class can update itself by calling its #update_data
  where a shared pointer of this object is passed to an Updater object
  paired as ::UpdatePair.

  About usage in Python,
  please see pybind::py_element.
*/
class Element : public Generator, public EnShThis<Element> {
  /*!
    The number of created objects (a.k.a. instances) of Element class.
    This member is only used for setting #dataid.
  */
  static int instance_count;
  /*!
    The number of times this object will be used in the future.
    This member can be incremented by #increment_remain and
    decremented by #decrement_remain. If this member becomes 0 in
    #decrement_remain, #data is cleared to save memory.
  */
  int n_remain = 0;
  /*!
    Unique ID for an object of Element class. This member is used
    for preventing duplication of updating process of #data.
    For more details, please see Updater class.
  */
  int dataid;
  /*!
    Data *element* (or *entity*) itself. This member is
    a ::Json object, which is a very flexible data container
    consisting of hierarchically organized items: pairs of a string key
    and int/bool/double/string/array value.
    Thanks to this flexibility, this class can store data for box,
    atoms, molecules, beads, cube, ... and more!!
  */
  Json data;
  /*!
    List of keys of the data.
    This member stores string keys which #data has.
  */
  Vec<Str> datakeys;
  /*!
    Name of a class of instance calling #required_keys.
    Showing the class name in an error message raised by #required_keys
    helps debugging.
  */
  Str checking_classname;
  /*!
    A variable used by OpenMP. In this program, #data is updated
    in a multithreading context. To prevent the #data from being
    updated from multiple threads at the same time, this member must be
    locked in #update_data, #increment_remain and #decrement_remain.
  */
  omp_lock_t omp_lock;
  /*!
    This method increments #n_remain.

    @return None.

    If one increments #n_remain of this object before using
    #data and then decrements it after using it, the #data is
    cleared to save memory. This system is convenient to access #data
    multiple times while saving memory.
  */
  void increment_remain();
  /*!
    This method decrements #n_remain.

    @return None.

    If one increments #n_remain of this object before using #data
    and then decrements it after using it, the #data is cleared
    to save memory. This system is convenient to access #data
    multiple times while saving memory.
  */
  void decrement_remain();
  /*!
    This method updates #data of this object.

    @param upd
      Shared pointer to an Updater object updating the #data.

    @return None.

    This method updates #data using an object of Updater
    taken as `upd`. This object and the Updater object are paired
    as ::UpdatePair by #append_updater in advance. In this method,
    a shared pointer of this object is passed to Updater::compute
    of the Updater object.
  */
  void update_data(
    const ShPtr<Updater> &upd);
  /*!
    @brief For speeding up to access values in ::Json.

    @return List of pairs: key and distance from the previous item
    (distance from the beginning for the first item).

    For more details about usage, please see #get_json or #array2d.
  */
  Vec<std::pair<Str,int>> get_key_advances(
    const Json &key_);
  //! To use #increment_remain, #decrement_remain and #update_data.
  friend class Generator;
 public:
  /*!
    @brief Constructor of Element class.

    This constructor is thread-unsafe because it accesses its
    members thread-globally. Ensure this constructor is not called
    in a multithreading context.
  */
  Element();
  virtual ~Element() = default;
  /*!
    @brief Get this object as a shared pointer of Element class.

    @param name
      Leave it as it is (default is `nullptr`).

    @return Shared pointer to this Element object.

    One needs to get as Element when using this #data.
  */
  virtual ShPtr<Element> get_element(
    const Json &name = nullptr) override;
  /*!
    @brief Get this object as a shared pointer of Generator class.

    @param name
      Leave it as it is (default is `nullptr`).

    @return Shared pointer to this object up-casted to Generator.

    One needs to get as Generator when storing this object.
  */
  virtual ShPtr<Generator> get_generator(
    const Json &name = nullptr) override;
  //! @copydoc Generator::talk_with
  virtual void talk_with(
    const Str &classname) override;
  /*!
    @brief Append an Updater object to this Element object:
    the only way to extend an updating process
    associated with this object.

    @param upd
      An Adder or Filter object to be paired with this Element object
      as an ::UpdatePair object, which is appended to
      a sequence of ::UpdatePair objects
      describing the updating process of this object.

    @return This Element object.

    <span class="remove_in_table">
      To update the data, one needs to create an Updater object
      and then appends it to an Element object using this method.
      In this method, Generator::update_chain stored in
      Updater::ext_generator of the `upd` is merged to
      Generator::update_chain of this object; then an ::UpdatePair
      consisting of this object and the `upd` is appended to
      Generator::update_chain of this object.
    </span>
  */
  ShPtr<Element> append_updater(
    const ShPtr<Updater> &upd);
  /*!
    @brief Get the reference to #data of this object.

    @return Constant reference to this Element::data.

    One can refer the whole data stored in this object
    by this method.
  */
  const Json &get_data();
  /*!
    @brief Get the partial data of this object.

    @param key_
      A ::Json object for either a key or an array of keys.

    @return A ::Json object (not a reference).

    One can get the partial data stored in this object by this method.
    To select which property is included in the returned ::Json object,
    pass a string key for the property as `key_`.

    @note
      If you'd like to modify (sorting etc.) contents of #data,
      please use this method insted of #get_data.
  */
  Json get_json(
    const Json &key_);
  /*!
    @brief Get keys of the data of this object.

    @return Set of keys stored in #datakeys.

    One can refer the keys (property names) in this object
    by this method.
  */
  Set<Str> get_keys();
  /*!
    @brief Extract values of a property in #data as a one-dimensional
    Eigen-Array.

    @param array
      Mutable reference to ::ArrayXi or ::ArrayXd.

    @param key
      A string key for a property to be extracted.

    @return None.

    If one passed ::ArrayXi or ::ArrayXd as a reference, this method
    fills it by values of a property specified by `key`.
  */
  template <typename T>
  void array1d(
    T &array,
    const Str &key);
  /*!
    @brief Extract values of properties in #data as a two-dimensional
    Eigen-Array.

    @param array
      Mutable reference to ::ArrayXXi or ::ArrayXXd.

    @param keys
      List of string keys for properties to be extracted.

    @return None.

    If one passed ::ArrayXXi or ::ArrayXXd as a reference, this method
    fills it by values of some properties specified by `keys`.
  */
  template <typename T>
  void array2d(
    T &array,
    const Vec<Str> &keys);
  /*!
    @brief Update #datakeys.
    This method must be called after setting new properties to #data.

    @return None.

    If #data is an array,
    only the first element is used for investigating keys.
  */
  void update_keys();
  /*!
    @brief Check if this object has required key(s).

    @param key_
      A ::Json object for either a key or an array of keys
      for required property.

    @return None.

    If this object does not have the given required key(s),
    a runtime error is thrown in C++ (and also raised in Python).
  */
  void required_keys(
    const Json &key_);
  /*!
    @brief Check if this object has optional key(s).

    @param key_
      A ::Json object for either a key or an array of keys
      for optional property.

    @return A boolean.

    If this object has the given key(s), it returns true. If
    not, it returns false.
  */
  bool optional_keys(
    const Json &key_);
  //! @copydoc Element::get_data
  const Json &get_data_py();
  //! @copydoc Element::get_keys
  Set<Str> get_keys_py();
  /*!
    @brief Get integer values stored in Element::data of this object
    as a one-dimensional Numpy-Array.

    @param key
      A string key specifying a property.

    @return ::ArrayXi (Numpy-Array in Python).
  */
  ArrayXi get_1d_int_py(
    const Str &key);
  /*!
    @brief Get float values stored in Element::data of this object
    as a one-dimensional Numpy-Array.

    @param key
      A string key specifying a property.

    @return ::ArrayXd (Numpy-Array in Python).
  */
  ArrayXd get_1d_float_py(
    const Str &key);
  /*!
    @brief Get integer values stored in Element::data of this object
    as a two-dimensional Numpy-Array.

    @param *args
      An ordered list of keys specifying properties
      (Python's variable number arguments).

    @return ::ArrayXXi (Numpy-Array in Python).
  */
  ArrayXXi get_2d_int_py(
    const py::args &args);
  /*!
    @brief Get float values stored in Element::data of this object
    as a two-dimensional Numpy-Array.

    @param *args
      An ordered list of keys specifying properties
      (Python's variable number arguments).

    @return ::ArrayXXd (Numpy-Array in Python).
  */
  ArrayXXd get_2d_float_py(
    const py::args &args);
 private:
  /*!
    Routines to be conducted
    when a wrapper of getter is called from Python.

    @return None.

    This method runs updating process associated with this
    object so that a wrapper of getter can access the filled #data.
  */
  void init_for_python();
};

//! *ElPtr* is an alias for a shared pointer of Element class.
using ElPtr = ShPtr<Element>;

#endif
