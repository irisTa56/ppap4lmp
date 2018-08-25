/* ---------------------------------------------------------------------
GenElement: stands for Generator containing data 'element'.

create: 2018/07/01 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "gen_element.h"
#include "utils.h"

int GenElement::instance_count = 0;

/* ------------------------------------------------------------------ */
// assumed to be not called from multithreads
GenElement::GenElement()
{
  instance_count++;
  ID = instance_count;
  omp_init_lock(&omp_lock);
}

/* ------------------------------------------------------------------ */

ShPtr<GenElement> GenElement::get_element(
  Json name)
{
  if (name != nullptr)
  {
    runtime_error("GenElement::get_element accepts no argument");
  }

  return shared_from_this();
}

/* ------------------------------------------------------------------ */

ShPtr<Generator> GenElement::get_generator(
  Json name)
{
  if (name != nullptr)
  {
    runtime_error("GenElement::get_generator accepts no argument");
  }

  return shared_from_this();
}

/* ------------------------------------------------------------------ */

void GenElement::increment_remain()
{
  #pragma omp atomic
  n_remain++;
}

/* ------------------------------------------------------------------ */

void GenElement::decrement_remain()
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
        item.second->remove_from_blacklist(ID);
      }
    }

    logging("Data-" + std::to_string(ID) + " has been deleted");
  }
  else if (n_remain < 0)
  {
    runtime_error(
      "Data-" + std::to_string(ID) + ": Invalid data use is detected");
  }

  omp_unset_lock(&omp_lock);
}

/* ------------------------------------------------------------------ */

void GenElement::update_data(ShPtr<Updater> upd)
{
  omp_set_lock(&omp_lock);

  upd->compute(data, datakeys, ID);

  omp_unset_lock(&omp_lock);
}

/* ------------------------------------------------------------------ */
// assumed to be not called from multithreads
ShPtr<GenElement> GenElement::append_updater(ShPtr<Updater> upd)
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

const Json &GenElement::get_data()
{
  return data;
}

/* ------------------------------------------------------------------ */

const Set<Str> &GenElement::get_keys()
{
  return datakeys;
}

/* ------------------------------------------------------------------ */

ArrayXi GenElement::get_1d_int(
  const Str &key)
{
  ArrayXi tmp(data.is_array() ? data.size() : 1);

  if (data.is_array())
  {
    auto length = data.size();

    for (int i = 0; i != length; ++i)
    {
      tmp(i) = data[i][key];
    }
  }
  else
  {
    tmp(0) = data[key];
  }

  return tmp;
}

/* ------------------------------------------------------------------ */

ArrayXd GenElement::get_1d_double(
  const Str &key)
{
  ArrayXd tmp(data.is_array() ? data.size() : 1);

  if (data.is_array())
  {
    auto length = data.size();

    for (int i = 0; i != length; ++i)
    {
      tmp(i) = data[i][key];
    }
  }
  else
  {
    tmp(0) = data[key];
  }

  return tmp;
}

/* ------------------------------------------------------------------ */

ArrayXXi GenElement::get_2d_int(
  const List<Str> &keys)
{
  auto n_keys = keys.size();

  ArrayXXi tmp(data.is_array() ? data.size() : 1, n_keys);

  if (data.is_array())
  {
    auto length = data.size();

    for (int i = 0; i != length; ++i)
    {
      auto &d = data[i];

      for (int j = 0; j != n_keys; ++j)
      {
        tmp(i, j) = d[keys[j]];
      }
    }
  }
  else
  {
    for (int j = 0; j != n_keys; ++j)
    {
      tmp(0, j) = data[keys[j]];
    }
  }

  return tmp;
}

/* ------------------------------------------------------------------ */

ArrayXXd GenElement::get_2d_double(
  const List<Str> &keys)
{
  auto n_keys = keys.size();

  ArrayXXd tmp(data.is_array() ? data.size() : 1, n_keys);

  if (data.is_array())
  {
    auto length = data.size();

    for (int i = 0; i != length; ++i)
    {
      auto &d = data[i];

      for (int j = 0; j != n_keys; ++j)
      {
        tmp(i, j) = d[keys[j]];
      }
    }
  }
  else
  {
    for (int j = 0; j != n_keys; ++j)
    {
      tmp(0, j) = data[keys[j]];
    }
  }

  return tmp;
}

/* ------------------------------------------------------------------ */

const Json &GenElement::get_data_py()
{
  try
  {
    hello();
  }
  catch (std::runtime_error &e)
  {
    logging(e.what());
  }

  return get_data();
}

/* ------------------------------------------------------------------ */

const Set<Str> &GenElement::get_keys_py()
{
  try
  {
    hello();
  }
  catch (std::runtime_error &e)
  {
    logging(e.what());
  }

  return get_keys();
}

/* ------------------------------------------------------------------ */

const ArrayXi GenElement::get_1d_int_py(
  const Str &key)
{
  try
  {
    hello();
  }
  catch (std::runtime_error &e)
  {
    logging(e.what());
  }

  return check_containment<Str>(datakeys, key)
    ? get_1d_int(key) : ArrayXi();
}

/* ------------------------------------------------------------------ */

const ArrayXd GenElement::get_1d_double_py(
  const Str &key)
{
  try
  {
    hello();
  }
  catch (std::runtime_error &e)
  {
    logging(e.what());
  }

  return check_containment<Str>(datakeys, key)
    ? get_1d_double(key) : ArrayXd();
}

/* ------------------------------------------------------------------ */

const ArrayXXi GenElement::get_2d_int_py(
  const List<Str> &keys)
{
  try
  {
    hello();
  }
  catch (std::runtime_error &e)
  {
    logging(e.what());
  }

  return check_containment<Str>(
    datakeys, Set<Str>(keys.begin(), keys.end()))
    ? get_2d_int(keys) : ArrayXXi();
}

/* ------------------------------------------------------------------ */

const ArrayXXd GenElement::get_2d_double_py(
  const List<Str> &keys)
{
  try
  {
    hello();
  }
  catch (std::runtime_error &e)
  {
    logging(e.what());
  }

  return check_containment<Str>(
    datakeys, Set<Str>(keys.begin(), keys.end()))
    ? get_2d_double(keys) : ArrayXXd();
}
