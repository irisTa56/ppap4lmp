#include <typeinfo>
#include <cxxabi.h>

#include "key_checker.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

const bool KeyChecker::check_key(
  const Set<Str> &datakeys,
  const Str &needkey,
  Str suffix)
{
  return check_keys(datakeys, {needkey}, suffix);
}

/* ------------------------------------------------------------------ */

const bool KeyChecker::check_keys(
  const Set<Str> &datakeys,
  const List<Str> &needkeys,
  Str suffix)
{
  List<Str> missing_keys;

  for (const auto &needkey : needkeys)
  {
    if (datakeys.find(needkey) == datakeys.end())
    {
      missing_keys.push_back(needkey);
    }
  }

  if (missing_keys.empty())
  {
    return true;
  }
  else
  {
    Str msg = get_my_class_name() + " needs";

    for (const auto &missing : missing_keys)
    {
      if (*(--msg.end()) == *"'")
      {
        msg += ",";
      }

      msg += " '" + missing + "'";
    }

    if (!suffix.empty())
    {
      msg += " " + suffix;
    }

    runtime_error(msg);

    return false;
  }
}

/* ------------------------------------------------------------------ */

const bool KeyChecker::check_key(
  ShPtr<GenElement> elem,
  const Str &needkey)
{
  return check_keys(elem->get_keys(), {needkey}, "externally");
}

/* ------------------------------------------------------------------ */

const bool KeyChecker::check_keys(
  ShPtr<GenElement> elem,
  const List<Str> &needkeys)
{
  return check_keys(elem->get_keys(), needkeys, "externally");
}

/* ------------------------------------------------------------------ */

const Str KeyChecker::get_my_class_name()
{
  return abi::__cxa_demangle(typeid(*this).name(), 0, 0, new int());
}