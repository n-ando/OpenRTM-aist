// -*- C++ -*-
/*!
 * @file FsmActionListener.cpp
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

#include <rtm/FsmActionListener.h>

namespace RTC
{

  //============================================================
  /*!
   * @if jp
   * @class PostFsmActionListener クラス
   * @else
   * @class PostFsmActionListener class
   * @endif
   */
  PostFsmActionListener::~PostFsmActionListener(){}

  /*!
   * @if jp
   * @class PreFsmActionListener クラス
   * @else
   * @class PreFsmActionListener class
   * @endif
   */
  PreFsmActionListener::~PreFsmActionListener(){}

  /*!
   * @if jp
   * @class PortActionListener クラス
   * @else
   * @class PortActionListener class
   * @endif
   */
  FsmStructureActionListener::~FsmStructureActionListener(){}
  


  //============================================================
  /*!
   * @if jp
   * @class PreFsmActionListener ホルダクラス
   * @else
   * @class PreFsmActionListener holder class
   * @endif
   */
  PreFsmActionListenerHolder::PreFsmActionListenerHolder()
  {
  }
    
  
  PreFsmActionListenerHolder::~PreFsmActionListenerHolder()
  {
    Guard guard(m_mutex);
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        if (m_listeners[i].second)
          {
            delete m_listeners[i].first;
          }
      }
  }

  
  void PreFsmActionListenerHolder::
  addListener(PreFsmActionListener* listener,
              bool autoclean)
  {
    Guard guard(m_mutex);
    m_listeners.push_back(Entry(listener, autoclean));
  }
  
  
  void PreFsmActionListenerHolder::
  removeListener(PreFsmActionListener* listener)
  {
    Guard guard(m_mutex);
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
  
  
  void PreFsmActionListenerHolder::notify(UniqueId ec_id)
  {
    Guard guard(m_mutex);
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        m_listeners[i].first->operator()(ec_id);
      }
  }

  //============================================================
  /*!
   * @if jp
   * @class PostFsmActionListener ホルダクラス
   * @else
   * @class PostFsmActionListener holder class
   * @endif
   */
  PostFsmActionListenerHolder::PostFsmActionListenerHolder()
  {
  }
  

  PostFsmActionListenerHolder::~PostFsmActionListenerHolder()
  {
    Guard guard(m_mutex);
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        if (m_listeners[i].second)
          {
            delete m_listeners[i].first;
          }
      }
  }

  
  void PostFsmActionListenerHolder::
  addListener(PostFsmActionListener* listener, bool autoclean)
  {
    Guard guard(m_mutex);
    m_listeners.push_back(Entry(listener, autoclean));
  }

  
  void PostFsmActionListenerHolder::
  removeListener(PostFsmActionListener* listener)
  {
    Guard guard(m_mutex);
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

    
  void PostFsmActionListenerHolder::notify(UniqueId ec_id,
                                                 ReturnCode_t ret)
  {
    Guard guard(m_mutex);
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        m_listeners[i].first->operator()(ec_id, ret);
      }
  }


  /*!
   * @if jp
   * @class FsmStructureActionListener ホルダクラス
   * @else
   * @class FsmStructureActionListener holder class
   * @endif
   */
  FsmStructureActionListenerHolder::FsmStructureActionListenerHolder()
  {
  }
    
  
  FsmStructureActionListenerHolder::~FsmStructureActionListenerHolder()
  {
    Guard guard(m_mutex);
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        if (m_listeners[i].second)
          {
            delete m_listeners[i].first;
          }
      }
  }

  
  void FsmStructureActionListenerHolder::addListener(FsmStructureActionListener* listener,
                                             bool autoclean)
  {
    Guard guard(m_mutex);
    m_listeners.push_back(Entry(listener, autoclean));
  }
  
  
  void FsmStructureActionListenerHolder::removeListener(FsmStructureActionListener* listener)
  {
    Guard guard(m_mutex);
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
  
  
  void FsmStructureActionListenerHolder::notify(const RTC::FsmStructure& pprofile)
  {
    Guard guard(m_mutex);
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        m_listeners[i].first->operator()(pprofile);
      }
  }

};


