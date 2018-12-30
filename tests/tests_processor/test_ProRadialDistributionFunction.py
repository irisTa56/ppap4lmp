import unittest

import os
import sys

sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from test_utils import check_error_msg

import numpy as np

from random import uniform

from ppap4lmp import (
  create, StaCustom, ProRadialDistributionFunction, execute_omp)

class TestProRadialDistributionFunction(unittest.TestCase):

  def test_error01(self):

    atoms = create(StaCustom([
      {"x": 1.0*i, "y": 1.0*i, "z": 1.0*i}
      for i in range(100)]))
    box = create(StaCustom({"foo": 0.0, "bar": 1.0}))

    pro = ProRadialDistributionFunction(atoms, box)

    check_error_msg(
      self, "RuntimeError: Missing key(s) 'id' in ProRadialDistributionFunction", execute_omp, pro)

  def test_error02(self):

    atoms = create(StaCustom([
      {"id": i+1, "x": 1.0*i, "y": 1.0*i, "z": 1.0*i}
      for i in range(100)]))
    box = create(StaCustom({"foo": 0.0, "bar": 1.0}))

    pro = ProRadialDistributionFunction(atoms, box)

    check_error_msg(
      self, "RuntimeError: Missing key(s) 'hi_x', 'hi_y', 'hi_z', 'lo_x', 'lo_y', 'lo_z' in ProRadialDistributionFunction", execute_omp, pro)

  def test_cubic(self):

    abst_atoms = []
    atom_id = 0

    for ix in range(10):
      for iy in range(10):
        for iz in range(10):

          atom_id += 1

          abst_atoms.append({
            "id": atom_id, "x": 1.0*ix, "y": 1.0*iy, "z": 1.0*iz})

    atoms = create(StaCustom(abst_atoms))

    box = create(StaCustom({
      "lo_x": 0.0, "hi_x": 10.0, "periodic_x": True,
      "lo_y": 0.0, "hi_y": 10.0, "periodic_y": True,
      "lo_z": 0.0, "hi_z": 10.0, "periodic_z": True}))

    pro = ProRadialDistributionFunction(atoms, box)

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

  def test_cubic_bin_from_r_to_r_plus_dr(self):

    abst_atoms = []
    atom_id = 0

    for ix in range(10):
      for iy in range(10):
        for iz in range(10):

          atom_id += 1

          abst_atoms.append({
            "id": atom_id, "x": 1.0*ix, "y": 1.0*iy, "z": 1.0*iz})

    atoms = create(StaCustom(abst_atoms))

    box = create(StaCustom({
      "lo_x": 0.0, "hi_x": 10.0, "periodic_x": True,
      "lo_y": 0.0, "hi_y": 10.0, "periodic_y": True,
      "lo_z": 0.0, "hi_z": 10.0, "periodic_z": True}))

    pro = ProRadialDistributionFunction(atoms, box)

    num_bins = 20
    bin_width = 0.1

    pro.set_bin(bin_width, num_bins)

    pro.bin_from_r_to_r_plus_dr()

    execute_omp(pro)

    self.assertTrue(np.allclose(
      pro.get_r_axis(), np.arange(0.0, num_bins*bin_width, bin_width)))

    expected_rdf = np.zeros(num_bins)

    data = [
      {"index": 10, "num": 6},
      {"index": 14, "num": 12},
      {"index": 17, "num": 8}]

    for d in data:

      r_inner = (d["index"]) * bin_width
      r_outer = (d["index"]+1.0) * bin_width

      dV = (4.0*np.pi/3.0) * (
        np.power(r_outer, 3) - np.power(r_inner, 3))

      expected_rdf[d["index"]] = (d["num"]/dV)/1.0

    self.assertTrue(np.allclose(pro.get_rdf(), expected_rdf))

  def test_cubic_beyond_half_box_length(self):

    abst_atoms = []
    atom_id = 0

    for ix in range(3):
      for iy in range(3):
        for iz in range(3):

          atom_id += 1

          abst_atoms.append({
            "id": atom_id, "x": 1.0*ix, "y": 1.0*iy, "z": 1.0*iz})

    atoms = create(StaCustom(abst_atoms))

    box = create(StaCustom({
      "lo_x": 0.0, "hi_x": 3.0, "periodic_x": True,
      "lo_y": 0.0, "hi_y": 3.0, "periodic_y": True,
      "lo_z": 0.0, "hi_z": 3.0, "periodic_z": True}))

    pro = ProRadialDistributionFunction(atoms, box)

    num_bins = 20
    bin_width = 0.1

    pro.set_bin(bin_width, num_bins)

    pro.beyond_half_box_length()

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

  def test_traj(self):

    atoms_traj = []
    box_traj = []

    for i in range(10):

      abst_atoms = []
      atom_id = 0

      for ix in range(10):
        for iy in range(10):
          for iz in range(10):

            atom_id += 1

            abst_atoms.append({
              "id": atom_id,
              "x": 1.0*(ix+0.5) + uniform(-0.005, 0.005),
              "y": 1.0*(iy+0.5) + uniform(-0.005, 0.005),
              "z": 1.0*(iz+0.5) + uniform(-0.005, 0.005)})

      atoms_traj.append(create(StaCustom(abst_atoms)))

      box_traj.append(create(StaCustom({
        "lo_x": 0.0, "hi_x": 10.0, "periodic_x": True,
        "lo_y": 0.0, "hi_y": 10.0, "periodic_y": True,
        "lo_z": 0.0, "hi_z": 10.0, "periodic_z": True})))

    pro = ProRadialDistributionFunction(list(zip(atoms_traj, box_traj)))

    num_bins = 20
    bin_width = 0.1

    pro.set_bin(bin_width, num_bins)

    execute_omp(pro)

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

    rdf = pro.get_rdf()

    self.assertTrue(np.allclose(rdf, expected_rdf))

    rdf_traj = pro.get_rdf_traj()

    rdf_sum = np.zeros(num_bins)

    for rdf_tmp in rdf_traj:

      self.assertTrue(np.allclose(rdf_tmp, expected_rdf))

      rdf_sum += rdf_tmp

    self.assertTrue(np.allclose(len(rdf_traj) * rdf, rdf_sum))

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestProRadialDistributionFunction("test_error01"))
  suite.addTest(TestProRadialDistributionFunction("test_error02"))
  suite.addTest(TestProRadialDistributionFunction("test_cubic"))
  suite.addTest(TestProRadialDistributionFunction("test_cubic_bin_from_r_to_r_plus_dr"))
  suite.addTest(TestProRadialDistributionFunction("test_cubic_beyond_half_box_length"))
  suite.addTest(TestProRadialDistributionFunction("test_traj"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
