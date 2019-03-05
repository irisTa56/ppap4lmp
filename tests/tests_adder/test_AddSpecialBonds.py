import unittest

import os
import sys

sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from test_utils import TestCasePPAP

from ppap4lmp import create, StaCustom, StaMolecules, AddSpecialBonds

class TestAddSpecialBonds(TestCasePPAP):

  def test_error01(self):

    atoms = create(StaCustom(
      [{"id": i, "mol": i//10} for i in range(100)]))
    moles = create(StaCustom([{"id": i} for i in range(10)]))

    abst_special_bonds = [
      [j for j in range(10) if abs(i-j) < 3 and i != j]
      for i in range(10)]

    atoms.append_updater(AddSpecialBonds(moles, abst_special_bonds))

    self.check_error_msg(
      "RuntimeError: Missing key(s) 'atom-ids' in AddSpecialBonds", atoms.get_data)

  def test_error02(self):

    atoms = create(StaCustom(
      [{"id": i, "mol": i//10} for i in range(100)]))
    moles = create(StaMolecules(atoms))

    abst_special_bonds = [
      [j for j in range(10) if abs(i-j) < 3 and i != j]
      for i in range(10)]

    atoms.append_updater(AddSpecialBonds(
      moles, {1: abst_special_bonds + [[0]], 2: abst_special_bonds }))

    self.check_error_msg(
      "RuntimeError: The numbers of atoms in a molecule are inconsistent", atoms.get_data)

  def test_exclude_angle(self):

    atoms = create(StaCustom(
      [{"id": i+1, "mol": i//10 + 1} for i in range(100)]))
    moles = create(StaMolecules(atoms))

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

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestAddSpecialBonds("test_error01"))
  suite.addTest(TestAddSpecialBonds("test_error02"))
  suite.addTest(TestAddSpecialBonds("test_exclude_angle"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
