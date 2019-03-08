// -*- C++ -*-
/*!
 * @file  FastRTPSManager.h
 * @brief FastRTPSManager class
 * @date  $Date: 2019-02-04 03:08:03 $
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

#ifndef RTC_FASTRTPSMANAGER_H
#define RTC_FASTRTPSMANAGER_H

#include "FastRTPSInPort.h"
#include "FastRTPSOutPort.h"
#include <map>
#include <vector>
#include <coil/Mutex.h>
#include <fastrtps/fastrtps_fwd.h>

namespace RTC
{
    /*!
     * @if jp
     * @class FastRTPSManager
     * @brief FastRTPSManager クラス
     *
     * FastRTPSを管理するクラス
     *
     *
     * @since 2.0.0
     *
     * @else
     * @class FastRTPSManager
     * @brief FastRTPSManager class
     *
     * 
     *
     * @since 2.0.0
     *
     * @endif
     */
    class FastRTPSManager
    {
        typedef coil::Mutex Mutex;
        typedef coil::Guard<Mutex> Guard;
    public:
        /*!
         * @if jp
         * @brief コンストラクタ
         *
         * コンストラクタ
         *
         * @else
         * @brief Constructor
         *
         * Constructor
         *
         * @endif
         */
        FastRTPSManager();
        /*!
         * @if jp
         * @brief コピーコンストラクタ
         *
         * @param manager FastRTPSManager
         *
         * @else
         * @brief Copy Constructor
         *
         * @param manager FastRTPSManager
         *
         * @endif
         */
        FastRTPSManager(const FastRTPSManager &manager);
        /*!
         * @if jp
         * @brief デストラクタ
         *
         * デストラクタ
         *
         * @else
         * @brief Destructor
         *
         * Destructor
         *
         * @endif
         */
        ~FastRTPSManager();
        /*!
         * @if jp
         * @brief マネージャ開始
         *
         *
         * @else
         * @brief 
         *
         * 
         *
         * @endif
         */
        void start();

        /*!
         * @if jp
         * @brief Participant取得
         *
         * @return Participant
         *
         * @else
         * @brief get Participant
         *
         * @return Participant
         *
         * @endif
         */
        eprosima::fastrtps::Participant *getParticipant();
        /*!
         * @if jp
         * @brief 型の登録
         *
         * @param type 登録するデータのインスタンス
         * @return true：登録成功、false：登録失敗
         *
         * @else
         * @brief 
         *
         * @param type
         * @return 
         *
         * @endif
         */
        bool registerType(eprosima::fastrtps::TopicDataType* type);
        /*!
         * @if jp
         * @brief 型の登録解除
         *
         * @param name 型名
         * @return true：解除成功、false：解除失敗
         *
         * @else
         * @brief
         *
         * @param name
         * @return
         *
         * @endif
         */
        bool unregisterType(const char* name);


        /*!
         * @if jp
         * @brief 初期化関数
         * 
         * @return インスタンス
         *
         * @else
         * @brief 
         *
         * @return 
         * 
         *
         * @endif
         */
        static FastRTPSManager* init();
        /*!
         * @if jp
         * @brief インスタンス取得
         * 
         * @return インスタンス
         *
         * @else
         * @brief 
         *
         * @return 
         * 
         *
         * @endif
         */
        static FastRTPSManager& instance();
    private:
        static FastRTPSManager* manager;
        static Mutex mutex;
	    eprosima::fastrtps::Participant *m_participant;
    protected:
        //mutable Logger rtclog;
    };
}




#endif // RTC_FASTRTPSMANAGER_H

