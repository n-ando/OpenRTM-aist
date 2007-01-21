// -*- C++ -*-
/*!
 * @file DataFlowComponentBase.h
 * @brief DataFlowParticipant RT-Component base class
 * @date $Date: 2007-01-21 14:02:42 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: DataFlowComponentBase.h,v 1.2 2007-01-21 14:02:42 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2007/01/09 09:47:22  n-ando
 * DataFlowParticipant RT-Component base class
 *
 */

#ifndef DataFlowComponentBase_h
#define DataFlowComponentBase_h

#include <rtm/idl/RTCSkel.h>
#include <rtm/RTObject.h>
#include <rtm/PeriodicExecutionContext.h>

namespace RTC
{
  /*!
   * @if jp
   * @class DataFlowComponentBas
   * @brief DataFlowComponentBase クラス
   * @else
   * @class DataFlowComponentBase
   * @brief DataFlowComponentBase class
   * @endif
   */
  class Manager;

  class DataFlowComponentBase
    : public RTObject_impl
      
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    DataFlowComponentBase(Manager* manager);


    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~DataFlowComponentBase();


    /*!
     * @if jp
     * @brief 初期化
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
