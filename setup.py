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

headers = sorted(
  glob.glob("src/pybind/*.h") + glob.glob("src/pybind/*/*.h"))

pybinds = []
classes = []
functions = []

for header in headers:

  with open(header[:-2]+".cpp", "r") as f:

    lines = f.readlines()

    for i, line in enumerate(lines):

      line_ = line.lstrip()

      if line_.startswith("void pybind::py_"):
        pybinds.append("  {}(m);".format(re.split("[ (]", line_)[1]))
      elif line_.startswith("py::class_<") and 12 < len(line_):
        classes.append(re.split("[,<>]", line_)[1])
      elif line_.startswith("m.def("):
        if 7 < len(line_):
          functions.append(line_[6:].split("\"")[1])
        else:
          functions.append(lines[i+1].lstrip().split("\"")[1])

def priority(x):
  if x.count("element"):
    return 1
  elif x.count("updater"):
    return 2
  else:
    return 3 + x.count("_")

headers.sort(key=priority)
pybinds.sort(key=priority)
classes.sort()
functions.sort()

#-----------------------------------------------------------------------

with open("src/pybind.h", "w") as f:

  f.write("""/*!
  @file src/pybind.h
  @brief This file includes all the header files containing definitions
  of functions to bind C++ and Python.
  @author Takayuki Kobayashi
  @date 2018/09/08

  This file is not included in the GitHub repository.
  It will be created at installation time.
  To find the way how this file is written,
  please see `setup.py` in the root directory of this project.
*/

#ifndef PYBIND_H
#define PYBIND_H

#include <pybind11/pybind11.h>

{}

//! Macro for generating Python module named `_ppap4lmp`.
PYBIND11_MODULE(_ppap4lmp, m)
{{
{}
}}

#endif
""".format(
  "\n".join(["#include \"{}\"".format(h[4:]) for h in headers]),
  "\n".join(pybinds)))

#-----------------------------------------------------------------------

with open("ppap4lmp/__init__.py", "w") as f:

  f.write("""from ._version import version_info, __version__
from ._ppap4lmp import \\
  {}
__all__ = [
  "{}"
]
""".format(
  ", ".join(classes + list(set(functions))),
  "\", \n  \"".join(classes + list(set(functions)))))

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
