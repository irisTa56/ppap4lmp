import unittest

import os
import sys

sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from test_utils import TestCasePPAP, generate_random_unit_vector

import numpy as np

from random import randrange

from ppap4lmp import (
  create, AddMap, AddBondLength,
  StaCustom, StaDumpAtoms, StaMolecules, StaBeads)

class TestAddBondLength(TestCasePPAP):

  def test_single_length(self):

    right_length = 121.0

    bonds_py = [{"atom1-id": 1, "atom2-id": 2}]

    atoms_py = [
      {"id": 1, "xu": 0.0, "yu": 0.0, "zu": 0.0},
      {"id": 2, "xu": 0.0, "yu": 0.0, "zu": 121.0},
    ]

    bonds = create(StaCustom(bonds_py))
    atoms = create(StaCustom(atoms_py))
    bonds.append_updater(AddBondLength(atoms))

    self.assertTrue(np.allclose(bonds.get_data()[0]["length"], right_length))

  def test_sequence_lengths(self):

    right_lengths = np.random.uniform(0.5, 1.5, 1000)

    lo = -100.0
    hi = 100.0

    bonds_py = []

    atoms_py = [{
      "id": 1,
      "xu": np.random.uniform(lo, hi),
      "yu": np.random.uniform(lo, hi),
      "zu": np.random.uniform(lo, hi),
    }]

    for i, length in enumerate(right_lengths):

      vec = generate_random_unit_vector()

      atoms_py.append({
        "id": i+2,
        "xu": atoms_py[i]["xu"] + length * vec[0],
        "yu": atoms_py[i]["yu"] + length * vec[1],
        "zu": atoms_py[i]["zu"] + length * vec[2],
      })

      bonds_py.append({
        "id": i+1,
        "atom1-id": i+1,
        "atom2-id": i+2,
      })

    bonds = create(StaCustom(bonds_py))
    atoms = create(StaCustom(atoms_py))
    bonds.append_updater(AddBondLength(atoms))

    self.assertTrue(
      np.allclose(right_lengths, bonds.get_1d_float("length")))

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestAddBondLength("test_single_length"))
  suite.addTest(TestAddBondLength("test_sequence_lengths"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
