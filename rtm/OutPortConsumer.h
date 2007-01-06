// -*- C++ -*-
/*!
 * @file  OutPortConsumer.h
 * @brief OutPortConsumer class
 * @date  $Date: 2007-01-06 17:57:14 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: OutPortConsumer.h,v 1.3 2007-01-06 17:57:14 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2006/12/02 18:46:55  n-ando
 * OutPortCorbaConsumer class was moved to OutPortCorbaConsumer.h
 *
 * Revision 1.1  2006/11/27 09:44:41  n-ando
 * The first commitment.
 *
 */

#ifndef OutPortConsumer_h
#define OutPortConsumer_h

#include <rtm/CorbaConsumer.h>
#include <rtm/NVUtil.h>

namespace RTC
{
  /*!
   * @if jp
   * @class OutPortConsumer
   * @brief OutPortConsumer クラス
   * @else
   * @class OutPortConsumer
   * @brief OutPortConsumer class
   * @endif
   */
  class OutPortConsumer
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    //    OutPortConsumer(){};

    /*!
     * @if jp
     *
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~OutPortConsumer(){};

    virtual void pull() = 0;
    virtual bool subscribeInterface(const SDOPackage::NVList& properties) = 0;
    virtual void unsubscribeInterface(const SDOPackage::NVList& properties) = 0;
  protected:
  
  private:

  };
};     // namespace RTC
#endif // OutPortConsumer_h

