import unittest

import os
import sys
sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from test_utils import check_error_msg

from ppap4lmp import \
  create, StaCustom, StaDumpAtoms, StaMolecules, StaBeads

class TestStaBeads(unittest.TestCase):

  def test_error01(self):

    atoms = create(
      StaDumpAtoms("dumps_atom/atom.0.dump", 0))
    moles = create(StaMolecules(atoms))

    check_error_msg(
      self, "RuntimeError: Mapping to Beads must be specified by 'indices-in-mol'",
      create, StaBeads(moles, [{"foo": [1, 2, 3]}]))

  def test_error02(self):

    atoms = create(
      StaDumpAtoms("dumps_atom/atom.0.dump", 0))
    moles = create(StaMolecules(atoms))

    check_error_msg(
      self, "RuntimeError: The numbers of elements in 'indices-in-mol' and 'weights' are inconsistent",
      create, StaBeads(moles, [
        {"indices-in-mol": [1, 2, 3, 4], "weights": [1.0, 1.0, 1.0]}
      ]))

  def test_error03(self):

    atoms = create(
      StaDumpAtoms("dumps_atom/atom.0.dump", 0))
    moles = create(StaMolecules(atoms))

    check_error_msg(
      self, "RuntimeError: The number of 'type' is invalid",
      create, StaBeads(moles, [
        {"indices-in-mol": [1, 2], "weights": [1.0, 1.0]},
        {"indices-in-mol": [3, 4], "type": 1, "weights": [1.0, 1.0]}
      ]))

  def test_error04(self):

    atoms = create(
      StaDumpAtoms("dumps_atom/atom.0.dump", 0))
    moles = create(StaMolecules(atoms))

    check_error_msg(
      self, "RuntimeError: The number of 'weights' is invalid",
      create, StaBeads(moles, {
          1: [
            {"indices-in-mol": [1, 2]},
            {"indices-in-mol": [3, 4, 5]}
          ],
          2: [
            {"indices-in-mol": [1, 2, 3], "weights": [1.0, 1.0, 1.0]},
            {"indices-in-mol": [3, 4], "weights": [1.0, 1.0]}
          ]
        }))

  def test_atom_id(self):

    atoms = create(
      StaDumpAtoms("dumps_atom/atom.0.dump", 0))
    moles = create(StaMolecules(atoms))

    mappings = [
      [0, 1, 2, 12, 13, 14, 15, 16, 17, 18],
      [3, 4, 5, 19, 20, 21, 22, 23, 24],
      [6, 7, 8, 25, 26, 27, 28, 29, 30],
      [9, 10, 11, 31, 32, 33, 34, 35, 36, 37]]

    abst_beads = [{
      "type": 1,
      "indices-in-mol": mapping,
      "weights": [1.0] * len(mapping)
    } for mapping in mappings]

    beads = create(StaBeads(moles, abst_beads))

    self.assertEqual(
      beads.get_keys(),
      {"id", "mol", "type", "atom-ids", "atom-weights"})

    data = beads.get_data()

    for d in data:

      offset = (d["mol"]-1) * 38
      in_mol = (d["id"]-1) % 4

      self.assertEqual(
        d["atom-ids"], [offset + i + 1 for i in mappings[in_mol]])

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestStaBeads("test_error01"))
  suite.addTest(TestStaBeads("test_error02"))
  suite.addTest(TestStaBeads("test_error03"))
  suite.addTest(TestStaBeads("test_error04"))
  suite.addTest(TestStaBeads("test_atom_id"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
