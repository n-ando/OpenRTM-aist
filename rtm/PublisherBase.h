// -*- C++ -*-
/*!
 * @file PublisherBase.h
 * @brief Publisher base class
 * @date $Date: 2007-06-22 10:55:07 $
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
 * $Id: PublisherBase.h,v 1.1.4.1 2007-06-22 10:55:07 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/11/27 09:44:43  n-ando
 * The first commitment.
 *
 */

#ifndef PublisherBase_h
#define PublisherBase_h

namespace RTC
{
  /*
  typedef PublisherBase* (*PublisherNewFunc)(InPortConsumer& consumer,
					     Properties& property);
  typedef void (*PublisherDeleteFunc)(PublisherBase* rtc);
  
  template <class _New>
  PublisherBase* CreatePublisher(InPortConsumer& consumer,
				 Properties& property)
  {
    return new _New(consumer, property);
  }
  
  template <class _Delete>
  void Delete(PublisherBase* publisher)
  {
    delete publisher;
  }
  */

  /*!
   * @if jp
   *
   * @class PublisherBase
   *
   * @brief Publisher 基底クラス
   * 
   * Publisher* の基底クラス PublisherBase.
   * 各種 Publisher はこのクラスを継承して詳細を実装する。
   *
   * @else
   *
   * @class PublisherBase
   *
   * @brief Base class of Publisher.
   *
   * A base class of Publisher*.
   * Variation of Publisher* which implements details of Publisher
   * inherits this PublisherBase class.
   *
   * @endif
   */
  class PublisherBase
  {
  public:
    virtual void update() = 0;
    virtual ~PublisherBase(){};
    virtual void release(){}
  };

};
#endif // PublisherBase_h
