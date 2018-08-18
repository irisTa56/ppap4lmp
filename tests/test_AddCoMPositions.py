import unittest
import traceback

from random import randrange

from ppap4lmp import \
  Element, StaCustom, StaDumpAtoms, StaMolecules, AddMap, AddCoMPositions

class TestAddCoMPositions(unittest.TestCase):

  def test_error(self):

    atoms = Element(
      StaDumpAtoms("dumps_bead/bead.2990000.dump", 2990000))
    molecules = Element(StaMolecules(atoms))

    molecules.append_updater(
      AddCoMPositions(Element(StaCustom({"foo": 0, "bar": 1}))))

    try:
      molecules.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: AddCoMPositions needs 'id', 'mass' and '*u' "
        + "(x/y/z) externally")

  def test_positions(self):

    atoms = Element(
      StaDumpAtoms("dumps_bead/bead.2990000.dump", 2990000))
    atoms.append_updater(AddMap("type", "mass", {1: 147.28}))

    self._test_positions(atoms)

    atoms = Element(
      StaDumpAtoms("dumps_dodecane_10000atm/atom.0.dump", 0))

    self._test_positions(atoms)

  def _test_positions(self, atoms):

    mols = Element(StaMolecules(atoms))
    mols.append_updater(AddCoMPositions(atoms))

    mol_data = mols.get_data()

    target = mol_data[randrange(len(mol_data))]

    atom_ids = set(target["atom-ids"])
    atom_data = atoms.get_data()

    tmpm = 0.0
    tmpx = 0.0
    tmpy = 0.0
    tmpz = 0.0

    for atom in atom_data:

      if atom["id"] in atom_ids:

        m = atom["mass"]

        tmpm += m
        tmpx += m * atom["xu"]
        tmpy += m * atom["yu"]
        tmpz += m * atom["zu"]

    tmpx /= tmpm
    tmpy /= tmpm
    tmpz /= tmpm

    self.assertEqual(target["xu"], tmpx)
    self.assertEqual(target["yu"], tmpy)
    self.assertEqual(target["zu"], tmpz)