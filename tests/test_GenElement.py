import unittest

import numpy as np

from random import randrange

from ppap4lmp import GenElement, StaDumpAtoms, AddMap, FilSet

class TestGenElement(unittest.TestCase):

  def __init__(self, *args, **kwargs):

    super().__init__(*args, **kwargs)

    self.args = ("tests/dumps_bead/bead.2990000.dump", 2990000)

  def test_get_data(self):

    print("\n\nTestGenElement.test_get_data:")

    data = GenElement(
      ).set_initializer(StaDumpAtoms(*self.args)
      ).append_updater(AddMap("type", "mass", {1: 147.28})
      ).get_data()

    for i in range(10):
      d = data[randrange(len(data))]
      self.assertEqual((d["type"], d["mass"]), (1, 147.28))

  def test_check_keys(self):

    print("\n\nTestGenElement.test_check_keys:")

    gen = GenElement().set_initializer(StaDumpAtoms(*self.args))

    self.assertEqual(
      gen.check_keys(["fx", "fy", "fz", "gx", "gy", "gz"]),
      [True, True, True, False, False, False])

    self.assertTrue(gen.check_key("id"))
    self.assertFalse(gen.check_key("index"))

  def test_getters(self):

    print("\n\nTestGenElement.test_getters:")

    gen = GenElement(
      ).set_initializer(StaDumpAtoms(*self.args)
      ).append_updater(AddMap("type", "mass", {1: 147.28}))

    ps = gen.get_double_array(["xu", "yu", "zu"])

    self.assertTrue(
      np.allclose(ps[0], np.array([3.77161, 3.01851, 14.3644])))

    self.assertTrue(
      np.allclose(ps[-1], np.array([-43.7141, -0.108626, 14.3606])))

    gen.append_updater(FilSet({"mol": set(range(1, 11))}))

    ids = gen.get_int_vector("id")

    self.assertTrue(np.allclose(
      np.sort(ids), np.arange(120001, 120001+27*10)))

    masses = gen.get_double_vector("mass")

    self.assertTrue(np.all(masses == 147.28))