/*!
  @file src/core/element.cpp
  @brief This file has an implementation of Element class,
  which is one of the cores of this program.
  @author Takayuki Kobayashi
  @date 2018/07/01
*/

#include "element.h"
#include "updater.h"
#include "../utils/message.h"
#include "../utils/pyargs_to_vec.h"
#include "../utils/runtime_error.h"

namespace ut = utils;

int Element::instance_count = 0;

/* ------------------------------------------------------------------ */

Element::Element()
{
  instance_count++;
  dataid = instance_count;
  omp_init_lock(&omp_lock);
}

/* ------------------------------------------------------------------ */

void Element::increment_remain()
{
  #pragma omp atomic
  n_remain++;
}

/* ------------------------------------------------------------------ */

void Element::decrement_remain()
{
  omp_set_lock(&omp_lock);

  n_remain--;

  if (n_remain == 0)
  {
    if (data.is_array())
    {
      data.get_ref<Json::array_t&>().clear();
      data.get_ref<Json::array_t&>().shrink_to_fit();
      data = nullptr;
    }
    else
    {
      data.clear();
      data = nullptr;
    }

    datakeys.clear();

    auto shared_this = shared_from_this();

    for (const auto &item : update_chain)
    {
      if (item.first == shared_this)
      {
        item.second->remove_from_blacklist(dataid);
      }
    }

    ut::log("Data-" + std::to_string(dataid) + " has been deleted");
  }
  else if (n_remain < 0)
  {
    ut::runtime_error(
      "Data-" + std::to_string(dataid) + " was used illegally");
  }

  omp_unset_lock(&omp_lock);
}

/* ------------------------------------------------------------------ */

void Element::update_data(
  const ShPtr<Updater> &upd)
{
  omp_set_lock(&omp_lock);

  upd->compute(data, datakeys, dataid);

  omp_unset_lock(&omp_lock);
}

/* ------------------------------------------------------------------ */

ElPtr Element::get_element(
  const Json &name)
{
  if (name != nullptr)
  {
    ut::runtime_error("Rejection of non-null Json");
  }

  return shared_from_this();
}

/* ------------------------------------------------------------------ */

ShPtr<Generator> Element::get_generator(
  const Json &name)
{
  if (name != nullptr)
  {
    ut::runtime_error("Rejection of non-null Json");
  }

  return shared_from_this();
}

/* ------------------------------------------------------------------ */

void Element::set_checking_classname(
  const Str &classname)
{
  datakeys.set_checking_classname(classname);
}

/* ------------------------------------------------------------------ */

void Element::unset_checking_classname()
{
  datakeys.unset_checking_classname();
}

/* ------------------------------------------------------------------ */

ElPtr Element::append_updater(
  const ShPtr<Updater> &upd)
{
  auto gen = upd->get_ext_generator();

  if (gen)
  {
    merge_update_chain(gen->get_update_chain());
  }

  update_chain.push_back(UpdatePair(shared_from_this(), upd));

  return shared_from_this();
}

/* ------------------------------------------------------------------ */

Json Element::get_data(const Json &key_)
{
  Vec<Str> keys = key_.is_array() ? key_ : Json::array({key_});

  Json tmp;

  if (data.is_array())
  {
    tmp = Json::array();
    tmp.get_ref<Json::array_t&>().reserve(data.size());

    for (const auto &d : data)
    {
      tmp.push_back({});
      auto &elem = tmp.back();

      for (const auto &key : keys)
      {
        elem[key] = d[key];
      }
    }
  }
  else
  {
    for (const auto &key : keys)
    {
      tmp[key] = data[key];
    }
  }

  return tmp;
}

/* ------------------------------------------------------------------ */

const Json &Element::get_data()
{
  return data;
}

/* ------------------------------------------------------------------ */

const DataKeys &Element::get_keys()
{
  return datakeys;
}

/* ------------------------------------------------------------------ */

template <typename T>
void Element::array1d(
  T &array,
  const Str &key)
{
  array.resize(data.is_array() ? data.size() : 1);

  if (data.is_array())
  {
    int index = 0;

    for (const auto &d : data)
    {
      array(index++) = d[key];
    }
  }
  else
  {
    array(0) = data[key];
  }
}

/* ------------------------------------------------------------------ */

template <typename T>
void Element::array2d(
  T &array,
  const Vec<Str> &keys)
{
  array.resize(data.is_array() ? data.size() : 1, keys.size());

  if (data.is_array())
  {
    int irow = 0;

    for (const auto &d : data)
    {
      int icol = 0;

      for (const auto &key : keys)
      {
        array(irow, icol++) = d[key];
      }

      irow++;
    }
  }
  else
  {
    int icol = 0;

    for (const auto &key : keys)
    {
      array(0, icol++) = data[key];
    }
  }
}

/* wrappers for DataKeys' methods ----------------------------------- */

void Element::required(
  const Json &key_)
{
  datakeys.required(key_);
}

/* ------------------------------------------------------------------ */

bool Element::optional(
  const Json &key_)
{
  return datakeys.optional(key_);
}

/* functions for Python --------------------------------------------- */

const Json &Element::get_data_py()
{
  init_for_python();

  return data;
}

/* ------------------------------------------------------------------ */

const Set<Str> &Element::get_keys_py()
{
  init_for_python();

  return datakeys.get();
}

/* ------------------------------------------------------------------ */

ArrayXi Element::get_1d_int_py(
  const Str &key)
{
  init_for_python();

  required(key);

  ArrayXi array;
  array1d(array, key);

  return array;
}

/* ------------------------------------------------------------------ */

ArrayXd Element::get_1d_float_py(
  const Str &key)
{
  init_for_python();

  required(key);

  ArrayXd array;
  array1d(array, key);

  return array;
}

/* ------------------------------------------------------------------ */

ArrayXXi Element::get_2d_int_py(
  const py::args &args)
{
  init_for_python();

  Vec<Str> keys;
  ut::pyargs_to_vec(args, keys);

  required(keys);

  ArrayXXi array;
  array2d(array, keys);

  return array;
}

/* ------------------------------------------------------------------ */

ArrayXXd Element::get_2d_float_py(
  const py::args &args)
{
  init_for_python();

  Vec<Str> keys;
  ut::pyargs_to_vec(args, keys);

  required(keys);

  ArrayXXd array;
  array2d(array, keys);

  return array;
}

/* ------------------------------------------------------------------ */

void Element::init_for_python()
{
  try
  {
    hello();
  }
  catch (std::runtime_error &e)
  {
    ut::log("ERROR - " + Str(e.what()));
  }
}

/* ------------------------------------------------------------------ */
