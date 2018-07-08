/* ---------------------------------------------------------------------
Updater: is an abstract class to update data held by Generator.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef UPDATER_H
#define UPDATER_H

#include "generator.h"

class Updater {
  omp_lock_t omp_lock;
  std::unordered_set<std::string> dataname_blacklist;
 protected:
  std::shared_ptr<Generator> reference_generator;
  virtual void compute_impl(json &) = 0;
  const bool check_blacklist(const std::string &);
 public:
  Updater() { omp_init_lock(&omp_lock); }
  virtual ~Updater() = default;
  virtual void compute(json &, const std::string &) = 0;
  virtual void initialize_datatype(std::string &);
  virtual const bool is_callable(const std::string &);
  void remove_from_blacklist(const std::string &);
  const std::shared_ptr<Generator> get_generator();
};

/* ------------------------------------------------------------------ */
// for pybind11

// trampoline class to bind Python
template <class UPD = Updater>
class PyUpdater : public UPD {
 public:
  using UPD::UPD;
  void compute(json &data, const std::string &dataname) override
  {
    PYBIND11_OVERLOAD_PURE(void, UPD, compute, data, dataname);
  }
  void initialize_datatype(std::string &datatype) override
  {
    PYBIND11_OVERLOAD(void, UPD, initialize_datatype, datatype);
  }
  const bool is_callable(const std::string &datatype) override
  {
    PYBIND11_OVERLOAD(const bool, UPD, is_callable, datatype);
  }
 protected:
  void compute_impl(json &data) override
  {
    PYBIND11_OVERLOAD_PURE(void, UPD, compute_impl, data);
  }
};

static void pybind_updater(py::module &m)
{
  py::class_<Updater,PyUpdater<>,std::shared_ptr<Updater>>(m, "Updater")
    .def(py::init<>());
}

#endif