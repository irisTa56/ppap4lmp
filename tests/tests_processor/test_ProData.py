import unittest

import os
import sys

sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from test_utils import TestCasePPAP

from ppap4lmp import create, StaCustom, ProData, execute_omp

class TestProData(TestCasePPAP):

  def test_error01(self):

    elems = [
      create(StaCustom({"A": i, "B": i*i})) for i in range(1000)]
    pro = ProData(elems)
    pro.select("C")

    self.check_error_msg(
      "RuntimeError: Missing key(s) 'C' in ProData", execute_omp, pro)

  def test_without_select(self):

    data = [{"A": i, "B": i*i} for i in range(1000)]
    elems = [create(StaCustom(d)) for d in data]

    pro = ProData(elems)

    execute_omp(pro)

    self.assertEqual(pro.get_results(), data)

    data = [
      [{"A": j, "B": i*j} for j in range(100)]
      for i in range(100)]
    elems = [create(StaCustom(d)) for d in data]

    pro = ProData(elems)

    execute_omp(pro)

    self.assertEqual(pro.get_results(), data)

  def test_with_select(self):

    data = [{"A": i, "B": i*i} for i in range(1000)]
    data2 = [{"A": i, "B": i*i, "C": i*i*i} for i in range(1000)]
    elems = [create(StaCustom(
      {"A": d["A"], "B": d["B"], "C": d["A"] + d["B"]})) for d in data]

    pro = ProData(elems)
    pro.select("A", "B")

    execute_omp(pro)

    self.assertEqual(pro.get_results(), data)

    data = [
      [{"A": j, "B": i*j} for j in range(100)]
      for i in range(100)]
    data2 = [
      [{"A": j, "B": i*j, "C": i+j} for j in range(100)]
      for i in range(100)]
    elems = [create(StaCustom(d)) for d in data]

    pro = ProData(elems)
    pro.select("A", "B")

    execute_omp(pro)

    self.assertEqual(pro.get_results(), data)

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestProData("test_error01"))
  suite.addTest(TestProData("test_without_select"))
  suite.addTest(TestProData("test_with_select"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
