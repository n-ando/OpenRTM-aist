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

#include <coil/Mutex.h>

namespace coil
{
    Mutex::Mutex(const char * name)
    {
      SECURITY_DESCRIPTOR sd_buffer;
      ::InitializeSecurityDescriptor(&sd_buffer,
                                     SECURITY_DESCRIPTOR_REVISION);
      ::SetSecurityDescriptorDacl(&sd_buffer, TRUE, nullptr, FALSE);
      m_Security_attr.nLength = sizeof(SECURITY_ATTRIBUTES);
      m_Security_attr.lpSecurityDescriptor = &sd_buffer;
      m_Security_attr.bInheritHandle = TRUE;
      mutex_ = ::CreateMutexA(&m_Security_attr, FALSE, name);
    }

    Mutex:: ~Mutex()
    {
      ::CloseHandle(mutex_);
    }

} // namespace coil
