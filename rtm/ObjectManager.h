// -*- C++ -*-
/*!
 * @file ObjectManager.h
 * @brief Object management class
 * @date $Date: 2006-10-17 10:21:50 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ObjectManager.h,v 1.1 2006-10-17 10:21:50 n-ando Exp $
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
  typedef std::vector<Object*>                  ObjectVector;
  typedef typename ObjectVector::iterator       ObjectVectorItr;
  typedef typename ObjectVector::const_iterator ObjectVectorConstItr;

  struct Error
  {
    Error(const std::string& _reason)
      : reason(_reason) {};
    std::string reason;
  };

  struct AlreadyRegistered
    : public Error
  {
    AlreadyRegistered()
      : Error("Already registered") {};
  };

  struct NoSuchObject
    : public Error
  {
    NoSuchObject()
      : Error("No such object") {};
  };

  struct SystemError
    : public Error
  {
    SystemError()
      : Error("System error") {};
  };

  ObjectManager(){};

  ~ObjectManager(){};

  void registerObject(Object* obj)
  {
    ObjectVectorItr it;
    ACE_Guard<ACE_Thread_Mutex> guard(m_objects._mutex);

    it = std::find_if(m_objects._obj.begin(), m_objects._obj.end(),
		      Predicate(obj));
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

  Object* unregisterObject(const Identifier& id)
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
	Object* obj(*it);
	m_objects._obj.erase(it);
	return obj;
      }
    throw SystemError();
    return NULL;;
  }


  Object* find(const Identifier& id) const
  {
    ObjectVectorConstItr it;
    ACE_Guard<ACE_Thread_Mutex> guard(m_objects._mutex);

    it = std::find_if(m_objects._obj.begin(), m_objects._obj.end(),
		      Predicate(id));
    if (it == m_objects._obj.end())
      {
	throw NoSuchObject();
      }
    else
      {
	return *it;
      }
    throw SystemError();
    return NULL;
  }


  std::vector<Object*> getObjects() const
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_objects._mutex);
    return m_objects._obj;
  }

  template <class Pred>
  void for_each(Pred p)
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_objects._mutex);
    std::for_each(m_objects._obj.begin(), m_objects._obj.end(), p);
  }

 protected:
  struct Objects
  {
    mutable ACE_Thread_Mutex _mutex;
    ObjectVector _obj;
  };
  Objects m_objects;

};

#endif // ObjectManager_h
