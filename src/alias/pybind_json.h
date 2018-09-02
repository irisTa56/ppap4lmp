#ifndef ALIAS_PYBIND_JSON_H
#define ALIAS_PYBIND_JSON_H

static py::object json_dumps = py::module::import("json").attr("dumps");
static py::object json_loads = py::module::import("json").attr("loads");

/* NOTE:
  Casting Json from C++ to Python (and vice versa) is done by
  serialization, that is, Json is once converted to a string. This
  process might take a long time. So, using other containers is
  preferable (if you can).
*/

namespace pybind11
{
  namespace detail
  {
    template <>
    struct type_caster<Json> {
     public:

      PYBIND11_TYPE_CASTER(Json, _("json"));

      bool load(handle src, bool)
      {
        try
        {
          value = Json::parse(
            py::cast<std::string>(json_dumps(py::cast<object>(src))));
        }
        catch (...)
        {
          return false;
        }

        return true;
      }

      static handle cast(Json src, return_value_policy, handle)
      {
        return json_loads(src.dump()).release();
      }
    };
  } // namespace detail
} // namespace pybind11

#endif