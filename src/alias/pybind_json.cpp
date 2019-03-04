/*!
  @file src/alias/pybind_json.cpp
  @brief This file has an implementation of type caster for ::Json.
  @author Takayuki Kobayashi
  @date 2019/03/04
*/

#include "json.h"
#include "pybind.h"
#include "pybind_json.h"


namespace pybind11
{
  namespace detail
  {
    namespace impl
    {
      Json to_json(const py::handle& obj)
      {
        if (obj.is_none())
        {
          return nullptr;
        }
        else if (py::isinstance<py::bool_>(obj))
        {
          return obj.cast<bool>();
        }
        else if (py::isinstance<py::int_>(obj))
        {
          return obj.cast<int>();
        }
        else if (py::isinstance<py::float_>(obj))
        {
          return obj.cast<double>();
        }
        else if (py::isinstance<py::str>(obj))
        {
          return obj.cast<std::string>();
        }
        else if (py::isinstance<py::tuple>(obj) || py::isinstance<py::list>(obj))
        {
          Json out;

          for (const py::handle& value : obj)
          {
            out.push_back(to_json(value));
          }

          return out;
        }
        else if (py::isinstance<py::dict>(obj))
        {
          Json out;

          for (const py::handle& key : obj)
          {
            out[key.cast<std::string>()] = to_json(obj[key]);
          }

          return out;
        }
        else  // fallback to slower method
        {
          try
          {
            return Json::parse(py::cast<std::string>(
              py::module::import("json").attr("dumps")(py::cast<py::object>(obj))));
          }
          catch (...)
          {
            throw std::runtime_error(
              "to_json not implemented for this type of object: "+ obj.cast<std::string>());
          }
        }
      }

      py::object from_json(const Json& j)
      {
        if (j.is_null())
        {
          return py::none();
        }
        else if (j.is_boolean())
        {
          return py::bool_(j.get<bool>());
        }
        else if (j.is_number_integer())
        {
          return py::int_(j.get<int>());
        }
        else if (j.is_number_float())
        {
          return py::float_(j.get<double>());
        }
        else if (j.is_string())
        {
          return py::str(j.get<std::string>());
        }
        else if (j.is_array())
        {
          py::list obj;

          for (const auto& el : j)
          {
            obj.attr("append")(from_json(el));
          }

          return obj;
        }
        else // object
        {
          py::dict obj;

          for (Json::const_iterator it = j.cbegin(); it != j.cend(); ++it)
          {
            obj[py::str(it.key())] = from_json(it.value());
          }

          return obj;
        }
      }
    }

    bool type_caster<Json>::load(
      handle src, bool)
    {
      try
      {
        value = impl::to_json(src);
      }
      catch (...)
      {
        return false;
      }

      return true;
    }

    handle type_caster<Json>::cast(
      Json src, return_value_policy, handle)
    {
      return impl::from_json(src).release();
    }
  }
}
