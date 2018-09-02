#ifndef PYBIND_STA_CUSTOM_H
#define PYBIND_STA_CUSTOM_H

#include <starters/sta_custom.h>
#include <pybind/starter.h>

static void pybind_sta_custom(py::module &m)
{
  py::class_<StaCustom,PyUpdater<StaCustom>,Starter,Updater,ShPtr<StaCustom>>(m, "StaCustom")
    .def(py::init<const Json &>());
}

#endif