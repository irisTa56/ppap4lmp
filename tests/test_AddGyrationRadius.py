import unittest
import traceback

from math import sqrt

from ppap4lmp import \
  Element, StaCustom, StaMolecules, \
  AddCoMPositions, AddInertiaMoment, AddGyrationRadius

class TestAddGyrationRadius(unittest.TestCase):

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
    molecules.append_updater(AddGyrationRadius())

    try:
      molecules.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: AddGyrationRadius needs 'mass' and 'I_**' (x/y/z)")

  def test_isotropic(self):

    atoms = Element(StaCustom(self.custom_data))
    molecules = Element(StaMolecules(atoms))
    molecules.append_updater(AddCoMPositions(atoms))
    molecules.append_updater(AddInertiaMoment(atoms))
    molecules.append_updater(AddGyrationRadius())

    data = molecules.get_data()[0]

    self.assertEqual(data["Rg_x"], data["Rg_y"])
    self.assertEqual(data["Rg_x"], data["Rg_z"])
    self.assertEqual(
      data["Rg"],
      sqrt(0.5 * (data["Rg_x"]**2 + data["Rg_y"]**2 + data["Rg_z"]**2)))
