import unittest
import traceback

from copy import deepcopy
from random import uniform

import numpy as np

from ppap4lmp import \
  Element, StaCustom, ProMeanSquareDisplacement, InvOMP

class TestProMeanSquareDisplacement(unittest.TestCase):

  abst_atoms = []
  atom_id = 0

  for i in range(-1, 2):
    for j in range(-1, 2):
      for k in range(-1, 2):

        atom_id += 1

        abst_atoms.append({
          "id": atom_id, "mass": 12.01,
          "xu": float(i), "yu": float(j), "zu": float(k)})

  def test_error01(self):

    dummy_data = deepcopy(self.abst_atoms)

    for i in range(len(dummy_data)):
      del dummy_data[i]["mass"]

    atoms = Element(StaCustom(dummy_data))

    pro = ProMeanSquareDisplacement([atoms])

    try:
      InvOMP(pro).execute()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: ProMeanSquareDisplacement needs 'mass' "
        + "externally")

  def test_dimension_3d(self):

    abst_atoms_traj = []

    for itraj in range(10):

      tmp = deepcopy(self.abst_atoms)

      shift_x = uniform(-100.0, 100.0)
      shift_y = uniform(-100.0, 100.0)
      shift_z = uniform(-100.0, 100.0)

      for atom in tmp:

        atom["xu"] *= itraj + 1
        atom["yu"] *= itraj + 1
        atom["zu"] *= itraj + 1

        atom["xu"] += shift_x
        atom["yu"] += shift_y
        atom["zu"] += shift_z

      abst_atoms_traj.append(tmp)

    atomses = [
      Element(StaCustom(a)) for a in abst_atoms_traj]

    pro = ProMeanSquareDisplacement(atomses)

    InvOMP(pro).execute()

    expect = np.array([2.0*i*i for i in range(10)])

    self.assertTrue(np.allclose(
      pro.get_mean_square_displacement(), expect))

    expect_array = []

    for itraj in range(10):

      tmp = []

      for i in range(-1, 2):
        for j in range(-1, 2):
          for k in range(-1, 2):

            tmp.append(float(i*i+j*j+k*k)*itraj*itraj)

      expect_array.append(tmp)

    self.assertTrue(np.allclose(
      pro.get_displacement2_array(), np.array(expect_array)))

  def test_dimension_2d(self):

    abst_atoms_traj = []

    for itraj in range(10):

      tmp = deepcopy(self.abst_atoms)

      shift_x = uniform(-100.0, 100.0)
      shift_y = uniform(-100.0, 100.0)
      shift_z = uniform(-100.0, 100.0)

      for atom in tmp:

        atom["xu"] *= itraj + 1
        atom["yu"] *= itraj + 1
        atom["zu"] *= itraj + 1

        atom["xu"] += shift_x
        atom["yu"] += shift_y
        atom["zu"] += shift_z

      abst_atoms_traj.append(tmp)

    atomses = [
      Element(StaCustom(a)) for a in abst_atoms_traj]

    pro_xyz = ProMeanSquareDisplacement(atomses)

    pro_xy = ProMeanSquareDisplacement(atomses)
    pro_xy.set_dimension(True, True, False)

    pro_yz = ProMeanSquareDisplacement(atomses)
    pro_yz.set_dimension(False, True, True)

    pro_xz = ProMeanSquareDisplacement(atomses)
    pro_xz.set_dimension(True, False, True)

    InvOMP([pro_xyz, pro_xy, pro_yz, pro_xz]).execute()

    self.assertTrue(np.allclose(
      pro_xy.get_mean_square_displacement(),
      pro_yz.get_mean_square_displacement()))

    self.assertTrue(np.allclose(
      pro_xy.get_mean_square_displacement(),
      pro_xz.get_mean_square_displacement()))

    self.assertTrue(np.allclose(
      2*pro_xyz.get_mean_square_displacement(),
      pro_xz.get_mean_square_displacement() +
      pro_yz.get_mean_square_displacement() +
      pro_xz.get_mean_square_displacement()))