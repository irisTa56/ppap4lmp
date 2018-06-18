from ppap4lmp import __version__, \
  DataBox, ExtrBoxDump

print("version: " + __version__)

box_data = DataBox()
print(box_data.get_iv("periodicity"))
print(box_data.get_edge())


dump_prefix = "tests/dumps_bead/bead"
dump_suffix = "dump"
timestep = 3000000

box_reader = ExtrBoxDump(
  ".".join([dump_prefix, str(timestep), dump_suffix]), timestep)

box_data = box_reader.get_data()

print(box_data.get_periodicity())
print(box_data.get_da("edge"))


print("Pass! (^o^)b")
