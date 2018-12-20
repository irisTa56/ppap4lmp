import unittest

import os
import sys
sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from error_checker import check_error_msg

import numpy as np

from math import sqrt

from ppap4lmp import create, StaCustom, ProThicknessProfile, execute_omp

class TestProThicknessProfile(unittest.TestCase):

  def test_error01(self):

    atoms = create(StaCustom([
      {"x": 1.0*i, "y": 1.0*i, "z": 1.0*i}
      for i in range(100)]))
    box = create(StaCustom({"foo": 0.0, "bar": 1.0}))

    pro = ProThicknessProfile(atoms, box)

    check_error_msg(
      self, "RuntimeError: Missing key(s) 'radius' in ProThicknessProfile", execute_omp, pro)

  def test_error02(self):

    atoms = create(StaCustom([
      {"x": 1.0*i, "y": 1.0*i, "z": 1.0*i, "radius": 1.0}
      for i in range(100)]))
    box = create(StaCustom({"foo": 0.0, "bar": 1.0}))

    pro = ProThicknessProfile(atoms, box)

    check_error_msg(
      self, "RuntimeError: Missing key(s) 'hi_x', 'hi_y', 'lo_x', 'lo_y' in ProThicknessProfile", execute_omp, pro)

  def test_20x30(self):

    atoms = [
      create(StaCustom([
        {"x": 1.0*ix, "y": 1.0*iy, "z": 1.0*i, "radius": 1.0}
        for ix in range(20) for iy in range(30)]))
      for i in range(10)]
    box = [
      create(StaCustom({
        "lo_x": 0.0, "hi_x": 20.0, "lo_y": 0.0, "hi_y": 30.0}))
      for i in range(10)]

    pro = ProThicknessProfile(list(zip(atoms, box)))
    pro.set_grid(20, 30)

    execute_omp(pro)

    conditions = pro.get_conditions()

    for c in conditions:

      self.assertEqual(c, {
        "origin_x": 0.0,  "origin_y": 0.0,
        "delta_x": 1.0, "delta_y": 1.0, "nx": 20, "ny": 30})

    profiles = pro.get_profiles()

    for i, p in enumerate(profiles):

      self.assertTrue(np.allclose(p, np.full((20, 30), float(i+1))))

  def test_20x30_with_offset(self):

    atoms = [
      create(StaCustom([
        {"x": 1.0*ix-10.0, "y": 1.0*iy, "z": 1.0*i+20.0, "radius": 1.0}
        for ix in range(20) for iy in range(30)]))
      for i in range(10)]
    box = [
      create(StaCustom({
        "lo_x": -10.0, "hi_x": 10.0, "lo_y": 0.0, "hi_y": 30.0}))
      for i in range(10)]

    pro = ProThicknessProfile(list(zip(atoms, box)))
    pro.set_grid(20, 30)
    pro.set_offset(20.0)

    execute_omp(pro)

    conditions = pro.get_conditions()

    for c in conditions:

      self.assertEqual(c, {
        "origin_x": -10.0,  "origin_y": 0.0,
        "delta_x": 1.0, "delta_y": 1.0, "nx": 20, "ny": 30})

    profiles = pro.get_profiles()

    for i, p in enumerate(profiles):

      self.assertTrue(np.allclose(p, np.full((20, 30), float(i+1))))

  def test_20x30_with_shift(self):

    atoms = [
      create(StaCustom([
        {"x": 1.0*ix, "y": 1.0*iy-10.0, "z": 1.0*i, "radius": 1.0}
        for ix in range(20) for iy in range(30)]))
      for i in range(10)]
    box = [
      create(StaCustom({
        "lo_x": 0.0, "hi_x": 20.0, "lo_y": -10.0, "hi_y": 20.0}))
      for i in range(10)]

    pro = ProThicknessProfile(list(zip(atoms, box)))
    pro.set_grid(20, 30)
    pro.shift_half_delta()

    execute_omp(pro)

    conditions = pro.get_conditions()

    for c in conditions:

      self.assertEqual(c, {
        "origin_x": 0.5,  "origin_y": -9.5,
        "delta_x": 1.0, "delta_y": 1.0, "nx": 20, "ny": 30})

    profiles = pro.get_profiles()

    addition = 0.5 * sqrt(2)

    for i, p in enumerate(profiles):

      self.assertTrue(np.allclose(
        p, np.full((20, 30), float(i) + addition)))

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestProThicknessProfile("test_error01"))
  suite.addTest(TestProThicknessProfile("test_error02"))
  suite.addTest(TestProThicknessProfile("test_20x30"))
  suite.addTest(TestProThicknessProfile("test_20x30_with_offset"))
  suite.addTest(TestProThicknessProfile("test_20x30_with_shift"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
