import unittest
import traceback

from ppap4lmp import \
  Element, StaCustom, StaDumpAtoms, StaMolecules, StaBeads

class TestStaBeads(unittest.TestCase):

  def test_error01(self):

    atoms = Element(
      StaDumpAtoms("dumps_atom/atom.0.dump", 0))
    moles = Element(StaMolecules(atoms))

    try:
      beads = Element(StaBeads(moles, [{"foo": [1, 2, 3]}]))
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: Mapping to Beads must be specified by "
        + "'indices-in-mol'")

  def test_error02(self):

    atoms = Element(
      StaDumpAtoms("dumps_atom/atom.0.dump", 0))
    moles = Element(StaMolecules(atoms))

    try:
      beads = Element(StaBeads(moles, [
        {"indices-in-mol": [1, 2, 3, 4], "weights": [1.0, 1.0, 1.0]}]))
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: The numbers of elements in 'indices-in-mol' "
        + "and 'weights' are inconsistent")

  def test_error03(self):

    atoms = Element(
      StaDumpAtoms("dumps_atom/atom.0.dump", 0))
    moles = Element(StaMolecules(atoms))

    try:
      beads = Element(StaBeads(moles, [
        {"indices-in-mol": [1, 2], "weights": [1.0, 1.0]},
        {"indices-in-mol": [3, 4], "type": 1, "weights": [1.0, 1.0]}]))
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: The number of 'type' is invalid")

  def test_error04(self):

    atoms = Element(
      StaDumpAtoms("dumps_atom/atom.0.dump", 0))
    moles = Element(StaMolecules(atoms))

    try:
      beads = Element(StaBeads(moles, {
        1: [
          {"indices-in-mol": [1, 2]},
          {"indices-in-mol": [3, 4, 5]}],
        2: [
          {"indices-in-mol": [1, 2, 3], "weights": [1.0, 1.0, 1.0]},
          {"indices-in-mol": [3, 4], "weights": [1.0, 1.0]}]}))
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: The number of 'weights' is invalid")

  def test_atom_id(self):

    atoms = Element(
      StaDumpAtoms("dumps_atom/atom.0.dump", 0))
    moles = Element(StaMolecules(atoms))

    mappings = [
      [0, 1, 2, 12, 13, 14, 15, 16, 17, 18],
      [3, 4, 5, 19, 20, 21, 22, 23, 24],
      [6, 7, 8, 25, 26, 27, 28, 29, 30],
      [9, 10, 11, 31, 32, 33, 34, 35, 36, 37]]

    abst_beads = [{
      "type": 1,
      "indices-in-mol": mapping,
      "weights": [1.0] * len(mapping)
    } for mapping in mappings]

    beads = Element(StaBeads(moles, abst_beads))

    self.assertEqual(
      beads.get_keys(),
      {"id", "mol", "type", "atom-ids", "atom-weights"})

    data = beads.get_data()

    for d in data:

      offset = (d["mol"]-1) * 38
      in_mol = (d["id"]-1) % 4

      self.assertEqual(
        d["atom-ids"], [offset + i + 1 for i in mappings[in_mol]])
