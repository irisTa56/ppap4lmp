import unittest

import os
import sys
sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from error_checker import check_error_msg

import numpy as np

from copy import deepcopy
from random import uniform

from ppap4lmp import \
  create, StaCustom, StaMolecules, AddChildPositions, \
  AddCoMPosition, AddInertiaMoment, AddGyrationRadius

class TestAddChildPositions(unittest.TestCase):

  def test_error01(self):

    atoms = create(StaCustom(
      [{"id": i, "mol": i//10} for i in range(100)]))

    moles = create(StaMolecules(atoms))
    moles.append_updater(AddChildPositions(atoms, "child"))

    check_error_msg(
      self, "RuntimeError: Missing key(s) 'child-ids', 'xu', 'yu', 'zu'", moles.get_data)

  def test_random(self):

    rs = 10*np.random.random_sample((10, 3)) - 5
    ms = np.random.random_sample(10) + 1
    com = (rs.T*ms).T.sum(axis=0)/ms.sum()

    expected = rs - com

    abst_atoms_in_mol = [
      {
        "id": i+1,
        "mol": 1,
        "mass": ms[i],
        "xu": rs[i,0],
        "yu": rs[i,1],
        "zu": rs[i,2]
      }
      for i in range(10)]

    abst_atoms = []

    for imol in range(100):

      tmp = deepcopy(abst_atoms_in_mol)

      shift_x = uniform(-100.0, 100.0)
      shift_y = uniform(-100.0, 100.0)
      shift_z = uniform(-100.0, 100.0)

      for atom in tmp:

        atom["id"] += 10*imol
        atom["mol"] += imol
        atom["xu"] += shift_x
        atom["yu"] += shift_y
        atom["zu"] += shift_z

      abst_atoms.extend(tmp)

    atoms = create(StaCustom(abst_atoms))

    moles = create(StaMolecules(atoms))
    moles.append_updater(AddCoMPosition(atoms))
    moles.append_updater(AddChildPositions(atoms, "atom"))

    data = moles.get_data()

    for d in data:

      self.assertTrue(np.allclose(expected, np.array(
        [d["atom-xs"], d["atom-ys"], d["atom-zs"]]).T))

  def test_gyration_radius(self):

    n_samples = 2000

    rs = 100*np.random.random_sample((n_samples, 3)) - 50

    abst_atoms = [
      {
        "id": i+1,
        "mol": i//20 + 1,
        "mass": 12.011,
        "xu": rs[i,0],
        "yu": rs[i,1],
        "zu": rs[i,2]
      }
      for i in range(2000)]

    atoms = create(StaCustom(abst_atoms))

    moles = create(StaMolecules(atoms))
    moles.append_updater(AddCoMPosition(atoms))
    moles.append_updater(AddChildPositions(atoms, "atom"))

    moles.append_updater(AddInertiaMoment(atoms))
    moles.append_updater(AddGyrationRadius())

    data = moles.get_data()

    for d in data:

      xyzs = d["atom-xs"] + d["atom-ys"] + d["atom-zs"]

      self.assertAlmostEqual(
        d["Rg^2"], sum([a*a for a in xyzs])/len(d["atom-ids"]))

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestAddChildPositions("test_error01"))
  suite.addTest(TestAddChildPositions("test_random"))
  suite.addTest(TestAddChildPositions("test_gyration_radius"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
