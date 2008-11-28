#!/usr/bin/env python
# -*- python -*-
#
#  @file template.py
#  @brief doil servant class template
#  @date $Date$
#  @author Noriaki Ando <n-ando@aist.go.jp>
# 
#  Copyright (C) 2008
#      Task-intelligence Research Group,
#      Intelligent Systems Research Institute,
#      National Institute of
#          Advanced Industrial Science and Technology (AIST), Japan
#      All rights reserved.
# 
#  $Id$
# 


# doil type conversion header
typeconv_h = """\
// -*- C++ -*-
/*!
 * @file TypeConversion.h
 * @brief doil-CORBA type conversion
 * @date $Date$
 * @author This file was automatically generated from [idl_fname] 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#ifndef [typeconv_include_guard] 
#define [typeconv_include_guard] 

//
[for inc in include_h]
#include <[inc]>
[endfor]

#include <[types_h_path]>

[for decl in declarations]
[decl]
[endfor]

#endif // [typeconv_include_guard]

"""
typeconv_cpp = """\
// -*- C++ -*-
/*!
 * @file TypeConversion.h
 * @brief doil-CORBA type conversion
 * @date $Date$
 * @author This file was automatically generated from [idl_fname] 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/corba/BasicTypeConversion.h>
#include <[typeconv_h_path]>
#include <doil/corba/SeqTypeConversion.h>
#include <doil/corba/CORBAManager.h>

[for node in tree]
[if node.corba.decl_type is "interface"]
#include <[node.local.iface_h_path]>
[endif]
[endfor]

[for impl in implementations]
[impl]
[endfor]

// end of TypeConversion

"""


#------------------------------------------------------------
# object conversion declaration
object_conv_h = """\
// corba object -> local object
bool
corba_to_local([corba.name_fq]_ptr _from,
               [local.iface_name_fq]* _to);

// local object -> corba object
bool
local_to_corba([local.iface_name_fq]* _from,
               [corba.name_fq]_ptr _to);

"""

#------------------------------------------------------------
# object conversion implementation
object_conv_cpp = """\
// corba object -> local object
bool
corba_to_local([corba.name_fq]_ptr _from,
               [local.iface_name_fq]* _to)
{
  doil::LocalBase* lobj;
  lobj = doil::CORBA::CORBAManager::instance().toLocal((::CORBA::Object_ptr&)_from);
  if (lobj == NULL) return false;
  _to = dynamic_cast< [local.iface_name_fq]* >(lobj);
  if (_to == NULL) return false;
  return true;
}

// local object -> corba object
bool
local_to_corba([local.iface_name_fq]* _from,
               [corba.name_fq]_ptr _to)
{
  CORBA::Object_ptr obj;
  obj = doil::CORBA::CORBAManager::instance().toReference((doil::LocalBase*)_from);
  _to = [corba.name_fq]::_narrow(obj);
  if (CORBA::is_nil(_to)) return false;
  return true;
}

"""

#------------------------------------------------------------
# object declaration
struct_conv_h = """\
// struct corba -> local
bool
corba_to_local(const [corba.name_fq]& _from,
               [local.name_fq]& _to);

// struct local -> corba
bool
local_to_corba(const [local.name_fq]& _from,
               [corba.name_fq]& _to);

"""
#------------------------------------------------------------
# struct conversion declaration
struct_conv_cpp = """\
// struct corba -> local
bool
corba_to_local(const [corba.name_fq]& _from,
               [local.name_fq]& _to)
{
[for mem in members]
[if mem.corba.tk is "tk_objref"]
  if (!corba_to_local(([mem.corba.base_type]&)_from.[mem.corba.member_name],
                      _to.[mem.local.member_name]))
[else]
  if (!corba_to_local(_from.[mem.corba.member_name],
                      _to.[mem.local.member_name]))
[endif]
     return false;
[endfor]
  return true;
}

// struct local -> corba
bool
local_to_corba(const [local.name_fq]& _from,
               [corba.name_fq]& _to)
{
[for mem in members]
[if mem.corba.tk is "tk_objref"]
  if (!local_to_corba(_from.[mem.local.member_name],
                      ([mem.corba.base_type]&)_to.[mem.corba.member_name]))
[else]
  if (!local_to_corba(_from.[mem.local.member_name],
                      _to.[mem.corba.member_name]))
[endif]
     return false;
[endfor]
  return true;
}

"""

#------------------------------------------------------------
# union conversion declaration
union_conv_h = """\
// union corba -> local
bool
corba_to_local(const [local.name_fq]& _from,
               [corba.name_fq]& _to);

// union local -> corba
bool
corba_to_local(const [corba.name_fq]& _from,
               [local.name_fq]& _to);

"""

#------------------------------------------------------------
# union conversion implementation
union_conv_cpp = """\
// union corba -> local
bool
corba_to_local(const [corba.name_fq]& _from,
               [local.name_fq]& _to)
{
  switch (_from._d())
    {
[for cas in cases]
     case [cas.corba.discriminator_fq] :
       {
         [cas.local.case_type] l[cas.local.case_member];
         [cas.corba.case_type] c[cas.corba.case_member];
         c[cas.corba.case_member] = _from.[cas.corba.case_member]();
         corba_to_local(c[cas.corba.case_member], l[cas.local.case_member]);
         _to.set_[cas.local.case_member](l[cas.local.case_member]);
         break;
       }
[endfor]
      default:
        return false;
    }
  return true;
}

// union local -> corba
bool
local_to_corba(const [local.name_fq]& _from,
               [corba.name_fq]& _to)
{
  switch (_from.get_type())
    {
[for cas in cases]
    case [cas.local.discriminator_fq] :
      {
        [cas.corba.case_type] c[cas.corba.case_member];
        [cas.local.case_type] l[cas.local.case_member];
        l[cas.local.case_member] = _from.get_[cas.corba.case_member]();
        local_to_corba(l[cas.local.case_member], c[cas.corba.case_member]);
        _to.[cas.local.case_member](c[cas.corba.case_member]);
        break;
      }
[endfor]
      default:
        return false;
    }
  return true;
}

"""

#------------------------------------------------------------
# enum conversion declaration
enum_conv_h = """\
// enum corba -> local
inline bool
corba_to_local(const [corba.name_fq]& _from,
               [local.name_fq]& _to)
{
  _to = [local.name_fq]((long)_from);
  return true;
}

// enum local -> corba
inline bool
local_to_corba(const [local.name_fq]& _from,
               [corba.name_fq]& _to)
{
  _to = [corba.name_fq]((long)_from);
  return true;
}

"""

#------------------------------------------------------------
# enum conversion implementation
enum_conv_cpp = """\
"""

exception_conv_h = """\
// exxception corba -> local
bool
corba_to_local(const [local.name_fq]& _from,
               [corba.name_fq]& _to);

// exception local -> corba
bool
corba_to_local(const [corba.name_fq]& _from,
               [local.name_fq]& _to);

"""
exception_conv_cpp = """\
// exception corba -> local
bool
corba_to_local(const [corba.name_fq]& _from,
               [local.name_fq]& _to)
{
[for mem in members]
  if (!corba_to_local(_from.[mem.corba.member_name],
                      _to.[mem.local.member_name]))
     return false;
[endfor]
  return true;
}

// exception local -> corba
bool
local_to_corba(const [local.name_fq]& _from,
               [corba.name_fq]& _to)
{
[for mem in members]
  if (!local_to_corba(_from.[mem.local.member_name],
                      _to.[mem.corba.member_name]))
     return false;
[endfor]
  return true;
}

"""

#------------------------------------------------------------
# typedef conversion declaration
typedef_decl_h = """\
[if corba.tk is "tk_alias"][elif corba.tk is "tk_string"][else]
// typedef corba -> local : [corba.tk] 
bool
corba_to_local(const [corba.derived_type_fq]& _from,
               [local.derived_type_fq]& _to);

// typedef local -> corba : [corba.tk] 
bool
local_to_corba(const [local.derived_type_fq]& _from,
               [corba.derived_type_fq]& _to);

[endif]
"""
#------------------------------------------------------------
# typedef conversion implementation
typedef_dec_cpp = """\
[if corba.tk is "tk_alias"][elif corba.tk is "tk_string"][else]
// typedef corba -> local : [corba.tk] 
bool
corba_to_local(const [corba.derived_type_fq]& _from,
               [local.derived_type_fq]& _to)
{
[if corba.tk is "tk_sequence"]
  return corba_to_local_seq< [corba.derived_type_fq],
                             [corba.element_type_fq],
                             [local.derived_type_fq],
                             [local.element_type_fq] >(_from, _to);
[elif corba.tk is "tk_enum"]
  _to = [corba.derived_type_fq]((long)_from);
  return true;
[elif corba.tk is "tk_string"]
  return corba_to_local((const [corba.base_type])_from,
                        ([local.base_type]&)_to);
[else]
[if-any corba.is_primitive]
  _to = _from;
[else]
  return corba_to_local((const [corba.base_type])_from,
                        ([local.base_type]&)_to);
[endif]
[endif]
}

// typedef local -> corba : [corba.tk] 
bool
local_to_corba(const [local.derived_type_fq]& _from,
               [corba.derived_type_fq]& _to)
{
[if corba.tk is "tk_sequence"]
  return local_to_corba_seq< [local.derived_type_fq],
                             [local.element_type_fq],
                             [corba.derived_type_fq],
                             [corba.element_type_fq] >(_from, _to);
[elif corba.tk is "tk_enum"]
  _to = [corba.derived_type]((CORBA::Long)rhs);
  return true;
[elif corba.tk is "tk_string"]
  return local_to_corba((const [local.base_type]&)_from,
                        ([corba.base_type])_to);
[else]
[if-any corba.is_primitive]
  _to = _from;
[else]
  return local_to_corba(([local.base_type])_from,
                        ([corba.base_type]&)_to);
[endif]
[endif]
}
[endif]
"""



#------------------------------------------------------------
# doil servant header file template
#
# Given keys.
# - servant_name   : doil servant class name
# - iface_name : interface class name to be delegated by this servant
# - include_guard  : include guard definition name
# - fq_POA_name    : fully qualified POA name
# - operations     : operation definitions
#
servant_h = """\
// -*- C++ -*-
/*!
 * @file [local.servant_h] 
 * @brief [local.servant_name] CORBA servant for doil
 * @date $Date$
 * @author This file was automatically generated from [idl_fname]
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef [local.servant_include_guard] 
#define [local.servant_include_guard] 

#include <coil/Properties.h>
#include <doil/corba/CORBAServantBase.h>
[for inc in include_h]
#include <[inc]>
[endfor]

#include <[types_h_path]>

namespace doil
{
  class ImplBase;
};

// interface class forward declaration
[for ns in local.iface_ns]
namespace [ns] 
{
[endfor]
  class [local.iface_name];
[for-inv ns in local.iface_ns]
}; // namespace [ns]

[endfor]


[for ns in local.servant_ns]
namespace [ns] 
{
[endfor]

  class [local.servant_name] 
   : public virtual [corba.name_poa],
     public virtual ::doil::CORBA::CORBAServantBase
  {
  public:
    [local.servant_name](doil::ImplBase* impl);
    virtual ~[local.servant_name]();

[for op in operations]
    virtual [op.return.corba.retn_type] [op.name]
([for a in op.args]
[if-index a is last][a.corba.arg_type] [a.corba.arg_name]
[else][a.corba.arg_type] [a.corba.arg_name], [endif]
[endfor]);
[endfor]

  private:
    [local.iface_name_fq]* m_impl;
  };

[for-inv ns in local.servant_ns]
}; // namespace [ns] 
[endfor]

extern "C"
{
  void [local.servant_name]CORBAInit(coil::Properties& prop);
};

#endif // [local.servant_include_guard]

"""

#
# doil servant code file template
#
# Given keys.
# - servant_name   : doil servant class name
# - iface_name : interface class name to be delegated by this servant
# - include_guard  : include guard definition name
# - fq_POA_name    : fully qualified POA name
# - operations     : operation definitions
#
servant_cpp = """\
// -*- C++ -*-
/*!
 * @file [local.servant_cpp] 
 * @brief [local.iface_name] CORBA servant for doil
 * @date $Date$
 * @author This file was automatically generated from [idl_fname]
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/ImplBase.h>
#include <doil/corba/CORBAManager.h>
#include <[local.iface_h_path]>
#include <[local.servant_h_path]>
#include <[typeconv_h_path]>

[for ns in local.servant_ns]
namespace [ns] 
{
[endfor]
  /*!
   * @brief ctor
   */ 
  [local.servant_name]::[local.servant_name](doil::ImplBase* impl)
   : ::doil::CORBA::CORBAServantBase(impl), m_impl(NULL)
  {
    m_impl = dynamic_cast< [local.iface_name_fq]* >(impl);
    if (m_impl == NULL) throw std::bad_alloc();
    m_impl->incRef();
  }

  /*!
   * @brief dtor
   */ 
  [local.servant_name]::~[local.servant_name]()
  {
    m_impl->decRef();
  }

  [for op in operations]

  /*!
   * @brief [op.name] 
   */ 
  [op.return.corba.retn_type] [local.servant_name]::[op.name]
([for a in op.args]
[if-index a is last][a.corba.arg_type] [a.corba.arg_name]
[else][a.corba.arg_type] [a.corba.arg_name], [endif]
[endfor])
  {
[for a in op.args]
    [a.local.var_type] [a.local.var_name];
[endfor]

[for a in op.args][if a.corba.direction is "out"][else]
[if-any a.corba.is_primitive]
    [a.local.var_name] = [a.corba.arg_name];
[else]
    corba_to_local([a.corba.arg_name], [a.local.var_name]);
[endif]
[endif][endfor]

[if op.return.corba.tk is "tk_void"][else]
    [op.return.local.retn_type] local_ret;
    [op.return.corba.retn_type] corba_ret;
    local_ret = [endif]
m_impl->[op.name]
([for a in op.args][if-index a is last][a.local.var_name][else][a.local.var_name], [endif][endfor]);

[for a in op.args][if a.corba.direction is "in"][else]
    local_to_corba([a.local.var_name], [a.corba.arg_name]);
[endif][endfor]
[if op.return.corba.tk is "tk_void"][else]
[if-any op.return.corba.is_primitive]
    corba_ret = local_ret;
[else]
    local_to_corba(local_ret, corba_ret);
[endif]
    return corba_ret;
[endif]
  }
[endfor]

[for-inv ns in local.servant_ns]
}; // namespace [ns] 
[endfor]

extern "C"
{
  void [local.servant_name]CORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerFactory("[local.servant_name]",
                        doil::New< [local.servant_name_fq] >,
                        doil::Delete< [local.servant_name_fq] >);
  }
};
"""





adapter_h = """
// -*- C++ -*-
/*!
 * @file [adapter_h] 
 * @brief [adapter_name] CORBA adapter for doil
 * @date $Date$
 * @author This file was automatically generated by omniidl/doil backend
 *
 * $Id$
 */
#ifndef [adapter_include_guard] 
#define [adapter_include_guard] 

#include <coil/Properties.h>
#include <doil/corba/CORBAManager.h>
#include <doil/ImplBase.h>
#include <[iface_h]>
#include <[adapter_h_path]>
[for inc in include_h]
#include <[inc]>
[endfor]


[for ns in adapter_ns]
namespace [ns] 
{
[endfor]

  class [adapter_name] 
   : public virtual doil::LocalBase,
     public virtual [iface_name]

  {
  public:
    [adapter_name](::CORBA::Object_ptr obj);
    virtual ~[adapter_name]();

[for op in operations]
    virtual [op.return.local.retn_type] [op.name]
([for a in op.args]
[if-index a is last][a.local.arg_type] [a.local.arg_name]
[else][a.local.arg_type] [a.local.arg_name], [endif]
[endfor]);
[endfor]

  private:
    [corba_iface]_ptr m_obj;
  };

[for ns in adapter_ns]
}; // namespace [ns] 
[endfor]

#ifndef [servant_include_guard] 


#endif // [servant_include_guard]


extern "C"
{
  void [adapter_name]CORBAInit(coil::Properties& prop);
};

#endif // [adapter_include_guard]

"""


adapter_cpp = """\
// -*- C++ -*-
/*!
 * @file [adapter_cpp] 
 * @brief [iface_name] CORBA adapter for doil
 * @date $Date$
 * @author This file was automatically generated by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/ImplBase.h>
#include <doil/corba/CORBAManager.h>
#include <[iface_h_path]>
#include <[adapter_h_path]>

[for ns in adapter_ns]
namespace [ns] 
{
[endfor]
  /*!
   * @brief ctor
   */ 
  [adapter_name]::[adapter_name](::CORBA::Object_ptr obj)
   : m_obj(::CORBA::Object::_nil())
  {
    m_obj = [corba_iface]::_narrow(obj);
    if ([corba_iface]::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = [corba_iface]::duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  [adapter_name]::~[adapter_name]()
  {
    ::CORBA::release(m_obj);
  }

  [for op in operations]

  /*!
   * @brief [op.name] 
   */ 
  [op.return.local.retn_type] [adapter_name]::[op.name]
([for a in op.args]
[if-index a is last][a.local.arg_type] [a.local.arg_name]
[else][a.local.arg_type] [a.local.arg_name], [endif]
[endfor])
  {
[for a in op.args]
    [a.corba.decl_type] _[a.corba.arg_name];
[endfor]

[for a in op.args][if a.local.direction is "out"][else]
    [a.corba.arg_name] << [a.local.arg_name];
[endif][endfor]

[if op.return.local.tk is "tk_void"][else]
    [op.return.corba.retn_type] _ret;
    [op.return.local.retn_type] ret;
    _ret = [endif]
m_obj->[op.name]
([for a in op.args][if-index a is last]_[a.corba.arg_name][else]_[a.corba.argvar_name], [endif][endfor]);

[for a in op.args][if a.local.direction is "in"][else]
    [a.local.arg_name] << [a.corba.var_name];
[endif][endfor]
[if op.return.local.tk is "tk_void"][else]
    ret << _ret;
    return ret;
[endif]
  }
[endfor]

[for ns in adapter_ns]
}; // namespace [ns] 
[endfor]

extern "C"
{
  void [adapter_name]CORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerFactory("[adapter_name]",
                        doil::New<[adapter_name]>,
                        doil::Delete<[adapter_name]>);
  }
};
"""
