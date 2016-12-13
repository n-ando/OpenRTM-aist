// -*- C++ -*-
/*!
 * @file RtcDataConv.h
 * @brief data convert functions for python
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

%module RtcDataType


%include "std_vector.i"

%{
#include "rtm/idl/RTCDataTypeStub.h"
#include "RtcDataConv.h"
%}

%import "rtm/idl/RTCDataTypeSkel.h"
%import "rtm/idl/RTMBaseSkel.h"


namespace std
{
%template(HogeShortSeq)           vector<short>;
%template(LongSeq)            vector<long>;
%template(UShortSeq)          vector<unsigned short>;
%template(ULongSeq)           vector<unsigned long>;
%template(FloatSeq)           vector<float>;
%template(DoubleSeq)          vector<double>;
%template(CharSeq)            vector<char>;
%template(BooleanSeq)         vector<bool>;
}



%newobject RTM::RtcManager::create_component;

namespace RTM
{
  struct Time {
	// 本当はCORBA::ULong. どこかでtypedef されているはず???
	unsigned long sec;
	unsigned long nsec;
  };
  
  template <class T, class U>
  class TimedDataPy
  {
  public:
	TimedDataPy(T& value);
	//	TimedDataPy();
	RTM::Time tm;
	U data;
  };
  
  
  template <class T, class U>
  class TimedDataSeqPy
  {
  public:
	TimedDataSeqPy(T& value);
	//	TimedDataSeqPy();
	RTM::Time tm;
	vector<U> data;
  };
};



/*
 * Basic data types
 */
%template(TimedState)      RTM::TimedDataPy<RTM::TimedState, short>;
%template(TimedShort)      RTM::TimedDataPy<RTM::TimedShort, short>;
%template(TimedLong)       RTM::TimedDataPy<RTM::TimedLong, long>;
%template(TimedUShort)     RTM::TimedDataPy<RTM::TimedUShort, unsigned short>;
%template(TimedULong)      RTM::TimedDataPy<RTM::TimedULong, unsigned long>;
%template(TimedFloat)      RTM::TimedDataPy<RTM::TimedFloat, float>;
%template(TimedDouble)     RTM::TimedDataPy<RTM::TimedDouble, double>;
%template(TimedChar)       RTM::TimedDataPy<RTM::TimedChar, char>;
%template(TimedBoolean)    RTM::TimedDataPy<RTM::TimedBoolean, bool>;
%template(TimedOctet)      RTM::TimedDataPy<RTM::TimedOctet, char>;
//%template(TimedStringPy)     RTM::TimedDataPy<RTM::TimedString, CORBA::String>;

/*
 * Sequence data types
 */
%template(TimedShortSeq)   RTM::TimedDataSeqPy<RTM::TimedShortSeq, short>;
%template(TimedLongSeq)    RTM::TimedDataSeqPy<RTM::TimedLongSeq, long>;
%template(TimedUShortSeq)  RTM::TimedDataSeqPy<RTM::TimedUShortSeq, unsigned short>;
%template(TimedULongSeq)   RTM::TimedDataSeqPy<RTM::TimedULongSeq, unsigned long>;
%template(TimedFloatSeq)   RTM::TimedDataSeqPy<RTM::TimedFloatSeq, float>;
%template(TimedDoubleSeq)  RTM::TimedDataSeqPy<RTM::TimedDoubleSeq, double>;
%template(TimedCharSeq)    RTM::TimedDataSeqPy<RTM::TimedCharSeq, char>;
%template(TimedBooleanSeq) RTM::TimedDataSeqPy<RTM::TimedBooleanSeq, bool>;
%template(TimedOctetSeq)   RTM::TimedDataSeqPy<RTM::TimedOctetSeq, char>;
//%template(TimedStringSeq)  RTM::TimedDataSeqPy<RTM::TimedStringSeq, CORBA::TimedStringSeq>;



