// -*- C++ -*-
/*!
 * @file UUID.h
 * @brief UUID wrapper class
 * @date $Date: 2006-10-17 19:18:50 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: UUID.h,v 1.1 2006-10-17 19:18:50 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#ifndef UUID_h
#define UUID_h

#ifdef WITH_ACE
#include <ace/UUID.h>
#else
#include <uuid.h>
#endif

namespace RTC_Utils
{
#ifdef WITH_ACE
  typedef ACE_Utils::UUID UUID;

  class UUID_Generator
    : public ACE_Utils::UUID_Generator
  {
  public:
    UUID_Generator() : ACE_Utils::UUID_Generator() {};
#ifndef ACE_5_6_1_OR_EARLIER  
    ACE_Utils::UUID*
    generateUUID(ACE_UINT16 version=0x0001, u_char variant=0x80)
    {
      return ACE_Utils::UUID_Generator::generate_UUID(version, variant);
    }
#endif
  };
#else
  class UUID
  {
    uuid_t _uuid;
  public:
    UUID();
    UUID(uuid_t*);
    std::string* to_string();
  };
  
  class UUID_Generator
  {
  public:
    UUID_Generator();
    
    void init();
    UUID* generateUUID(int n, int h);
  };
#endif
};

#endif // UUID_h
