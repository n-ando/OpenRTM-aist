// -*- C++ -*-

/*!
 * @file  OpenSpliceOutPort_impl.cpp
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



#include "OpenSpliceInPort_Impl.h"
#include "OpenSpliceManager.h"
#include "ccpp_CORBACdrData.h"



namespace RTC
{
    class OpenSpliceInPort_impl : public OpenSpliceInPortBase
    {
    public:
        OpenSpliceInPort_impl();
        ~OpenSpliceInPort_impl();
        bool init(OpenSpliceInPortListenerBase* inportlistener, std::string datatype, std::string idlpath, std::string topic, bool endian = true, bool corbamode = true);
    private:
        std::string m_topic;
        std::string m_dataType;
        DDS::DataReader_var m_reader;
        bool m_endian;
        std::string m_idlPath;
        bool m_corbamode;
    };

    /*!
     * @if jp
     * @class SubListener
     * @brief SubListener クラス
     *
     * Subscriberのリスナ
     *
     *
     * @since 2.0.0
     *
     * @else
     * @class OpenSpliceInPort
     * @brief OpenSpliceInPort class
     *
     *
     *
     * @since 2.0.0
     *
     * @endif
     */
    class SubListener : public DDS::DataReaderListener
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
        SubListener(OpenSpliceInPortListenerBase* provider);
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
        ~SubListener();
        virtual void on_requested_deadline_missed(DDS::DataReader_ptr reader, const DDS::RequestedDeadlineMissedStatus& status);
        virtual void on_requested_incompatible_qos(DDS::DataReader_ptr reader, const DDS::RequestedIncompatibleQosStatus& status);
        virtual void on_sample_rejected(DDS::DataReader_ptr reader, const DDS::SampleRejectedStatus& status);
        virtual void on_liveliness_changed(DDS::DataReader_ptr reader, const DDS::LivelinessChangedStatus& status);
        virtual void on_data_available(DDS::DataReader_ptr reader);
        virtual void on_subscription_matched(DDS::DataReader_ptr reader, const DDS::SubscriptionMatchedStatus& status);
        virtual void on_sample_lost(DDS::DataReader_ptr reader, const DDS::SampleLostStatus& status);

    private:
        OpenSpliceInPortListenerBase* m_provider;
    };

    OpenSpliceInPortBase::~OpenSpliceInPortBase()
    {

    }

    OpenSpliceInPortListenerBase::~OpenSpliceInPortListenerBase()
    {

    }


    OpenSpliceInPort_impl::OpenSpliceInPort_impl(): m_endian(true), m_corbamode(true)
    {
    }
    OpenSpliceInPort_impl::~OpenSpliceInPort_impl()
    {
        if (m_reader != nullptr)
        {
            OpenSpliceManager& topicmgr = OpenSpliceManager::instance();
            topicmgr.deleteReader(m_reader);
        }
    }
    bool OpenSpliceInPort_impl::init(OpenSpliceInPortListenerBase* inportlistener, std::string datatype, std::string idlpath, std::string topic, bool endian, bool corbamode)
    {
        m_corbamode = corbamode;
        OpenSpliceManager& topicmgr = OpenSpliceManager::instance();

        topicmgr.registerType(m_dataType, m_idlPath);

        topicmgr.createTopic(topic, m_dataType);

        DDS::DataReaderListener_var listener = new SubListener(inportlistener);

        m_reader = topicmgr.createReader(m_topic, listener);
    
        if (!OpenSpliceManager::checkHandle(m_reader, "createReader"))
        {
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
  SubListener::SubListener(OpenSpliceInPortListenerBase* provider): m_provider(provider)
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
  SubListener::~SubListener()
  {
  }

  void SubListener::on_requested_deadline_missed(DDS::DataReader_ptr reader, const DDS::RequestedDeadlineMissedStatus& status)
  {

  }
  void SubListener::on_requested_incompatible_qos(DDS::DataReader_ptr reader, const DDS::RequestedIncompatibleQosStatus& status)
  {

  }
  void SubListener::on_sample_rejected(DDS::DataReader_ptr reader, const DDS::SampleRejectedStatus& status)
  {

  }
  void SubListener::on_liveliness_changed(DDS::DataReader_ptr reader, const DDS::LivelinessChangedStatus& status)
  {

  }
  void SubListener::on_data_available(DDS::DataReader_ptr reader)
  {
      DDS::ReturnCode_t status;

      OpenRTM::CORBACdrDataDataReader_var cdr_reader = OpenRTM::CORBACdrDataDataReader::_narrow(reader);

      if (!OpenSpliceManager::checkHandle(cdr_reader, "failednarrow CORBACdrDataDataReader"))
      {
          return;
      }

      DDS::CDRSample received_data;
      DDS::SampleInfo info;
      DDS::Long max_samples;
      DDS::ULong sample_states;
      DDS::ULong view_states;
      status = cdr_reader->read_cdr(received_data, info, DDS::LENGTH_UNLIMITED, DDS::ANY_SAMPLE_STATE, DDS::ANY_VIEW_STATE);

      if (!OpenSpliceManager::checkStatus(status, "failed read cdr data"))
      {
          return;
      }

      RTC::ByteData data;
      data.writeData(received_data.blob.get_buffer(), received_data.blob.length());
      m_provider->put(data);
  }
  void SubListener::on_subscription_matched(DDS::DataReader_ptr reader, const DDS::SubscriptionMatchedStatus& status)
  {

  }
  void SubListener::on_sample_lost(DDS::DataReader_ptr reader, const DDS::SampleLostStatus& status)
  {

  }

  OpenSpliceInPortBase* createOpenSpliceInPort(OpenSpliceInPortListenerBase* inportlistener, std::string datatype, std::string idlpath, std::string topic, bool endian, bool corbamode)
  {
      OpenSpliceInPort_impl* subscriber = new OpenSpliceInPort_impl();
      subscriber->init(inportlistener, datatype, idlpath, topic, endian, corbamode);

      return subscriber;
  }
} // namespace RTC


