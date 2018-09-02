#ifndef PYBIND_UPDATER_H
#define PYBIND_UPDATER_H

#include <core/updater.h>

// trampoline class to bind Python
template <class UPD = Updater>
class PyUpdater : public UPD {
 protected:
  void compute_impl(
    Json &data, Set<Str> &datakeys) override
  {
    PYBIND11_OVERLOAD_PURE(
      void, UPD, compute_impl, data, datakeys);
  }
 public:
  using UPD::UPD;
  void compute(
    Json &data, Set<Str> &datakeys, int dataid) override
  {
    PYBIND11_OVERLOAD_PURE(
      void, UPD, compute, data, datakeys, dataid);
  }
};

static void pybind_updater(py::module &m)
{
  py::class_<
    Updater,PyUpdater<>,ShPtr<Updater>>(m, "Updater")
    .def(py::init<>());
}

#endif