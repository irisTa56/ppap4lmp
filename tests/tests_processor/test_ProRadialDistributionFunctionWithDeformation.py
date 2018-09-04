import unittest
import traceback
import math

import numpy as np

from scipy.stats import special_ortho_group

from random import uniform

from ppap4lmp import create, StaCustom, StaMolecules, \
  AddCoMPosition, AddWrappedPosition, AddInertiaMoment, InvOMP, \
  ProRadialDistributionFunctionWithDeformation, \
  ProRadialDistributionFunction

ProRDFWD = ProRadialDistributionFunctionWithDeformation
ProRDF = ProRadialDistributionFunction

class TestProRadialDistributionFunctionWithDeformation(unittest.TestCase):

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

    try:
      InvOMP(pro).execute()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: Missing key(s) 'I_xx', 'I_xy', 'I_xz', 'I_yy', "
        + "'I_yz', 'I_zz', 'id', 'mass'")

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
      "lo_x": 0.0, "hi_x": 10.0, "periodic_x": True,
      "lo_y": 0.0, "hi_y": 10.0, "periodic_y": True,
      "lo_z": 0.0, "hi_z": 10.0, "periodic_z": True}))

    mols.append_updater(AddWrappedPosition(box))

    pro = ProRDFWD(mols, box)

    num_bins = 20
    bin_width = 0.1

    pro.set_bin(bin_width, num_bins)

    InvOMP(pro).execute()

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

      dV = (4.0*math.pi/3.0) * (
        math.pow(r_outer, 3) - math.pow(r_inner, 3))

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
      "lo_x": 0.0, "hi_x": 10.0, "periodic_x": True,
      "lo_y": 0.0, "hi_y": 10.0, "periodic_y": True,
      "lo_z": 0.0, "hi_z": 10.0, "periodic_z": True}))

    mols.append_updater(AddWrappedPosition(box))

    pro = ProRDFWD(mols, box)

    num_bins = 20
    bin_width = 0.1

    pro.set_bin(bin_width, num_bins)

    InvOMP(pro).execute()

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

      dV = (4.0*math.pi/3.0) * (
        math.pow(r_outer, 3) - math.pow(r_inner, 3))

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
        "lo_x": 0.0, "hi_x": 10.0, "periodic_x": True,
        "lo_y": 0.0, "hi_y": 10.0, "periodic_y": True,
        "lo_z": 0.0, "hi_z": 10.0, "periodic_z": True
      })) for i in range(n_traj)]

    molses = [
      create(StaMolecules(atoms))
        .append_updater(AddCoMPosition(atoms))
        .append_updater(AddInertiaMoment(atoms))
        .append_updater(AddWrappedPosition(box))
      for atoms, box in zip(atomses, boxes)]

    pro_with_modify = ProRDFWD(list(zip(molses, boxes)))
    pro_without_modify = ProRDF(list(zip(molses, boxes)))

    InvOMP([pro_with_modify, pro_without_modify]).execute()

    self.assertTrue(np.allclose(
      pro_with_modify.get_rdf(), pro_without_modify.get_rdf()))
    self.assertTrue(np.allclose(
      np.array(pro_with_modify.get_rdf_traj()),
      np.array(pro_without_modify.get_rdf_traj())))

  def test_for_beads(self):
    pass
