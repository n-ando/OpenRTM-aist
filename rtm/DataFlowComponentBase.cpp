// -*- C++ -*-
/*!
 * @file DataFlowComponentBase.cpp
 * @brief DataFlowParticipant RT-Component base class
 * @date $Date: 2007-01-09 09:47:15 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: DataFlowComponentBase.cpp,v 1.1 2007-01-09 09:47:15 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#include <rtm/DataFlowComponentBase.h>
#include <rtm/Manager.h>
#include <iostream>

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  DataFlowComponentBase::DataFlowComponentBase(Manager* manager)
    : RTObject_impl(manager)
  {
    m_ref = this->_this();
    m_objref = m_ref;
    
    m_pec = new PeriodicExecutionContext(m_ref, 1000);
    std::cout << "init()" << std::endl;
    m_pec->add(m_ref);
    std::cout << "DataFlowComponentBase done" << std::endl;
  }


  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  DataFlowComponentBase::~DataFlowComponentBase()
  {
  }


  /*!
   * @if jp
   * @brief 初期化
   * @else
   * @brief Initialization
   * @endif
   */
  void DataFlowComponentBase::init()
  {
  }


}; // namespace RTC
