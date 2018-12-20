import unittest

import os
import sys
sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from error_checker import check_error_msg

from copy import deepcopy
from math import sqrt
from random import uniform

import numpy as np

from ppap4lmp import \
  create, StaCustom, StaMolecules, ProDistanceInMolecule, execute_omp

class TestProDistanceInMolecule(unittest.TestCase):

  base_data = [
    {"id": 1, "mol": 1, "xu": 0.0, "yu": 1.0, "zu": 2.0},
    {"id": 2, "mol": 1, "xu": 2.0, "yu": 1.0, "zu": 0.0},
    {"id": 3, "mol": 1, "xu": 1.0, "yu": 2.0, "zu": 3.0},
    {"id": 4, "mol": 1, "xu": 3.0, "yu": 2.0, "zu": 1.0},
    {"id": 5, "mol": 1, "xu": 2.0, "yu": 3.0, "zu": 4.0},
    {"id": 6, "mol": 1, "xu": 4.0, "yu": 3.0, "zu": 2.0},
  ]

  def test_error01(self):

    dummy_data = deepcopy(self.base_data)

    for i in range(len(dummy_data)):
      del dummy_data[i]["xu"]

    atoms = create(StaCustom(dummy_data))
    mols = create(StaMolecules(atoms))

    pro = ProDistanceInMolecule(mols, atoms)

    check_error_msg(
      self, "RuntimeError: Missing key(s) 'xu' in ProDistanceInMolecule", execute_omp, pro)

  def test_error02(self):

    atoms = create(StaCustom(self.base_data))
    mols = create(StaCustom([{"id": 1, "foo": "var"}]))

    pro = ProDistanceInMolecule(mols, atoms)

    check_error_msg(
      self, "RuntimeError: Missing key(s) 'atom-ids' in ProDistanceInMolecule", execute_omp, pro)

  def test_squared_distance(self):

    abst_atoms = []
    n_atoms_in_mol = len(self.base_data)

    for imol in range(10):

      tmp = deepcopy(self.base_data)

      shift_x = uniform(-100.0, 100.0)
      shift_y = uniform(-100.0, 100.0)
      shift_z = uniform(-100.0, 100.0)

      for atom in tmp:

        atom["id"] += imol*n_atoms_in_mol
        atom["mol"] += imol
        atom["xu"] += shift_x
        atom["yu"] += shift_y
        atom["zu"] += shift_z

      abst_atoms.extend(tmp)

    abst_atoms_traj = []

    for itraj in range(10):

      tmp = deepcopy(abst_atoms)

      for atom in tmp:
        atom["xu"] *= itraj + 1
        atom["yu"] *= itraj + 1
        atom["zu"] *= itraj + 1

      abst_atoms_traj.append(tmp)

    atomses = [
      create(StaCustom(a)) for a in abst_atoms_traj]
    molses = [
      create(StaMolecules(a)) for a in atomses]

    pro = ProDistanceInMolecule(list(zip(molses, atomses)))
    pro.set_indices(0, 5)

    execute_omp(pro)

    expects = np.array(
      [[20.0*(i+1)*(i+1)] * 10 for i in range(10)])

    self.assertTrue(np.allclose(pro.get_distance2_array(), expects))

  def test_square_rooted_distance(self):

    abst_atoms = []
    n_atoms_in_mol = len(self.base_data)

    for imol in range(10):

      tmp = deepcopy(self.base_data)

      shift_x = uniform(-100.0, 100.0)
      shift_y = uniform(-100.0, 100.0)
      shift_z = uniform(-100.0, 100.0)

      for atom in tmp:

        atom["id"] += imol*n_atoms_in_mol
        atom["mol"] += imol
        atom["xu"] += shift_x
        atom["yu"] += shift_y
        atom["zu"] += shift_z

      abst_atoms.extend(tmp)

    abst_atoms_traj = []

    for itraj in range(10):

      tmp = deepcopy(abst_atoms)

      for atom in tmp:
        atom["xu"] *= itraj + 1
        atom["yu"] *= itraj + 1
        atom["zu"] *= itraj + 1

      abst_atoms_traj.append(tmp)

    atomses = [
      create(StaCustom(a)) for a in abst_atoms_traj]
    molses = [
      create(StaMolecules(a)) for a in atomses]

    pro = ProDistanceInMolecule(list(zip(molses, atomses)))
    pro.set_indices(1, 5)

    execute_omp(pro)

    expects = np.array(
      [[sqrt(12.0)*(i+1)] * 10 for i in range(10)])

    self.assertTrue(np.allclose(pro.get_distance_array(), expects))

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestProDistanceInMolecule("test_error01"))
  suite.addTest(TestProDistanceInMolecule("test_error02"))
  suite.addTest(TestProDistanceInMolecule("test_squared_distance"))
  suite.addTest(TestProDistanceInMolecule("test_square_rooted_distance"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
