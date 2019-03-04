/*!
  @file src/alias/pybind_json.h
  @brief To bind ::Json to Python, a custom type caster of
  *pybind11* is required.
  @author Takayuki Kobayashi
  @date 2018/09/09
*/

#ifndef ALIAS_PYBIND_JSON_H
#define ALIAS_PYBIND_JSON_H

namespace pybind11
{
  namespace detail
  {
    //! A type caster of *pybind11* for ::Json.
    template <> struct type_caster<Json> {
     public:

      //! Macro for casting ::Json.
      PYBIND11_TYPE_CASTER(Json, _("json"));

      //! Loading a ::Json object from Python to C++.
      bool load(handle src, bool);

      //! Casting a ::Json object from C++ to Python.
      static handle cast(Json src, return_value_policy, handle);
    };
  } // namespace detail
} // namespace pybind11

#endif