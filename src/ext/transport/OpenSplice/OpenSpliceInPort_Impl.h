// -*- C++ -*-
/*!
 * @file  OpenSpliceInPort_impl.h
 * @brief OpenSpliceInPort_impl class
 * @date  $Date: 2019-02-21 03:08:03 $
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

#ifndef RTC_OPENSPLICEINPORT_IMPL_H
#define RTC_OPENSPLICEINPORT_IMPL_H

#define LIBRARY_EXPORTS
#include <rtm/ByteData.h>
#undef LIBRARY_EXPORTS


namespace RTC
{
    class OpenSpliceInPortListenerBase
    {
    public:
        ~OpenSpliceInPortListenerBase();
        virtual void put(RTC::ByteData& data) = 0;
    };

    class OpenSpliceInPortBase
    {
    public:
        virtual ~OpenSpliceInPortBase() = 0;
        virtual bool init(OpenSpliceInPortListenerBase* inportlistener, std::string datatype, std::string idlpath, std::string topic, bool endian=true, bool corbamode=true) = 0;
    private:
    };

    OpenSpliceInPortBase* createOpenSpliceInPort(OpenSpliceInPortListenerBase* inportlistener, std::string datatype, std::string idlpath, std::string topic, bool endian = true, bool corbamode = true);
}


#endif // RTC_OPENSPLICEINPORT_H

