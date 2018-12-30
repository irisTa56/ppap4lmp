import unittest

import os
import sys
sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from test_utils import check_error_msg

import numpy as np

from random import randrange

from ppap4lmp import \
  create, StaCustom, StaDumpAtoms, StaMolecules, StaBeads, \
  AddMap, AddBondLength

def get_random_unit_vector():
  while True:
    x = np.random.randn(3)  # standard normal distribution
    r = np.linalg.norm(x)
    if r != 0.:
      return x/r

class TestAddBondLength(unittest.TestCase):

  def test01(self):
    bond_o2_in_py = 121.0
    bond_in_py = [
      {"atom1-id" : 1,"atom2-id" :2}

    ]
    atoms_in_py = [
      {"id" : 1 ,"xu" : 0.0, "yu" : 0.0 ,"zu" :0.0},
      {"id" : 2 ,"xu" : 0.0, "yu" : 0.0, "zu" :121.0},
    ]
    bond = create(StaCustom(bond_in_py))
    atoms = create(StaCustom(atoms_in_py))
    bond.append_updater(AddBondLength(atoms))
    self.assertTrue(bond_o2_in_py == bond.get_data()[0]["length"])

  def test02(self):
    bond_lengths = np.random.uniform(0.5, 1.5,2)
    lo = -100.0
    hi = 100.0
    bond_list = []
    atom_list = [
      {"id" : 1,
       "xu" : np.random.uniform(lo, hi) ,
       "yu" : np.random.uniform(lo, hi) ,
       "zu" : np.random.uniform(lo, hi),}

      ]
    for i , length in enumerate(bond_lengths):
      vec = get_random_unit_vector()
      atom_list.append({
      "id" : i+2,
       "xu" :atom_list[i]["xu"] + length * vec[0],
       "yu" :atom_list[i]["yu"] + length * vec[1],
       "zu" :atom_list[i]["zu"] + length * vec[2],
        }
      )
      bond_list.append({
        "id" : i+1 ,
        "atom1-id" : i+1 ,
        "atom2-id" : i+2,}
        )

    bond = create(StaCustom(bond_list))
    atoms = create(StaCustom(atom_list))
    bond.append_updater(AddBondLength(atoms))
    print(bond_lengths)
    print(bond.get_1d_float("length"))
    self.assertTrue(np.allclose(bond_lengths, bond.get_1d_float("length")))






if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestAddBondLength("test02"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
