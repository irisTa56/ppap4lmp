import unittest

import os
import sys

sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from test_utils import TestCasePPAP

import numpy as np

from scipy.stats import special_ortho_group

from random import uniform

from ppap4lmp import (
  create, StaCustom, StaMolecules, StaDumpAtoms, StaDumpBox, StaBeads,
  AddCoMPosition, AddWrappedPosition, AddInertiaMoment, execute_omp,
  ProRadialDistributionFunctionWithDeformation,
  ProRadialDistributionFunction)

ProRDFWD = ProRadialDistributionFunctionWithDeformation
ProRDF = ProRadialDistributionFunction

class TestProRadialDistributionFunctionWithDeformation(TestCasePPAP):

  def create_rotated_abst_atoms_in_mol(
    self, size, id_start, mol, shift_x, shift_y, shift_z):

    initial = np.array([
      [size, 0.0, 0.0], [-size, 0.0, 0.0],
      [0.0, size, 0.0], [0.0, -size, 0.0],
      [0.0, 0.0, size], [0.0, 0.0, -size]])

    # create a random rotation matrix
    rot_mat = special_ortho_group.rvs(3)

    # rotate
    rotated = np.dot(rot_mat, initial.T).T

    return [{
      "id": id_start+i, "mol": mol, "mass": 12.011,
      "xu": rotated[i,0] + shift_x,
      "yu": rotated[i,1] + shift_y,
      "zu": rotated[i,2] + shift_z} for i in range(6)]

  def test_error01(self):

    atoms = create(StaCustom([
      {"x": 1.0*i, "y": 1.0*i, "z": 1.0*i}
      for i in range(100)]))
    box = create(StaCustom({"foo": 0.0, "bar": 1.0}))

    pro = ProRDFWD(atoms, box)

    self.check_error_msg(
      "RuntimeError: Missing key(s) 'I_xx', 'I_xy', 'I_xz', 'I_yy', 'I_yz', 'I_zz', 'id', 'mass' in ProRadialDistributionFunctionWithDeformation", execute_omp, pro)

  def test_cubic_isotropic(self):

    abst_atoms = []
    mol_id = 0

    for ix in range(10):
      for iy in range(10):
        for iz in range(10):

          mol_id += 1

          abst_atoms.extend(
            self.create_rotated_abst_atoms_in_mol(
              uniform(-0.5, 0.5), 6*(mol_id-1)+1, mol_id,
              1.0*ix, 1.0*iy, 1.0*iz))

    atoms = create(StaCustom(abst_atoms))

    mols = create(StaMolecules(atoms))
    mols.append_updater(AddCoMPosition(atoms))
    mols.append_updater(AddInertiaMoment(atoms))

    box = create(StaCustom({
      "lo_x": 0.0, "hi_x": 10.0, "pbc_x": True,
      "lo_y": 0.0, "hi_y": 10.0, "pbc_y": True,
      "lo_z": 0.0, "hi_z": 10.0, "pbc_z": True}))

    mols.append_updater(AddWrappedPosition(box))

    pro = ProRDFWD(mols, box)

    num_bins = 20
    bin_width = 0.1

    pro.set_bin(bin_width, num_bins)

    execute_omp(pro)

    self.assertTrue(np.allclose(
      pro.get_r_axis(), np.arange(0.0, num_bins*bin_width, bin_width)))

    expected_rdf = np.zeros(num_bins)

    data = [
      {"index": 10, "num": 6},
      {"index": 14, "num": 12},
      {"index": 17, "num": 8}]

    for d in data:

      r_inner = (d["index"]-0.5) * bin_width
      r_outer = (d["index"]+0.5) * bin_width

      dV = (4.0*np.pi/3.0) * (
        np.power(r_outer, 3) - np.power(r_inner, 3))

      expected_rdf[d["index"]] = (d["num"]/dV)/1.0

    self.assertTrue(np.allclose(pro.get_rdf(), expected_rdf))

  def test_cubic_same_size(self):

    abst_atoms = []
    mol_id = 0

    for ix in range(10):
      for iy in range(10):
        for iz in range(10):

          mol_id += 1

          abst_atoms.extend(
            self.create_rotated_abst_atoms_in_mol(
              3.14, 6*(mol_id-1)+1, mol_id,
              1.0*ix, 1.0*iy, 1.0*iz))

    atoms = create(StaCustom(abst_atoms))

    mols = create(StaMolecules(atoms))
    mols.append_updater(AddCoMPosition(atoms))
    mols.append_updater(AddInertiaMoment(atoms))

    box = create(StaCustom({
      "lo_x": 0.0, "hi_x": 10.0, "pbc_x": True,
      "lo_y": 0.0, "hi_y": 10.0, "pbc_y": True,
      "lo_z": 0.0, "hi_z": 10.0, "pbc_z": True}))

    mols.append_updater(AddWrappedPosition(box))

    pro = ProRDFWD(mols, box)

    num_bins = 20
    bin_width = 0.1

    pro.set_bin(bin_width, num_bins)

    execute_omp(pro)

    self.assertTrue(np.allclose(
      pro.get_r_axis(), np.arange(0.0, num_bins*bin_width, bin_width)))

    expected_rdf = np.zeros(num_bins)
    expected_Rg2 = np.zeros(num_bins)

    data = [
      {"index": 10, "num": 6},
      {"index": 14, "num": 12},
      {"index": 17, "num": 8}]

    for d in data:

      r_inner = (d["index"]-0.5) * bin_width
      r_outer = (d["index"]+0.5) * bin_width

      dV = (4.0*np.pi/3.0) * (
        np.power(r_outer, 3) - np.power(r_inner, 3))

      expected_rdf[d["index"]] = (d["num"]/dV)/1.0
      expected_Rg2[d["index"]] = 3.14*3.14

    self.assertTrue(np.allclose(pro.get_rdf(), expected_rdf))

    Rg2s = pro.get_squared_gyration_radius()

    self.assertTrue(np.allclose(Rg2s["isotropic"], expected_Rg2))
    self.assertTrue(np.allclose(Rg2s["parallel"], expected_Rg2))
    self.assertTrue(np.allclose(Rg2s["perpendicular"], expected_Rg2))

  def test_with_and_without_modification(self):

    n_traj = 100
    n_mols = 100

    abst_atoms_traj = []
    mol_id = 0

    for i in range(n_traj):

      abst_atoms = []
      mol_id = 0

      for i in range(n_mols):

        mol_id += 1

        abst_atoms.extend(
          self.create_rotated_abst_atoms_in_mol(
            uniform(-1.0, 1.0), 6*(mol_id-1)+1, mol_id,
            uniform(-50.0, 50.0),
            uniform(-50.0, 50.0),
            uniform(-50.0, 50.0)))

      abst_atoms_traj.append(abst_atoms)

    atomses = [
      create(StaCustom(abst_atoms)) for abst_atoms in abst_atoms_traj]

    boxes = [
      create(StaCustom({
        "lo_x": 0.0, "hi_x": 10.0, "pbc_x": True,
        "lo_y": 0.0, "hi_y": 10.0, "pbc_y": True,
        "lo_z": 0.0, "hi_z": 10.0, "pbc_z": True
      })) for i in range(n_traj)]

    molses = [
      create(StaMolecules(atoms))
        .append_updater(AddCoMPosition(atoms))
        .append_updater(AddInertiaMoment(atoms))
        .append_updater(AddWrappedPosition(box))
      for atoms, box in zip(atomses, boxes)]

    pro_with_modify = ProRDFWD(list(zip(molses, boxes)))
    pro_without_modify = ProRDF(list(zip(molses, boxes)))

    num_bins = 20
    bin_width = 0.1

    pro_with_modify.set_bin(bin_width, num_bins)
    pro_without_modify.set_bin(bin_width, num_bins)

    execute_omp([pro_with_modify, pro_without_modify])

    self.assertTrue(np.allclose(
      pro_with_modify.get_rdf(), pro_without_modify.get_rdf()))
    self.assertTrue(np.allclose(
      np.array(pro_with_modify.get_rdf_traj()),
      np.array(pro_without_modify.get_rdf_traj())))

  def test_for_beads(self):

    n_samples = 50
    interval = 1000

    atomses = [create(
      StaDumpAtoms("dumps_atom/atom.{}.dump".format(i), i))
      for i in range(0, n_samples*interval+1, interval)]
    boxes = [create(
      StaDumpBox("dumps_atom/atom.{}.dump".format(i), i))
      for i in range(0, n_samples*interval+1, interval)]
    molses = [create(StaMolecules(atoms)) for atoms in atomses]

    mappings = [
      [0, 1, 2, 12, 13, 14, 15, 16, 17, 18],
      [3, 4, 5, 19, 20, 21, 22, 23, 24],
      [6, 7, 8, 25, 26, 27, 28, 29, 30],
      [9, 10, 11, 31, 32, 33, 34, 35, 36, 37]]

    abst_beads = [
      {"type": 1, "indices-in-mol": mapping} for mapping in mappings]

    beadses = [create(StaBeads(mols, abst_beads))
        .append_updater(AddCoMPosition(atoms))
        .append_updater(AddInertiaMoment(atoms))
        .append_updater(AddWrappedPosition(box))
      for atoms, box, mols in zip(atomses, boxes, molses)]

    pro = ProRDFWD(list(zip(beadses, boxes)))

    num_bins = 150
    bin_width = 0.1

    pro.set_bin(bin_width, num_bins)
    pro.set_margin(2.0)

    execute_omp(pro)

    Rg2s = pro.get_squared_gyration_radius()

    self.assertTrue(np.allclose(
      Rg2s["isotropic"],
      (1/3)*Rg2s["parallel"] + (2/3)*Rg2s["perpendicular"]))

    Rg2s_traj = pro.get_squared_gyration_radius_traj()

    self.assertTrue(np.allclose(
      np.array(Rg2s_traj["isotropic"]),
      (1/3)*np.array(Rg2s_traj["parallel"])
        + (2/3)*np.array(Rg2s_traj["perpendicular"])))

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestProRadialDistributionFunctionWithDeformation("test_error01"))
  suite.addTest(TestProRadialDistributionFunctionWithDeformation("test_cubic_isotropic"))
  suite.addTest(TestProRadialDistributionFunctionWithDeformation("test_cubic_same_size"))
  suite.addTest(TestProRadialDistributionFunctionWithDeformation("test_with_and_without_modification"))
  suite.addTest(TestProRadialDistributionFunctionWithDeformation("test_for_beads"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
