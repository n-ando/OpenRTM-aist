// -*- C++ -*-
/*!
 * @file NVList.h
 * @brief NVList helper class
 * @date $Date: 2006-09-11 19:06:19 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: NVList.h,v 1.1 2006-09-11 19:06:19 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#include "rtm/idl/SDOpackageSkel.hh"


class NVListEx
  : public SDOPackage::NVList
{
  CORBA::Any* operator[](char* name)
  {
    std::string n(name);
    CORBA::ULong length = this->lenggth();
    for (CORBA::ULong i = 0; i < length; ++i)
      {
	if (std::string(this->name) == n)
	  return &(this->value);
      }
    throw InvalidParameter();
    return CORBA::Any();
  }

  CORBA::Any operator[](char* name)
  {
    CORBA::Any* value;
    return *((*this)[name]);
  }

  CORBA::Boolean setShortValue(const char* name, CORBA::Short value);
  
  CORBA::Boolean setLongValue(const char* name, CORBA::Long value);
  
  CORBA::Boolean setFloatValue(const char* name, CORBA::Float value);
  
  CORBA::Boolean setDoubleValue(const char* name, CORBA::Double value);
  
  CORBA::Boolean setCharValue(const char* name, CORBA::Char value);
  
  CORBA::Boolean setBoolValue(const char* name, CORBA::Boolean value);
  
  CORBA::Boolean setOctetValue(const char* name, CORBA::Octet value);
  
  CORBA::Boolean setStringValue(const char* name, const char* value);

  CORBA::Short   getShortValue(const char* name);

  CORBA::Long    getLongValue(const char* name);

  CORBA::Float   getFloatValue(const char* name);

  CORBA::Double  getDoubleValue(const char* name);

  CORBA::Char    getCharValue(const char* name);

  CORBA::Boolean getBoolValue(const char* name);

  CORBA::Octet   getOctetValue(const char* name);


};
    
    
