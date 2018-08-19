import unittest
import traceback

from ppap4lmp import \
  Element, StaCustom, StaMolecules, AddCoMPositions, AddInertiaMoment

class TestAddInertiaMoment(unittest.TestCase):

  custom_data = [
    {"id": 1, "mol": 1, "mass": 1.0, "xu": 1.0, "yu": 0.0, "zu": 0.0},
    {"id": 2, "mol": 1, "mass": 1.0, "xu": -1.0, "yu": 0.0, "zu": 0.0},
    {"id": 3, "mol": 1, "mass": 1.0, "xu": 0.0, "yu": 1.0, "zu": 0.0},
    {"id": 4, "mol": 1, "mass": 1.0, "xu": 0.0, "yu": -1.0, "zu": 0.0},
    {"id": 5, "mol": 1, "mass": 1.0, "xu": 0.0, "yu": 0.0, "zu": 1.0},
    {"id": 6, "mol": 1, "mass": 1.0, "xu": 0.0, "yu": 0.0, "zu": -1.0},
  ]

  def test_error(self):

    atoms = Element(StaCustom(self.custom_data))
    molecules = Element(StaMolecules(atoms))
    molecules.append_updater(AddCoMPositions(atoms))

    molecules.append_updater(
      AddInertiaMoment(Element(StaCustom({"foo": 0, "bar": 1}))))

    try:
      molecules.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: AddInertiaMoment needs 'id', 'mass' and '*u' "
        + "(x/y/z) externally")

    atoms = Element(StaCustom(self.custom_data))
    molecules = Element(StaMolecules(atoms))
    molecules.append_updater(AddInertiaMoment(atoms))

    try:
      molecules.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: AddInertiaMoment needs 'atom-ids' and '*u' (x/y/z)")

  def test_isotropic(self):

    atoms = Element(StaCustom(self.custom_data))
    molecules = Element(StaMolecules(atoms))
    molecules.append_updater(AddCoMPositions(atoms))
    molecules.append_updater(AddInertiaMoment(atoms))

    data = molecules.get_data()[0]

    self.assertEqual(data["I_xx"], data["I_yy"])
    self.assertEqual(data["I_yy"], data["I_zz"])
    self.assertEqual(data["I_xy"], data["I_yz"])
    self.assertEqual(data["I_zx"], data["I_xy"])
