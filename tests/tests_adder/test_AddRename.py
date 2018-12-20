import unittest

import os
import sys
sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from error_checker import check_error_msg

import numpy as np

from ppap4lmp import create, StaCustom, AddRename

class TestAddRename(unittest.TestCase):

  def test_error01(self):

    elem = create(StaCustom({"foo": 0, "bar": 1}))
    elem.append_updater(AddRename("dummy", "new"))

    check_error_msg(
      self, "RuntimeError: Missing key(s) 'dummy' in AddRename", elem.get_data)

  def test_error02(self):

    elem = create(StaCustom({"foo": 0, "bar": 1}))
    elem.append_updater(AddRename("foo", "bar"))

    check_error_msg(
      self, "RuntimeError: Key 'bar' already exists", elem.get_data)

  def test_error03(self):

    elem = create(StaCustom({"foo": 0, "bar": 1}))
    elem.append_updater(AddRename("foo", "id"))

    check_error_msg(
      self, "RuntimeError: Adder cannot add 'id'", elem.get_data)

  def test_nonarray(self):

    data_old = {"A": 1, "B": 2}
    data_new = {"B": 2, "C": 1}

    elem = create(StaCustom(data_old))
    elem.append_updater(AddRename("A", "C"))

    self.assertEqual(data_new, elem.get_data())
    self.assertEqual({"B", "C"}, elem.get_keys())

  def test_array(self):

    elem = create(StaCustom([{"A": i, "B": i*i} for i in range(1000)]))
    vec_old = elem.get_1d_int("A")

    elem.append_updater(AddRename("B", "C"))
    elem.append_updater(AddRename("A", "B"))
    vec_new = elem.get_1d_int("B")

    self.assertTrue(np.allclose(vec_old, vec_new))
    self.assertEqual({"B", "C"}, elem.get_keys())

  def test_overwrite(self):

    data_old = [{"A": i, "B": i*i, "C": i%3} for i in range(1000)]
    data_new = [{"A": i, "B": i%3} for i in range(1000)]

    elem = create(StaCustom(data_old))
    elem.append_updater(AddRename("C", "B").overwrite())

    self.assertEqual(data_new, elem.get_data())
    self.assertEqual({"A", "B"}, elem.get_keys())

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestAddRename("test_error01"))
  suite.addTest(TestAddRename("test_error02"))
  suite.addTest(TestAddRename("test_error03"))
  suite.addTest(TestAddRename("test_nonarray"))
  suite.addTest(TestAddRename("test_array"))
  suite.addTest(TestAddRename("test_overwrite"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
