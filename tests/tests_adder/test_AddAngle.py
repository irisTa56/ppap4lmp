import unittest

import os
import sys
sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from error_checker import check_error_msg

import numpy as np

from random import randrange

from ppap4lmp import \
  create, StaCustom, StaDumpAtoms, StaMolecules, StaBeads, \
  AddMap, AddAngle

def get_random_unit_vector():
  while True:
    x = np.random.randn(3)  # standard normal distribution
    r = np.linalg.norm(x)
    if r != 0.:
      return x/r

def q_mult(q1, q2):

  x1, y1, z1, w1 = q1
  x2, y2, z2, w2 = q2

  w = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2
  x = w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2
  y = w1 * y2 + y1 * w2 + z1 * x2 - x1 * z2
  z = w1 * z2 + z1 * w2 + x1 * y2 - y1 * x2

  return x, y, z ,w

def q_conjugate(q):

  x, y, z ,w = q

  return -x, -y, -z, w

def rot(deg, n, v):

  c = np.cos(deg)
  s = np.sin(deg)

  q1 = [n[0]*s, n[1]*s, n[2]*s, c]
  q2 = list(v) + [0.0]

  return q_mult(q_mult(q1, q2), q_conjugate(q1))[:3]

class TestAddAngle(unittest.TestCase):

  def test01(self):
    angle_right_in_py = 45/180*np.pi
    angle_in_py = [
      {"id": 1, "atom1-id" : 1,"atom2-id" :2,"atom3-id" :3}

    ]
    atoms_in_py = [
      {"id" : 1 ,"xu" : 1.0, "yu" : 1.0 ,"zu" :0.0},
      {"id" : 2 ,"xu" : 1.0, "yu" : 0.0, "zu" :0.0},
      {"id" : 3 ,"xu" : 1.0, "yu" : 1.0, "zu" :1.0}
    ]
    angle = create(StaCustom(angle_in_py))
    atoms = create(StaCustom(atoms_in_py))
    angle.append_updater(AddAngle(atoms))
    #print(angle_right_in_py)
    #print(angle.get_data()[0]["angle"])

    if abs(angle_right_in_py-
      angle.get_data()[0]["angle"])<0.0000000001:
      T = True
    else:
      T =False

    self.assertTrue(T)

  def test02(self):
    angles = np.random.uniform(0.0,np.pi,6)

    lo = -100.0
    hi = 100.0

    bond_angle_list = []

    atom_list = [{
      "id" : 1,
      "xu" : np.random.uniform(lo, hi),
      "yu" : np.random.uniform(lo, hi),
      "zu" : np.random.uniform(lo, hi)
    }]#Set the position of the first atom

    vec_test = get_random_unit_vector()
    length = np.random.uniform(0.8, 1.2)
    atom_list.append({
      "id" : 2,
      "xu" : atom_list[0]["xu"] + length * vec_test[0],
      "yu" : atom_list[0]["yu"] + length * vec_test[1],
      "zu" : atom_list[0]["zu"] + length * vec_test[2]
    })#Set the position of the second atom

    for i , angle in enumerate(angles):
      vec1 = [
        atom_list[i]["xu"] - atom_list[i+1]["xu"],
        atom_list[i]["yu"] - atom_list[i+1]["yu"],
        atom_list[i]["zu"] - atom_list[i+1]["zu"]]
        #the vector of the 1st and 2nd atoms

      vec_test2 = get_random_unit_vector()
      length2 = np.random.uniform(0.8, 1.2)
      atom_list_test=[{
        "id" : i,
        "xu" : atom_list[i+1]["xu"] + length2 * vec_test2[0],
        "yu" : atom_list[i+1]["yu"] + length2 * vec_test2[1],
        "zu" : atom_list[i+1]["zu"] + length2 * vec_test2[2]
      }]#Set the position of the temporary third atom

      vec2 = [
        atom_list_test[0]["xu"] - atom_list[i+1]["xu"],
        atom_list_test[0]["yu"] - atom_list[i+1]["yu"],
        atom_list_test[0]["zu"] - atom_list[i+1]["zu"]]
        #the vector of the 2nd and 3rd atoms

      n_vec = np.cross(vec1,vec2)
      #the Normal vector of vec1 and vec2

      angle_first =np.arccos(
      (vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2])/(
      np.sqrt(vec1[0] * vec1[0] + vec1[1] * vec1[1] + vec1[2] * vec1[2])*
      np.sqrt(vec2[0] * vec2[0] + vec2[1] * vec2[1] + vec2[2] * vec2[2])
      ))#the angle of vec1 and vec2

      vec3 = rot((angle_first-angle), n_vec, vec2)
      #Rotate vector 2

      angle_rot = np.arccos(
      (vec3[0] * vec2[0] + vec3[1] * vec2[1] + vec3[2] * vec2[2])/(
      np.sqrt(vec3[0] * vec3[0] + vec3[1] * vec3[1] + vec3[2] * vec3[2])*
      np.sqrt(vec2[0] * vec2[0] + vec2[1] * vec2[1] + vec2[2] * vec2[2])
      ))
      #the rotation angle of vec2
      #print(angle_first,angle_rot,angle)
      #to see the angle of vec1 and vec2,
      #the rotation angle of vec2
      #and the true angle

      atom_list.append({
        "id" : i+3,
        "xu" : vec3[0] + atom_list[i+1]["xu"],
        "yu" : vec3[1] + atom_list[i+1]["yu"],
        "zu" : vec3[2] + atom_list[i+1]["zu"]
      })#Set the position of the right third atom

      bond_angle_list.append({
        "id" : i+1 ,
        "atom1-id" : i+1,
        "atom2-id" : i+2,
        "atom3-id" : i+3}
        )

    bond = create(StaCustom(bond_angle_list))
    atoms = create(StaCustom(atom_list))
    bond.append_updater(AddAngle(atoms))

    #print(angles)
    #print(bond.get_1d_float("angle"))

    self.assertTrue(np.allclose(angles, bond.get_1d_float("angle")))





if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestAddAngle("test02"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
