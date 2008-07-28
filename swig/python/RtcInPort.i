// -*- C++ -*-
/*!
 * @file RtcInPort.i
 * @brief swig interface file for RtcInPort
 * @date $Data$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

%module RtcInPort

%{
#include "rtm/RtcInPort.h"
%}
%import "RtcDataType.i"
%import "rtm/idl/RTCInPortSkel.h"

%inline %{
using namespace std;
%}



%newobject RTM::*::read;

/*
 * RTM::InPortBase and RTM::InPortAny<T> interface definition
 * 
 */
namespace RTM
{
  struct PortProfile
  {
	//    CORBA::String name;
	//    CORBA::TypeCode port_type;
	//	NVList properties;
  };

  class InPortBase
  {
  public:
	InPortBase();
	virtual ~InPortBase();
    virtual void put(const CORBA::Any& value) = 0;
	virtual RTM::PortProfile* profile();
	char* name();
  };

  template <class T> class InPortAny
  : public InPortBase
  {
   public:
    InPortAny(const char* name, int bufsize=64);
	virtual ~InPortAny();
    virtual void put(const CORBA::Any& value);
	virtual T read();
    char* name();
  };
};


/*
 * Template instantiation of InPort<T>
 */
%template(TimedStateIn)            RTM::InPortAny<RTM::TimedState>;
%template(TimedShortIn)            RTM::InPortAny<RTM::TimedShort>;
%template(TimedLongIn)             RTM::InPortAny<RTM::TimedLong>;
%template(TimedUShortIn)           RTM::InPortAny<RTM::TimedUShort>;
%template(TimedULongIn)            RTM::InPortAny<RTM::TimedULong>;
%template(TimedFloatIn)            RTM::InPortAny<RTM::TimedFloat>;
%template(TimedDoubleIn)           RTM::InPortAny<RTM::TimedDouble>;
%template(TimedCharIn)             RTM::InPortAny<RTM::TimedChar>;
%template(TimedBooleanIn)          RTM::InPortAny<RTM::TimedBoolean>;
%template(TimedOctetIn)            RTM::InPortAny<RTM::TimedOctet>;
%template(TimedStringIn)           RTM::InPortAny<RTM::TimedString>;
%template(TimedShortSeqIn)         RTM::InPortAny<RTM::TimedShortSeq>;
%template(TimedLongSeqIn)          RTM::InPortAny<RTM::TimedLongSeq>;
%template(TimedUShortSeqIn)        RTM::InPortAny<RTM::TimedUShortSeq>;
%template(TimedULongSeqIn)         RTM::InPortAny<RTM::TimedULongSeq>;
%template(TimedFloatSeqIn)         RTM::InPortAny<RTM::TimedFloatSeq>;
%template(TimedDoubleSeqIn)        RTM::InPortAny<RTM::TimedDoubleSeq>;
%template(TimedCharSeqIn)          RTM::InPortAny<RTM::TimedCharSeq>;
%template(TimedBooleanSeqIn)       RTM::InPortAny<RTM::TimedBooleanSeq>;
%template(TimedOctetSeqIn)         RTM::InPortAny<RTM::TimedOctetSeq>;
%template(TimedStringSeqIn)        RTM::InPortAny<RTM::TimedStringSeq>;
