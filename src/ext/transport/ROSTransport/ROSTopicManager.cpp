// -*- C++ -*-
/*!
 * @file  ROSTopicManager.cpp
 * @brief ROSTopicManager class
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

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <WinSock2.h>
#endif
#include "ROSTopicManager.h"
#include <ros/xmlrpc_manager.h>
#include <ros/network.h>
#include <xmlrpcpp/XmlRpcSocket.h>
#include <ros/connection.h>
#include <ros/connection_manager.h>


namespace ros
{
  namespace network
  {
    void init(const M_string& remappings);
  }
}


namespace RTC
{
  ROSTopicManager* ROSTopicManager::manager = nullptr;
  std::mutex ROSTopicManager::mutex;


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
  ROSTopicManager::ROSTopicManager()
  : rtclog("ROSTopicManager"),
    m_subnum(0),
    m_pubnum(0)
  {

  }

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
  ROSTopicManager::ROSTopicManager(const ROSTopicManager &/*mgr*/)
  : rtclog("ROSTopicManager")
  {
    
  }
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
  ROSTopicManager::~ROSTopicManager()
  {
    
  }

  /*!
   * @if jp
   * @brief トピックマネージャ開始
   *
   *
   * @else
   * @brief 
   *
   * 
   *
   * @endif
   */
  void ROSTopicManager::start()
  {
    ros::M_string remappings;
    ros::network::init(remappings);

    m_xmlrpc_manager = ros::XMLRPCManager::instance();

    m_xmlrpc_manager->bind("requestTopic", boost::bind(&ROSTopicManager::requestTopicCallback, this, _1, _2));
    m_xmlrpc_manager->bind("publisherUpdate", boost::bind(&ROSTopicManager::pubUpdateCallback, this, _1, _2));
    m_xmlrpc_manager->bind("getSubscriptions", boost::bind(&ROSTopicManager::getSubscriptionsCallback, this, _1, _2));
    m_xmlrpc_manager->bind("getPublications", boost::bind(&ROSTopicManager::getPublicationsCallback, this, _1, _2));
    m_xmlrpc_manager->bind("getBusStats", boost::bind(&ROSTopicManager::getBusStatsCallback, this, _1, _2));
    m_xmlrpc_manager->bind("getBusInfo", boost::bind(&ROSTopicManager::getBusInfoCallback, this, _1, _2));
    m_xmlrpc_manager->bind("getPid", boost::bind(&ROSTopicManager::getPidCallback, this, _1, _2));

    m_poll_manager = ros::PollManager::instance();
    m_poll_manager->start();
    m_tcpserver_transport = boost::make_shared<ros::TransportTCP>(&m_poll_manager->getPollSet());
    
    m_tcpserver_transport->listen(ros::network::getTCPROSPort(), 
                            100, 
                            boost::bind(&ROSTopicManager::tcprosAcceptConnection, this, _1));

    m_xmlrpc_manager->start();
  }

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
  void ROSTopicManager::shutdown()
  {
      m_xmlrpc_manager->shutdown();
      m_tcpserver_transport->close();
      m_poll_manager->shutdown();
  }

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
  void ROSTopicManager::requestTopicCallback(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
  {
      if (params.getType() != XmlRpc::XmlRpcValue::TypeArray)
      {
          result = ros::xmlrpc::responseInt(0, ros::console::g_last_error_message, 0);
          return;
      }
      if (params.size() < 3)
      {
          result = ros::xmlrpc::responseInt(0, ros::console::g_last_error_message, 0);
          return;
      }

      if (params[0].getType() != XmlRpc::XmlRpcValue::TypeString)
      {
          result = ros::xmlrpc::responseInt(0, ros::console::g_last_error_message, 0);
          return;
      }
      if (params[1].getType() != XmlRpc::XmlRpcValue::TypeString)
      {
          result = ros::xmlrpc::responseInt(0, ros::console::g_last_error_message, 0);
          return;
      }

      std::string callerid = params[0];
      std::string topic = params[1];
      
      XmlRpc::XmlRpcValue protocols = params[2];
      if (protocols.getType() != XmlRpc::XmlRpcValue::TypeArray)
      {
          result = ros::xmlrpc::responseInt(0, ros::console::g_last_error_message, 0);
          return;
      }
      for(int i=0;i < protocols.size();i++)
      {
        if (protocols[i].getType() != XmlRpc::XmlRpcValue::TypeArray)
        {
          result = ros::xmlrpc::responseInt(0, ros::console::g_last_error_message, 0);
          return;
        }
        if (protocols[i][0].getType() != XmlRpc::XmlRpcValue::TypeString)
        {
            result = ros::xmlrpc::responseInt(0, ros::console::g_last_error_message, 0);
            return;
        }
        std::string protocol = std::string(protocols[i][0]);
      
        if (protocol == std::string("TCPROS"))
        {
          XmlRpc::XmlRpcValue tcpros_params;
          
          tcpros_params[0] = std::string("TCPROS");
          tcpros_params[1] = ros::network::getHost();
          tcpros_params[2] = int(m_tcpserver_transport->getServerPort());
          result.setSize(3);
          result[0] = int(1);
          result[1] = std::string();
          result[2] = tcpros_params;
          return;
        }
      }
      result = ros::xmlrpc::responseInt(0, ros::console::g_last_error_message, 0);

  }
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
  void ROSTopicManager::getSubscriptionsCallback(XmlRpc::XmlRpcValue& /*params*/, XmlRpc::XmlRpcValue& result)
  {
    result[0] = 1;
    result[1] = std::string("subscriptions");
    XmlRpc::XmlRpcValue subs;
    subs.setSize(0);
    for(auto & subscriber : m_subscribers)
    {
      XmlRpc::XmlRpcValue sub;
      sub[0] = subscriber->getName();
      sub[1] = subscriber->datatype();
      subs[subs.size()] = sub;
    }
    result[2] = subs;
  }
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
  void ROSTopicManager::getPublicationsCallback(XmlRpc::XmlRpcValue& /*params*/, XmlRpc::XmlRpcValue& result)
  {
    result[0] = 1;
    result[1] = std::string("publications");
    XmlRpc::XmlRpcValue pubs;
    pubs.setSize(0);
    for(auto & publisher : m_publishers)
    {
      XmlRpc::XmlRpcValue pub;
      pub[0] = publisher->getName();
      pub[1] = publisher->datatype();
      pubs[pubs.size()] = pub;
    }
    result[2] = pubs;
  }
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
  void ROSTopicManager::getBusStatsCallback(XmlRpc::XmlRpcValue& /*params*/, XmlRpc::XmlRpcValue& /*result*/)
  {
  }

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
  void ROSTopicManager::getBusInfoCallback(XmlRpc::XmlRpcValue& /*params*/, XmlRpc::XmlRpcValue& result)
  {
    result[0] = 1;
    result[1] = std::string("bus info");
  
    XmlRpc::XmlRpcValue bus;
    for(auto & subscriber : m_subscribers)
    {
      subscriber->getInfo(result[2]);
    }

    for(auto & publisher : m_publishers)
    {
      publisher->getInfo(result[2]);
    }

  }
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
  void ROSTopicManager::getPidCallback(XmlRpc::XmlRpcValue& /*params*/, XmlRpc::XmlRpcValue& /*result*/)
  {
  }

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
  void ROSTopicManager::pubUpdateCallback(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result)
  {
    if (params.getType() != XmlRpc::XmlRpcValue::TypeArray)
    {
        result = ros::xmlrpc::responseInt(0, ros::console::g_last_error_message, 0);
        return;
    }
    if (params.size() < 3)
    {
        result = ros::xmlrpc::responseInt(0, ros::console::g_last_error_message, 0);
        return;
    }

    if (params[0].getType() != XmlRpc::XmlRpcValue::TypeString)
    {
        result = ros::xmlrpc::responseInt(0, ros::console::g_last_error_message, 0);
        return;
    }
    if (params[1].getType() != XmlRpc::XmlRpcValue::TypeString)
    {
        result = ros::xmlrpc::responseInt(0, ros::console::g_last_error_message, 0);
        return;
    }

    std::string caller_id = params[0];
    std::string topic = params[1];
    
    
    if (params[2].getType() != XmlRpc::XmlRpcValue::TypeArray)
    {
    
      result = ros::xmlrpc::responseInt(0, ros::console::g_last_error_message, 0);
      return;
    }
    
    std::vector<std::string> new_ = std::vector<std::string>();
    std::vector<std::string> old_ = m_cons[topic];
    
    for (int i = 0; i < params[2].size(); i++)
    {
      if (params[2][i].getType() != XmlRpc::XmlRpcValue::TypeString)
      {
          result = ros::xmlrpc::responseInt(0, ros::console::g_last_error_message, 0);
          break;
      }
      std::string xmlrpc_uri = params[2][i];
      if (xmlrpc_uri.empty())
      {
          result = ros::xmlrpc::responseInt(0, ros::console::g_last_error_message, 0);
          break;
      }
      bool already_connected = false;
      for (auto con = m_tcp_pub_connecters.begin(); con != m_tcp_pub_connecters.end(); con++)
      {
        if(con->getCallerID() == caller_id && con->getTopic() == topic && con->getURI() == xmlrpc_uri)
        {
          RTC_WARN(("%s already connected", xmlrpc_uri.c_str()));
          if(con->getConnection()->isDropped())
          {
            RTC_ERROR(("delete connector: %s", xmlrpc_uri.c_str()));
            con = m_tcp_pub_connecters.erase(con);
          }
          else
          {
            already_connected = true;
            break;
          }
        }
      }
      
      if(!already_connected)
      {
        for(auto & subscriber : m_subscribers)
        {
          subscriber->connectTCP(caller_id, topic, xmlrpc_uri);
        }
      }
      new_.emplace_back(xmlrpc_uri);
    }

    for(auto & old_uri : old_)
    {
      std::vector<std::string>::iterator itr_uri = std::find(new_.begin(), new_.end(), old_uri);
      size_t index = std::distance( new_.begin(), itr_uri );
    
      if (index == new_.size()) 
      {
        for (auto con = m_tcp_pub_connecters.begin(); con != m_tcp_pub_connecters.end(); con++)
        {
          if(con->getCallerID() == caller_id && con->getTopic() == topic && con->getURI() == old_uri)
          {
            con = m_tcp_pub_connecters.erase(con);
          }
        }
      }
    }
    
    result = ros::xmlrpc::responseInt(1, "", 0);
 
  }



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
  void ROSTopicManager::addPublisher(ROSOutPort *publisher)
  {

    if(!existPublisher(publisher))
    {
      m_publishers.emplace_back(publisher);
    }
  }


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
  void ROSTopicManager::addSubscriber(ROSInPort *subscriber)
  {
    if(!existSubscriber(subscriber))
    {
      m_subscribers.emplace_back(subscriber);
    }
    
  }

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
  bool ROSTopicManager::removePublisher(ROSOutPort *publisher)
  {
    if(existPublisher(publisher))
    {
      m_publishers.erase(remove(m_publishers.begin(), m_publishers.end(), publisher), m_publishers.end());
      return true;
    }
    return false;
  }

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
  bool ROSTopicManager::removeSubscriber(ROSInPort *subscriber)
  {
    if(existSubscriber(subscriber))
    {
      m_subscribers.erase(remove(m_subscribers.begin(), m_subscribers.end(), subscriber), m_subscribers.end());
      return true;
    }
    return false;
  }


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
  bool ROSTopicManager::existPublisher(ROSOutPort *publisher)
  {
    std::vector<ROSOutPort*>::iterator itr = std::find(m_publishers.begin(), m_publishers.end(), publisher);
    size_t index = std::distance( m_publishers.begin(), itr );
    
    return (index != m_publishers.size());
  }


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
  bool ROSTopicManager::existSubscriber(ROSInPort *subscriber)
  {
    std::vector<ROSInPort*>::iterator itr = std::find(m_subscribers.begin(), m_subscribers.end(), subscriber);
    size_t index = std::distance( m_subscribers.begin(), itr );
    return (index != m_subscribers.size());
  }

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
  std::vector<ROSTopicManager::PublisherLink> & ROSTopicManager::getPublisherLinkList()
  {
    return m_tcp_pub_connecters;
  }
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
  std::vector<ROSTopicManager::SubscriberLink> & ROSTopicManager::getSubscriberLinkList()
  {
    return m_tcp_sub_connecters;
  }


  /*!
   * @if jp
   * @brief サブスクライバーの存在確認
   * 
   * @param connection サブスクライバー
   * @param caller_id サブスクライバー
   * @param topic サブスクライバー
   * @param xmlrpc_uri サブスクライバー
   * @return True：存在する
   *
   * @else
   * @brief 
   *
   * @param connection 
   * @param caller_id 
   * @param topic 
   * @param xmlrpc_uri 
   * @return 
   * 
   *
   * @endif
   */
  bool ROSTopicManager::addPublisherLink(ros::ConnectionPtr& connection, const std::string &caller_id, const std::string &topic, const std::string &xmlrpc_uri)
  {
    m_tcp_pub_connecters.push_back(ROSTopicManager::PublisherLink(connection, m_pubnum, caller_id, topic, xmlrpc_uri));
    m_pubnum++;
    return true;
  }
  /*!
   * @if jp
   * @brief サブスクライバーの存在確認
   * 
   * @param uri サブスクライバー
   * @return True：存在する
   *
   * @else
   * @brief 
   *
   * @param uri 
   * @return 
   * 
   *
   * @endif
   */
  bool ROSTopicManager::removePublisherLink(ros::ConnectionPtr& connection)
  {
    for (auto con = m_tcp_pub_connecters.begin(); con != m_tcp_pub_connecters.end(); con++)
    {
      if(con->getConnection() == connection)
      {
        con->getConnection()->drop(ros::Connection::Destructing);
        con = m_tcp_pub_connecters.erase(con);
        return true;
      }
    }
    return false;
  }
  /*!
   * @if jp
   * @brief サブスクライバーの存在確認
   * 
   * @param connection サブスクライバー
   * @param caller_id サブスクライバー
   * @param topic サブスクライバー
   * @param xmlrpc_uri サブスクライバー
   * @return True：存在する
   *
   * @else
   * @brief 
   *
   * @param connection 
   * @param caller_id 
   * @param topic 
   * @param xmlrpc_uri 
   * @return 
   * 
   *
   * @endif
   */
  bool ROSTopicManager::addSubscriberLink(ros::ConnectionPtr& connection)
  {
    m_tcp_sub_connecters.push_back(ROSTopicManager::SubscriberLink(connection, m_subnum));
    m_subnum++;
    return true;
  }
  /*!
   * @if jp
   * @brief サブスクライバーの存在確認
   * 
   * @param uri サブスクライバー
   * @return True：存在する
   *
   * @else
   * @brief 
   *
   * @param uri 
   * @return 
   * 
   *
   * @endif
   */
  bool ROSTopicManager::removeSubscriberLink(ros::ConnectionPtr& connection)
  {
    for (auto con = m_tcp_sub_connecters.begin(); con != m_tcp_sub_connecters.end(); con++)
    {
      if(con->getConnection() == connection)
      {
        con->getConnection()->drop(ros::Connection::Destructing);
        con = m_tcp_sub_connecters.erase(con);
        return true;
      }
    }
    return false;
  }


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
  ROSTopicManager::PublisherLink* ROSTopicManager::getPublisherLink(const ros::ConnectionPtr& connection)
  {
    for(auto & tcp_connecter : m_tcp_pub_connecters)
    {
      if(tcp_connecter.getConnection() == connection)
      {
        return &tcp_connecter;
      }
    }
    return nullptr;
  }
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
  ROSTopicManager::SubscriberLink* ROSTopicManager::getSubscriberLink(const ros::ConnectionPtr& connection)
  {
    for(auto & tcp_connecter : m_tcp_sub_connecters)
    {
      if(tcp_connecter.getConnection() == connection)
      {
        return &tcp_connecter;
      }
    }
    return nullptr;
  }

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
  ROSTopicManager* ROSTopicManager::init()
  {
    std::lock_guard<std::mutex> guard(mutex);
    if (!manager)
    {
      manager = new ROSTopicManager();
      manager->start();
    }
    return manager;
  }

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
  ROSTopicManager& ROSTopicManager::instance()
  {
    std::lock_guard<std::mutex> guard(mutex);
    if (!manager)
    {
      manager = new ROSTopicManager();
      manager->start();
    }
    return *manager;
  }

  /*!
   * @if jp
   * @brief ROSTopicManagerが初期化されている場合に終了処理を呼び出す
   *
   *
   * @else
   * @brief
   *
   * @return
   *
   *
   * @endif
   */
  void ROSTopicManager::shutdown_global()
  {
      std::lock_guard<std::mutex> guard(mutex);
      if (manager)
      {
          manager->shutdown();
      }
  }

    /*!
   * @if jp
   * @brief コンストラクタ
   *
   * @else
   * @brief Constructor
   *
   * @endif
   */
  ROSTopicManager::PublisherLink::PublisherLink() : m_num(0)
  {
  }
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
  ROSTopicManager::PublisherLink::PublisherLink(ros::ConnectionPtr conn, int num, const std::string &caller_id, const std::string &topic, const std::string &xmlrpc_uri)
  {
    m_conn = conn;
    m_num = num;
    m_caller_id = caller_id;
    m_topic = topic;
    m_xmlrpc_uri = xmlrpc_uri;
  }
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
  ROSTopicManager::PublisherLink::PublisherLink(const PublisherLink &obj)
  {
    m_conn = obj.m_conn;
    m_num = obj.m_num;
    m_caller_id = obj.m_caller_id;
    m_topic = obj.m_topic;
    m_xmlrpc_uri = obj.m_xmlrpc_uri;
  }
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
  ROSTopicManager::PublisherLink::~PublisherLink()
  {

  }
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
  ros::ConnectionPtr ROSTopicManager::PublisherLink::getConnection()
  {
    return m_conn;
  }
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
  void ROSTopicManager::PublisherLink::setConnection(ros::ConnectionPtr conn)
  {
    m_conn = conn;
  }
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
  int ROSTopicManager::PublisherLink::getNum()
  {
    return m_num;
  }

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
  const std::string ROSTopicManager::PublisherLink::getCallerID() const
  {
    return m_caller_id;
  }

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
  const std::string ROSTopicManager::PublisherLink::getTopic() const
  {
    return m_topic;
  }

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
  const std::string ROSTopicManager::PublisherLink::getURI() const
  {
    return m_xmlrpc_uri;
  }

  /*!
   * @if jp
   * @brief コンストラクタ
   *
   * @else
   * @brief Constructor
   *
   * @endif
   */
  ROSTopicManager::SubscriberLink::SubscriberLink() : m_num(0)
  {
  }

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
  ROSTopicManager::SubscriberLink::SubscriberLink(ros::ConnectionPtr conn, int num)
  {
    m_conn = conn;
    m_num = num;
  }
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
  ROSTopicManager::SubscriberLink::SubscriberLink(const SubscriberLink &obj)
  {
    m_conn = obj.m_conn;
    m_nodename = obj.m_nodename;
    m_num = obj.m_num;
  }
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
  ROSTopicManager::SubscriberLink::~SubscriberLink()
  {

  }
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
  void ROSTopicManager::SubscriberLink::setNoneName(std::string& name)
  {
    m_nodename = name;
  }
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
  const std::string ROSTopicManager::SubscriberLink::getNodeName() const
  {
    return m_nodename;
  }
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
  void ROSTopicManager::SubscriberLink::setConnection(ros::ConnectionPtr conn)
  {
    m_conn = conn;
  }
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
  ros::ConnectionPtr ROSTopicManager::SubscriberLink::getConnection()
  {
    return m_conn;
  }
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
  int ROSTopicManager::SubscriberLink::getNum()
  {
    return m_num;
  }
}

