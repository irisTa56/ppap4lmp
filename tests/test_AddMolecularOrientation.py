import unittest
import traceback

import numpy as np

from math import sqrt

from ppap4lmp import \
  Element, StaCustom, StaMolecules, \
  AddCoMPositions, AddInertiaMoment, AddMolecularOrientation

class TestAddMolecularOrientation(unittest.TestCase):

  custom_data = [
    {"id": 1, "mol": 1, "mass": 1.0, "xu": 2.0, "yu": 1.0, "zu": 1.0},
    {"id": 2, "mol": 1, "mass": 1.0, "xu": 0.0, "yu": 1.0, "zu": 1.0},
    {"id": 3, "mol": 1, "mass": 1.0, "xu": 1.0, "yu": 2.0, "zu": 1.0},
    {"id": 4, "mol": 1, "mass": 1.0, "xu": 1.0, "yu": 0.0, "zu": 1.0},
    {"id": 5, "mol": 1, "mass": 1.0, "xu": 1.0, "yu": 1.0, "zu": 2.0},
    {"id": 6, "mol": 1, "mass": 1.0, "xu": 1.0, "yu": 1.0, "zu": 0.0},
  ]

  def test_error(self):

    atoms = Element(StaCustom(self.custom_data))
    molecules = Element(StaMolecules(atoms))
    molecules.append_updater(AddMolecularOrientation())

    try:
      molecules.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: AddMolecularOrientation needs 'I_**' "
        + "(xx/yy/zz/xy/yz/zx)")

  def test_isotropic(self):

    atoms = Element(StaCustom(self.custom_data))
    molecules = Element(StaMolecules(atoms))
    molecules.append_updater(AddCoMPositions(atoms))
    molecules.append_updater(AddInertiaMoment(atoms))
    molecules.append_updater(AddMolecularOrientation())

    data = molecules.get_data()[0]

    evals = data["I_values"]
    self.assertEqual(evals[0], evals[1])
    self.assertEqual(evals[0], evals[2])

    evecs = data["I_vectors"]
    self.assertTrue(np.allclose(np.array(evecs), np.identity(3)))

  def test_x_oriented(self):

    atoms = Element(StaCustom([
      {"id": 1, "mol": 1, "mass": 1.0, "xu": 1.0, "yu": 1.0, "zu": 1.0},
      {"id": 2, "mol": 1, "mass": 1.0, "xu": 2.0, "yu": 1.0, "zu": 1.0},
      {"id": 3, "mol": 1, "mass": 1.0, "xu": 4.0, "yu": 1.0, "zu": 1.0},
      {"id": 4, "mol": 1, "mass": 1.0, "xu": 8.0, "yu": 1.0, "zu": 1.0},
    ]))
    molecules = Element(StaMolecules(atoms))
    molecules.append_updater(AddCoMPositions(atoms))
    molecules.append_updater(AddInertiaMoment(atoms))
    molecules.append_updater(AddMolecularOrientation())

    data = molecules.get_data()[0]

    self.assertEqual(data["S_x"], 1.0)
    self.assertEqual(data["S_y"], -0.5)
    self.assertEqual(data["S_z"], -0.5)
