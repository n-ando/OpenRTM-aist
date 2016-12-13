// -*- C++ -*-
/*!
 * @file  BasicTypeConversion.h
 * @brief doil Ice basic type conversion functions
 * @date  $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef DOIL_ICE_BASICTYPECONVERSION_H
#define DOIL_ICE_BASICTYPECONVERSION_H

#include <coil/stringutil.h>
#include <doil/ice/Ice.h>

//-------------------------------------------------------------
// local -> ice
inline bool local_to_ice(const short int _from, ::Ice::Short& _to)
{
  _to = _from;
  return true;
}

inline bool local_to_ice(const unsigned short _from, ::Ice::Short& _to)
{
  _to = _from;
  return true;
}

inline bool local_to_ice(const long int _from, ::Ice::Long& _to)
{
  _to = _from;
  return true;
}

inline bool local_to_ice(const unsigned long int _from, ::Ice::Long& _to)
{
  _to = _from;
  return true;
}

inline bool local_to_ice(const float _from, ::Ice::Float& _to)
{
  _to = _from;
  return true;
}

inline bool local_to_ice(const double _from, ::Ice::Double& _to)
{
  _to = _from;
  return true;
}

inline bool local_to_ice(const char _from, ::Ice::Byte& _to)
{
  _to = _from;
  return true;
}

inline bool local_to_ice(const bool _from, bool& _to)
{
  _to = _from;
  return true;
}

inline bool local_to_ice(const unsigned char _from, ::Ice::Byte& _to)
{
  _to = _from;
  return true;
}


/*
inline bool local_to_ice(const std::string& _from, ::Ice::String_member& _to)
{
  _to.out() = ::Ice::string_dup(_from.c_str());
  return true;
}


//inline bool local_to_ice(const std::string& _from, _Ice_String_element::_Ice_String_element _to)
inline bool local_to_ice(const std::string& _from, ::_Ice_String_element _to)
{
  _to.out() = ::Ice::string_dup(_from.c_str());
  return true;
}



inline bool local_to_ice(const ::std::string& _from, char*& _to)
{
  _to = ::Ice::string_dup(_from.c_str());
  return true;
}

inline bool local_to_ice(const std::string& _from, ::Ice::Any& _to)
{
  _to <<= ::Ice::Any::from_string(_from.c_str(), _from.size());
  return true;
}

inline bool local_to_ice(const std::string& _from, std::string* _to)
{
  //    if (_from == "tk_null")
  //      _to = new ::Ice::TypeCode(Ice::tk_null);
  //    else if (_from == "tk_void")
  //      _to = new ::Ice::TypeCode(Ice::tk_void);
  //    else if (_from == "tk_short")
  //      _to = new ::Ice::TypeCode(Ice::tk_short);
  //    else if (_from == "tk_long")
  //      _to = new ::Ice::TypeCode(Ice::tk_long);
  //    else if (_from == "tk_ushort")
  //      _to = new ::Ice::TypeCode(Ice::tk_ushort);
  //    else if (_from == "tk_ulong")
  //      _to = new ::Ice::TypeCode(Ice::tk_ulong);
  //    else if (_from == "tk_float")
  //      _to = new ::Ice::TypeCode(Ice::tk_float);
  //    else if (_from == "tk_double")
  //      _to = new ::Ice::TypeCode(Ice::tk_double);
  //    else if (_from == "tk_boolean")
  //      _to = new ::Ice::TypeCode(Ice::tk_boolean);
  //    else if (_from == "tk_char")
  //      _to = new ::Ice::TypeCode(Ice::tk_char);
  //    else if (_from == "tk_octet")
  //      _to = new ::Ice::TypeCode(Ice::tk_octet);
  //    else if (_from == "tk_any")
  //      _to = new ::Ice::TypeCode(Ice::tk_any);
  //    else if (_from == "tk_TypeCode")
  //      _to = new ::Ice::TypeCode(Ice::tk_TypeCode);
  //    else if (_from == "tk_Principal")
  //      _to = new ::Ice::TypeCode(Ice::tk_Principal);
  //    else if (_from == "tk_longlong")
  //      _to = new ::Ice::TypeCode(Ice::tk_longlong);
  //    else if (_from == "tk_ulonglong")
  //      _to = new ::Ice::TypeCode(Ice::tk_ulonglong);
  //    else if (_from == "tk_longdouble")
  //      _to = new ::Ice::TypeCode(Ice::tk_longdouble);
  //    else if (_from == "tk_wchar")
  //      _to = new ::Ice::TypeCode(Ice::tk_wchar);
  //    else if (_from == "tk_fixed")
  //      _to = new ::Ice::TypeCode(Ice::tk_fixed);
  //    else if (_from == "tk_value")
  //      _to = new ::Ice::TypeCode(Ice::tk_value);
  //    else if (_from == "tk_value_box")
  //      _to = new ::Ice::TypeCode(Ice::tk_value_box);
  //    else if (_from == "native")
  //      _to = new ::Ice::TypeCode(Ice::native);
  //    else if (_from == "tk_abstract_interface")
  //      _to = new ::Ice::TypeCode(Ice::tk_abstract_interface);
  //    else
  //      return false;
  return true;
}
*/
//-------------------------------------------------------------
// ice -> local
inline bool ice_to_local(const ::Ice::Short _from, short& _to)
{
  _to = _from;
  return true;
}
/*
inline bool ice_to_local(const ::Ice::UShort _from, unsigned short& _to)
{
  _to = _from;
  return true;
}
*/
inline bool ice_to_local(const ::Ice::Long _from, int& _to)
{
  _to = _from;
  return true;
}
/*
inline bool ice_to_local(const ::Ice::ULong _from, unsigned int& _to)
{
  _to = _from;
  return true;
}
*/
inline bool ice_to_local(const ::Ice::Float _from, float& _to)
{
  _to = _from;
  return true;
}

inline bool ice_to_local(const ::Ice::Double _from, double& _to)
{
  _to = _from;
  return true;
}

inline bool ice_to_local(const ::Ice::Byte _from, char& _to)
{
  _to = _from;
  return true;
}

inline bool ice_to_local(const bool _from, unsigned char& _to)
{
  _to = _from;
  return true;
}

inline bool ice_to_local(const ::Ice::Byte _from, unsigned char& _to)
{
  _to = _from;
  return true;
}

inline bool ice_to_local(const bool _from, bool& _to)
{
  _to = _from;
  return true;
}

inline bool ice_to_local(const char* _from, std::string& _to)
{
  _to = _from;
  return true;
}

//  inline bool ice_to_local(char* _from, std::string& _to)
//  {
//    _to = _from;
//  }
/*
inline bool ice_to_local(const ::Ice::Any& _from, std::string& _to)
{
  const char* str;
  if (_from >>= str)
    {
      _to = str;
      return true;
    }
  ::Ice::Short short_var;
  if (_from >>= short_var)
    {
      _to = ::coil::otos(short_var);
      return true;
    }
  ::Ice::UShort ushort_var;
  if (_from >>= ushort_var)
    {
      _to = ::coil::otos(ushort_var);
      return true;
    }
  ::Ice::Long long_var;
  if (_from >>= long_var)
    {
      _to = ::coil::otos(long_var);
      return true;
    }
  ::Ice::ULong ulong_var;
  if (_from >>= ulong_var)
    {
      _to = ::coil::otos(ulong_var);
      return true;
    }
  ::Ice::Float float_var;
  if (_from >>= float_var)
    {
      _to = ::coil::otos(float_var);
      return true;
    }
  ::Ice::Double double_var;
  if (_from >>= double_var)
    {
      _to = ::coil::otos(double_var);
      return true;
    }
}
*/
/*
inline bool
ice_to_local(const Ice::TypeCode_member& _from, std::string& _to)
{
  try
    {
      _to = _from->name();
      return true;
    }
  catch ( ::Ice::TypeCode::BadKind& e )
    {
      return false;
    }
  return true;
}
*/

#endif // DOIL_ICE_UTIL_H
