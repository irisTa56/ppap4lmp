from ppap4lmp import __version__, \
  DataBox, ExtrBoxDump, ProcData, InvoOMP

print("version: " + __version__)

print("\n01 ---\n")

dump_prefix = "tests/dumps_bead/bead"
dump_suffix = "dump"

extrs = [
  ExtrBoxDump(".".join([dump_prefix, str(n), dump_suffix]), n)
  for n in range(2990000, 3000000, 1000)]

proc = ProcData(extrs)

invoker = InvoOMP(proc)
invoker.execute()

for d in proc.get_results():
  print(d.get_periodicity())

print("\nPass! (^o^)b")
