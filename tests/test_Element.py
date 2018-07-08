import unittest

import numpy as np

from random import randrange

from ppap4lmp import \
  Element, StaDumpAtoms, StaDumpBox, AddMap, FilSet, FilComparison, \
  StaMolecules, AddWrappedPositions

class TestElement(unittest.TestCase):

  def __init__(self, *args, **kwargs):

    super().__init__(*args, **kwargs)

    self.args = ("dumps_bead/bead.2990000.dump", 2990000)

  def test_get_data(self):

    print("\n\nTestElement.test_get_data:")

    gen = Element(StaDumpAtoms(*self.args))
    gen.append_updater(AddMap("type", "mass", {1: 147.28}))

    data = gen.get_data()

    for i in range(10):
      d = data[randrange(len(data))]
      self.assertEqual((d["type"], d["mass"]), (1, 147.28))

  def test_getters(self):

    print("\n\nTestElement.test_getters:")

    gen = Element(StaDumpAtoms(*self.args))
    gen.append_updater(AddMap("type", "mass", {1: 147.28}))

    ps = gen.get_2d_double(["xu", "yu", "zu"])

    self.assertEqual(list(ps[0]), [3.77161, 3.01851, 14.3644])
    self.assertEqual(list(ps[-1]), [-43.7141, -0.108626, 14.3606])

    masses = gen.get_1d_double("mass")

    self.assertTrue(np.all(masses == 147.28))

    filtered_gen = Element(FilSet(gen, {"mol": set(range(1, 11))}))

    ids = filtered_gen.get_1d_int("id")

    self.assertTrue(np.allclose(
      np.sort(ids), np.arange(120001, 120001+27*10)))

    gen.append_updater(FilSet({"mol": set(range(1, 11))}))

    vs1 = gen.get_2d_double(["vx", "vy", "vz"])
    vs2 = filtered_gen.get_2d_double(["vx", "vy", "vz"])

    self.assertTrue(np.allclose(vs1, vs2))

  def test_filter(self):

    print("\n\nTestElement.test_filter:")

    gen = Element(StaDumpAtoms(*self.args))

    length = len(gen.get_data())

    gen_x = Element(FilComparison(gen, [("xu", ">", 0.0)]))

    xs = gen_x.get_1d_double("xu")

    self.assertTrue(np.all(xs > 0.0))

    gen_y = Element(FilComparison(gen, [("yu", ">", 0.0)]))

    ys = gen_y.get_1d_double("yu")

    self.assertTrue(np.all(ys > 0.0))

    gen_x_and_y = Element(
      FilComparison(gen, [("xu", ">", 0.0), ("yu", ">", 0.0)]))

    xs2 = gen_x_and_y.get_1d_double("xu")
    ys2 = gen_x_and_y.get_1d_double("yu")

    self.assertTrue(np.all((xs2 + ys2) > 0.0))
    self.assertTrue(np.all((xs2 * ys2) > 0.0))

    gen.append_updater(
      FilComparison([("xu", "<=", 0.0), ("yu", "<=", 0.0)]))

    filtered_lengtn = len(gen.get_data())

    self.assertEqual(
      filtered_lengtn + len(xs) + len(ys) - len(xs2), length)

    gen_new = Element(StaDumpAtoms(*self.args))
    gen_new.append_updater(
      FilComparison([("xu", ">", 100.0), ("xu", "<", 200.0)]))

    xs3 = gen_new.get_1d_double("xu")

    self.assertTrue(np.all(xs3 > 100.0) and np.all(xs3 < 200.0))

  def test_molecules(self):

    print("\n\nTestElement.test_molecules:")

    atoms = Element(StaDumpAtoms(*self.args))
    mols = Element(StaMolecules(atoms))

    mol_data = mols.get_data()

    for d in mol_data:

      self.assertEqual(
        sorted(d["atom-ids"]),
        list(range(120001+27*(d["id"]-1), 120001+27*d["id"])))

  def test_wrapped(self):

    print("\n\nTestElement.test_wrapped:")

    atoms = Element(StaDumpAtoms(*self.args))
    box = Element(StaDumpBox(*self.args))

    atoms.append_updater(AddWrappedPositions(box))

    wrapped = atoms.get_2d_double(["x", "y", "z"])
    unwrapped = atoms.get_2d_double(["xu", "yu", "zu"])

    diff = unwrapped - wrapped
    diff_x = diff.T[0] / 662.0
    diff_y = diff.T[1] / 331.0

    self.assertTrue(np.all(diff_x.round() == diff_x))
    self.assertTrue(np.all(diff_y.round() == diff_y))
    self.assertTrue(np.allclose(wrapped.T[2], unwrapped.T[2]))
