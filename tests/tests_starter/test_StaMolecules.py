import unittest

import os
import sys
sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from test_utils import check_error_msg

from ppap4lmp import create, StaDumpBox, StaDumpAtoms, StaMolecules

class TestStaMolecules(unittest.TestCase):

  def test_error01(self):

    molecules = create(StaMolecules(
      create(StaDumpBox("dumps_bead/bead.2990000.dump", 2990000))))

    check_error_msg(
      self, "RuntimeError: Missing key(s) 'id', 'mol' in StaMolecules", molecules.get_data)

  def test_get_data(self):

    self._test_get_data(
      ("dumps_bead/bead.2990000.dump", 2990000),
      6, set(range(120136, 120163)))

    self._test_get_data(
      ("dumps_atom/atom.0.dump", 0),
      5, set(range(153, 191)))

  def _test_get_data(self, arguments, expected_id, expected_atoms):

    molecules = create(StaMolecules(create(StaDumpAtoms(*arguments))))
    data = molecules.get_data()

    self.assertEqual(data[expected_id-1]["id"], expected_id)
    self.assertEqual(set(data[expected_id-1]["atom-ids"]), expected_atoms)

  def test_get_keys(self):

    self._test_get_keys(
      ("dumps_bead/bead.2990000.dump", 2990000), {"id", "atom-ids"})

    self._test_get_keys(
      ("dumps_atom/atom.0.dump", 0), {"id", "atom-ids"})

  def _test_get_keys(self, arguments, expectation):

    molecules = create(StaMolecules(create(StaDumpAtoms(*arguments))))

    self.assertEqual(molecules.get_keys(), expectation)

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestStaMolecules("test_error01"))
  suite.addTest(TestStaMolecules("test_get_data"))
  suite.addTest(TestStaMolecules("test_get_keys"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
