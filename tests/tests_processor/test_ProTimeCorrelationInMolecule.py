import unittest
import traceback

from copy import deepcopy
from random import uniform

import numpy as np

from ppap4lmp import \
  create, StaCustom, StaMolecules, ProTimeCorrelationInMolecule, execute_omp

class TestProTimeCorrelationInMolecule(unittest.TestCase):

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

    atomses = [create(StaCustom(dummy_data)) for i in range(10)]
    molses = [create(StaMolecules(atoms)) for atoms in atomses]

    pro = ProTimeCorrelationInMolecule(list(zip(molses, atomses)))

    try:
      execute_omp(pro)
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: Missing key(s) 'xu'")

  def test_error02(self):

    atomses = [create(StaCustom(self.base_data)) for i in range(10)]
    molses = [create(StaCustom([{"id": 1}])) for i in range(10)]

    pro = ProTimeCorrelationInMolecule(list(zip(molses, atomses)))

    try:
      execute_omp(pro)
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: Missing key(s) 'atom-ids'")

  def test_error03(self):

    atoms_traj = []
    base_atoms = deepcopy(self.base_data)

    for i in range(2, 12):

      atoms_tmp = []

      for j in range(1, i):

        for k, atom in enumerate(base_atoms):
          atom["id"] = (j-1) * len(base_atoms) + k + 1
          atom["mol"] = j

        atoms_tmp.extend(deepcopy(base_atoms))

      atoms_traj.append(create(StaCustom(atoms_tmp)))

    mols_traj = [create(StaMolecules(atoms)) for atoms in atoms_traj]

    pro = ProTimeCorrelationInMolecule(list(zip(mols_traj, atoms_traj)))

    try:
      execute_omp(pro)
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: Number of molecules and molecular types must "
        + "be unchanged")

  def test_rotate_stick(self):

    n_mols = 10

    rotate_data = []
    initial_atoms = []

    for imol in range(n_mols):

      ps = np.random.uniform(-10.0, 10.0, (3,3))

      m_point = 0.5 * (ps[0] + ps[1])

      cross = np.cross(ps[1] - ps[0], ps[2] - ps[0])
      n_vector = cross / np.linalg.norm(cross)

      rotate_data.append({"normal": n_vector, "middle": m_point})

      initial_atoms.extend([
        {"id": 2*imol+i+1, "mol": imol+1, "xyz": ps[i]}
        for i in range(2)
      ])

    atoms_traj = []

    for i in range(181):

      atoms_tmp = deepcopy(initial_atoms)

      for atom in atoms_tmp:

        m = rotate_data[atom["mol"]-1]["middle"]
        n = rotate_data[atom["mol"]-1]["normal"]

        rotated_xyz = np.array(rot(i, n, atom["xyz"]-m)) + m

        atom["xu"] = rotated_xyz[0]
        atom["yu"] = rotated_xyz[1]
        atom["zu"] = rotated_xyz[2]

        del atom["xyz"]

      atoms_traj.append(create(StaCustom(atoms_tmp)))

    mols_traj = [create(StaMolecules(atoms)) for atoms in atoms_traj]

    pro = ProTimeCorrelationInMolecule(list(zip(mols_traj, atoms_traj)))
    pro.set_indices(0, 1)

    execute_omp(pro)

    expects = np.array([np.cos(i*np.pi/180) for i in range(181)])

    self.assertTrue(np.allclose(pro.get_time_correlation(), expects))


# Functions to rotate a vector via quaternian

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

  c = np.cos(deg*np.pi/360)
  s = np.sin(deg*np.pi/360)

  q1 = [n[0]*s, n[1]*s, n[2]*s, c]
  q2 = list(v) + [0.0]

  return q_mult(q_mult(q1, q2), q_conjugate(q1))[:3]