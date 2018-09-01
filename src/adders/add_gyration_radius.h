/* ---------------------------------------------------------------------
AddGyrationRadius: stands for Adder for Gyration Radius (of molecules).

create: 2018/07/15 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_GYRATION_RADIUS_H
#define ADD_GYRATION_RADIUS_H

#include <adders/adder.h>

class AddGyrationRadius : public Adder, public EnShThis<AddGyrationRadius> {
  bool add_squared = false;
  bool add_sqrted = true;
 protected:
  virtual void compute_impl(
    Json &data,
    Set<Str> &datakeys) override;
 public:
  using Adder::Adder;
  virtual ~AddGyrationRadius() = default;
  ShPtr<AddGyrationRadius> with_squared(
    bool add_squared_ = true);
  ShPtr<AddGyrationRadius> without_sqrted(
    bool without_sqrted_ = true);
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_add_gyration_radius(py::module &m)
{
  py::class_<AddGyrationRadius,PyUpdater<AddGyrationRadius>,Adder,Updater,ShPtr<AddGyrationRadius>>(m, "AddGyrationRadius")
    .def(py::init<>())
    .def(
      "with_squared", &AddGyrationRadius::with_squared,
      py::arg("add_squared_") = true)
    .def(
      "without_sqrted", &AddGyrationRadius::without_sqrted,
      py::arg("without_sqrted_") = true);
}

#endif