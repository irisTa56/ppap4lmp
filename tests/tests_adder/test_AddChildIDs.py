import unittest

import os
import sys

sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from test_utils import TestCasePPAP

from ppap4lmp import (
  create, StaCustom, StaDumpAtoms, StaMolecules, AddChildIDs)

class TestAddChildIDs(TestCasePPAP):

  def test_error01(self):

    atoms = create(StaCustom(
      [{"id": i, "mol": i//10} for i in range(100)]))

    moles = create(StaCustom([{"id": i} for i in range(10)]))
    moles.append_updater(AddChildIDs(atoms, "atom", "molecule-id"))

    self.check_error_msg(
      "RuntimeError: Missing key(s) 'molecule-id' in AddChildIDs", moles.get_data)

  def test_error02(self):

    atoms = create(StaCustom(
      [{"id": i, "mol": i//10} for i in range(100)]))

    moles = create(StaCustom([{"index": i} for i in range(10)]))
    moles.append_updater(AddChildIDs(atoms, "atom", "mol"))

    self.check_error_msg(
      "RuntimeError: Missing key(s) 'id' in AddChildIDs", moles.get_data)

  def test_2way_molecules(self):

    self._test_2way_molecules(
      ("dumps_bead/bead.2990000.dump", 2990000),
      list(range(1, 1001)))

    self._test_2way_molecules(
      ("dumps_atom/atom.0.dump", 0),
      list(range(1, 181)))

  def _test_2way_molecules(self, arguments, mol_ids):

    atoms = create(StaDumpAtoms(*arguments))

    mols1 = create(StaMolecules(atoms))

    mols2 = create(StaCustom([{"id": i} for i in mol_ids]))
    mols2.append_updater(AddChildIDs(atoms, "atom", "mol"))

    self.assertEqual(mols1.get_data(), mols2.get_data())

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestAddChildIDs("test_error01"))
  suite.addTest(TestAddChildIDs("test_error02"))
  suite.addTest(TestAddChildIDs("test_2way_molecules"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
