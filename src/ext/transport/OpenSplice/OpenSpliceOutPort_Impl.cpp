// -*- C++ -*-
/*!
 * @file  OpenSpliceOutPort.cpp
 * @brief OpenSpliceOutPort class
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



#include "OpenSpliceOutPort_impl.h"
#include "OpenSpliceManager.h"
#include "ccpp_CORBACdrData.h"






namespace RTC
{
    class OpenSpliceOutPort_impl : public OpenSpliceOutPortBase
    {
    public:
        OpenSpliceOutPort_impl();
        ~OpenSpliceOutPort_impl();
        bool init(std::string datatype, std::string idlpath, std::string topic, bool endian = true, bool corbamode = true);
        bool write(RTC::ByteData& data);

    private:
        std::string m_topic;
        std::string m_dataType;
        DDS::DataWriter_var m_writer;
        bool m_endian;
        std::string m_idlPath;
        bool m_corbamode;
    };

    class PubListener : public DDS::DataWriterListener
    {
    public:
        /*!
         * @if jp
         * @brief コンストラクタ
         *
         * コンストラクタ
         *
         *
         * @else
         * @brief Constructor
         *
         * Constructor
         *
         *
         * @endif
         */
        PubListener();

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
        ~PubListener();

        virtual void on_offered_deadline_missed(DDS::DataWriter_ptr writer, const DDS::OfferedDeadlineMissedStatus& status);
        virtual void on_offered_incompatible_qos(DDS::DataWriter_ptr writer, const DDS::OfferedIncompatibleQosStatus& status);
        virtual void on_liveliness_lost(DDS::DataWriter_ptr writer, const DDS::LivelinessLostStatus& status);
        virtual void on_publication_matched(DDS::DataWriter_ptr writer, const DDS::PublicationMatchedStatus& status);
    };



    OpenSpliceOutPortBase::~OpenSpliceOutPortBase()
    {

    }

    OpenSpliceOutPort_impl::OpenSpliceOutPort_impl() : m_endian(true), m_corbamode(true)
    {
    }
    OpenSpliceOutPort_impl::~OpenSpliceOutPort_impl()
    {
        if (m_writer != nullptr)
        {
            OpenSpliceManager& topicmgr = OpenSpliceManager::instance();
            topicmgr.deleteWriter(m_writer);
        }
    }
    bool OpenSpliceOutPort_impl::init(std::string datatype, std::string idlpath, std::string topic, bool endian, bool corbamode)
    {
        m_topic = topic;
        m_dataType = datatype;
        m_endian = endian;
        m_idlPath = idlpath;
        m_corbamode = corbamode;

        OpenSpliceManager& topicmgr = OpenSpliceManager::instance();
        topicmgr.registerType(m_dataType, m_idlPath);

        topicmgr.createTopic(topic, m_dataType);

       	DDS::DataWriterListener_var listener = new PubListener();

        DDS::DataWriter_var writer = topicmgr.createWriter(m_topic, listener);

        if (!OpenSpliceManager::checkHandle(writer, "createWriter"))
        {
            return false;
        }

        m_writer = OpenRTM::CORBACdrDataDataWriter::_narrow(writer);

        if (!OpenSpliceManager::checkHandle(m_writer, "CORBACdrDataDataWriter::_narrow(writer)"))
        {
            return false;
        }

        return true;
    }
    bool OpenSpliceOutPort_impl::write(RTC::ByteData& data)
    {

        if (!OpenSpliceManager::checkHandle(m_writer, "createWriter"))
        {
            return false;
        }

        ::DDS::CDRSample sample;

        if (m_corbamode)
        {
            sample.blob.length(data.getDataLength() + 4);

            DDS::Octet_ptr b = sample.blob.get_buffer();
            b[0] = 0;
            if (m_endian)
            {
                b[1] = 1;
            }
            else
            {
                b[1] = 0;
            }
            b[2] = 0;
            b[3] = 0;

            memcpy(b + 4, data.getBuffer(), data.getDataLength());
        }
        else
        {
            sample.blob.length(data.getDataLength());
            DDS::Octet_ptr b = sample.blob.get_buffer();
            memcpy(b, data.getBuffer(), data.getDataLength());
        }

        OpenRTM::CORBACdrDataDataWriter_var writer = OpenRTM::CORBACdrDataDataWriter::_narrow(m_writer);
        if (!OpenSpliceManager::checkHandle(writer, "writer narrow"))
        {
            return false;
        }


        DDS::ReturnCode_t result = writer->write_cdr(sample, DDS::HANDLE_NIL);

        if (!OpenSpliceManager::checkStatus(result, "write_cdr() failed"))
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     *
     * @endif
     */
    PubListener::PubListener()
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
    PubListener::~PubListener()
    {
    }

    void PubListener::on_offered_deadline_missed(DDS::DataWriter_ptr writer, const DDS::OfferedDeadlineMissedStatus& status)
    {

    }
    void PubListener::on_offered_incompatible_qos(DDS::DataWriter_ptr writer, const DDS::OfferedIncompatibleQosStatus& status)
    {

    }
    void PubListener::on_liveliness_lost(DDS::DataWriter_ptr writer, const DDS::LivelinessLostStatus& status)
    {

    }
    void PubListener::on_publication_matched(DDS::DataWriter_ptr writer, const DDS::PublicationMatchedStatus& status)
    {

    }


    OpenSpliceOutPortBase* createOpenSpliceOutPort(std::string datatype, std::string idlpath, std::string topic, bool endian, bool corbamode)
    {
        OpenSpliceOutPort_impl* publisher = new OpenSpliceOutPort_impl();
        publisher->init(datatype, idlpath, topic, endian, corbamode);

        return publisher;
    }

} // namespace RTC