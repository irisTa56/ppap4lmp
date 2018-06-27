import unittest

from random import randrange

from ppap4lmp import GenAtomsDump, AddMap

class TestGenAtomsDump(unittest.TestCase):

  def __init__(self, *args, **kwargs):

    super().__init__(*args, **kwargs)

    self.args = ("tests/dumps_bead/bead.2990000.dump", 2990000)

  def test_position_type(self):

    print("\n\nTestGenAtomsDump.test_position_type:")

    expected_result = [False, False, True, False]

    gen = GenAtomsDump(*self.args)

    self.assertEqual([
      gen.is_unscaled(False),
      gen.is_scaled(False),
      gen.is_unwrapped(False),
      gen.is_scaled_unwrapped(False)], expected_result)

  def test_get_positions(self):

    print("\n\nTestGenAtomsDump.test_get_positions:")

    expected_result = [3.77161, 3.01851, 14.3644, -43.7141, -0.108626, 14.3606]

    gen = GenAtomsDump(*self.args)
    ps = gen.get_positions("unwrapped")

    self.assertEqual(list(ps[0])+list(ps[-1]), expected_result)

  def test_get_data(self):

    print("\n\nTestGenAtomsDump.test_get_data:")

    expected_result = [1, 147.28]

    gen = GenAtomsDump(*self.args)
    gen.append_adder(AddMap("type", "mass", {1: 147.28}))

    data = gen.get_data()

    for i in range(10):
      d = data[randrange(len(data))]
      self.assertEqual([d["type"], d["mass"]], expected_result)

  def test_count_keys(self):

    print("\n\nTestGenAtomsDump.test_count_keys:")

    expected_result = [1, 1, 1, 0, 0, 0]

    gen = GenAtomsDump(*self.args)

    self.assertEqual(
      gen.count_keys(["fx", "fy", "fz", "gx", "gy", "gz"]),
      expected_result)

    self.assertEqual(
      gen.count_keys(["fx", "fy", "fz", "gx", "gy", "gz"],
        check_only_front = False),
      expected_result)
