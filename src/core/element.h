/*!
  @file src/core/element.h
  @brief This file has a definition of the Element class, which is
  one of the cores of this program.
  @author Takayuki Kobayashi
  @date 2018/07/01
  @details \e Element stands for Generator containing data \e element,
  or data entity. Please see the class definition for more details.
*/

#ifndef ELEMENT_H
#define ELEMENT_H

#include <omp.h>

#include <alias/eigen.h>
#include <alias/pybind.h>
#include <core/generator.h>
#include <class/data_keys.h>

/*!
  @brief The Element class is one of the cores of this program.
  @details This class inherited from the Generator class and
  EnShThis<Element> (alias of std::enable_shared_from_this<Element>).
  The Element class is different from the Generator class and its
  subclasses other than this class by owning the data element (or data
  entity). The data is stored as a Json (nlohmann::json) instance in
  the \e data, and the set of attributes (or property names, keys) of
  the data is stored as a DataKeys instance in the \e datakeys. This
  class can update its own data by calling the \e update_data method
  where an editable reference of the \e data is passed to an Updater
  instance.
*/
class Element : public Generator, public EnShThis<Element> {
  /*!
    @brief The number of created instances of the Element class.
    @details This member is only used to set the \e dataid.
  */
  static int instance_count;
  /*!
    @brief The number of times this class will be used in the future.
    @details This member can be incremented by the \e increment_remain
    method and decremented by the \e decrement_remain method. If this
    member becomes 0 in the \e decrement_remain method, the \e data is
    cleared to save memory.
  */
  int n_remain = 0;
  /*!
    @brief Unique ID for an instance of the Element class.
    @details This member is used to prevent duplication of updating
    process of the data. For more details, please see the Updater
    class.
  */
  int dataid;
  /*!
    @brief Data element (or data entity)
    @details This member is an instance of Json (nlohmann::json), which
    is a very flexible data container consisting of hierarchically
    organized pairs of a string key and int/bool/double/string/array
    value. This can store data of Lammps' Box, Lammps' Atoms,
    Molecules, Beads, Gaussian's Cube ... and more!!
  */
  Json data;
  /*!
    @brief Set of attributes (or property names, keys) of the data.
    @details This member stores string keys the \e data has. Note that
    after updating the \e data, this member must be manually updated
    (add/remove keys) in Updater or its subclasses. For more details,
    please see the DataKeys class.
  */
  DataKeys datakeys;
  /*!
    @brief A variable used for OpenMP.
    @details This member used to update the data exclusively in a
    multithread. To prevent the data from being updated from multiple
    threads, this member must be locked in the \e update_data.
  */
  omp_lock_t omp_lock;
  /*!
    @brief This method increments the \e n_remain.
    @param None.
    @return None.
    @details Please see the \e decrement_remain method.
  */
  void increment_remain();
  /*!
    @brief This method decrements the \e n_remain.
    @param None.
    @return None.
    @details If one increments \e n_remain of an instance of this class
    before using the \e data of the instance and decrements it after
    using the \e data, the \e data is cleared. This system is
    convenient to access the \e data multiple times and, at the same
    time, save memory.
  */
  void decrement_remain();
  /*!
    @brief This method updates the \e data of the instance.
    @param const ShPtr<Updater> &upd.
    @return None.
    @details This method updates the \e data of the instance using an
    instance of the Updater class taking as the \e upd; passes the
    \e data, \e datakeys and \e data to the Updater instance.
  */
  void update_data(
    const ShPtr<Updater> &upd);
  /*!
    @brief To use the \e increment_remain, \e decrement_remain,
    \e update_data, Generator needs to be a friend class.
  */
  friend class Generator;
 public:
  /*!
    @brief Constructor of the Element class.
    @param None.
    @return Instance of the class.
    @details This constructor is thread-unsafe because it accesses its
    members thread-globally. Ensure this constructor is called from
    (via) Python and not called in a multithreads context.
  */
  Element();
  virtual ~Element() = default;
  /*!
    @brief Get this instance as a shared pointer of the Element class.
    @param const Json &name = nullptr.
    @return Shared pointer of this Element class.
    @details One needs get as the Element when accessing the data. The
    \e name must be left as default (Non-default argument is only
    required by other subclasses of the Generator).
  */
  virtual ShPtr<Element> get_element(
    const Json &name = nullptr) override;
  /*!
    @brief Get this instance as a shared pointer of the Generator class.
    @param const Json &name = nullptr.
    @return Shared pointer of this Generator class.
    @details One needs get as the Generator when storing the instance.
    The \e name must be left as default (Non-default argument is only
    required by other subclasses of the Generator).
  */
  virtual ShPtr<Generator> get_generator(
    const Json &name = nullptr) override;
  /*!
    @brief Append an instance of the Updater class to this instance.
    <b>Can be called from Python</b>.
    @param const ShPtr<Updater> &upd.
    @return Shared pointer of this Element class.
    @details To update the data, one creates an instance of the Updater
    class and appends it to an instance of the Element class.
    UpdatePair in \e update_chain stored in the external Generator in
    the Updater instance will be merged to the \e update_chain of this
    instance; then the pair consisting of this instance and the
    instance of the Updater token as the \e upd will be added to the
    \e update_chain of this instance. Please see also the Generator
    class and Updater class.
  */
  ShPtr<Element> append_updater(
    const ShPtr<Updater> &upd);
  /*!
    @brief Get the reference to data of this instance.
    @param None.
    @return Constant reference to Json.
    @details One can refer the whole data stored in this instance by
    this method.
  */
  const Json &get_data();
  /*!
    @brief Get the partial data of this instance.
    @param const Json &key_ (should be a string or an array of string).
    @return Json (not a reference).
    @details One can get the partial data stored in this instance by
    this method. To select which data is included, specify a key or an
    array of keys as the \e key_.
  */
  Json get_data(
    const Json &key_);
  /*!
    @brief Get keys of the data of this instance.
    @param None.
    @return Constant reference to DataKeys.
    @details One can get the keys (property names) in the data.
  */
  const DataKeys &get_keys();
  /*!
    @brief Extract the data as an one-dimensional Eigen-Array.
    @param T &array (T should be ArrayXi or ArrayXd).
    @param const Str &key.
    @return None.
    @details If one passed ArrayXi or ArrayXd as a reference, this
    method fills it by values of a property specified a key passed as
    the second \e key.
  */
  template <typename T>
  void array1d(
    T &array,
    const Str &key);
  /*!
    @brief Extract the data as a tow-dimensional Eigen-Array.
    @param T &array (T should be ArrayXXi or ArrayXXd).
    @param const Vec<Str> &keys.
    @return None.
    @details If one passed ArrayXXi or ArrayXXd as a reference, this
    method fills it by values of some properties specified a vector of
    keys passed as the second \e keys.
  */
  template <typename T>
  void array2d(
    T &array,
    const Vec<Str> &keys);
  /*!
    @brief Wrapper for \e required method of the DataKeys class.
    @param const Json &key_ (should be a string or an array of string).
    @return None.
    @details It is convenient that the method can be called without
    getting DataKeys' instance from this Element instance. For more
    details, please see the DataKeys class.
  */
  void required(
    const Json &key_);
  /*!
    @brief Wrapper for \e optional method of the DataKeys class.
    @param const Json &key_ (should be a string or an array of string).
    @return bool.
    @details It is convenient that the method can be called without
    getting DataKeys' instance from this Element instance. For more
    details, please see the DataKeys class.
  */
  bool optional(
    const Json &key_);
  /*!
    @brief Wrapper for the \e get_data method which returns a
    reference. <b>Can be called from Python</b> as \e get_data.
    @param None.
    @return Constance reference to Json.
    @details This method provides a functionality to access the data of
    this instance directly from Python. An updating process associated
    with this instance is executed before getting the data.
  */
  const Json &get_data_py();
  /*!
    @brief Wrapper for the \e get_keys method. <b>Can be called from
    Python</b> as \e get_keys.
    @param None.
    @return Constance reference to set of strings.
    @details This method provides a functionality to access the set of
    keys of the data of this instance directly from Python. An updating
    process associated with this instance is executed before getting
    the set of keys.
  */
  const Set<Str> &get_keys_py();
  /*!
    @brief Wrapper for the \e array1d method for integer values. <b>Can
    be called from Python</b> as \e get_1d_int.
    @param const Str &key.
    @return ArrayXi (Numpy-Array in Python).
    @details This method provides a functionality to access the data of
    this instance directly from Python as an one-dimensional array. An
    updating process associated with this instance is executed before
    getting the data.
  */
  ArrayXi get_1d_int_py(
    const Str &key);
  /*!
    @brief Wrapper for the \e array1d method for float (double in C++)
    values. <b>Can be called from Python</b> as \e get_1d_float.
    @param const Str &key.
    @return ArrayXd (Numpy-Array in Python).
    @details This method provides a functionality to access the data of
    this instance directly from Python as an one-dimensional array. An
    updating process associated with this instance is executed before
    getting the data.
  */
  ArrayXd get_1d_float_py(
    const Str &key);
  /*!
    @brief Wrapper for the \e array2d method for integer values. <b>Can
    be called from Python</b> as \e get_2d_int.
    @param const py::args &args (*args in Python).
    @return ArrayXXi (Numpy-Array in Python).
    @details This method provides a functionality to access the data of
    this instance directly from Python as a two-dimensional array. An
    updating process associated with this instance is executed before
    getting the data.
  */
  ArrayXXi get_2d_int_py(
    const py::args &args);
  /*!
    @brief Wrapper for the \e array2d method for float (double in C++)
    values. <b>Can be called from Python</b> as \e get_2d_float.
    @param const py::args &args (*args in Python).
    @return ArrayXXd (Numpy-Array in Python).
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
    @param None.
    @return None.
    @details This method runs updating process associated with this
    instance so that a wrapper of getter can access the filled data.
  */
  void init_for_python();
};

/*!
  @brief \e ElPtr is an alias for \e ShPtr<Element>.
*/
using ElPtr = ShPtr<Element>;

#endif
