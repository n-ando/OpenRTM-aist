// -*- C++ -*-
/*!
 * @file ObjectManager.h
 * @brief Object management class
 * @date $Date: 2006-10-17 10:21:44 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ObjectManager.cpp,v 1.1 2006-10-17 10:21:44 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef ObjectManager_h
#define ObjectManager_h

#include <vector>
#include <string>
#include <algorithm>

#include <ace/Thread.h>
#include <ace/Synch.h>

template <typename Identifier, typename Object, typename Predicate>
class ObjectManager
{
 public:
  typedef std::vector<Object*>                 ObjectVector;
  typedef std::vector<Object*>::iterator       ObjectVectorItr;
  typedef std::vector<Object*>::const_iterator ObjectVectorConstItr;

  struct Error
  {
    Error(const std::string& _reason)
      : reason(_reason) {}
    std::string reason;
  };

  struct AlreadyRegistered
    :public Error
  {
    AlreadyRegistered()
      : Error("Already registered") {}
  };

  struct NoSuchObject
    :public Error
  {
    NoSuchObject()
      : Error("No such object") {}
  };

  struct SystemError
    :public Error
  {
    SystemError()
      : Error("System error") {}
  };

  ObjectManager(){};

  virtual ~ObjectManager(){};
  
  void register(const Identifier& id, const Object* obj)
  {
    ObjectVectorItr it;
    ACE_Guard<ACE_Thread_Mutex> guard(m_objects._mutex);

    it = std::find_if(m_objects._obj.begin(), m_objects._obj.end(),
		      Predicate(id));
    if (it == m_objects._obj.end())
      {
	m_objects._obj.push_back(obj);
	return;
      }
    else
      {
	throw AlreadyRegistered();
      }
    return;
  }

  Object* unregister(const Identifier& id)
  {
    ObjectVectorItr it;
    ACE_Guard<ACE_Thread_Mutex> guard(m_objects._mutex);

    it = std::find_if(m_objects._obj.begin(), m_objects._obj.end(),
		      Predicate(id));
    if (it == m_objects._obj.end())
      {
	throw NoSuchObject();
      }
    else
      {
	Object* obj(m_objects._obj);
	m_objects._obj.erase(it);
	return obj;
      }
    throw SystemError();
    return NULL;;
  }


  Object* find(const Identifier& Id)
  {
    ObjectVectorItr it;
    ACE_Guard<ACE_Thread_Mutex> guard(m_objects._mutex);

    it = std::find_if(m_objects._obj.begin(), m_objects._obj.end(),
		      Predicate(id));
    if (it == m_objects._obj.end())
      {
	throw NoSuchObject();
      }
    else
      {
	return m_objects._obj;
      }
    throw SystemError();
    return NULL;
  }


  std::vector<Object*> getObjects()
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_objects._mutex);
    return m_objects._obj;
  }


 protected:
  struct Objects
  {
    ACE_Thread_Mutex _mutex;
    ObjectVector _obj;
  };
  Objects m_objects;

};

#endif // ObjectManager_h
