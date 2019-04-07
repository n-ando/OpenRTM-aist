// -*- C++ -*-
/*!
 * @file  OpenSpliceManager.h
 * @brief OpenSpliceManager class
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

#ifndef RTC_OPENSPLICEMANAGER_H
#define RTC_OPENSPLICEMANAGER_H

#include <vector>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <ccpp_dds_dcps.h>


namespace RTC
{
    /*!
     * @if jp
     * @class OpenSpliceManager
     * @brief OpenSpliceManager クラス
     *
     * OpenSpliceを管理するクラス
     *
     *
     * @since 2.0.0
     *
     * @else
     * @class OpenSpliceManager
     * @brief OpenSpliceManager class
     *
     * 
     *
     * @since 2.0.0
     *
     * @endif
     */
    class OpenSpliceManager
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
        OpenSpliceManager();
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
        OpenSpliceManager(const OpenSpliceManager &manager);
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
        ~OpenSpliceManager();
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
        DDS::DomainParticipant_var getParticipant();
        /*!
         * @if jp
         * @brief DataWriter生成
         *
         * @return DataWriter
         *
         * @else
         * @brief create DataWriter
         *
         * @return DataWriter
         *
         * @endif
         */
        DDS::DataWriter_var createWriter(std::string topic_name, DDS::DataWriterListener_var listener);
        /*!
         * @if jp
         * @brief DataReader生成
         *
         * @return DataReader
         *
         * @else
         * @brief create DataReader
         *
         * @return DataReader
         *
         * @endif
         */
        DDS::DataReader_var createReader(std::string topic_name, DDS::DataReaderListener_var listener);
        /*!
         * @if jp
         * @brief DataWriter削除
         *
         * @return DataWriter
         *
         * @else
         * @brief delete DataWriter
         *
         * @return DataWriter
         *
         * @endif
         */
        DDS::ReturnCode_t deleteWriter(DDS::DataWriter_var writer);
        /*!
         * @if jp
         * @brief DataReader削除
         *
         * @return DataReader
         *
         * @else
         * @brief delete DataReader
         *
         * @return DataReader
         *
         * @endif
         */
        DDS::ReturnCode_t deleteReader(DDS::DataReader_var reader);
        /*!
         * @if jp
         * @brief トピック生成
         *
         * @return DataReader
         *
         * @else
         * @brief create Topic
         *
         * @return DataReader
         *
         * @endif
         */
        bool createTopic(std::string topic_name, std::string typeName);
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
        bool registerType(std::string datatype, std::string idlpath);
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
        static OpenSpliceManager* init();
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
        static OpenSpliceManager& instance();

        static bool checkStatus(DDS::ReturnCode_t status, const char *info);
        static bool checkHandle(void *handle, std::string info);
    private:
        static OpenSpliceManager* manager;
        static Mutex mutex;
        DDS::DomainParticipantFactory_var m_factory;
        DDS::DomainId_t m_domain;
        DDS::DomainParticipant_var m_participant;
        DDS::Publisher_var m_publisher;
        DDS::Subscriber_var m_subscriber;
    protected:
        //mutable Logger rtclog;
    };

    class TopicType
    {
    public:
        TopicType();
        TopicType(std::string &inid, std::string &inkeys, std::string &indescriptor);
        TopicType(const TopicType &obj);
        TopicType& operator = (const TopicType& obj);
        std::string id;
        std::string keys;
        std::string descriptor;
    };

}


#endif // RTC_OPENSPLICEMANAGER_H

