// -*- C++ -*-
/*!
 * @file NamingManager.h
 * @brief naming Service helper class
 * @date $Date: 2006-11-04 21:11:44 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: NamingManager.h,v 1.1 2006-11-04 21:11:44 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */
#ifndef NamingManager_h
#define NamingManager_h

#include <rtm/CorbaNaming.h>
#include <rtm/RTObject.h>


namespace RTC
{
  class NamingBase
  {
  public:
    NamingBase() {};
    virtual ~NamingBase() {};
    virtual void bindObject(const char* name, const RTObject_impl* rtobj) = 0;
    virtual void unbindObject(const char* name) = 0;
  };


 
  class NamingOnCorba
    : public virtual NamingBase
  {
  public:
    NamingOnCorba(CORBA::ORB_ptr orb, const char* names)
      : m_cosnaming(orb, names)
    {};
    virtual ~NamingOnCorba(){};

    virtual void bindObject(const char* name, const RTObject_impl* rtobj);

    virtual void unbindObject(const char* name);

  private:
    CorbaNaming m_cosnaming;
  };

  class NamingManager
  {
  public:
    NamingManager(){};
    NamingManager(Properties& prop){};
    ~NamingManager(){};

    void registerNaming(NamingBase* names);

    void bindObject(const char* name, const RTObject_impl* rtobj);
    void unbindObject(const char* name);

  protected:
    std::vector<NamingBase*> m_namings;

    struct binder
    {
      binder(const char* name, const RTObject_impl* rtobj)
	: m_name(name), m_obj(rtobj) {};
      void operator()(NamingBase* naming)
      {
	naming->bindObject(m_name, m_obj);
      }
      const char* m_name;
      const RTObject_impl* m_obj;
    };

    struct unbinder
    {
      unbinder(const char* name) : m_name(name) {};
      void operator()(NamingBase* naming)
      {
	naming->unbindObject(m_name);
      }
      const char* m_name;
    };
    
  }; // class NamingManager



}; // namespace RTC

#endif // NamingManager_h
