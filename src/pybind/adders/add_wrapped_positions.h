#ifndef PYBIND_ADD_WRAPPED_POSITIONS_H
#define PYBIND_ADD_WRAPPED_POSITIONS_H

#include <adders/add_wrapped_positions.h>
#include <pybind/adders/adder.h>

static void pybind_add_wrapped_positions(py::module &m)
{
  py::class_<AddWrappedPositions,PyUpdater<AddWrappedPositions>,Adder,Updater,ShPtr<AddWrappedPositions>>(m, "AddWrappedPositions")
    .def(py::init<const ShPtr<Element> &>());
}

#endif