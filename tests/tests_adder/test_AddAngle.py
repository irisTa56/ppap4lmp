import unittest

import os
import sys

sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from test_utils import (
  check_error_msg, generate_random_unit_vector, rotate_vector)

import numpy as np

from random import randrange

from ppap4lmp import (
  create, AddMap, AddAngle,
  StaCustom, StaDumpAtoms, StaMolecules, StaBeads)

def convert_to_deg(rad):
  return rad * (180.0/np.pi)

def compute_angle(v1, v2):
  return convert_to_deg(
    np.arccos(np.dot(v1, v2) / (np.linalg.norm(v1)*np.linalg.norm(v2))))

class TestAddAngle(unittest.TestCase):

  def test_single_angle(self):

    right_angle = 45.0

    angles_py = [
      {"id": 1, "atom1-id": 1, "atom2-id": 2, "atom3-id": 3}
    ]

    atoms_py = [
      {"id": 1, "xu": 1.0, "yu": 1.0, "zu": 0.0},
      {"id": 2, "xu": 1.0, "yu": 0.0, "zu": 0.0},
      {"id": 3, "xu": 1.0, "yu": 1.0, "zu": 1.0},
    ]

    angles = create(StaCustom(angles_py))
    atoms = create(StaCustom(atoms_py))
    angles.append_updater(AddAngle(atoms))

    self.assertTrue(np.allclose(
      convert_to_deg(angles.get_data()[0]["angle"]), right_angle))

  def test_sequence_angles(self):

    right_angles = np.random.uniform(0.0, 180.0, 100000)

    lo = -100.0
    hi = 100.0

    angles_py = []

    atoms_py = [{
      "id": 1,
      "xu": np.random.uniform(lo, hi),
      "yu": np.random.uniform(lo, hi),
      "zu": np.random.uniform(lo, hi)
    }] # set position of the first atom

    vec_1to2 = generate_random_unit_vector()
    length_12 = np.random.uniform(0.8, 1.2)

    atoms_py.append({
      "id": 2,
      "xu": atoms_py[0]["xu"] + length_12 * vec_1to2[0],
      "yu": atoms_py[0]["yu"] + length_12 * vec_1to2[1],
      "zu": atoms_py[0]["zu"] + length_12 * vec_1to2[2],
    }) # set position of the second atom

    for i, angle in enumerate(right_angles):
      """
      `angle` consists of `i`-, `i+1`- and `i+2`-th atoms.
      Position of the `i+2`-th atom should be determined here.
      """
      r1 = np.array([
        atoms_py[i]["xu"], atoms_py[i]["yu"], atoms_py[i]["zu"]])
      r2 = np.array([
        atoms_py[i+1]["xu"], atoms_py[i+1]["yu"], atoms_py[i+1]["zu"]])

      vec_test = generate_random_unit_vector()
      length = np.random.uniform(0.8, 1.2)

      r3 = r2 + length*vec_test

      vec_2to1 = r1 - r2
      vec_2to3 = r3 - r2

      # normal vector of a plane defined by `vec_2to1` and `vec_2to3`
      n_vec = np.cross(vec_2to3, vec_2to1)

      # angle defined by `vec_2to1` and `vec_2to3`
      angle_tmp = compute_angle(vec_2to1, vec_2to3)

      vec_2to3_rotated = rotate_vector(vec_2to3, n_vec, angle_tmp-angle)

      atoms_py.append({
        "id": i+3,
        "xu": r2[0] + vec_2to3_rotated[0],
        "yu": r2[1] + vec_2to3_rotated[1],
        "zu": r2[2] + vec_2to3_rotated[2],
      }) # set right position of the third atom

      angles_py.append({
        "id": i+1 ,
        "atom1-id": i+1,
        "atom2-id": i+2,
        "atom3-id": i+3
      })

    angles = create(StaCustom(angles_py))
    atoms = create(StaCustom(atoms_py))
    angles.append_updater(AddAngle(atoms))

    self.assertTrue(
      np.allclose(right_angles, convert_to_deg(angles.get_1d_float("angle"))))

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestAddAngle("test_single_angle"))
  suite.addTest(TestAddAngle("test_sequence_angles"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
