import unittest

import os
import sys

sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from test_utils import check_error_msg

import numpy as np

from math import sqrt

from ppap4lmp import (
  create, StaCustom, StaMolecules,
  AddCoMPosition, AddInertiaMoment, AddMolecularOrientation)

class TestAddMolecularOrientation(unittest.TestCase):

  custom_data = [
    {"id": 1, "mol": 1, "mass": 1.0, "xu": 2.0, "yu": 1.0, "zu": 1.0},
    {"id": 2, "mol": 1, "mass": 1.0, "xu": 0.0, "yu": 1.0, "zu": 1.0},
    {"id": 3, "mol": 1, "mass": 1.0, "xu": 1.0, "yu": 2.0, "zu": 1.0},
    {"id": 4, "mol": 1, "mass": 1.0, "xu": 1.0, "yu": 0.0, "zu": 1.0},
    {"id": 5, "mol": 1, "mass": 1.0, "xu": 1.0, "yu": 1.0, "zu": 2.0},
    {"id": 6, "mol": 1, "mass": 1.0, "xu": 1.0, "yu": 1.0, "zu": 0.0},
  ]

  def test_error01(self):

    atoms = create(StaCustom(self.custom_data))
    molecules = create(StaMolecules(atoms))
    molecules.append_updater(AddMolecularOrientation())

    check_error_msg(
      self, "RuntimeError: Missing key(s) 'I_xx', 'I_xy', 'I_xz', 'I_yy', 'I_yz', 'I_zz' in AddMolecularOrientation", molecules.get_data)

  def test_isotropic(self):

    atoms = create(StaCustom(self.custom_data))
    molecules = create(StaMolecules(atoms))
    molecules.append_updater(AddCoMPosition(atoms))
    molecules.append_updater(AddInertiaMoment(atoms))
    molecules.append_updater(AddMolecularOrientation())

    data = molecules.get_data()[0]

    evals = data["I_values"]
    self.assertEqual(evals[0], evals[1])
    self.assertEqual(evals[0], evals[2])

    evecs = data["I_vectors"]
    self.assertTrue(np.allclose(np.array(evecs), np.identity(3)))

  def test_x_oriented(self):

    atoms = create(StaCustom([
      {"id": 1, "mol": 1, "mass": 1.0, "xu": 1.0, "yu": 1.0, "zu": 1.0},
      {"id": 2, "mol": 1, "mass": 1.0, "xu": 2.0, "yu": 1.0, "zu": 1.0},
      {"id": 3, "mol": 1, "mass": 1.0, "xu": 4.0, "yu": 1.0, "zu": 1.0},
      {"id": 4, "mol": 1, "mass": 1.0, "xu": 8.0, "yu": 1.0, "zu": 1.0},
    ]))
    molecules = create(StaMolecules(atoms))
    molecules.append_updater(AddCoMPosition(atoms))
    molecules.append_updater(AddInertiaMoment(atoms))
    molecules.append_updater(AddMolecularOrientation())

    data = molecules.get_data()[0]

    self.assertEqual(data["S_x"], 1.0)
    self.assertEqual(data["S_y"], -0.5)
    self.assertEqual(data["S_z"], -0.5)

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestAddMolecularOrientation("test_error01"))
  suite.addTest(TestAddMolecularOrientation("test_isotropic"))
  suite.addTest(TestAddMolecularOrientation("test_x_oriented"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
