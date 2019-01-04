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
  create, AddMap, AddDihedralAngle,
  StaCustom, StaDumpAtoms, StaMolecules, StaBeads)

def convert_to_deg(rad):
  return rad * (180.0/np.pi)

def compute_angle(v1, v2):
  return convert_to_deg(
    np.arccos(np.dot(v1, v2) / (np.linalg.norm(v1)*np.linalg.norm(v2))))

class TestAddDihedralAngle(unittest.TestCase):

  def test_single_dihedral_angle(self):

    right_dihedral_angle = 135.0

    bond_in_py = [
      {"atom1-id" : 1,"atom2-id" :2,"atom3-id" : 3,"atom4-id" :4}
    ]

    atoms_in_py = [
      {"id" : 1 ,"xu" : -1.0, "yu" : 0.0 ,"zu" :0.0},
      {"id" : 2 ,"xu" : 0.0, "yu" : 0.0, "zu" :0.0},
      {"id" : 3 ,"xu" : 0.0, "yu" : 1.0, "zu" :0.0},
      {"id" : 4 ,"xu" : 1.0, "yu" : 1.0, "zu" :-1.0}
    ]

    bond = create(StaCustom(bond_in_py))
    atoms = create(StaCustom(atoms_in_py))
    bond.append_updater(AddDihedralAngle(atoms))

    self.assertTrue(np.allclose(
      convert_to_deg(bond.get_data()[0]["dihedral_angle"]), right_dihedral_angle))

  def test_sequence_dihedral_angles(self):

    right_dihedral_angles = np.random.uniform(0.0,180.0,1000)

    lo = -100.0
    hi = 100.0

    bond_list = []

    atom_list = [{
      "id" : 1 ,
      "xu" : np.random.uniform(lo, hi) ,
      "yu" : np.random.uniform(lo, hi) ,
      "zu" : np.random.uniform(lo, hi)
    }]#Set the position of the first atom

    vec_1to2 = generate_random_unit_vector()
    length12 = np.random.uniform(0.8, 1.2)

    atom_list.append({
      "id" : 2,
      "xu" : atom_list[0]["xu"] + length12 * vec_1to2[0],
      "yu" : atom_list[0]["yu"] + length12 * vec_1to2[1],
      "zu" : atom_list[0]["zu"] + length12 * vec_1to2[2]
    })#Set the position of the second atom

    vec_2to3 = generate_random_unit_vector()
    length23 = np.random.uniform(0.8, 1.2)

    atom_list.append({
      "id" : 3,
      "xu" : atom_list[1]["xu"] + length23 * vec_2to3[0],
      "yu" : atom_list[1]["yu"] + length23 * vec_2to3[1],
      "zu" : atom_list[1]["zu"] + length23 * vec_2to3[2]
    })#Set the position of the third atom

    for i , dihedral_angle in enumerate(right_dihedral_angles):

      r1 = np.array([
        atom_list[i]["xu"], atom_list[i]["yu"], atom_list[i]["zu"]])
      r2 = np.array([
        atom_list[i+1]["xu"], atom_list[i+1]["yu"], atom_list[i+1]["zu"]])
      r3 = np.array([
        atom_list[i+2]["xu"], atom_list[i+2]["yu"], atom_list[i+2]["zu"]])

      vec_test = generate_random_unit_vector()
      length34 = np.random.uniform(0.8, 1.2)

      r4 = r3 + length34 * vec_test
      #Set the position of the temporary forth atom

      vec_1to2 = r2 - r1
      vec_2to3 = r3 - r2
      vec_3to4 = r4 - r3
      #the vevtor of the four atoms

      b12 = np.cross(vec_1to2, vec_2to3)
      b23 = np.cross(vec_2to3, vec_3to4)
      b2u = vec_2to3/(np.linalg.norm(vec_2to3))
      b123 = np.cross(b12,b23)
      y = np.dot(b123, b2u)
      x = np.dot(b12, b23)

      dihedral_angle_tmp = convert_to_deg(np.arctan2(y,x))

      if dihedral_angle_tmp*2-dihedral_angle <0.0:
        rotated_angle = dihedral_angle-dihedral_angle_tmp
      else :
        rotated_angle = dihedral_angle_tmp-dihedral_angle

      if dihedral_angle_tmp > dihedral_angle and rotated_angle >0.0 or \
      dihedral_angle_tmp < dihedral_angle and rotated_angle <0.0 :
        n_vec = -vec_2to3
      else :
        n_vec = vec_2to3

      vec_3to4_rotated = rotate_vector(vec_3to4, n_vec, rotated_angle)
      #Rotate vec_3to4

      atom_list.append({
        "id" : i+4,
        "xu" : r3[0] + vec_3to4_rotated[0],
        "yu" : r3[1] + vec_3to4_rotated[1],
        "zu" : r3[2] + vec_3to4_rotated[2]
      })#Set the position of the true forth atom

      bond_list.append({
        "id" : i+1 ,
        "atom1-id" : i+1,
        "atom2-id" : i+2,
        "atom3-id" : i+3,
        "atom4-id" : i+4
        })

    bond = create(StaCustom(bond_list))
    atoms = create(StaCustom(atom_list))
    bond.append_updater(AddDihedralAngle(atoms))

    self.assertTrue(np.allclose(
      right_dihedral_angles, convert_to_deg(bond.get_1d_float("dihedral_angle"))))


if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestAddDihedralAngle("test_single_dihedral_angle"))
  suite.addTest(TestAddDihedralAngle("test_sequence_dihedral_angles"))

  runner = unittest.TextTestRunner()
runner.run(suite)