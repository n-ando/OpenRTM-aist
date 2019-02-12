// -*- C++ -*-
/*!
 * @file  ROSMessageInfo.cpp
 * @brief ROS Massage Type Info class
 * @date  $Date: 2019-02-05 03:08:03 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2018
 *     Nobuhiko Miyamoto
 *     Robot Innovation Research Center,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *
 *     All rights reserved.
 *
 *
 */

#include "ROSMessageInfo.h"

namespace RTC
{
    std::string ROSMessageInfoBase::type()
    {
        return m_type;
    }

    std::string ROSMessageInfoBase::md5sum()
    { 
        return m_md5sum;
    }

    std::string ROSMessageInfoBase::message_definition()
    {
        return m_message_definition;
    }
}



