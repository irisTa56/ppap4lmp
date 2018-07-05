
# ppap4lmp

PostProcess and Analysis Program for LAMMPS

## Installation

### via Conda

```bash
conda install -c irista56 ppap4lmp
```

### Development version

Just clone this repository and pip install. Note that Eigen needs to be installed.

```bash
git clone --recursive https://github.com/irisTa56/ppap4lmp.git
cd ppap4lmp
pip install .
# (or) pip install -e .
# (or) pip install --user .
# (or) pip install --user -e .
```

## Acknowledgement

This project would not be possible without the following great open-source projects.

* [pybind/cmake_example](https://github.com/pybind/cmake_example)
* [pybind11](https://github.com/pybind/pybind11)
* [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page)
* [nlohmann/json](https://github.com/nlohmann/json)
