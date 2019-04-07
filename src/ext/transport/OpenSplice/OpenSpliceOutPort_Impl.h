// -*- C++ -*-
/*!
 * @file  OpenSpliceOutPort_impl.h
 * @brief OpenSpliceOutPort_impl class
 * @date  $Date: 2019-01-31 03:08:03 $
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

#ifndef RTC_OPENSPLICEOUTPORT_IMPL_H
#define RTC_OPENSPLICEOUTPORT_IMPL_H

#define LIBRARY_EXPORTS
#include <rtm/ByteData.h>
#undef LIBRARY_EXPORTS



namespace RTC
{
    class OpenSpliceOutPortBase
    {
    public:
        virtual ~OpenSpliceOutPortBase() = 0;
        virtual bool init(std::string datatype, std::string idlpath, std::string topic, bool endian = true, bool corbamode = true) = 0;
        virtual bool write(RTC::ByteData& data) = 0;
    };

    OpenSpliceOutPortBase* createOpenSpliceOutPort(std::string datatype, std::string idlpath, std::string topic, bool endian = true, bool corbamode = true);
}



#endif // RTC_OPENSPLICEOUTPORT_H

