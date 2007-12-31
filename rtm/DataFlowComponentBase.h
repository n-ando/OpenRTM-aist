// -*- C++ -*-
/*!
 * @file DataFlowComponentBase.h
 * @brief DataFlowParticipant RT-Component base class
 * @date $Date: 2007-12-31 03:08:02 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: DataFlowComponentBase.h,v 1.2.4.1 2007-12-31 03:08:02 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2007/01/21 14:02:42  n-ando
 * Kanji-code was changed.
 *
 * Revision 1.1  2007/01/09 09:47:22  n-ando
 * DataFlowParticipant RT-Component base class
 *
 */

#ifndef DataFlowComponentBase_h
#define DataFlowComponentBase_h

#include <rtm/idl/RTCSkel.h>
#include <rtm/RTObject.h>
#include <rtm/PeriodicExecutionContext.h>

/*!
 * @if jp
 * @namespace RTC
 *
 * @brief RTコンポーネント
 *
 * @else
 *
 * @namespace RTC
 *
 * @endif
 */
namespace RTC
{
  class Manager;
  /*!
   * @if jp
   * @class DataFlowComponentBase
   * @brief DataFlowComponentBase クラス
   *
   * データフロー型RTComponentの基底クラス。
   * 各種データフロー型RTComponentを実装する場合は、本クラスを継承する形で実装
   * する。
   *
   * @since 0.4.0
   *
   * @else
   * @class DataFlowComponentBase
   * @brief DataFlowComponentBase class
   * @endif
   */
  
  class DataFlowComponentBase
    : public RTObject_impl
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @param manager マネージャオブジェクト
     *
     * @else
     * @brief Constructor
     * @endif
     */
    DataFlowComponentBase(Manager* manager);
    
    /*!
     * @if jp
     * @brief デストラクタ
     *
     * デストラクタ
     *
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~DataFlowComponentBase();
    
    /*!
     * @if jp
     * @brief 初期化
     *
     * データフロー型 RTComponent の初期化を実行する。
     * 実際の初期化処理は、各具象クラス内に記述する。
     *
     * @else
     * @brief Initialization
     * @endif
     */
    void init();
    
  private:
    DataFlowComponent_var m_ref;
    PeriodicExecutionContext* m_pec;
    ExecutionContextService_var m_ecref;
  };
}; // namespace RTC
#endif // DataFlowComponentBase_h
