// -*- C++ -*-
/*!
 * @file NamingManager.h
 * @brief naming Service helper class
 * @date $Date: 2006-11-04 21:11:36 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: NamingManager.cpp,v 1.1 2006-11-04 21:11:36 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#include <rtm/NamingManager.h>
#include <functional>
#include <algorithm>
#include <iostream>

namespace RTC
{
  void NamingOnCorba::bindObject(const char* name,
				 const RTObject_impl* rtobj)
  {
    std::cout << "bindObject()" << std::endl;
    std::cout << name << std::endl;
    try
      {
	m_cosnaming.rebindByString(name, rtobj->getObjRef(), true);
      }
    catch (...)
      {
	;
      }
  }

  void NamingOnCorba::unbindObject(const char* name)
  {
    try
      {
	m_cosnaming.unbind(name);
      }
    catch (...)
      {
	;
      }
  }

  void NamingManager::registerNaming(NamingBase* names)
  {
    m_namings.push_back(names);
  }
  
  void NamingManager::bindObject(const char* name, 
			       const RTObject_impl* rtobj)
  {
    std::for_each(m_namings.begin(), m_namings.end(),
		  binder(name, rtobj));
  }
  
  void NamingManager::unbindObject(const char* name)
  {
    std::for_each(m_namings.begin(), m_namings.end(), unbinder(name));
  }
}; // namespace RTC
