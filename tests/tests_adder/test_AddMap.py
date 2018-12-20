import unittest

import os
import sys
sys.path.append(
  os.path.join(os.path.dirname(os.path.realpath(__file__)), ".."))
from error_checker import check_error_msg

from ppap4lmp import create, StaCustom, AddMap

class TestAddMap(unittest.TestCase):

  def test_error01(self):

    elem = create(StaCustom({"foo": 0, "bar": 1}))
    elem.append_updater(AddMap("dummy", "new", {1: 0}))

    check_error_msg(
      self, "RuntimeError: Missing key(s) 'dummy' in AddMap", elem.get_data)

  def test_error02(self):

    elem = create(StaCustom({"foo": 0, "bar": 1}))
    elem.append_updater(AddMap("foo", "bar", {0: 1}))

    check_error_msg(
      self, "RuntimeError: Key 'bar' already exists", elem.get_data)

  def test_nonarray(self):

    data_old = {"A": 1, "B": 2}
    data_new = {"A": 1, "B": 2, "C": 3}

    elem = create(StaCustom(data_old))
    elem.append_updater(AddMap("A", "C", {1: 3, 2: 2, 3: 1}))

    self.assertEqual(data_new, elem.get_data())
    self.assertEqual({"A", "B", "C"}, elem.get_keys())

  def test_array(self):

    data_old = [{"A": i, "B": i*i} for i in range(1000)]
    data_new = [{"A": i, "B": i*i, "C": i%3} for i in range(1000)]

    mapping = {i: i%3 for i in range(1000)}

    elem = create(StaCustom(data_old))
    elem.append_updater(AddMap("A", "C", mapping))

    self.assertEqual(data_new, elem.get_data())
    self.assertEqual({"A", "B", "C"}, elem.get_keys())

  def test_overwrite(self):

    data_old = [{"A": i, "B": i*i} for i in range(1000)]
    data_new = [{"A": i, "B": i%3} for i in range(1000)]

    mapping = {i: i%3 for i in range(1000)}

    elem = create(StaCustom(data_old))
    elem.append_updater(AddMap("A", "B", mapping).overwrite())

    self.assertEqual(data_new, elem.get_data())
    self.assertEqual({"A", "B"}, elem.get_keys())

if __name__ == "__main__":

  suite = unittest.TestSuite()

  suite.addTest(TestAddMap("test_error01"))
  suite.addTest(TestAddMap("test_error02"))
  suite.addTest(TestAddMap("test_nonarray"))
  suite.addTest(TestAddMap("test_array"))
  suite.addTest(TestAddMap("test_overwrite"))

  runner = unittest.TextTestRunner()
  runner.run(suite)
