// -*- C++ -*-
/*!
 * @file ObjectManager.h
 * @brief Object management class
 * @date $Date: 2007-04-13 18:11:26 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ObjectManager.h,v 1.4 2007-04-13 18:11:26 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2006/11/06 01:42:22  n-ando
 * ObjectManager's for_each has been modified to return Predicate object.
 *
 * Revision 1.2  2006/10/25 17:31:03  n-ando
 * for_each()'s arguments are changed from value to reference.
 *
 * Revision 1.1  2006/10/17 10:21:50  n-ando
 * The first commitment.
 *
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


  ObjectManager(){};


  ~ObjectManager(){};


  bool registerObject(Object* obj)
  {
    ObjectVectorItr it;
    ACE_Guard<ACE_Thread_Mutex> guard(m_objects._mutex);

    it = std::find_if(m_objects._obj.begin(), m_objects._obj.end(),
		      Predicate(obj));
    if (it == m_objects._obj.end())
      {
	m_objects._obj.push_back(obj);
	return true;
      }
    return false;
  }


  Object* unregisterObject(const Identifier& id)
  {
    ObjectVectorItr it;
    ACE_Guard<ACE_Thread_Mutex> guard(m_objects._mutex);

    it = std::find_if(m_objects._obj.begin(), m_objects._obj.end(),
		      Predicate(id));
    if (it != m_objects._obj.end())
      {
	Object* obj(*it);
	m_objects._obj.erase(it);
	return obj;
      }
    return NULL;;
  }


  Object* find(const Identifier& id) const
  {
    ObjectVectorConstItr it;
    ACE_Guard<ACE_Thread_Mutex> guard(m_objects._mutex);
    it = std::find_if(m_objects._obj.begin(), m_objects._obj.end(),
		      Predicate(id));
    if (it != m_objects._obj.end())
      {
	return *it;
      }
    return NULL;
  }


  std::vector<Object*> getObjects() const
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_objects._mutex);
    return m_objects._obj;
  }


  template <class Pred>
  Pred for_each(Pred p)
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_objects._mutex);
    return std::for_each(m_objects._obj.begin(), m_objects._obj.end(), p);
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
