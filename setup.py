import os
import re
import sys
import glob
import platform
import subprocess

from setuptools import setup, find_packages, Extension
from setuptools.command.build_ext import build_ext
from distutils.version import LooseVersion


class CMakeExtension(Extension):

  def __init__(self, name, sourcedir=""):

    super().__init__(name, sources=[])
    self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):

  def run(self):

    try:
      subprocess.check_output(["cmake", "--version"])
    except OSError:
      raise RuntimeError(
        "CMake must be installed to build the following extensions: " +
        ", ".join(e.name for e in self.extensions))

    if platform.system() == "Windows":
      RuntimeError("Windows is not supported")

    for ext in self.extensions:
      self.build_extension(ext)

  def build_extension(self, ext):

    extdir = os.path.abspath(
      os.path.dirname(self.get_ext_fullpath(ext.name)))
    cmake_args = [
      "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=" + extdir,
      "-DPYTHON_EXECUTABLE=" + sys.executable]

    cfg = "Debug" if self.debug else "Release"
    build_args = ["--config", cfg]

    if platform.system() == "Windows":
      RuntimeError("Windows is not supported")
    else:
      cmake_args += ["-DCMAKE_BUILD_TYPE=" + cfg]
      cmake_args += ["-DCMAKE_CXX_FLAGS_RELEASE='-fopenmp -O3 -fPIC'"]
      build_args += ["--", "-j2"]

    env = os.environ.copy()
    env["CXXFLAGS"] = "{} -DVERSION_INFO=\\\"{}\\\"".format(
      env.get("CXXFLAGS", ""), self.distribution.get_version())

    if not os.path.exists(self.build_temp):
      os.makedirs(self.build_temp)

    subprocess.check_call(
      ["cmake", ext.sourcedir] + cmake_args, cwd=self.build_temp, env=env)
    subprocess.check_call(
      ["cmake", "--build", "."] + build_args, cwd=self.build_temp)

#-----------------------------------------------------------------------

affixes = [
  "generator", "processor", "invoker",
  "updater", "starter", "filter", "adder"]

all_header_names = [
  os.path.basename(h)[:-2] for h in glob.glob("src/*.h")]

pybinds = []
classnames = []

for affix in affixes:

  with open("src/headers_{}.h".format(affix), "w") as headers:

    names = sorted(
      [n for n in all_header_names if n.startswith(affix[:3])],
      key=lambda x: x.replace("_", "~"))

    for name in names:
      headers.write("#include \"{}.h\"\n".format(name))

      with open("src/{}.h".format(name), "r") as header:
        for line in header:
          line_ = line.lstrip()
          if line_.startswith("static void pybind_"):
            pybinds.append("  pybind_{}(m);".format(name))
          elif line_.startswith("py::class_<") and 12 < len(line_):
            classnames.append(re.split("[,<>]", line_[11:])[0])

classnames.sort()

#-----------------------------------------------------------------------

with open("src/pybind.h", "w") as f:

  f.write("""#ifndef PYBIND_H
#define PYBIND_H

#include <pybind11/pybind11.h>

{headers}

#include "utils_py.h"

PYBIND11_MODULE(_ppap4lmp, m)
{{
{pybind}

  pybind_utils(m);
}}

#endif
""".format(
  headers="\n".join([
    "#include \"headers_{}.h\"".format(affix) for affix in affixes]),
  pybind="\n".join(pybinds)))

#-----------------------------------------------------------------------

with open("ppap4lmp/__init__.py", "w") as f:

  f.write("""from ._version import version_info, __version__
from ._ppap4lmp import \\
  {}, Element, log_switch

__all__ = [
  "{}",
  "Element",
  "log_switch",
]
""".format(", ".join(classnames), "\", \n  \"".join(classnames)))

#-----------------------------------------------------------------------

version_ns = {}
with open(os.path.join("ppap4lmp", "_version.py")) as f:
  exec(f.read(), {}, version_ns)

with open("README.md", "r") as fh:
  long_description = fh.read()

setup(
  name="ppap4lmp",
  version=version_ns["__version__"],
  author="Takayuki Kobayashi",
  author_email="iris.takayuki@gmail.com",
  description="PostProcess and Analysis Program for LAMMPS",
  license="MIT",
  long_description=long_description,
  long_description_content_type="text/markdown",
  url="https://github.com/irisTa56/ppap4lmp",
  ext_modules=[CMakeExtension("ppap4lmp._ppap4lmp")],
  cmdclass=dict(build_ext=CMakeBuild),
  classifiers=(
    "Programming Language :: Python :: 3",
    "License :: OSI Approved :: MIT License",
  ),
  packages=find_packages(),
)
