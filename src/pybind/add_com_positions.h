#ifndef PYBIND_ADD_COM_POSITIONS_H
#define PYBIND_ADD_COM_POSITIONS_H

#include <adders/add_com_positions.h>
#include <pybind/adder.h>

static void pybind_add_com_positions(py::module &m)
{
  py::class_<AddCoMPositions,PyUpdater<AddCoMPositions>,Adder,Updater,ShPtr<AddCoMPositions>>(m, "AddCoMPositions")
    .def(py::init<ShPtr<GenElement>>());
}

#endif