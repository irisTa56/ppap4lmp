cmake_minimum_required(VERSION 3.11.0)
project(ppap4lmp)

find_package(pybind11 REQUIRED)

#==========================#
# Write header of pybind.h #
#==========================#

file(WRITE src/pybind.h
  "#ifndef PYBIND_H\n"
  "#define PYBIND_H\n\n"
  "#include \"headers_data.h\"\n"
  "#include \"headers_processor.h\"\n\n"
  #"namespace py = pybind11;\n\n"
  "PYBIND11_MODULE(ppap4lmp, m) {\n"
  "  m.doc() = \"PostProcess and Analysis Program for LAMMPS\";\n"
  "#ifdef VERSION_INFO\n"
  "  m.attr(\"__version__\") = VERSION_INFO;\n"
  "#else\n"
  "  m.attr(\"__version__\") = \"dev\";\n"
  "#endif\n\n"
)

#=========================#
# Preparation for headers #
#=========================#

FILE(GLOB HFILES src/*.h)

#--------------------#
# Data class headers #
#--------------------#

file(WRITE src/headers_data.h "#include \"data.h\"\n")
file(APPEND src/pybind.h "  setup_pybind_data(m);\n")

foreach(filepath ${HFILES})
  get_filename_component(basename ${filepath} NAME_WE)
  if(${basename} MATCHES "^data_")
    file(APPEND src/headers_data.h "#include \"" ${basename} ".h\"\n")
    file(APPEND src/pybind.h "  setup_pybind_" ${basename} "(m);\n")
  endif()
endforeach()

#-------------------------#
# Processor class headers #
#-------------------------#

file(WRITE src/headers_processor.h "#include \"processor.h\"\n")
file(APPEND src/pybind.h "  setup_pybind_processor(m);\n")

foreach(filepath ${HFILES})
  get_filename_component(basename ${filepath} NAME_WE)
  if(${basename} MATCHES "^processor_")
    file(APPEND src/headers_processor.h "#include \"" ${basename} ".h\"\n")
    file(APPEND src/pybind.h "  setup_pybind_" ${basename} "(m);\n")
  endif()
endforeach()

#==========================#
# Write footer of pybind.h #
#==========================#

file(APPEND src/pybind.h
  "\n}\n\n"
  "#endif\n"
)

#=========#
# Compile #
#=========#

FILE(GLOB CPPFILES src/*.cpp)
pybind11_add_module(ppap4lmp ${CPPFILES})
