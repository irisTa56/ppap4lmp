import unittest
import traceback

from ppap4lmp import Element, StaCustom, AddMap

class TestAddMap(unittest.TestCase):

  def test_error(self):

    elem = Element(StaCustom({"foo": 0, "var": 1}))
    elem.append_updater(AddMap("dummy", "new", {1: 0}))

    try:
      elem.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: AddMap needs 'dummy'")

    elem = Element(StaCustom({"foo": 0, "var": 1}))
    elem.append_updater(AddMap("foo", "var", {0: 1}))

    try:
      elem.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: AddMap cannot overwrite 'var'")

  def test_nonarray(self):

    data_old = {"A": 1, "B": 2}
    data_new = {"A": 1, "B": 2, "C": 3}

    elem = Element(StaCustom(data_old))
    elem.append_updater(AddMap("A", "C", {1: 3, 2: 2, 3: 1}))

    self.assertEqual(data_new, elem.get_data())
    self.assertEqual({"A", "B", "C"}, elem.get_keys())

  def test_array(self):

    data_old = [{"A": i, "B": i*i} for i in range(1000)]
    data_new = [{"A": i, "B": i*i, "C": i%3} for i in range(1000)]

    mapping = {i: i%3 for i in range(1000)}

    elem = Element(StaCustom(data_old))
    elem.append_updater(AddMap("A", "C", mapping))

    self.assertEqual(data_new, elem.get_data())
    self.assertEqual({"A", "B", "C"}, elem.get_keys())