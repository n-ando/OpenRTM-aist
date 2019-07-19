// -*- C++ -*-
/*!
 * @file  ROSTopicManager.h
 * @brief ROSTopicManager class
 * @date  $Date: 2019-02-04 03:08:03 $
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

#ifndef RTC_ROSTOPICMANAGER_H
#define RTC_ROSTOPICMANAGER_H

#include "ROSInPort.h"
#include "ROSOutPort.h"
#include <map>
#include <vector>
#include <xmlrpcpp/XmlRpc.h>
#include <ros/poll_manager.h>
#include <ros/transport/transport_tcp.h>

namespace RTC
{
    /*!
     * @if jp
     * @class ROSTopicManager
     * @brief ROSTopicManager クラス
     *
     * ROSのトピックを管理するクラス
     *
     *
     * @since 2.0.0
     *
     * @else
     * @class ROSTopicManager
     * @brief ROSTopicManager class
     *
     * 
     *
     * @since 2.0.0
     *
     * @endif
     */
    class ROSTopicManager
    {
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
        ROSTopicManager();
        /*!
         * @if jp
         * @brief コピーコンストラクタ
         *
         * @param manager ROSTopicManager
         *
         * @else
         * @brief Copy Constructor
         *
         * @param manager ROSTopicManager
         *
         * @endif
         */
        ROSTopicManager(const ROSTopicManager &manager);
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
        ~ROSTopicManager();
        /*!
         * @if jp
         * @brief トピックマネージャ開始
         * XML-RPC、TCPサーバー、ポールマネージャを開始する
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
         * @brief 終了処理
         * XML-RPC、TCPサーバー、ポールマネージャを終了する
         *
         * @else
         * @brief
         *
         *
         *
         * @endif
         */
        void shutdown();
        /*!
         * @if jp
         * @brief requestTopic関数リモート呼び出し時のコールバック関数
         * サブスクライバーからの接続時に呼ばれる
         * 
         * @param params
         * @param result
         *
         * @else
         * @brief 
         *
         * @param params
         * @param result
         * 
         *
         * @endif
         */
        void requestTopicCallback(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result);
        /*!
         * @if jp
         * @brief pubUpdate関数リモート呼び出し時のコールバック関数
         * パブリッシャーの更新時に呼ばれる
         * 
         * @param params
         * @param result
         *
         * @else
         * @brief 
         *
         * @param params
         * @param result
         * 
         *
         * @endif
         */
        void pubUpdateCallback(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result);
        /*!
         * @if jp
         * @brief パブリッシャーの追加
         * 
         * @param publisher パブリッシャー
         *
         * @else
         * @brief add publisher
         *
         * @param publisher 
         * 
         *
         * @endif
         */
        void addPublisher(ROSOutPort *publisher);
        /*!
         * @if jp
         * @brief サブスクライバーの追加
         * 
         * @param subscriber サブスクライバー
         *
         * @else
         * @brief add subscriber
         *
         * @param subscriber 
         * 
         *
         * @endif
         */
        void addSubscriber(ROSInPort *subscriber);
        /*!
         * @if jp
         * @brief パブリッシャーの削除
         * 
         * @param publisher パブリッシャー
         *
         * @else
         * @brief remove publisher
         *
         * @param publisher 
         * 
         *
         * @endif
         */
        bool removePublisher(ROSOutPort *publisher);
        /*!
         * @if jp
         * @brief サブスクライバーの削除
         * 
         * @param subscriber サブスクライバー
         *
         * @else
         * @brief remove subscriber
         *
         * @param subscriber 
         * 
         *
         * @endif
         */
        bool removeSubscriber(ROSInPort *subscriber);
        /*!
         * @if jp
         * @brief パブリッシャーの存在確認
         * 
         * @param publisher パブリッシャー
         * @return True：存在する
         *
         * @else
         * @brief 
         *
         * @param publisher 
         * @return 
         * 
         *
         * @endif
         */
        bool existPublisher(ROSOutPort *publisher);
        /*!
         * @if jp
         * @brief サブスクライバーの存在確認
         * 
         * @param subscriber サブスクライバー
         * @return True：存在する
         *
         * @else
         * @brief 
         *
         * @param subscriber 
         * @return 
         * 
         *
         * @endif
         */
        bool existSubscriber(ROSInPort *subscriber);
        /*!
         * @if jp
         * @brief TCP接続受け入れ時のコールバック関数
         * 
         * @param transport ros::Transport
         *
         * @else
         * @brief 
         *
         * @param transport 
         * @return 
         * 
         *
         * @endif
         */
        void tcprosAcceptConnection(const ros::TransportTCPPtr& transport)
        {
            for(auto & publisher : m_publishers) 
            {
                publisher->connectTCP(transport);
            }
        };

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
        static ROSTopicManager* init();
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
        static ROSTopicManager& instance();
        /*!
         * @if jp
         * @brief ROSTopicManagerが初期化されている場合に終了処理を呼び出す
         *
         *
         * @else
         * @brief
         *
         *
         *
         * @endif
         */
        static void shutdown_global();
        /*!
         * @if jp
         * @brief Subscriber一覧を取得
         *
         * @param params 
         * @param result 
         *
         * @else
         * @brief
         *
         *
         * @param params 
         * @param result 
         *
         * @endif
         */
        void getSubscriptionsCallback(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result);
        /*!
         * @if jp
         * @brief Publisher一覧を取得
         *
         * @param params 
         * @param result 
         *
         * @else
         * @brief
         *
         *
         * @param params 
         * @param result 
         *
         * @endif
         */
        void getPublicationsCallback(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result);
        /*!
         * @if jp
         * @brief コネクタの状態取得
         *
         * @param params 
         * @param result 
         *
         * @else
         * @brief
         *
         *
         * @param params 
         * @param result 
         *
         * @endif
         */
        void getBusStatsCallback(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result);
        /*!
         * @if jp
         * @brief コネクタの情報取得
         *
         * @param params 
         * @param result 
         *
         * @else
         * @brief
         *
         *
         * @param params 
         * @param result 
         *
         * @endif
         */
        void getBusInfoCallback(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result);
        /*!
         * @if jp
         * @brief プロセスID取得
         *
         * @param params 
         * @param result 
         *
         * @else
         * @brief
         *
         *
         * @param params 
         * @param result 
         *
         * @endif
         */
        void getPidCallback(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result);
    private:
        static ROSTopicManager* manager;
        static std::mutex mutex;
        std::vector<ROSOutPort*> m_publishers;
        std::vector<ROSInPort*> m_subscribers;
        ros::PollManagerPtr m_poll_manager;
        ros::TransportTCPPtr m_tcpserver_transport;
        ros::XMLRPCManagerPtr m_xmlrpc_manager;
        std::map<std::string, std::vector<std::string>> m_cons;
    protected:
    };
}




#endif // RTC_ROSTOPICMANAGER_H

