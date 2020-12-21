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
#include <vector>
#include <map>
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
        mutable Logger rtclog;
        unsigned int m_subnum;
        unsigned int m_pubnum;
    public:
        /*!
        * @if jp
        * @class PublisherLink
        * @brief PublisherLink クラス
        *
        * ros::Connection、コネクタのIDを格納するクラス
        *
        * @since 2.0.0
        *
        * @else
        * @class PublisherLink
        * @brief PublisherLink class
        *
        * 
        *
        * @since 2.0.0
        *
        * @endif
        */
        class PublisherLink
        {
        public:
            /*!
            * @if jp
            * @brief コンストラクタ
            *
            * @else
            * @brief Constructor
            *
            * @endif
            */
            PublisherLink(void);
            /*!
            * @if jp
            * @brief コンストラクタ
            *
            * @param conn ros::Connection
            * @param num コネクタのID
            *
            * @else
            * @brief Constructor
            *
            * @param conn 
            * @param num 
            *
            * @endif
            */
            PublisherLink(ros::ConnectionPtr conn, int num, const std::string &caller_id, const std::string &topic, const std::string &xmlrpc_uri);
            /*!
            * @if jp
            * @brief コピーコンストラクタ
            *
            * @param obj コピー元 
            *
            * @else
            * @brief Copy Constructor
            *
            * @param obj
            *
            * @endif
            */
            PublisherLink(const PublisherLink &obj);
            /*!
            * @if jp
            * @brief デストラクタ
            *
            *
            * @else
            * @brief Destructor
            *
            *
            * @endif
            */
            ~PublisherLink();
            /*!
            * @if jp
            * @brief ros::Connectionを取得
            *
            * @return ros::Connection
            *
            * @else
            * @brief 
            *
            * @return
            *
            * @endif
            */
            ros::ConnectionPtr getConnection();
            /*!
            * @if jp
            * @brief ros::Connectionを設定
            *
            * @param conn ros::Connection
            *
            * @else
            * @brief 
            *
            * @param conn
            *
            * @endif
            */
            void setConnection(ros::ConnectionPtr conn);
            /*!
            * @if jp
            * @brief コネクタのID取得
            *
            * @return コネクタのID
            *
            * @else
            * @brief 
            *
            * @return
            *
            * @endif
            */
            int getNum();
            /*!
            * @if jp
            * @brief コネクタのID取得
            *
            * @return コネクタのID
            *
            * @else
            * @brief 
            *
            * @return
            *
            * @endif
            */
            const std::string getCallerID() const;
            /*!
            * @if jp
            * @brief コネクタのID取得
            *
            * @return コネクタのID
            *
            * @else
            * @brief 
            *
            * @return
            *
            * @endif
            */
            const std::string getTopic() const;
            /*!
            * @if jp
            * @brief コネクタのID取得
            *
            * @return コネクタのID
            *
            * @else
            * @brief 
            *
            * @return
            *
            * @endif
            */
            const std::string getURI() const;
        private:
            ros::ConnectionPtr m_conn;
            int m_num;
            std::string m_caller_id;
            std::string m_topic;
            std::string m_xmlrpc_uri;
        };

        /*!
        * @if jp
        * @class SubscriberLink
        * @brief SubscriberLink クラス
        *
        * ros::Connection、接続先のノード名、コネクタのIDを格納するクラス
        *
        * @since 2.0.0
        *
        * @else
        * @class SubscriberLink
        * @brief SubscriberLink class
        *
        * 
        *
        * @since 2.0.0
        *
        * @endif
        */
        class SubscriberLink
        {
        public:
            /*!
            * @if jp
            * @brief コンストラクタ
            *
            * @else
            * @brief Constructor
            *
            * @endif
            */
            SubscriberLink();
            /*!
            * @if jp
            * @brief コンストラクタ
            *
            * @param conn ros::Connection
            * @param num コネクタのID
            *
            * @else
            * @brief Constructor
            *
            * @param conn 
            * @param num 
            *
            * @endif
            */
            SubscriberLink(ros::ConnectionPtr conn, int num);
            /*!
            * @if jp
            * @brief コピーコンストラクタ
            *
            * @param obj コピー元 
            *
            * @else
            * @brief Copy Constructor
            *
            * @param obj
            *
            * @endif
            */
            SubscriberLink(const SubscriberLink &obj);
            /*!
            * @if jp
            * @brief デストラクタ
            *
            *
            * @else
            * @brief Destructor
            *
            *
            * @endif
            */
            ~SubscriberLink();
            /*!
            * @if jp
            * @brief 接続先のノード名を設定
            *
            * @param name ノード名
            *
            * @else
            * @brief 
            *
            * @param name
            *
            * @endif
            */
            void setNoneName(std::string& name);
            /*!
            * @if jp
            * @brief 接続先のノード名を取得
            *
            * @return ノード名
            *
            * @else
            * @brief 
            *
            * @return
            *
            * @endif
            */
            const std::string getNodeName() const;
            /*!
            * @if jp
            * @brief ros::Connectionを設定
            *
            * @param conn ros::Connection
            *
            * @else
            * @brief 
            *
            * @param conn
            *
            * @endif
            */
            void setConnection(ros::ConnectionPtr conn);
            /*!
            * @if jp
            * @brief ros::Connectionを取得
            *
            * @return ros::Connection
            *
            * @else
            * @brief 
            *
            * @return
            *
            * @endif
            */
            ros::ConnectionPtr getConnection();
            /*!
            * @if jp
            * @brief コネクタのID取得
            *
            * @return コネクタのID
            *
            * @else
            * @brief 
            *
            * @return
            *
            * @endif
            */
            int getNum();
        private:
            std::string m_nodename;
            ros::ConnectionPtr m_conn;
            int m_num;
        };
        std::vector<PublisherLink> m_tcp_pub_connecters;
        std::vector<SubscriberLink> m_tcp_sub_connecters;
        /*!
         * @if jp
         * @brief Publisher
         *
         * @return 
         *
         * @else
         * @brief
         *
         *
         * @return 
         *
         * @endif
         */
        std::vector<PublisherLink> & getPublisherLinkList();
        /*!
         * @if jp
         * @brief Subscriber
         *
         * @return 
         *
         * @else
         * @brief
         *
         *
         * @return 
         *
         * @endif
         */
        std::vector<SubscriberLink> & getSubscriberLinkList();
        /*!
         * @if jp
         * @brief サブスクライバーの存在確認
         * 
         * @param connection サブスクライバー
         * @param caller_id サブスクライバー
         * @param caller_id サブスクライバー
         * @param xmlrpc_uri サブスクライバー
         * @return True：存在する
         *
         * @else
         * @brief 
         *
         * @param connection 
         * @param caller_id 
         * @param caller_id 
         * @param xmlrpc_uri 
         * @return 
         * 
         *
         * @endif
         */
        bool addPublisherLink(ros::ConnectionPtr& connection, const std::string &caller_id, const std::string &topic, const std::string &xmlrpc_uri);
        /*!
         * @if jp
         * @brief サブスクライバーの存在確認
         * 
         * @param connection サブスクライバー
         * @return True：存在する
         *
         * @else
         * @brief 
         *
         * @param connection 
         * @return 
         * 
         *
         * @endif
         */
        bool removePublisherLink(ros::ConnectionPtr& connection);
        /*!
         * @if jp
         * @brief サブスクライバーの存在確認
         * 
         * @param connection サブスクライバー
         * @param caller_id サブスクライバー
         * @param caller_id サブスクライバー
         * @param xmlrpc_uri サブスクライバー
         * @return True：存在する
         *
         * @else
         * @brief 
         *
         * @param connection 
         * @param caller_id 
         * @param caller_id 
         * @param xmlrpc_uri 
         * @return 
         * 
         *
         * @endif
         */
        bool addSubscriberLink(ros::ConnectionPtr& connection);
        /*!
         * @if jp
         * @brief サブスクライバーの存在確認
         * 
         * @param connection サブスクライバー
         * @return True：存在する
         *
         * @else
         * @brief 
         *
         * @param connection 
         * @return 
         * 
         *
         * @endif
         */
        bool removeSubscriberLink(ros::ConnectionPtr& connection);
        /*!
         * @if jp
         * @brief サブスクライバーの存在確認
         * 
         * @param connection サブスクライバー
         * @return True：存在する
         *
         * @else
         * @brief 
         *
         * @param connection 
         * @return 
         * 
         *
         * @endif
         */
        PublisherLink* getPublisherLink(const ros::ConnectionPtr& connection);
        /*!
         * @if jp
         * @brief サブスクライバーの存在確認
         * 
         * @param connection サブスクライバー
         * @return True：存在する
         *
         * @else
         * @brief 
         *
         * @param connection 
         * @return 
         * 
         *
         * @endif
         */
        SubscriberLink* getSubscriberLink(const ros::ConnectionPtr& connection);
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
            RTC_PARANOID(("connectTCP()"));

            ros::ConnectionPtr tcp_connecter = boost::make_shared<ros::Connection>();
            
            addSubscriberLink(tcp_connecter);
            tcp_connecter->initialize(transport, true, boost::bind(&ROSTopicManager::onConnectionHeaderReceived, this, _1, _2));
            
            if(!tcp_connecter->isDropped())
            {
                RTC_VERBOSE(("Connector created."));      
                return;
            }
            else
            {
                removeSubscriberLink(tcp_connecter);
                RTC_VERBOSE(("Connector creation failed."));
                return;
            }
        }

       /*!
        * @if jp
        * @brief ヘッダ情報受信時のコールバック関数
        *
        *
        * @param conn ros::ConnectionPtr
        * @param header ヘッダ情報
        *
        * @return true：問題なし、false：ヘッダが不正
        * 
        * @else
        * @brief 
        *
        *
        * @param conn 
        * @param header 
        * 
        * @return
        *
        * @endif
        */
        bool onConnectionHeaderReceived(const ros::ConnectionPtr& conn, const ros::Header& header)
        {
            RTC_VERBOSE(("onConnectionHeaderReceived()"));

            bool ret = false;
            for(auto & publisher : m_publishers) 
            {
                if(publisher->onConnectionHeaderReceived(conn, header) == true)
                {
                    ret = true;
                }
            }
            return ret;
        }
    protected:
    };
}




#endif // RTC_ROSTOPICMANAGER_H

