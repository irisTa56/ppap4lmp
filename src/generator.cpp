/* ---------------------------------------------------------------------
Generator: is an abstract class to generate (and manage) data.

create: 2018/06/21 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include <algorithm>

#include <omp.h>

#include "generator.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

void Generator::appoint()
{
  for (const auto &item : update_chain)
  {
    item.first->increment_remain();
  }
}

/* ------------------------------------------------------------------ */

void Generator::hello()
{
  for (const auto &item : update_chain)
  {
    item.first->update_data(item.second);
  }
}

/* ------------------------------------------------------------------ */

void Generator::goodbye()
{
  for (const auto &item : update_chain)
  {
    item.first->decrement_remain();
  }
}

/* ------------------------------------------------------------------ */

std::shared_ptr<Generator> Generator::get_generator()
{
  return shared_from_this();
}

/* ------------------------------------------------------------------ */

std::shared_ptr<Generator> Generator::set_initial_updater(
  std::shared_ptr<Updater> upd)
{
  message("This function is for GenElement");
  return shared_from_this();
}

/* ------------------------------------------------------------------ */

std::shared_ptr<Generator> Generator::append_updater(
  std::shared_ptr<Updater> upd)
{
  message("This function is for GenElement");
  return shared_from_this();
}

/* ------------------------------------------------------------------ */

const bool Generator::check_key(
  const std::string &key)
{
  message("This function is for GenElement");
  return false;
}

/* ------------------------------------------------------------------ */

const std::vector<bool> Generator::check_keys(
  const std::vector<std::string> &keys)
{
  message("This function is for GenElement");
  return std::vector<bool>();
}

/* ------------------------------------------------------------------ */

const Eigen::VectorXi Generator::get_int_vector(
  const std::string &key)
{
  message("This function is for GenElement");
  return Eigen::VectorXi();
}

/* ------------------------------------------------------------------ */

const Eigen::VectorXd Generator::get_double_vector(
  const std::string &key)
{
  message("This function is for GenElement");
  return Eigen::VectorXd();
}

/* ------------------------------------------------------------------ */

const Eigen::ArrayXXi Generator::get_int_array(
  const std::vector<std::string> &keys)
{
  message("This function is for GenElement");
  return Eigen::ArrayXXi();
}

/* ------------------------------------------------------------------ */

const Eigen::ArrayXXd Generator::get_double_array(
  const std::vector<std::string> &keys)
{
  message("This function is for GenElement");
  return Eigen::ArrayXXd();
}

/* ------------------------------------------------------------------ */

const std::string &Generator::get_datatype()
{
  return datatype;
}

/* ------------------------------------------------------------------ */

const std::string &Generator::get_dataname()
{
  return dataname;
}

/* ------------------------------------------------------------------ */

void Generator::increment_remain()
{
  #pragma omp atomic
  n_remain += 1;
}

/* ------------------------------------------------------------------ */

void Generator::decrement_remain()
{
  #pragma omp critical
  {
    n_remain -= 1;

    if (n_remain == 0)
    {
      data.clear();
      data = nullptr;

      message(dataname + " has been deleted");
    }
    else if (n_remain < 0)
    {
      runtime_error(dataname + ": Invalid data use is detected");
    }
  }
}

/* ------------------------------------------------------------------ */

void Generator::update_data(std::shared_ptr<Updater> upd)
{
  #pragma omp critical
  upd->compute(data);
}

/* ------------------------------------------------------------------ */

void Generator::merge_update_chain(
  std::vector<UpdatePair> &u, const std::vector<UpdatePair> &v)
{
  for (auto itr = v.begin(); itr != v.end(); ++itr)
  {
    if (std::find(u.begin(), u.end(), *itr) == u.end())
    {
      for (auto jtr = u.begin(); jtr != u.end(); ++jtr)
      {
        bool match = false;

        for (auto ktr = itr+1; ktr != v.end(); ++ktr)
        {
          if (*ktr == *jtr)
          {
            match = true;
            break;
          }
        }

        if (match)
        {
          u.insert(jtr, *itr);
          break;
        }
      }
    }
  }
}

/* ------------------------------------------------------------------ */

const std::vector<UpdatePair> &Generator::get_update_chain()
{
  return update_chain;
}
