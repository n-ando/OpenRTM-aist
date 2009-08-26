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
%template(Point2D)                  RTM::OutPortAny<RTM::Point2D>;
%template(Vector2D)                 RTM::OutPortAny<RTM::Vector2D>;
%template(Pose2D)                   RTM::OutPortAny<RTM::Pose2D>;
%template(Velocity2D)               RTM::OutPortAny<RTM::Velocity2D>;
%template(PoseVel2D)                RTM::OutPortAny<RTM::PoseVel2D>;
%template(Size2D)                   RTM::OutPortAny<RTM::Size2D>;
%template(Geometry2D)               RTM::OutPortAny<RTM::Geometry2D>;
%template(Covariance2D)             RTM::OutPortAny<RTM::Covariance2D>;
%template(PointCovariance2D)        RTM::OutPortAny<RTM::PointCovariance2D>;
%template(Point3D)                  RTM::OutPortAny<RTM::Point3D>;
%template(Vector3D)                 RTM::OutPortAny<RTM::Vector3D>;
%template(Orientation3D)            RTM::OutPortAny<RTM::Orientation3D>;
%template(Pose3D)                   RTM::OutPortAny<RTM::Pose3D>;
%template(Velocity3D)               RTM::OutPortAny<RTM::Velocity3D>;
%template(PoseVel3D)                RTM::OutPortAny<RTM::PoseVel3D>;
%template(Size3D)                   RTM::OutPortAny<RTM::Size3D>;
%template(Geometry3D)               RTM::OutPortAny<RTM::Geometry3D>;
%template(Covariance3D)             RTM::OutPortAny<RTM::Covariance3D>;
%template(Colour)                   RTM::OutPortAny<RTM::Colour>;
%template(Carlike)                  RTM::OutPortAny<RTM::Carlike>;
%template(SpeedHeading)             RTM::OutPortAny<RTM::SpeedHeading>;
%template(OAP)                      RTM::OutPortAny<RTM::OAP>;
%template(TimedPoint2D)             RTM::OutPortAny<RTM::TimedPoint2D>;
%template(TimedVector2D)            RTM::OutPortAny<RTM::TimedVector2D>;
%template(TimedPose2D)              RTM::OutPortAny<RTM::TimedPose2D>;
%template(TimedVelocity2D)          RTM::OutPortAny<RTM::TimedVelocity2D>;
%template(TimedPoseVel2D)           RTM::OutPortAny<RTM::TimedPoseVel2D>;
%template(TimedSize2D)              RTM::OutPortAny<RTM::TimedSize2D>;
%template(TimedGeometry2D)          RTM::OutPortAny<RTM::TimedGeometry2D>;
%template(TimedCovariance2D)        RTM::OutPortAny<RTM::TimedCovariance2D>;
%template(TimedPointCovariance2D)   RTM::OutPortAny<RTM::TimedPointCovariance2D>;
%template(TimedPoint3D)             RTM::OutPortAny<RTM::TimedPoint3D>;
%template(TimedVector3D)            RTM::OutPortAny<RTM::TimedVector3D>;
%template(TimedOrientation3D)       RTM::OutPortAny<RTM::TimedOrientation3D>;
%template(TimedPose3D)              RTM::OutPortAny<RTM::TimedPose3D>;
%template(TimedVelocity3D)          RTM::OutPortAny<RTM::TimedVelocity3D>;
%template(TimedPoseVel3D)           RTM::OutPortAny<RTM::TimedPoseVel3D>;
%template(TimedSize3D)              RTM::OutPortAny<RTM::TimedSize3D>;
%template(TimedGeometry3D)          RTM::OutPortAny<RTM::TimedGeometry3D>;
%template(TimedCovariance3D)        RTM::OutPortAny<RTM::TimedCovariance3D>;
%template(TimedColour)              RTM::OutPortAny<RTM::TimedColour>;
%template(TimedCarlike)             RTM::OutPortAny<RTM::TimedCarlike>;
%template(TimedSpeedHeading)        RTM::OutPortAny<RTM::TimedSpeedHeading>;
%template(TimedOAP)                 RTM::OutPortAny<RTM::TimedOAP>;
