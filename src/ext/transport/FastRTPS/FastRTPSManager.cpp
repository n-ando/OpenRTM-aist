// -*- C++ -*-
/*!
 * @file  FastRTPSManager.cpp
 * @brief FastRTPSManager class
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


#include "FastRTPSManager.h"
#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/Domain.h>

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;


namespace RTC
{
  FastRTPSManager* FastRTPSManager::manager = NULL;
  coil::Mutex FastRTPSManager::mutex;


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
  FastRTPSManager::FastRTPSManager()// : rtclog("FastRTPSManager")
  {

  }

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
  FastRTPSManager::FastRTPSManager(const FastRTPSManager &manager)// : rtclog("FastRTPSManager")
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
  FastRTPSManager::~FastRTPSManager()
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
  void FastRTPSManager::start()
  {
      ParticipantAttributes PParam;
      PParam.rtps.builtin.domainId = 0;
      PParam.rtps.builtin.leaseDuration = c_TimeInfinite;
      PParam.rtps.setName("Participant_openrtm");
      m_participant = Domain::createParticipant(PParam);
   
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
  Participant* FastRTPSManager::getParticipant()
  {
      return m_participant;
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
  bool FastRTPSManager::registerType(TopicDataType* type)
  {
      return Domain::registerType(m_participant,type);	
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
  bool FastRTPSManager::unregisterType(const char* name)
  {
      return Domain::unregisterType(m_participant, name);
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
  FastRTPSManager* FastRTPSManager::init()
  {
    //RTC_PARANOID(("init()"));
    if (!manager)
    {
      Guard guard(mutex);
      manager = new FastRTPSManager();
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
  FastRTPSManager& FastRTPSManager::instance()
  {
    if (!manager)
    {
      Guard guard(mutex);
      manager = new FastRTPSManager();
      manager->start();
    }
    return *manager;
  }
}

