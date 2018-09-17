#ifndef PYBIND_STA_DUMP_BOX_H
#define PYBIND_STA_DUMP_BOX_H

#include <starters/sta_dump_box.h>
#include <pybind/starters_py/starter.h>

static void pybind_sta_dump_box(py::module &m)
{
  py::class_<StaDumpBox,PyUpdater<StaDumpBox>,StaDump,Starter,Updater,ShPtr<StaDumpBox>>(m, "StaDumpBox")
    .def(py::init<const Str &, int>());
}


#endif