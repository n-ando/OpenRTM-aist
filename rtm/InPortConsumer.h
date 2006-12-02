// -*- C++ -*-
/*!
 * @file  InPortConsumer.h
 * @brief InPortConsumer class
 * @date  $Date: 2006-12-02 18:39:06 $
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
 * $Id: InPortConsumer.h,v 1.2 2006-12-02 18:39:06 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/11/27 09:44:39  n-ando
 * The first commitment.
 *
 */

#ifndef InPortConsumer_h
#define InPortConsumer_h

namespace RTC
{
  /*!
   * @if jp
   * @class InPortConsumer
   * @brief InPortConsumer クラス
   * @else
   * @class InPortConsumer
   * @brief InPortConsumer class
   * @endif
   */
  class InPortConsumer
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    InPortConsumer();

    /*!
     * @if jp
     *
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~InPortConsumer(){};

    virtual void push() = 0;

  protected:
  
  private:

  };
};     // namespace RTC
#endif // InPortConsumer_h

