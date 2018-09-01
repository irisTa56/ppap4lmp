/* ---------------------------------------------------------------------
StaCustom: stands for Starter to generate Custom data.

create: 2018/08/16 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef STA_CUSTOM_H
#define STA_CUSTOM_H

#include <starters/starter.h>

class StaCustom : public Starter {
  Json json;
  Set<Str> jsonkeys;
 protected:
  virtual void compute_impl(
    Json &data,
    Set<Str> &datakeys) override;
 public:
  StaCustom(
    const Json &json_);
  virtual ~StaCustom() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_sta_custom(py::module &m)
{
  py::class_<StaCustom,PyUpdater<StaCustom>,Starter,Updater,ShPtr<StaCustom>>(m, "StaCustom")
    .def(py::init<const Json &>());
}

#endif