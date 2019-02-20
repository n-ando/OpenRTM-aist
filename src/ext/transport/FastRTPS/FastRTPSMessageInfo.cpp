// -*- C++ -*-
/*!
 * @file  FastRTPSMessageInfo.cpp
 * @brief Fast-RTPS Massage Type Info class
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

#include "FastRTPSMessageInfo.h"

namespace RTC
{
    /*!
     * @if jp
     *
     * @brief デストラクタ
     *
     * @else
     *
     * @brief Destructor
     *
     * @endif
     */
    FastRTPSMessageInfoBase::~FastRTPSMessageInfoBase(void)
    {

    }
    /*!
     * @if jp
     *
     * @brief トピック名を装飾する
     *
     * @param topic 装飾前のトピック名
     * @return 装飾後のトピック名
     *
     * @else
     *
     * @brief
     *
     * @param topic
     * @return
     *
     * @endif
     */
    std::string FastRTPSMessageInfoBase::topic_name(std::string topic)
    {
        return topic;
    }
    /*!
     * @if jp
     *
     * @brief データの型名取得
     *
     * @return 型名
     *
     * @else
     *
     * @brief
     *
     * @return
     *
     * @endif
     */
    std::string FastRTPSMessageInfoBase::data_type()
    { 
        return m_dataType;
    }
}



