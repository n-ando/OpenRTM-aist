// -*- C++ -*-
/*!
 * @file  OpenSpliceManager.cpp
 * @brief OpenSpliceManager class
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


#include "OpenSpliceManager.h"

#include <coil/process.h>
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <rapidxml_iterators.hpp>
#include "ccpp_CORBACdrData.h"
#include <iostream>



namespace RTC
{
  OpenSpliceManager* OpenSpliceManager::manager = NULL;
  coil::Mutex OpenSpliceManager::mutex;


  TopicType::TopicType()
  {

  }
  TopicType::TopicType(std::string &inid, std::string &inkeys, std::string &indescriptor) :
          id(inid), keys(inkeys), descriptor(indescriptor)
  {

  }
  TopicType::TopicType(const TopicType &obj) {
      id = obj.id;
      keys = obj.keys;
      descriptor = obj.descriptor;
  }
  TopicType& TopicType::operator = (const TopicType& obj) {
      id = obj.id;
      keys = obj.keys;
      descriptor = obj.descriptor;
      return *this;
  }

  template<typename Ch = char>
  class children {
      typedef rapidxml::node_iterator<Ch> iterator_type;
  public:
      explicit children(rapidxml::xml_node<Ch>* node) : node_(node) {}
      iterator_type begin() const { return iterator_type(node_); }
      iterator_type end() const { return iterator_type(); }
  private:
      rapidxml::xml_node<Ch>* node_;
  };


  static const std::string RetCodeName[13] =
  {
      "DDS_RETCODE_OK", "DDS_RETCODE_ERROR", "DDS_RETCODE_UNSUPPORTED",
      "DDS_RETCODE_BAD_PARAMETER", "DDS_RETCODE_PRECONDITION_NOT_MET",
      "DDS_RETCODE_OUT_OF_RESOURCES", "DDS_RETCODE_NOT_ENABLED",
      "DDS_RETCODE_IMMUTABLE_POLICY", "DDS_RETCODE_INCONSISTENT_POLICY",
      "DDS_RETCODE_ALREADY_DELETED", "DDS_RETCODE_TIMEOUT", "DDS_RETCODE_NO_DATA",
      "DDS_RETCODE_ILLEGAL_OPERATION"
  };


  bool OpenSpliceManager::checkStatus(DDS::ReturnCode_t status, const char *info)
  {
      if (status != DDS::RETCODE_OK && status != DDS::RETCODE_NO_DATA) {
          std::cerr << "Error in " << info << "with return code : " << RetCodeName[status].c_str() << std::endl;
          return false;
      }
      return true;
  }

  bool OpenSpliceManager::checkHandle(void *handle, std::string info)
  {
      if (!handle) {
          std::cerr << "Error in " << info.c_str() << ": Creation failed: invalid handle" << std::endl;
          return false;
      }
      return true;
  }

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
  OpenSpliceManager::OpenSpliceManager()// : rtclog("OpenSpliceManager")
  {

  }

  /*!
   * @if jp
   * @brief コピーコンストラクタ
   *  
   * @param manager OpenSpliceManager
   *
   * @else
   * @brief Copy Constructor
   *
   * @param manager OpenSpliceManager
   *
   * @endif
   */
  OpenSpliceManager::OpenSpliceManager(const OpenSpliceManager &/*mgr*/)// : rtclog("OpenSpliceManager")
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
  OpenSpliceManager::~OpenSpliceManager()
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
  void OpenSpliceManager::start()
  {
      DDS::ReturnCode_t result;

      m_factory = DDS::DomainParticipantFactory::get_instance();
      if(!checkHandle(m_factory, "get_instance() failed"))
      {
          return;
      }
      
      m_domain = DDS::DOMAIN_ID_DEFAULT;
      m_participant = m_factory->create_participant(m_domain, PARTICIPANT_QOS_DEFAULT, NULL, DDS::STATUS_MASK_NONE);
      if(!checkHandle(m_participant, "create_participant() failed"))
      {
          return;
      }

      DDS::PublisherQos pQos;
      result = m_participant->get_default_publisher_qos(pQos);
      if(!checkStatus(result, "get_default_publisher_qos() failed"))
      {
          return;
      }

      m_publisher = m_participant->create_publisher(pQos, NULL, DDS::STATUS_MASK_NONE);
      if(!checkHandle(m_publisher, "create_publisher() failed"))
      {
          return;
      }

      DDS::SubscriberQos sQos;
      result = m_participant->get_default_subscriber_qos(sQos);
      if(!checkStatus(result, "get_default_subscriber_qos() failed"))
      {
          return;
      }

      m_subscriber = m_participant->create_subscriber(sQos, NULL, DDS::STATUS_MASK_NONE);
      if(!checkHandle(m_subscriber, "create_subscriber() failed"))
      {
          return;
      }
  }

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
  DDS::DomainParticipant_var OpenSpliceManager::getParticipant()
  {
      return m_participant;
  }

  DDS::DataWriter_var OpenSpliceManager::createWriter(std::string topic_name, DDS::DataWriterListener_var listener)
  {
      DDS::Duration_t timeout;
      DDS::Topic_var topic = m_participant->find_topic(topic_name.c_str(), timeout);
      if(!checkHandle(topic, "find_topic() failed"))
      {
           return nullptr;
      }
      DDS::DataWriterQos wQos;
      DDS::ReturnCode_t result = m_publisher->get_default_datawriter_qos(wQos);
      if (!checkStatus(result, "get_default_datawriter_qos() failed"))
      {
          return nullptr;
      }

      DDS::TopicQos tQos;
      result = topic->get_qos(tQos);
      if (!checkStatus(result, "get_default_datawriter_qos() failed"))
      {
          return nullptr;
      }

      result = m_publisher->copy_from_topic_qos(wQos, tQos);
      if (!checkStatus(result, "copy_from_topic_qos() failed"))
      {
          return nullptr;
      }

      wQos.writer_data_lifecycle.autodispose_unregistered_instances = false;

      DDS::DataWriter_var writer = m_publisher->create_datawriter(topic, wQos, listener, DDS::STATUS_MASK_NONE);
      if (!checkHandle(writer, "create_datawriter() failed"))
      {
          return nullptr;
      }

      return writer;
  }

  DDS::DataReader_var OpenSpliceManager::createReader(std::string topic_name, DDS::DataReaderListener_var listener)
  {
      DDS::Duration_t timeout;
      DDS::Topic_var topic = m_participant->find_topic(topic_name.c_str(), timeout);
      if (!checkHandle(topic, "find_topic() failed"))
      {
          return nullptr;
      }
      DDS::DataReaderQos rQos;
      DDS::ReturnCode_t result = m_subscriber->get_default_datareader_qos(rQos);
      if (!checkStatus(result, "get_default_datareader_qos() failed"))
      {
          return nullptr;
      }

      DDS::TopicQos tQos;
      result = topic->get_qos(tQos);
      if (!checkStatus(result, "get_default_datawriter_qos() failed"))
      {
          return nullptr;
      }

      result = m_subscriber->copy_from_topic_qos(rQos, tQos);
      if (!checkStatus(result, "copy_from_topic_qos() failed"))
      {
          return nullptr;
      }
      DDS::StatusMask mask =
          DDS::DATA_AVAILABLE_STATUS | DDS::REQUESTED_DEADLINE_MISSED_STATUS;

      DDS::DataReader_var reader = m_subscriber->create_datareader(topic, rQos, listener, mask);
      if (!checkHandle(reader, "create_datawriter() failed"))
      {
          return nullptr;
      }

      return reader;
  }
  DDS::ReturnCode_t OpenSpliceManager::deleteWriter(DDS::DataWriter_var writer)
  {
      return m_publisher->delete_datawriter(writer);
  }

  DDS::ReturnCode_t OpenSpliceManager::deleteReader(DDS::DataReader_var reader)
  {
      return m_subscriber->delete_datareader(reader);
  }
  bool OpenSpliceManager::createTopic(std::string topic_name, std::string typeName)
  {
      DDS::ReturnCode_t result;
      DDS::TopicQos tQos;
      result = m_participant->get_default_topic_qos(tQos);
      if(!checkStatus(result, "get_default_topic_qos() failed"))
      {
          return false;
      }
      tQos.reliability.kind = DDS::RELIABLE_RELIABILITY_QOS;
      tQos.durability.kind = DDS::TRANSIENT_DURABILITY_QOS;
      DDS::Topic_var topic = m_participant->create_topic("HelloWorldData_Msg", typeName.c_str(), tQos, NULL, DDS::STATUS_MASK_NONE);
      if (!checkHandle(topic, "create_topic() failed"))
      {
          return false;
      }
      return true;
  }

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
  bool OpenSpliceManager::registerType(std::string datatype, std::string idlpath)
  {
      coil::vstring comout;
      std::string comin = "idlpp -l pythondesc ";
      comin.append(idlpath);
      coil::create_process(comin, comout);
      std::string xmlstr;
      for (auto c : comout)
      {
          xmlstr.append(c);
      }

      rapidxml::xml_document<> doc;
      doc.parse<rapidxml::parse_trim_whitespace>(const_cast<char*>(xmlstr.c_str()));
      rapidxml::xml_node<>* topics = doc.first_node("topics");

      std::map<std::string, TopicType> topiclist;
      if (topics != nullptr)
      {
          for (auto& topictype : children<>(topics))
          {
              rapidxml::xml_node<>* id = topictype.first_node("id");
              rapidxml::xml_node<>* keys = topictype.first_node("keys");
              rapidxml::xml_node<>* descriptor = topictype.first_node("descriptor");

              if (id != nullptr && keys != nullptr && descriptor != nullptr)
              {
                  rapidxml::xml_node<>* child = descriptor->first_node();
                  if (child != nullptr)
                  {
                      //std::cout << id->value() << "\t" << child->value() << std::endl;
                      topiclist[id->value()] = TopicType(std::string(id->value()), std::string(keys->value()), std::string(child->value()));
                  }
              }
          }
      }

      if (topiclist.count(datatype) == 0)
      {
          return false;
      }
      
      OpenRTM::CORBACdrDataTypeSupport_var typesupport = new OpenRTM::CORBACdrDataTypeSupport(datatype.c_str(), topiclist[datatype].keys.c_str(), topiclist[datatype].descriptor.c_str());

      DDS::String_var typeName = typesupport->get_type_name();
      DDS::ReturnCode_t result = typesupport->register_type(m_participant, typeName);
      if (checkStatus(result, "register_type() failed"))
      {
          return false;
      }
      return true;
  }

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
  bool OpenSpliceManager::unregisterType(const char* name)
  {
      return false;
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
  OpenSpliceManager* OpenSpliceManager::init()
  {
    //RTC_PARANOID(("init()"));
    Guard guard(mutex);
    if (!manager)
    {
      manager = new OpenSpliceManager();
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
  OpenSpliceManager& OpenSpliceManager::instance()
  {
    Guard guard(mutex);
    if (!manager)
    {
      manager = new OpenSpliceManager();
      manager->start();
    }
    return *manager;
  }
}

