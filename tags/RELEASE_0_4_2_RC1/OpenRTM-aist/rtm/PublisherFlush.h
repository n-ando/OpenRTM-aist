// -*- C++ -*-
/*!
 * @file  PublisherFlush.h
 * @brief PublisherFlush class
 * @date  $Date: 2007-01-06 18:00:44 $
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
 * $Id: PublisherFlush.h,v 1.2 2007-01-06 18:00:44 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/11/27 09:44:47  n-ando
 * The first commitment.
 *
 */

#ifndef PublisherFlush_h
#define PublisherFlush_h

#include <rtm/PublisherBase.h>
 
namespace RTC
{
  class InPortConsumer;
  class Properties;
  /*!
   * @if jp
   * @class PublisherFlush
   * @brief PublisherFlush クラス
   * @else
   * @class PublisherFlush
   * @brief PublisherFlush class
   * @endif
   */
  class PublisherFlush
    : public PublisherBase
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    PublisherFlush(InPortConsumer* consumer,
		   const Properties& property);
    
    /*!
     * @if jp
     *
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PublisherFlush();

    /*!
     * @if jp
     * @brief Observer関数
     * @else
     * @brief Observer function
     * @endif
     */
    virtual void update();
  protected:
  
  private:
    InPortConsumer* m_consumer;
    

  };
 
};     // namespace RTC
#endif // PublisherFlush_h

