// -*- C++ -*-
/*!
 * @file UUID.h
 * @brief UUID wrapper class
 * @date $Date: 2006-10-17 19:18:50 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef UUID_h
#define UUID_h

#ifdef WITH_ACE
#include <ace/UUID.h>
#else
#include <uuid.h>
#endif

/*!
 * @if jp
 * @namespace RTC_Utils
 *
 * @brief RTコンポーネント 用ユーティリティ
 *
 * @else
 *
 * @namespace RTC_Utils
 *
 * @brief RT-Component utility
 *
 * @endif
 */
namespace RTC_Utils
{
#ifdef WITH_ACE
  typedef ACE_Utils::UUID UUID;

  class UUID_Generator
    : public ACE_Utils::UUID_Generator
  {
  public:
    UUID_Generator() : ACE_Utils::UUID_Generator() {};
#ifndef ACE_5_6_1_OR_EARLIER  
    ACE_Utils::UUID*
    generateUUID(ACE_UINT16 version=0x0001, u_char variant=0x80)
    {
      return ACE_Utils::UUID_Generator::generate_UUID(version, variant);
    }
#endif
  };
#else
  /*!
   * @if jp
   * @class UUID
   * @brief UUID保持クラス
   * 
   * 生成した UUID の情報を保持するためのクラス。
   *
   * @since 0.4.0
   *
   * @else
   * @class UUID
   * @brief UUID hold class
   * 
   * This is a class to hold information for the generated UUID.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class UUID
  {
    uuid_t _uuid;
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * 
     * デフォルトコンストラクタ
     *
     * @else
     * @brief Constructor
     * 
     * Default constructor
     *
     * @endif
     */
    UUID();
    
    /*!
     * @if jp
     * @brief コピーコンストラクタ
     * 
     * コピーコンストラクタ
     *
     * @else
     * @brief Copy constructor
     * 
     * Copy constructor
     *
     * @endif
     */
    UUID(uuid_t*);
    
    /*!
     * @if jp
     * @brief 文字列変換
     * 
     * 保持している UUID 情報を文字列に変換して返す。
     *
     * @return 文字列変換結果
     *
     * @else
     * @brief Convert string
     * 
     * Convert holding UUID information into string and return it.
     *
     * @return String conversion result
     *
     * @endif
     */
    std::string* to_string();
  };
  
  /*!
   * @if jp
   * @class UUID_Generator
   * @brief UUID生成クラス
   * 
   * UUID 情報を生成するクラス。
   *
   * @since 0.4.0
   *
   * @else
   * @class UUID_Generator
   * @brief UUID generate class
   * 
   * This is a class to generate UUID information.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class UUID_Generator
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * 
     * デフォルトコンストラクタ
     *
     * @else
     * @brief Constructor
     * 
     * Default constructor
     *
     * @endif
     */
    UUID_Generator();
    
    /*!
     * @if jp
     * @brief 初期化
     * 
     * UUID 生成情報の初期化を行う。
     *
     * @else
     * @brief Initialize
     * 
     * Initialize the UUID creation information
     *
     * @endif
     */
    void init();
    
    /*!
     * @if jp
     * @brief UUID 生成
     * 
     * 設定された情報を基に UUID を生成する。
     *
     * @param n
     * @param h
     *
     * @return 生成した UUID
     *
     * @else
     * @brief Generate UUID
     * 
     * Generate UUID based on the configured information.
     *
     * @param n
     * @param h
     *
     * @return UUID that was generated.
     *
     * @endif
     */
    UUID* generateUUID(int n, int h);
  };
#endif
};

#endif // UUID_h
