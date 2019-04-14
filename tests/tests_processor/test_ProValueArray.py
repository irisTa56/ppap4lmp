import unittest

import os
import sys

sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from test_utils import TestCasePPAP

from random import shuffle

from ppap4lmp import create, StaCustom, ProValueArray, execute_omp

class TestProValueArray(TestCasePPAP):

  def test_error01(self):

    elems = [
      create(StaCustom({"id": i, "A": i*i})) for i in range(1000)]

    pro = ProValueArray(elems)

    self.check_error_msg(
      "RuntimeError: No selected value(s) for ProValueArray", execute_omp, pro)

  def test_error02(self):

    elems = [
      create(StaCustom({"id": i, "A": i*i})) for i in range(1000)]

    pro = ProValueArray(elems)
    pro.select("B")

    self.check_error_msg(
      "RuntimeError: Missing key(s) 'B' in ProValueArray", execute_omp, pro)

  def test_error03(self):

    data = [
      [{"id": j, "A": float(i*j)} for j in range(10*i+1)]
      for i in range(100)]
    elems = [create(StaCustom(d)) for d in data]
    pro = ProValueArray(elems)
    pro.select("A")

    self.check_error_msg(
      "RuntimeError: Length of trajectories must be the same", execute_omp, pro)

  def test_select_one(self):

    data = [[
      {"id": j, "A": float(i+j), "B": float(i*j)}
      for j in range(1000)]
      for i in range(100)]
    elems = [create(StaCustom(d)) for d in data]
    pro = ProValueArray(elems)
    pro.select("A")

    execute_omp(pro)

    arr_A = pro.get_results()["A"]

    for i, elem in enumerate(elems):

      ds = elem.get_data()

      for d in ds:
        self.assertEqual(arr_A[i][d["id"]], d["A"])

  def test_select_two(self):

    ids = list(range(1000))
    shuffle(ids)

    data = [[
      {"id": j, "A": float(i+j), "B": float(i*j)}
      for j in ids]
      for i in range(100)]
    elems = [create(StaCustom(d)) for d in data]

    pro = ProValueArray(elems)
    pro.select("A", "B")

    execute_omp(pro)

    arrs = pro.get_results()

    for i, elem in enumerate(elems):

      ds = elem.get_data()

      for d in ds:
        self.assertEqual(arrs["A"][i][d["id"]], d["A"])
        self.assertEqual(arrs["B"][i][d["id"]], d["B"])

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestProValueArray("test_error01"))
  suite.addTest(TestProValueArray("test_error02"))
  suite.addTest(TestProValueArray("test_error03"))
  suite.addTest(TestProValueArray("test_select_one"))
  suite.addTest(TestProValueArray("test_select_two"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
