// -*- C++ -*-
/*!
 * @file CorbaProxyBase.h
 * @brief RTM CORBA proxy base class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef DOIL_CORBA_CORBAPROXYBASE_H
#define DOIL_CORBA_CORBAPROXYBASE_H

#include <string>
#include <rtm/config_rtc.h>
#include <doil/ProxyBase.h>
#include <doil/ImplBase.h>
#include <doil/corba/CORBA.h>

namespace doil
{
namespace CORBA
{
  class CORBAProxyBase
    : public doil::ProxyBase,
#ifdef RTC_CORBA_CXXMAPPING11
      public virtual PortableServer::ServantBase
#else
      public virtual PortableServer::RefCountServantBase
#endif
  {
  public:
    //CORBAProxyBase(ImplBase* impl)
    CORBAProxyBase(::CORBA::Object_ptr impl)
      : m_refcount(1)//, m_id(impl->id()), m_name(impl->name())
    {
    }
    virtual ~CORBAProxyBase(){}

    virtual const char* id() const
    {
      return m_id.c_str();
    }

    virtual const char* name() const
    {
      return m_name.c_str();
    }

    virtual void incRef()
    {
      ++m_refcount;
    }

    virtual void decRef()
    {
      --m_refcount;
      if (m_refcount == 0)
        delete this;
    }

  protected:
    int m_refcount;
    std::string m_id;
    std::string m_name;

  };
}; // namespoace doil
}; // namespace CORBA
#endif // DOIL_CORBA_CORBAPROXYBASE_H

