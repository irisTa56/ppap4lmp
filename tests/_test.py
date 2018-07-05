from ppap4lmp import __version__, \
  Element, StaDumpAtoms

import time

start = time.time()

print("version: {}\n".format(__version__))

prefix = "dumps_bead/bead"
suffix = "dump"

gen = Element(
  StaDumpAtoms("dumps_bead/bead.2990000.dump", 2990000))

print(gen.get_map_to_index(["id", "mol"]))

elapsed_time = time.time() - start
print ("\nelapsed_time: {} [sec]".format(elapsed_time))

print("\nPass! (^o^)b")
