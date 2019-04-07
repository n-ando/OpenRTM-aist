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
            return IDLPATH::idlpath;
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

const char* BasicDataTypeFile::idlpath = "BasicDatatype.idl";

void OpenSpliceMessageInfoInit()
{
    RTC::appendOpenSpliceMessageInfo<RTC::TimedLong, BasicDataTypeFile>();
}