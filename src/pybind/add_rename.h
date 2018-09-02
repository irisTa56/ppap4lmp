#ifndef PYBIND_ADD_RENAME_H
#define PYBIND_ADD_RENAME_H

#include <adders/add_rename.h>
#include <pybind/adder.h>

static void pybind_add_rename(py::module &m)
{
  py::class_<AddRename,PyUpdater<AddRename>,Adder,Updater,ShPtr<AddRename>>(m, "AddRename")
    .def(py::init<const Str &,const Str &>())
    .def(
      "overwrite", &AddRename::overwrite,
      py::arg("do_overwrite_") = true);
}

#endif