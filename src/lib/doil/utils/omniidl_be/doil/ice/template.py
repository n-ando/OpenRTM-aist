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
 * @brief doil-Ice type conversion
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
 * @brief doil-Ice type conversion
 * @date $Date$
 * @author This file was automatically generated from [idl_fname] 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/ice/BasicTypeConversion.h>
#include <[typeconv_h_path]>
#include <doil/ice/SeqTypeConversion.h>
#include <doil/ice/IceManager.h>

[for node in tree]
[if node.ice.decl_type is "interface"]
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
// ice object -> local object
bool
ice_to_local([ice.name_fq]_ptr _from,
               [local.iface_name_fq]* _to);

// local object -> ice object
bool
local_to_ice([local.iface_name_fq]* _from,
               [ice.name_fq]_ptr _to);

"""

#------------------------------------------------------------
# object conversion implementation
object_conv_cpp = """\
// ice object -> local object
bool
ice_to_local([ice.name_fq]_ptr _from,
               [local.iface_name_fq]* _to)
{
  doil::LocalBase* lobj;
  lobj = doil::Ice::IceManager::instance().toLocal((::Ice::Object&)_from);
  if (lobj == NULL) return false;
  _to = dynamic_cast< [local.iface_name_fq]* >(lobj);
  if (_to == NULL) return false;
  return true;
}

// local object -> ice object
bool
local_to_ice([local.iface_name_fq]* _from,
               [ice.name_fq]_ptr _to)
{
  Ice::Object* obj;
  obj = doil::Ice::IceManager::instance().toReference((doil::LocalBase*)_from);
  _to = [ice.name_fq]::_narrow(obj);
  if (Ice::is_nil(_to)) return false;
  return true;
}

"""

#------------------------------------------------------------
# object declaration
struct_conv_h = """\
// struct ice -> local
bool
ice_to_local(const [ice.name_fq]& _from,
               [local.name_fq]& _to);

// struct local -> ice
bool
local_to_ice(const [local.name_fq]& _from,
               [ice.name_fq]& _to);

"""
#------------------------------------------------------------
# struct conversion declaration
struct_conv_cpp = """\
// struct ice -> local
bool
ice_to_local(const [ice.name_fq]& _from,
               [local.name_fq]& _to)
{
[for mem in members]
[if mem.ice.tk is "tk_objref"]
  if (!ice_to_local(([mem.ice.base_type]&)_from.[mem.ice.member_name],
                      _to.[mem.local.member_name]))
[else]
  if (!ice_to_local(_from.[mem.ice.member_name],
                      _to.[mem.local.member_name]))
[endif]
     return false;
[endfor]
  return true;
}

// struct local -> ice
bool
local_to_ice(const [local.name_fq]& _from,
               [ice.name_fq]& _to)
{
[for mem in members]
[if mem.ice.tk is "tk_objref"]
  if (!local_to_ice(_from.[mem.local.member_name],
                      ([mem.ice.base_type]&)_to.[mem.ice.member_name]))
[else]
  if (!local_to_ice(_from.[mem.local.member_name],
                      _to.[mem.ice.member_name]))
[endif]
     return false;
[endfor]
  return true;
}

"""

#------------------------------------------------------------
# union conversion declaration
union_conv_h = """\
// union ice -> local
bool
ice_to_local(const [local.name_fq]& _from,
               [ice.name_fq]& _to);

// union local -> ice
bool
ice_to_local(const [ice.name_fq]& _from,
               [local.name_fq]& _to);

"""

#------------------------------------------------------------
# union conversion implementation
union_conv_cpp = """\
// union ice -> local
bool
ice_to_local(const [ice.name_fq]& _from,
               [local.name_fq]& _to)
{
  switch (_from._d())
    {
[for cas in cases]
     case [cas.ice.discriminator_fq] :
       {
         [cas.local.case_type] l[cas.local.case_member];
         [cas.ice.case_type] c[cas.ice.case_member];
         c[cas.ice.case_member] = _from.[cas.ice.case_member]();
         ice_to_local(c[cas.ice.case_member], l[cas.local.case_member]);
         _to.set_[cas.local.case_member](l[cas.local.case_member]);
         break;
       }
[endfor]
      default:
        return false;
    }
  return true;
}

// union local -> ice
bool
local_to_ice(const [local.name_fq]& _from,
               [ice.name_fq]& _to)
{
  switch (_from.get_type())
    {
[for cas in cases]
    case [cas.local.discriminator_fq] :
      {
        [cas.ice.case_type] c[cas.ice.case_member];
        [cas.local.case_type] l[cas.local.case_member];
        l[cas.local.case_member] = _from.get_[cas.ice.case_member]();
        local_to_ice(l[cas.local.case_member], c[cas.ice.case_member]);
        _to.[cas.local.case_member](c[cas.ice.case_member]);
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
// enum ice -> local
inline bool
ice_to_local(const [ice.name_fq]& _from,
               [local.name_fq]& _to)
{
  _to = [local.name_fq]((long)_from);
  return true;
}

// enum local -> ice
inline bool
local_to_ice(const [local.name_fq]& _from,
               [ice.name_fq]& _to)
{
  _to = [ice.name_fq]((long)_from);
  return true;
}

"""

#------------------------------------------------------------
# enum conversion implementation
enum_conv_cpp = """\
"""

exception_conv_h = """\
// exxception ice -> local
bool
ice_to_local(const [local.name_fq]& _from,
               [ice.name_fq]& _to);

// exception local -> ice
bool
ice_to_local(const [ice.name_fq]& _from,
               [local.name_fq]& _to);

"""
exception_conv_cpp = """\
// exception ice -> local
bool
ice_to_local(const [ice.name_fq]& _from,
               [local.name_fq]& _to)
{
[for mem in members]
  if (!ice_to_local(_from.[mem.ice.member_name],
                      _to.[mem.local.member_name]))
     return false;
[endfor]
  return true;
}

// exception local -> ice
bool
local_to_ice(const [local.name_fq]& _from,
               [ice.name_fq]& _to)
{
[for mem in members]
  if (!local_to_ice(_from.[mem.local.member_name],
                      _to.[mem.ice.member_name]))
     return false;
[endfor]
  return true;
}

"""

#------------------------------------------------------------
# typedef conversion declaration
typedef_decl_h = """\
[if ice.tk is "tk_alias"][elif ice.tk is "tk_string"][elif ice.tk is "tk_long"][else]
// typedef ice -> local : [ice.tk] 
bool
ice_to_local(const [ice.derived_type_fq]& _from,
               [local.derived_type_fq]& _to);

// typedef local -> ice : [ice.tk] 
bool
local_to_ice(const [local.derived_type_fq]& _from,
               [ice.derived_type_fq]& _to);

[endif]
"""
#------------------------------------------------------------
# typedef conversion implementation
typedef_dec_cpp = """\
[if ice.tk is "tk_alias"][elif ice.tk is "tk_string"][elif ice.tk is "tk_long"][else]
// typedef ice -> local : [ice.tk] 
bool
ice_to_local(const [ice.derived_type_fq]& _from,
               [local.derived_type_fq]& _to)
{
[if ice.tk is "tk_sequence"]
  return ice_to_local_seq< [ice.derived_type_fq],
                             [ice.element_type_fq],
                             [local.derived_type_fq],
                             [local.element_type_fq] >(_from, _to);
[elif ice.tk is "tk_enum"]
  _to = [ice.derived_type_fq]((long)_from);
  return true;
[elif ice.tk is "tk_string"]
  return ice_to_local((const [ice.base_type])_from,
                        ([local.base_type]&)_to);
[else]
[if-any ice.is_primitive]
  _to = _from;
[else]
  return ice_to_local((const [ice.base_type])_from,
                        ([local.base_type]&)_to);
[endif]
[endif]
}

// typedef local -> ice : [ice.tk] 
bool
local_to_ice(const [local.derived_type_fq]& _from,
               [ice.derived_type_fq]& _to)
{
[if ice.tk is "tk_sequence"]
  return local_to_ice_seq< [local.derived_type_fq],
                             [local.element_type_fq],
                             [ice.derived_type_fq],
                             [ice.element_type_fq] >(_from, _to);
[elif ice.tk is "tk_enum"]
  _to = [ice.derived_type]((Ice::Long)rhs);
  return true;
[elif ice.tk is "tk_string"]
  return local_to_ice((const [local.base_type]&)_from,
                        ([ice.base_type])_to);
[else]
[if-any ice.is_primitive]
  _to = _from;
[else]
  return local_to_ice(([local.base_type])_from,
                        ([ice.base_type]&)_to);
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
 * @brief [local.servant_name] Ice servant for doil
 * @date $Date$
 * @author This file was automatically generated from [idl_fname]
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef [local.servant_include_guard] 
#define [local.servant_include_guard] 

#include <coil/Properties.h>
#include <doil/ice/IceServantBase.h>
#include <doil/ice/BasicTypeConversion.h>
[for inc in include_h]
#include <[inc]>
[endfor]
[for inc in inherits]
#include <[inc.local.servant_h]>
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
   : public virtual [ice.name_poa],
[for inc in inherits]
     public virtual [inc.local.servant_name_fq],
[endfor]
     public virtual ::doil::Ice::IceServantBase
  {
  public:
    [local.servant_name](doil::ImplBase* impl);
    virtual ~[local.servant_name]();

[for op in operations]
    virtual [op.return.ice.retn_type] [op.name]
([for a in op.args]
[if-index a is last][a.ice.arg_type] [a.ice.arg_name]
[else][a.ice.arg_type] [a.ice.arg_name], [endif]
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
  void [local.servant_name]IceInit(coil::Properties& prop);
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
 * @brief [local.iface_name] Ice servant for doil
 * @date $Date$
 * @author This file was automatically generated from [idl_fname]
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/ImplBase.h>
#include <doil/ice/IceManager.h>
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
   : ::doil::Ice::IceServantBase(impl), m_impl(NULL)[for inc in inherits],
     [inc.local.servant_name_fq](impl)[endfor] 
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
  [op.return.ice.retn_type] [local.servant_name]::[op.name]
([for a in op.args]
[if-index a is last][a.ice.arg_type] [a.ice.arg_name]
[else][a.ice.arg_type] [a.ice.arg_name], [endif]
[endfor])
  {
[for a in op.args]
    [a.local.var_type] [a.local.var_name];
[endfor]

[for a in op.args][if a.ice.direction is "out"][else]
[if-any a.ice.is_primitive]
    [a.local.var_name] = [a.ice.arg_name];
[else]
    ice_to_local([a.ice.arg_name], [a.local.var_name]);
[endif]
[endif][endfor]

[if op.return.ice.tk is "tk_void"]
[elif op.return.ice.tk is "tk_any"]
    [op.return.local.retn_type] local_ret;
    [op.return.ice.retn_type] ice_ret = 
        new [op.return.ice.base_type] ();
    local_ret =
[elif op.return.ice.tk is "tk_struct"]
    [op.return.local.retn_type] local_ret;
    [op.return.ice.retn_type] ice_ret = 
        new [op.return.ice.base_type] ();
    local_ret =
[elif op.return.ice.tk is "tk_alias"]
[if op.return.ice.deref_tk is "tk_long"]
    [op.return.local.retn_type] local_ret;
    [op.return.ice.retn_type] ice_ret;
    local_ret =
[elif op.return.ice.deref_tk is "tk_string"]
    [op.return.local.retn_type] local_ret;
    [op.return.ice.retn_type] ice_ret;
    local_ret =
[else]
    [op.return.local.retn_type] local_ret;
    [op.return.ice.retn_type] ice_ret = 
        new [op.return.ice.base_type] ();
    local_ret =
[endif]
[else]
    [op.return.local.retn_type] local_ret;
    [op.return.ice.retn_type] ice_ret;
    local_ret = 
[endif]
        m_impl->[op.name]
([for a in op.args][if-index a is last][a.local.var_name][else][a.local.var_name], [endif][endfor]);

[for a in op.args][if a.ice.direction is "in"][else]
    local_to_ice([a.local.var_name], [a.ice.arg_name]);
[endif][endfor]
[if op.return.ice.tk is "tk_void"][else]
[if op.return.ice.tk is "tk_any"]
    local_to_ice(local_ret, *ice_ret);
[elif op.return.ice.tk is "tk_struct"]
    local_to_ice(local_ret, *ice_ret);
[elif op.return.ice.tk is "tk_alias"]
[if op.return.ice.deref_tk is "tk_long"]
    local_to_ice(local_ret, ice_ret);
[elif op.return.ice.deref_tk is "tk_string"]
    local_to_ice(local_ret, ice_ret);
[else]
    local_to_ice(local_ret, *ice_ret);
[endif]
[else]
[if-any op.return.ice.is_primitive]
    ice_ret = local_ret;
[else]
    local_to_ice(local_ret, ice_ret);
[endif]
[endif]
    return ice_ret;
[endif]
  }
[endfor]

[for-inv ns in local.servant_ns]
}; // namespace [ns] 
[endfor]

extern "C"
{
  void [local.servant_name]IceInit(coil::Properties& prop)
  {
    doil::Ice::IceManager& mgr(doil::Ice::IceManager::instance());
    mgr.registerFactory("[local.servant_name]",
                        doil::New< [local.servant_name_fq] >,
                        doil::Delete< [local.servant_name_fq] >);
  }
};
"""





adapter_h = """\
// -*- C++ -*-
/*!
 * @file [local.adapter_h] 
 * @brief [local.adapter_name] Ice adapter for doil
 * @date $Date$
 * @author This file was automatically generated from [idl_fname] 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef [local.adapter_include_guard] 
#define [local.adapter_include_guard] 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/ice/IceManager.h>
#include <doil/ImplBase.h>
#include <[local.iface_h]>
[for inc in inherits]
#include <[inc.local.adapter_h]>
[endfor]
[for inc in include_h]
#include <[inc]>
[endfor]


[for ns in local.adapter_ns]
namespace [ns] 
{
[endfor]

  class [local.adapter_name] 
  : public virtual ::doil::LocalBase,
[for inc in inherits]
    public virtual [inc.local.adapter_name_fq],
[endfor]
    public virtual [local.iface_name_fq]

  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    [local.adapter_name](::Ice::Object* obj);
    virtual ~[local.adapter_name]();

[for op in operations]
    virtual [op.return.local.retn_type] [op.name]
([for a in op.args]
[if-index a is last][a.local.arg_type] [a.local.arg_name]
[else][a.local.arg_type] [a.local.arg_name], [endif]
[endfor])
      throw ([for raise in op.raises]
[if-index raise is first]
[raise.local.name_fq]
[else]
,
             [raise.local.name_fq]
[endif]
[endfor]
);


[endfor]

    const char* id() {return "[ice.idl_name]";}
    const char* name() {return m_name.c_str();}
    void incRef()
    {
      Guard guard(m_refcountMutex);
      ++m_refcount;
    }
    void decRef()
    {
      Guard guard(m_refcountMutex);
      --m_refcount;
      if (m_refcount == 0)
        delete this;
    }

  private:
    [ice.name_fq]_ptr m_obj;
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

[for ns in local.adapter_ns]
}; // namespace [ns] 
[endfor]

#ifndef [local.servant_include_guard] 


#endif // [local.servant_include_guard]


extern "C"
{
  void [local.adapter_name]IceInit(coil::Properties& prop);
};

#endif // [local.adapter_include_guard]

"""


adapter_cpp = """\
// -*- C++ -*-
/*!
 * @file [local.adapter_cpp] 
 * @brief [local.iface_name] Ice adapter for doil
 * @date $Date$
 * @author This file was automatically generated form [idl_fname] 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/ImplBase.h>
#include <doil/ice/IceManager.h>
#include <[local.iface_h_path]>
#include <[local.adapter_h_path]>
#include <[typeconv_h_path]>
#include <doil/ice/BasicTypeConversion.h>

[for ns in local.adapter_ns]
namespace [ns] 
{
[endfor]
  /*!
   * @brief ctor
   */ 
  [local.adapter_name]::[local.adapter_name](::Ice::Object* obj)
   : m_obj([ice.name_fq]::_nil()),
     m_refcount(1)[for inc in inherits],
     [inc.local.adapter_name_fq](obj)[endfor]

  {
    m_obj = [ice.name_fq]::_narrow(obj);
    if (::Ice::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = [ice.name_fq]::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  [local.adapter_name]::~[local.adapter_name]()
  {
    ::Ice::release(m_obj);
  }

  [for op in operations]

  /*!
   * @brief [op.name] 
   */ 
  [op.return.local.retn_type] [local.adapter_name]::[op.name]
([for a in op.args]
[if-index a is last][a.local.arg_type] [a.local.arg_name]
[else][a.local.arg_type] [a.local.arg_name], [endif]
[endfor])
      throw ([for raise in op.raises]
[if-index raise is first]
[raise.local.name_fq]
[else]
,
             [raise.local.name_fq]
[endif]
[endfor]
)
  {
    // Convert Local to Ice.
    // (The direction of the argument is 'in' or 'inout'.)
[for a in op.args]
    [a.ice.base_type] [a.ice.var_name];
[endfor]
[for a in op.args][if a.local.direction is "out"][else]
[if-any a.ice.is_primitive]
    [a.ice.var_name] = [a.local.arg_name];
[else]
[if a.local.tk is "tk_objref"]
    local_to_ice(const_cast< [a.local.var_type] >([a.local.arg_name]), [a.ice.var_name]);
[else]
    local_to_ice([a.local.arg_name], [a.ice.var_name]);
[endif]
[endif]
[endif][endfor]

    // Execute the method. 
[if op.return.local.tk is "tk_void"][else]
    [op.return.ice.retn_type] ice_ret;
    [op.return.local.retn_type] local_ret;
    ice_ret = [endif]
m_obj->[op.name]
([for a in op.args][if-index a is last][a.ice.var_name][else][a.ice.var_name], [endif][endfor]);

    // Convert Ice to Local.
    // (The direction of the argument is 'out' or 'inout'.)
[for a in op.args][if a.local.direction is "in"][else]
[if-any a.ice.is_primitive]
    [a.local.arg_name] = [a.ice.var_name];
[else]
    ice_to_local([a.ice.var_name], [a.local.arg_name]);
[endif]
[endif][endfor]

    // Generate the return value.
[if op.return.local.tk is "tk_void"][else]
[if op.return.local.tk is "tk_objref"]
    ice_to_local(ice_ret, local_ret);
[elif op.return.local.tk is "tk_enum"]
    ice_to_local(ice_ret, local_ret);
[else]
[if-any op.return.ice.is_primitive]
    local_ret = ice_ret;
[else]
[if op.return.ice.deref_tk is "tk_long"]
    local_ret = ice_ret;
[elif op.return.ice.deref_tk is "tk_string"]
    ice_to_local(ice_ret, local_ret);
[else]
    ice_to_local(*ice_ret, local_ret);
[endif]
[endif]
[endif]
[if op.return.ice.tk is "tk_any"]
    delete ice_ret; 
[elif op.return.ice.tk is "tk_struct"]
    delete ice_ret; 
[elif op.return.ice.tk is "tk_string"]
    ::Ice::string_free(ice_ret); 
[elif op.return.local.tk is "tk_objref"]
    ::Ice::release(ice_ret);
[elif op.return.ice.tk is "tk_alias"]
[if op.return.ice.deref_tk is "tk_long"]
[elif op.return.ice.deref_tk is "tk_string"]
    ::Ice::string_free(ice_ret); 
[else]
    delete ice_ret; 
[endif]
[endif]
    return local_ret;
[endif]
  }
[endfor]

[for ns in local.adapter_ns]
}; // namespace [ns] 
[endfor]

extern "C"
{
  void [local.adapter_name]IceInit(coil::Properties& prop)
  {
    doil::Ice::IceManager& mgr(doil::Ice::IceManager::instance());
    mgr.registerAdapterFactory("[local.adapter_name]",
                        doil::New< [local.adapter_name_fq] >,
                        doil::Delete< [local.adapter_name_fq] >);
  }
};

"""





proxy_h = """\
// -*- C++ -*-
/*!
 * @file [local.proxy_h] 
 * @brief [local.proxy_name] Ice proxy for doil
 * @date $Date$
 * @author This file was automatically generated from [idl_fname] 
 *         by omniidl/doil backend
 *
 * $Id$
 */
#ifndef [local.proxy_include_guard] 
#define [local.proxy_include_guard] 

#include <coil/Properties.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <doil/ice/IceManager.h>
#include <doil/ice/IceProxyBase.h>
#include <[local.iface_h]>
[for inc in inherits]
#include <[inc.local.proxy_h]>
[endfor]
[for inc in include_h]
#include <[inc]>
[endfor]


[for ns in local.proxy_ns]
namespace [ns] 
{
[endfor]

  class [local.proxy_name] 
  : public virtual ::doil::Ice::IceProxyBase,
[for inc in inherits]
    public virtual [inc.local.proxy_name_fq],
[endfor]
    public virtual [local.iface_name_fq]

  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    [local.proxy_name](::Ice::Object* obj);
    virtual ~[local.proxy_name]();

[for op in operations]
    virtual [op.return.local.retn_type] [op.name]
([for a in op.args]
[if-index a is last][a.local.arg_type] [a.local.arg_name]
[else][a.local.arg_type] [a.local.arg_name], [endif]
[endfor])
      throw ([for raise in op.raises]
[if-index raise is first]
[raise.local.name_fq]
[else]
,
             [raise.local.name_fq]
[endif]
[endfor]
);


[endfor]

    const char* id() {return "[ice.idl_name]";}
    const char* name() {return m_name.c_str();}
    void incRef()
    {
      Guard guard(m_refcountMutex);
      ++m_refcount;
    }
    void decRef()
    {
      Guard guard(m_refcountMutex);
      --m_refcount;
      if (m_refcount == 0)
        delete this;
    }

  private:
    [ice.name_fq]_ptr m_obj;
  private:
    std::string m_name;
    Mutex m_refcountMutex;
    int m_refcount;
  };

[for ns in local.proxy_ns]
}; // namespace [ns] 
[endfor]

#ifndef [local.servant_include_guard] 


#endif // [local.servant_include_guard]


extern "C"
{
  void [local.proxy_name]IceInit(coil::Properties& prop);
};

#endif // [local.proxy_include_guard]

"""


proxy_cpp = """\
// -*- C++ -*-
/*!
 * @file [local.proxy_cpp] 
 * @brief [local.iface_name] Ice proxy for doil
 * @date $Date$
 * @author This file was automatically generated form [idl_fname] 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/ice/IceManager.h>
#include <[local.iface_h_path]>
#include <[local.proxy_h_path]>
#include <[typeconv_h_path]>
#include <doil/ice/BasicTypeConversion.h>

[for ns in local.proxy_ns]
namespace [ns] 
{
[endfor]
  /*!
   * @brief ctor
   */ 
  [local.proxy_name]::[local.proxy_name](::Ice::Object* obj)
   : m_obj([ice.name_fq]::_nil()),
     m_refcount(1)[for inc in inherits],
     [inc.local.proxy_name_fq](obj)[endfor]
//   : m_obj([ice.name_fq]::_nil())[for inc in inherits],
//     [inc.local.proxy_name_fq](obj)[endfor]

  {
    m_obj = [ice.name_fq]::_narrow(obj);
    if (::Ice::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = [ice.name_fq]::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  [local.proxy_name]::~[local.proxy_name]()
  {
    ::Ice::release(m_obj);
  }

  [for op in operations]

  /*!
   * @brief [op.name] 
   */ 
  [op.return.local.retn_type] [local.proxy_name]::[op.name]
([for a in op.args]
[if-index a is last][a.local.arg_type] [a.local.arg_name]
[else][a.local.arg_type] [a.local.arg_name], [endif]
[endfor])
      throw ([for raise in op.raises]
[if-index raise is first]
[raise.local.name_fq]
[else]
,
             [raise.local.name_fq]
[endif]
[endfor]
)
  {
    // Convert Local to Ice.
    // (The direction of the argument is 'in' or 'inout'.)
[for a in op.args]
    [a.ice.base_type] [a.ice.var_name];
[endfor]
[for a in op.args][if a.local.direction is "out"][else]
[if-any a.ice.is_primitive]
//    [a.ice.var_name] = [a.local.arg_name];
    local_to_ice([a.local.arg_name], [a.ice.var_name]);
[else]
[if a.local.tk is "tk_objref"]
    local_to_ice(const_cast< [a.local.var_type] >([a.local.arg_name]), [a.ice.var_name]);
[else]
    local_to_ice([a.local.arg_name], [a.ice.var_name]);
[endif]
[endif]
[endif][endfor]

    // Execute the method. 
[if op.return.local.tk is "tk_void"][else]
    [op.return.ice.retn_type] ice_ret;
    [op.return.local.retn_type] local_ret;
    ice_ret = [endif]
m_obj->[op.name]
([for a in op.args][if-index a is last][a.ice.var_name][else][a.ice.var_name], [endif][endfor]);

    // Convert Ice to Local.
    // (The direction of the argument is 'out' or 'inout'.)
[for a in op.args][if a.local.direction is "in"][else]
[if-any a.ice.is_primitive]
//    [a.local.arg_name] = [a.ice.var_name];
    ice_to_local([a.ice.var_name], [a.local.arg_name]);
[else]
    ice_to_local([a.ice.var_name], [a.local.arg_name]);
[endif]
[endif][endfor]

    // Generate the return value.
[if op.return.local.tk is "tk_void"][else]
[if op.return.local.tk is "tk_objref"]
    ice_to_local(ice_ret, local_ret);
[elif op.return.local.tk is "tk_enum"]
    ice_to_local(ice_ret, local_ret);
[else]
[if-any op.return.ice.is_primitive]
//    local_ret = ice_ret;
    ice_to_local(ice_ret, local_ret);
[else]
[if op.return.ice.deref_tk is "tk_long"]
//    local_ret = ice_ret;
    ice_to_local(ice_ret, local_ret);
[elif op.return.ice.deref_tk is "tk_string"]
    ice_to_local(ice_ret, local_ret);
[else]
    ice_to_local(*ice_ret, local_ret);
[endif]
[endif]
[endif]
[if op.return.ice.tk is "tk_any"]
    delete ice_ret; 
[elif op.return.ice.tk is "tk_struct"]
    delete ice_ret; 
[elif op.return.ice.tk is "tk_string"]
    ::Ice::string_free(ice_ret); 
[elif op.return.local.tk is "tk_objref"]
    ::Ice::release(ice_ret);
[elif op.return.ice.tk is "tk_alias"]
[if op.return.ice.deref_tk is "tk_long"]
[elif op.return.ice.deref_tk is "tk_string"]
    ::Ice::string_free(ice_ret); 
[else]
    delete ice_ret; 
[endif]
[endif]
    return local_ret;
[endif]
  }
[endfor]

[for ns in local.proxy_ns]
}; // namespace [ns] 
[endfor]

extern "C"
{
  void [local.proxy_name]IceInit(coil::Properties& prop)
  {
    doil::Ice::IceManager& mgr(doil::Ice::IceManager::instance());
    mgr.registerProxyFactory("[local.proxy_name]",
                        doil::New< [local.proxy_name_fq] >,
                        doil::Delete< [local.proxy_name_fq] >);
  }
};

"""

