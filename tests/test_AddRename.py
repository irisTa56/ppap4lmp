import unittest
import traceback

import numpy as np

from ppap4lmp import create, StaCustom, AddRename

class TestAddRename(unittest.TestCase):

  def test_error01(self):

    elem = create(StaCustom({"foo": 0, "bar": 1}))
    elem.append_updater(AddRename("dummy", "new"))

    try:
      elem.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: AddRename needs 'dummy'")

  def test_error02(self):

    elem = create(StaCustom({"foo": 0, "bar": 1}))
    elem.append_updater(AddRename("foo", "bar"))

    try:
      elem.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: AddRename cannot overwrite 'bar'")

  def test_error03(self):

    elem = create(StaCustom({"foo": 0, "bar": 1}))
    elem.append_updater(AddRename("foo", "id"))

    try:
      elem.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: Adder cannot add 'id'")

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