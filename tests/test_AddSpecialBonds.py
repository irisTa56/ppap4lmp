import unittest
import traceback

from ppap4lmp import Element, StaCustom, StaMolecules, AddSpecialBonds

class TestAddSpecialBonds(unittest.TestCase):

  def test_error(self):

    atoms = Element(StaCustom(
      [{"id": i, "mol": i//10} for i in range(100)]))
    moles = Element(StaCustom([{"id": i} for i in range(10)]))

    abst_special_bonds = [
      [j for j in range(10) if abs(i-j) < 3 and i != j]
      for i in range(10)]

    atoms.append_updater(AddSpecialBonds(moles, abst_special_bonds))

    try:
      atoms.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: AddSpecialBonds needs 'atom-ids' externally")

    atoms = Element(StaCustom(
      [{"id": i, "mol": i//10} for i in range(100)]))
    moles = Element(StaMolecules(atoms))

    abst_special_bonds = [
      [j for j in range(10) if abs(i-j) < 3 and i != j]
      for i in range(10)]

    atoms.append_updater(AddSpecialBonds(
      moles, {1: abst_special_bonds + [[0]], 2: abst_special_bonds }))

    try:
      atoms.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: The numbers of atoms in a molecule are inconsistent")

  def test_exclude_angle(self):

    atoms = Element(StaCustom(
      [{"id": i+1, "mol": i//10 + 1} for i in range(100)]))
    moles = Element(StaMolecules(atoms))

    abst_special_bonds = [
      [j for j in range(10) if abs(i-j) < 3 and i != j]
      for i in range(10)]

    atoms.append_updater(AddSpecialBonds(moles, abst_special_bonds))

    data = atoms.get_data()

    for i, d in enumerate(data):

      myid = d["id"]

      if i%10 == 0:
        self.assertEqual(
          d["special-bonds"], [myid+j for j in [1, 2]])
      elif i%10 == 1:
        self.assertEqual(
          d["special-bonds"], [myid+j for j in [-1, 1, 2]])
      elif i%10 == 8:
        self.assertEqual(
          d["special-bonds"], [myid+j for j in [-2, -1, 1]])
      elif i%10 == 9:
        self.assertEqual(
          d["special-bonds"], [myid+j for j in [-2, -1]])
      else:
        self.assertEqual(
          d["special-bonds"], [myid+j for j in [-2, -1, 1, 2]])
