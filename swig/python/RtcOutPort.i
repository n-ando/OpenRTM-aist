// -*- C++ -*-
/*!
 * @file RtcOutPort.i
 * @brief swig interface file for RtcOutPort
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

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2005/05/12 09:06:19  n-ando
 * Public release.
 *
 *
 */

%module RtcOutPort

%{
#include "rtm/RtcOutPort.h"
#include "RtcDataConv.h"
%}

%import "rtm/idl/RTCInPortSkel.h"
%import "rtm/idl/RTCOutPortSkel.h"

%inline %{
  using namespace std;
  using namespace RTM;
%}


/*
 * RTM::OutPortBase and RTM::OutPortAny<T> interface definition
 * 
 */
namespace RTM
{
  class OutPortBase
  {
  public:
	OutPortBase();
	virtual ~OutPortBase();
	virtual CORBA::Any* get() = 0;
	virtual RtmRes unsubscribe(const char* id);
	virtual RTM::PortProfile* profile();
	//	virtual RtmRes push(const InPort_ptr& inport, SubscriptionID subsid);
	virtual void updateall();
	virtual char* name();
  };

  template <class T> class OutPortAny
	: public OutPortBase
  {
  public:
	OutPortAny(const char* name, int bufsize=64);
	virtual ~OutPortAny();
	virtual CORBA::Any* get();
	//	virtual void initBuffer(T& value);
	virtual void write(T value);
	
  };
};


/*
 * Template instantiation of OutPort<T>
 */
%template(TimedStateOut)            RTM::OutPortAny<RTM::TimedState>;
%template(TimedShortOut)            RTM::OutPortAny<RTM::TimedShort>;
%template(TimedLongOut)             RTM::OutPortAny<RTM::TimedLong>;
%template(TimedUShortOut)           RTM::OutPortAny<RTM::TimedUShort>;
%template(TimedULongOut)            RTM::OutPortAny<RTM::TimedULong>;
%template(TimedFloatOut)            RTM::OutPortAny<RTM::TimedFloat>;
%template(TimedDoubleOut)           RTM::OutPortAny<RTM::TimedDouble>;
%template(TimedCharOut)             RTM::OutPortAny<RTM::TimedChar>;
%template(TimedBooleanOut)          RTM::OutPortAny<RTM::TimedBoolean>;
%template(TimedOctetOut)            RTM::OutPortAny<RTM::TimedOctet>;
%template(TimedStringOut)           RTM::OutPortAny<RTM::TimedString>;
%template(TimedShortSeqOut)         RTM::OutPortAny<RTM::TimedShortSeq>;
%template(TimedLongSeqOut)          RTM::OutPortAny<RTM::TimedLongSeq>;
%template(TimedUShortSeqOut)        RTM::OutPortAny<RTM::TimedUShortSeq>;
%template(TimedULongSeqOut)         RTM::OutPortAny<RTM::TimedULongSeq>;
%template(TimedFloatSeqOut)         RTM::OutPortAny<RTM::TimedFloatSeq>;
%template(TimedDoubleSeqOut)        RTM::OutPortAny<RTM::TimedDoubleSeq>;
%template(TimedCharSeqOut)          RTM::OutPortAny<RTM::TimedCharSeq>;
%template(TimedBooleanSeqOut)       RTM::OutPortAny<RTM::TimedBooleanSeq>;
%template(TimedOctetSeqOut)         RTM::OutPortAny<RTM::TimedOctetSeq>;
%template(TimedStringSeqOut)        RTM::OutPortAny<RTM::TimedStringSeq>;
