// -*- C++ -*-
/*!
 * @file ComponentActionListener.cpp
 * @brief Component action listener class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2011
 *     Noriaki Ando
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <rtm/ComponentActionListener.h>

namespace RTC
{
  /*!
   * @if jp
   * @class PostComponentActionListener クラス
   * @else
   * @class PostComponentActionListener class
   * @endif
   */
  PostComponentActionListener::~PostComponentActionListener(){}

  /*!
   * @if jp
   * @class PreComponentActionListener クラス
   * @else
   * @class PreComponentActionListener class
   * @endif
   */
  PreComponentActionListener::~PreComponentActionListener(){}

  /*!
   * @if jp
   * @class PostComponentActionListener ホルダクラス
   * @else
   * @class PostComponentActionListener holder class
   * @endif
   */
  PostComponentActionListenerHolder::PostComponentActionListenerHolder()
  {
  }
  

  PostComponentActionListenerHolder::~PostComponentActionListenerHolder()
  {
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        if (m_listeners[i].second)
          {
            delete m_listeners[i].first;
          }
      }
  }

  
  void PostComponentActionListenerHolder::
  addListener(PostComponentActionListener* listener, bool autoclean)
  {
    m_listeners.push_back(Entry(listener, autoclean));
  }

  
  void PostComponentActionListenerHolder::
  removeListener(PostComponentActionListener* listener)
  {
    std::vector<Entry>::iterator it(m_listeners.begin());
    for (; it != m_listeners.end(); ++it)
      {
        if ((*it).first == listener)
          {
            if ((*it).second)
              {
                delete (*it).first;
              }
            m_listeners.erase(it);
            return;
          }
      }
    
  }

    
  void PostComponentActionListenerHolder::notify(UniqueId ec_id,
                                                 ReturnCode_t ret)
  {
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        m_listeners[i].first->operator()(ec_id, ret);
      }
  }


  /*!
   * @if jp
   * @class PreComponentActionListener ホルダクラス
   * @else
   * @class PreComponentActionListener holder class
   * @endif
   */
  PreComponentActionListenerHolder::PreComponentActionListenerHolder()
  {
  }
    
  
  PreComponentActionListenerHolder::~PreComponentActionListenerHolder()
  {
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        if (m_listeners[i].second)
          {
            delete m_listeners[i].first;
          }
      }
  }

  
  void PreComponentActionListenerHolder::addListener(PreComponentActionListener* listener,
                                            bool autoclean)
  {
    m_listeners.push_back(Entry(listener, autoclean));
  }
  

  void PreComponentActionListenerHolder::removeListener(PreComponentActionListener* listener)
  {
    std::vector<Entry>::iterator it(m_listeners.begin());
    
    for (; it != m_listeners.end(); ++it)
      {
        if ((*it).first == listener)
          {
            if ((*it).second)
              {
                delete (*it).first;
              }
            m_listeners.erase(it);
            return;
          }
      }
    
  }
  
  
  void PreComponentActionListenerHolder::notify(UniqueId ec_id)
  {
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        m_listeners[i].first->operator()(ec_id);
      }
  }
};


