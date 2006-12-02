/*! -*- C++ -*-
 *
 * @file RtcOutPortBase.cpp
 * @brief Output porty base class
 * @date $Date: 2006-12-02 18:46:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: OutPortBase.cpp,v 1.1 2006-12-02 18:46:05 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2005/05/27 07:34:21  n-ando
 * - InPort/OutPort interface was changed.
 *   subscribe/unsubscribe were completely changed.
 *
 * Revision 1.2  2005/05/16 06:35:11  n-ando
 * - In windows "delete uuid;" in constructor of OutPortBase does not work.
 *   To avoid this bug, "delete uuid" was replaced with "uuid->~UUID()".
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#include <algorithm>
#include <rtm/OutPortBase.h>
#include <rtm/PublisherBase.h>
#include <iostream>

namespace RTC
{

  // Functor to find Publisher by id
  struct OutPortBase::find_id
  {
    find_id(const char* id) : m_id(id) {};
    bool operator()(Publisher* pub)
    {
      return m_id == pub->id;
    }
    std::string m_id;
  };
  
  // Functor to notify update to Publishers
  struct OutPortBase::pub_push
  {
    void operator()(Publisher* pub)
    {
      pub->publisher->update();
    }
  };
  
  // Functor to delete Publishers
  struct OutPortBase::pub_del
  {
    void operator()(Publisher* pub)
    {
      delete pub;
    }
  }; 

  /*!
   * @if jp
   * @brief OutPortBase クラスデストラクタ
   * @else
   * @brief A destructor of OutPortBase class.
   * @endif
   */
  OutPortBase::~OutPortBase()
  {
    std::for_each(m_publishers.begin(), m_publishers.end(), pub_del());
  }


  /*!
   * @if jp
   * @brief Publisherの追加
   * @else
   * @brief Attach a publisher
   * @endif
   */
  void OutPortBase::attach(const char* id, PublisherBase* publisher)
  {
    attach_back(id, publisher);
  }


  /*!
   * @if jp
   * @brief Publisherの追加
   * @else
   * @brief Attach a publisher
   * @endif
   */
  void OutPortBase::attach_front(const char* id, PublisherBase* publisher)
  {
    m_publishers.insert(m_publishers.begin(), new Publisher(id, publisher));
  }


  /*!
   * @if jp
   * @brief Publisherの追加
   * @else
   * @brief Attach a publisher
   * @endif
   */
  void OutPortBase::attach_back(const char* id, PublisherBase* publisher)
  {
    m_publishers.push_back(new Publisher(id, publisher));
  }
  

  /*!
   * @if jp
   * @brief Publisherの削除
   * @else
   * @brief Detach a publisher
   * @endif
   */
  PublisherBase* OutPortBase::detach(const char* id)
  {
    std::vector<Publisher*>::iterator it;
    it = std::find_if(m_publishers.begin(), m_publishers.end(), find_id(id));
    if (it == m_publishers.end())
      return NULL;
    PublisherBase* pub((*it)->publisher);
    m_publishers.erase(it);
    return pub;
  }


  /*!
   * @if jp
   * @brief 更新の通知
   *
   * Publisherにデータの更新を通知する。
   *
   * @else
   *
   * @brief Notify data update
   *
   * This operation notify data update to Publishers
   *
   * @endif
   */
  void OutPortBase::notify()
  {
    std::for_each(m_publishers.begin(), m_publishers.end(), pub_push());
  }


}; // end of namespace RTM
