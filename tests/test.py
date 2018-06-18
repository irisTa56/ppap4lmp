from ppap4lmp import __version__, \
  DataBox, ExtrBoxDump, ProcData

print("version: " + __version__)

print("\n01: --------")

data = DataBox()
print(data.get_iv("periodicity"))
print(data.get_edge())

print("\n02: --------")

dump_prefix = "tests/dumps_bead/bead"
dump_suffix = "dump"
timestep = 3000000

extr = ExtrBoxDump(
  ".".join([dump_prefix, str(timestep), dump_suffix]), timestep)

box_data = extr.get_data()

print(box_data.get_periodicity())
print(box_data.get_da("edge"))

print("\n03: --------")

proc = ProcData(extr)

print("\nPass! (^o^)b")
