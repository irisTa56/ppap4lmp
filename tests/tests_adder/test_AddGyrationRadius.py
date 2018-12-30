import unittest

import os
import sys

sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from test_utils import check_error_msg

from copy import deepcopy
from math import sqrt

from ppap4lmp import (
  create, StaCustom, StaMolecules,
  AddCoMPosition, AddInertiaMoment, AddGyrationRadius)

class TestAddGyrationRadius(unittest.TestCase):

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
    molecules.append_updater(AddGyrationRadius())

    check_error_msg(
      self, "RuntimeError: Missing key(s) 'I_xx', 'I_yy', 'I_zz', 'mass' in AddGyrationRadius", molecules.get_data)

  def test_sqrted(self):

    atoms = create(StaCustom(self.custom_data))
    molecules = create(StaMolecules(atoms))
    molecules.append_updater(AddCoMPosition(atoms))
    molecules.append_updater(AddInertiaMoment(atoms))
    molecules.append_updater(AddGyrationRadius().with_sqrted())

    data = molecules.get_data()[0]

    self.assertAlmostEqual(data["Rg"], 1.0)
    self.assertAlmostEqual(data["Rg(x+y)"], sqrt(2/3))
    self.assertAlmostEqual(data["Rg(x)"], sqrt(1/3))

    self.assertEqual(data["Rg(x+y)"], data["Rg(y+z)"])
    self.assertEqual(data["Rg(x+y)"], data["Rg(z+x)"])

    self.assertEqual(data["Rg(x)"], data["Rg(y)"])
    self.assertEqual(data["Rg(x)"], data["Rg(z)"])

    self.assertEqual(
      molecules.get_keys(), {
        "id", "atom-ids", "mass", "xu", "yu", "zu",
        "I_xx", "I_yy", "I_zz", "I_xy", "I_xz", "I_yz",
        "Rg^2", "Rg^2(y+z)", "Rg^2(z+x)", "Rg^2(x+y)",
        "Rg^2(x)", "Rg^2(y)", "Rg^2(z)",
        "Rg", "Rg(y+z)", "Rg(z+x)", "Rg(x+y)",
        "Rg(x)", "Rg(y)", "Rg(z)"})

  def test_squared(self):

    custom_data = deepcopy(self.custom_data)

    custom_data[0]["xu"] = 3.0
    custom_data[1]["xu"] = -1.0

    atoms = create(StaCustom(custom_data))
    molecules = create(StaMolecules(atoms))
    molecules.append_updater(AddCoMPosition(atoms))
    molecules.append_updater(AddInertiaMoment(atoms))
    molecules.append_updater(AddGyrationRadius())

    data = molecules.get_data()[0]

    self.assertAlmostEqual(data["Rg^2"], 2.0)
    self.assertAlmostEqual(data["Rg^2(x+y)"], 5/3)
    self.assertAlmostEqual(data["Rg^2(y+z)"], 2/3)
    self.assertAlmostEqual(data["Rg^2(z+x)"], 5/3)
    self.assertAlmostEqual(data["Rg^2(x)"], 4/3)
    self.assertAlmostEqual(data["Rg^2(y)"], 1/3)
    self.assertAlmostEqual(data["Rg^2(z)"], 1/3)

    self.assertEqual(
      molecules.get_keys(), {
        "id", "atom-ids", "mass", "xu", "yu", "zu",
        "I_xx", "I_yy", "I_zz", "I_xy", "I_xz", "I_yz",
        "Rg^2", "Rg^2(y+z)", "Rg^2(z+x)", "Rg^2(x+y)",
        "Rg^2(x)", "Rg^2(y)", "Rg^2(z)"})

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestAddGyrationRadius("test_error01"))
  suite.addTest(TestAddGyrationRadius("test_sqrted"))
  suite.addTest(TestAddGyrationRadius("test_squared"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
