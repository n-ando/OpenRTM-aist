// -*- C++ -*-
/*!
 * @file IceProxyBase.h
 * @brief Doil Ice proxy base class
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

#ifndef DOIL_ICE_ICEPROXYBASE_H
#define DOIL_ICE_ICEPROXYBASE_H

#include <string>
#include <rtm/config_rtc.h>
#include <doil/ProxyBase.h>
#include <doil/ImplBase.h>
#include <doil/ice/Ice.h>

namespace doil
{
namespace Ice
{
  class IceProxyBase
    : public doil::ProxyBase,
      public virtual ::Ice::Object
  {
  public:
    IceProxyBase(ImplBase* impl)
      : m_refcount(1)//, m_id(impl->id()), m_name(impl->name())
    {
    }
    virtual ~IceProxyBase(){}

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
}; // namespace Ice
#endif // DOIL_ICE_ICEPROXYBASE_H

