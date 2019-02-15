import os
import yaml

from collections import OrderedDict

version_ns = {}
with open(os.path.join("..", "ppap4lmp", "_version.py")) as f:
  exec(f.read(), {}, version_ns)

with open("meta.yaml", "r") as f:
  lines = f.readlines()

for i in range(len(lines)):
  if lines[i].startswith("  version: "):
    lines[i] = "  version: {}\n".format(
      ".".join(map(str, version_ns["version_info"][:3])))
    break

with open("meta.yaml", "w") as f:
  lines = f.writelines(lines)
