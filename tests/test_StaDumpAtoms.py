import unittest
import traceback

import numpy as np

from random import randrange

from ppap4lmp import create, StaDumpAtoms

class TestStaDumpAtoms(unittest.TestCase):

  def test_error01(self):

    atoms = create(StaDumpAtoms("dummy.file", 0))

    try:
      atoms.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: No such a file: dummy.file")

  def test_get_data(self):

    self._test_get_data(
      ("dumps_bead/bead.2990000.dump", 2990000),
      (147, 148),
      [
        {
          "id": 120148, "mol": 6, "type": 1,
          "xu": 3.77161, "yu": 3.01851, "zu": 14.3644,
          "vx": 0.00174077, "vy": -0.00127023, "vz": -0.00282561,
          "fx": -1.92522, "fy": -4.13575, "fz": 6.11625
        },
        {
          "id": 120149, "mol": 6, "type": 1,
          "xu": 7.49911, "yu": 3.25055, "zu": 14.0532,
          "vx": -0.00139162, "vy": 0.00173209, "vz": -0.000243098,
          "fx": 1.2697, "fy": 1.22152, "fz": 6.86386
        }
      ])

    self._test_get_data(
      ("dumps_atom/atom.0.dump", 0),
      (171, 1346),
      [
        {
          "id": 172, "mol": 5, "type": 2, "mass": 1.008,
          "xu": 40.6151, "yu": 40.4349, "zu": 41.2021,
          "vx": -0.0103233, "vy": 0.00487254, "vz": 0.0114586
        },
        {
          "id": 1347, "mol": 36, "type": 2, "mass": 1.008,
          "xu": 32.9292, "yu": 31.0932, "zu": -0.800721,
          "vx": 0.000854753, "vy": -0.00263839, "vz": 0.0191835
        }
      ])

  def _test_get_data(self, arguments, indices, expectation):

    atoms = create(StaDumpAtoms(*arguments))
    data = atoms.get_data()

    self.assertEqual([data[i] for i in indices], expectation)

  def test_get_keys(self):

    self._test_get_keys(
      ("dumps_bead/bead.2990000.dump", 2990000),
      {
        "id", "mol", "type",
        "xu", "yu", "zu", "vx", "vy", "vz", "fx", "fy", "fz",
      })

    self._test_get_keys(
      ("dumps_atom/atom.0.dump", 0),
      {
        "id", "mol", "type", "mass",
        "xu", "yu", "zu", "vx", "vy", "vz"
      })

  def _test_get_keys(self, arguments, expectation):

    atoms = create(StaDumpAtoms(*arguments))

    self.assertEqual(atoms.get_keys(), expectation)

  def test_get_1d_int(self):

    self._test_get_1d_int(
      ("dumps_bead/bead.2990000.dump", 2990000), "id")

    self._test_get_1d_int(
      ("dumps_atom/atom.0.dump", 0), "mol")

  def _test_get_1d_int(self, arguments, key):

    atoms = create(StaDumpAtoms(*arguments))

    data = atoms.get_data()
    vec = atoms.get_1d_int(key)

    for i in range(10):
      idx = randrange(len(data))
      d = data[idx][key]
      self.assertEqual(d, vec[idx])
      self.assertTrue(isinstance(d, int))

  def test_get_1d_double(self):

    self._test_get_1d_double(
      ("dumps_bead/bead.2990000.dump", 2990000), "fx")

    self._test_get_1d_double(
      ("dumps_atom/atom.0.dump", 0), "vx")

  def _test_get_1d_double(self, arguments, key):

    atoms = create(StaDumpAtoms(*arguments))

    data = atoms.get_data()
    vec = atoms.get_1d_double(key)

    for i in range(10):
      idx = randrange(len(data))
      d = data[idx][key]
      self.assertEqual(d, vec[idx])
      self.assertTrue(isinstance(d, float))

  def test_get_2d_int(self):

    self._test_get_2d_int(
      ("dumps_bead/bead.2990000.dump", 2990000), ["id", "mol"])

    self._test_get_2d_int(
      ("dumps_atom/atom.0.dump", 0), ["id", "mol", "type"])

  def _test_get_2d_int(self, arguments, keys):

    atoms = create(StaDumpAtoms(*arguments))

    data = atoms.get_data()
    arr = atoms.get_2d_int(keys)

    for i in range(10):
      idx = randrange(len(data))
      d = data[idx]
      self.assertTrue(np.allclose(
        np.array([d[k] for k in keys]), arr[idx]))

  def test_get_2d_double(self):

    self._test_get_2d_double(
      ("dumps_bead/bead.2990000.dump", 2990000), ["vx", "fx"])

    self._test_get_2d_double(
      ("dumps_atom/atom.0.dump", 0), ["xu", "yu", "zu"])

  def _test_get_2d_double(self, arguments, keys):

    atoms = create(StaDumpAtoms(*arguments))

    data = atoms.get_data()
    arr = atoms.get_2d_double(keys)

    for i in range(10):
      idx = randrange(len(data))
      d = data[idx]
      self.assertTrue(np.allclose(
        np.array([d[k] for k in keys]), arr[idx]))
