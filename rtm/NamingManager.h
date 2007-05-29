// -*- C++ -*-
/*!
 * @file NamingManager.h
 * @brief naming Service helper class
 * @date $Date: 2007-04-26 15:37:48 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: NamingManager.h,v 1.3 2007-04-26 15:37:48 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2007/04/13 18:08:42  n-ando
 * Some changes for NameServers rebinding and objects rebinding.
 *
 * Revision 1.1  2006/11/04 21:11:44  n-ando
 * NamingManager was introduced to support multiple name server.
 *
 */
#ifndef NamingManager_h
#define NamingManager_h

#include <rtm/RTC.h>

#include <ace/Task.h>
#include <rtm/CorbaNaming.h>
#include <rtm/RTObject.h>
#include <rtm/SystemLogger.h>


namespace RTC
{
  class Manager;
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
    std::map<std::string, RTObject_impl*> m_names;
  };




  class NamingManager
  {
  public:
    NamingManager(Manager* manager);
    virtual ~NamingManager();

    void registerNameServer(const char* method, const char* name_server);
    void bindObject(const char* name, const RTObject_impl* rtobj);
    void update();
    void unbindObject(const char* name);
    void unbindAll();
    std::vector<RTObject_impl*> getObjects();

  protected:
    NamingBase* createNamingObj(const char* method, const char* name_server);
    void bindCompsTo(NamingBase* ns);
    void registerCompName(const char* name, const RTObject_impl* rtobj);
    void unregisterCompName(const char* name);


  protected:
    // Name Servers' method/name and object
    struct Names
    {
      Names(const char* meth, const char* name, NamingBase* naming)
	: method(meth), nsname(name), ns(naming)
      {
      }
      std::string method;
      std::string nsname;
      NamingBase* ns;
    };
    std::vector<Names*> m_names;
    ACE_Thread_Mutex m_namesMutex;

    // Components' name and object
    struct Comps
    {
      Comps(const char* n, const RTObject_impl* obj)
	: name(n), rtobj(obj)
      {}
      std::string name;
      const RTObject_impl* rtobj;
    };
    std::vector<Comps*> m_compNames;
    ACE_Thread_Mutex m_compNamesMutex;

    Manager* m_manager;
    MedLogbuf m_MedLogbuf;
    LogStream rtcout;
  }; // class NamingManager


}; // namespace RTC

#endif // NamingManager_h
