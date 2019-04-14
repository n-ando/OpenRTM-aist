// -*- C++ -*-
/*!
 * @file  OpenSpliceMessageInfo.cpp
 * @brief Fast-RTPS Massage Type Info class
 * @date  $Date: 2019-02-05 03:08:03 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2019
 *     Nobuhiko Miyamoto
 *     Robot Innovation Research Center,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *
 *     All rights reserved.
 *
 *
 */

#include "OpenSpliceMessageInfo.h"
#include <coil/stringutil.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>
#include <rtm/Typename.h>

namespace RTC
{
    OpenSpliceMessageInfoBase::~OpenSpliceMessageInfoBase(void)
    {
        
    }

    template <class DATATYPE, class IDLPATH>
    class OpenSpliceMessageInfo : public OpenSpliceMessageInfoBase
    {
        std::string topic_name(std::string topic) override
        {
            return topic;
        }

        std::string data_type() override
        {
            std::string data_type = ::CORBA_Util::toRepositoryIdOfStruct<DATATYPE>();
            coil::vstring strlist = coil::split(data_type, ":");
            if (strlist.size() != 3)
            {
                return "";
            }

            coil::replaceString(strlist[1], "/", "::");
            return strlist[1];
        }

        std::string idl_path() override
        {
            std::string path = coil::replaceEnv(IDLPATH::idlpath);
            coil::replaceString(path, "//", "/");
            coil::replaceString(path, "\\\\", "\\");
            return path;
        }
    };

    template <class DATATYPE, class IDLPATH>
    void appendOpenSpliceMessageInfo()
    {
        RTC::OpenSpliceMessageInfoFactory& factory(RTC::OpenSpliceMessageInfoFactory::instance());
        std::string data_type = ::CORBA_Util::toRepositoryIdOfStruct<DATATYPE>();
        factory.addFactory(data_type,
            ::coil::Creator < OpenSpliceMessageInfoBase,
            ::RTC::OpenSpliceMessageInfo<DATATYPE, IDLPATH> >,
            ::coil::Destructor< OpenSpliceMessageInfoBase,
            ::RTC::OpenSpliceMessageInfo<DATATYPE, IDLPATH> >);
    }
}

class BasicDataTypeFile
{
public:
    static const char* idlpath;
};

class ExtendedDataTypesFile
{
public:
    static const char* idlpath;
};

class InterfaceDataTypesFile
{
public:
    static const char* idlpath;
};

const char* BasicDataTypeFile::idlpath = "${RTM_IDL_PATH}/BasicDatatype.idl";
const char* ExtendedDataTypesFile::idlpath = "${RTM_IDL_PATH}/ExtendedDataTypes.idl";
const char* InterfaceDataTypesFile::idlpath = "${RTM_IDL_PATH}/InterfaceDataTypes.idl";

void OpenSpliceMessageInfoInit()
{
    RTC::appendOpenSpliceMessageInfo<RTC::TimedState, BasicDataTypeFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedShort, BasicDataTypeFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedLong, BasicDataTypeFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedUShort, BasicDataTypeFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedULong, BasicDataTypeFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedFloat, BasicDataTypeFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedDouble, BasicDataTypeFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedChar, BasicDataTypeFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedBoolean, BasicDataTypeFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedOctet, BasicDataTypeFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedString, BasicDataTypeFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedShortSeq, BasicDataTypeFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedLongSeq, BasicDataTypeFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedUShortSeq, BasicDataTypeFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedULongSeq, BasicDataTypeFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedFloatSeq, BasicDataTypeFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedDoubleSeq, BasicDataTypeFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedCharSeq, BasicDataTypeFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedBooleanSeq, BasicDataTypeFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedOctetSeq, BasicDataTypeFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedStringSeq, BasicDataTypeFile>();

    RTC::appendOpenSpliceMessageInfo<RTC::TimedRGBColour, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedPoint2D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedVector2D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedPose2D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedVelocity2D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedAcceleration2D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedPoseVel2D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedSize2D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedGeometry2D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedCovariance2D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedPointCovariance2D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedCarlike, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedSpeedHeading2D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedPoint3D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedVector3D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedOrientation3D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedPose3D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedVelocity3D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedAngularVelocity3D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedAcceleration3D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedAngularAcceleration3D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedPoseVel3D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedSize3D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedGeometry3D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedCovariance3D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedSpeedHeading3D, ExtendedDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo<RTC::TimedOAP, ExtendedDataTypesFile>();

    RTC::appendOpenSpliceMessageInfo < RTC::ActArrayActuatorPos, InterfaceDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo < RTC::ActArrayActuatorSpeed, InterfaceDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo < RTC::ActArrayActuatorCurrent, InterfaceDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo < RTC::ActArrayState, InterfaceDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo < RTC::CameraImage, InterfaceDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo < RTC::Fiducials, InterfaceDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo < RTC::GPSData, InterfaceDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo < RTC::GripperState, InterfaceDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo < RTC::INSData, InterfaceDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo < RTC::LimbState, InterfaceDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo < RTC::Hypotheses2D, InterfaceDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo < RTC::Hypotheses3D, InterfaceDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo < RTC::Features, InterfaceDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo < RTC::MultiCameraImages, InterfaceDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo < RTC::Path2D, InterfaceDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo < RTC::Path3D, InterfaceDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo < RTC::PointCloud, InterfaceDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo < RTC::PanTiltAngles, InterfaceDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo < RTC::PanTiltState, InterfaceDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo < RTC::RangeData, InterfaceDataTypesFile>();
    RTC::appendOpenSpliceMessageInfo < RTC::IntensityData, InterfaceDataTypesFile>();
}