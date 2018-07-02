import unittest

import numpy as np

from random import randrange

from ppap4lmp import \
  GenElement, StaDumpAtoms, AddMap, FilSet, FilComparison

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

    self.assertEqual(list(ps[0]), [3.77161, 3.01851, 14.3644])
    self.assertEqual(list(ps[-1]), [-43.7141, -0.108626, 14.3606])

    masses = gen.get_double_vector("mass")

    self.assertTrue(np.all(masses == 147.28))

    filtered_gen = GenElement(
      ).set_initializer(FilSet(gen, {"mol": set(range(1, 11))}))

    ids = filtered_gen.get_int_vector("id")

    self.assertTrue(np.allclose(
      np.sort(ids), np.arange(120001, 120001+27*10)))

    gen.append_updater(FilSet({"mol": set(range(1, 11))}))

    vs1 = gen.get_double_array(["vx", "vy", "vz"])
    vs2 = filtered_gen.get_double_array(["vx", "vy", "vz"])

    self.assertTrue(np.allclose(vs1, vs2))

  def test_filter(self):

    print("\n\nTestGenElement.test_filter:")

    gen = GenElement().set_initializer(StaDumpAtoms(*self.args))

    length = len(gen.get_data())

    gen_x = GenElement().set_initializer(
      FilComparison(gen, {"xu": (">", 0.0)}))

    xs = gen_x.get_double_vector("xu")

    self.assertTrue(np.all(xs > 0.0))

    gen_y = GenElement().set_initializer(
      FilComparison(gen, {"yu": (">", 0.0)}))

    ys = gen_y.get_double_vector("yu")

    self.assertTrue(np.all(ys > 0.0))

    gen_x_and_y = GenElement().set_initializer(
      FilComparison(gen, {"xu": (">", 0.0), "yu": (">", 0.0)}))

    xs2 = gen_x_and_y.get_double_vector("xu")
    ys2 = gen_x_and_y.get_double_vector("yu")

    self.assertTrue(np.all((xs2 + ys2) > 0.0))
    self.assertTrue(np.all((xs2 * ys2) > 0.0))

    gen.append_updater(
      FilComparison({"xu": ("<=", 0.0), "yu": ("<=", 0.0)}))

    filtered_lengtn = len(gen.get_data())

    self.assertEqual(
      filtered_lengtn + len(xs) + len(ys) - len(xs2), length)
