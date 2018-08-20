#include "pybind.h"

/* -- variables used in utils.h/utils_py.h -- */

bool ERROR_OCCURED = false;
bool ToF_LOGGING = false;
List<std::pair<int,Str>> ENUM_XYZ = {{0, "x"}, {1, "y"}, {2, "z"}};