// -*- C++ -*-
/*!
 * @file  MutexPosix.h
 * @brief RT-Middleware Service interface
 * @date  $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef COIL_MUTEX_H
#define COIL_MUTEX_H

#include <windows.h>

namespace coil
{
  typedef HANDLE pthread_mutex_t;
  
  class Mutex
  {
  public:
    Mutex(const char * const name = 0)
    {
        SECURITY_DESCRIPTOR sd_buffer;
        ::InitializeSecurityDescriptor(&sd_buffer, 
                                       SECURITY_DESCRIPTOR_REVISION);
        ::SetSecurityDescriptorDacl (&sd_buffer, TRUE, 0, FALSE);
		m_Security_attr.nLength = sizeof(SECURITY_ATTRIBUTES);
		m_Security_attr.lpSecurityDescriptor = &sd_buffer;
		m_Security_attr.bInheritHandle = TRUE;
		mutex_ = ::CreateMutexA( &m_Security_attr,
		                         FALSE,
                                         name );


    }

    ~Mutex()
    {
		::CloseHandle(mutex_);
		
    }

    inline void lock()
    {
		::WaitForSingleObject(mutex_,INFINITE);
    }

    inline bool trylock()
    {
        unsigned long dwret;
		dwret = ::WaitForSingleObject(mutex_,0);
        switch(dwret)
		{
		  case WAIT_ABANDONED:
			  return true;
			  break;
		  case WAIT_OBJECT_0:
			  return false;
		  case WAIT_TIMEOUT:
			  return true;
		  default:
			  return true;
		}
    }

    inline void unlock()
    {
		::ReleaseMutex(mutex_);
    }
    HANDLE mutex_;
    
  private:
    SECURITY_ATTRIBUTES m_Security_attr;

	Mutex(const Mutex&);
    Mutex& operator=(const Mutex &);
  };
};
#endif // COIL_MUTEX_H
