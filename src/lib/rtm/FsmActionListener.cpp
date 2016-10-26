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
   * @class FsmProfileListener クラス
   * @else
   * @class PortActionListener class
   * @endif
   */
  FsmProfileListener::~FsmProfileListener(){}

  /*!
   * @if jp
   * @class PortActionListener クラス
   * @else
   * @class PortActionListener class
   * @endif
   */
  FsmStructureListener::~FsmStructureListener(){}



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

  void PreFsmActionListenerHolder::notify(const char* state)
  {
    Guard guard(m_mutex);
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        m_listeners[i].first->operator()(state);
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

  void PostFsmActionListenerHolder::notify(const char* state,
                                           ReturnCode_t ret)
  {
    Guard guard(m_mutex);
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        m_listeners[i].first->operator()(state, ret);
      }
  }

  /*!
   * @if jp
   * @class FsmProfileListener ホルダクラス
   * @else
   * @class FsmProfileListener holder class
   * @endif
   */
  FsmProfileListenerHolder::FsmProfileListenerHolder()
  {
  }

  FsmProfileListenerHolder::~FsmProfileListenerHolder()
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

  void FsmProfileListenerHolder::addListener(FsmProfileListener* listener,
                                             bool autoclean)
  {
    Guard guard(m_mutex);
    m_listeners.push_back(Entry(listener, autoclean));
  }

  void
  FsmProfileListenerHolder::removeListener(FsmProfileListener* listener)
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

  void FsmProfileListenerHolder::notify(RTC::FsmProfile& profile)
  {
    Guard guard(m_mutex);
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        m_listeners[i].first->operator()(profile);
      }
  }

  /*!
   * @if jp
   * @class FsmStructureListener ホルダクラス
   * @else
   * @class FsmStructureListener holder class
   * @endif
   */
  FsmStructureListenerHolder::FsmStructureListenerHolder()
  {
  }

  FsmStructureListenerHolder::~FsmStructureListenerHolder()
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

  void FsmStructureListenerHolder::addListener(FsmStructureListener* listener,
                                               bool autoclean)
  {
    Guard guard(m_mutex);
    m_listeners.push_back(Entry(listener, autoclean));
  }

  void
  FsmStructureListenerHolder::removeListener(FsmStructureListener* listener)
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

  void FsmStructureListenerHolder::notify(RTC::FsmStructure& structure)
  {
    Guard guard(m_mutex);
    for (int i(0), len(m_listeners.size()); i < len; ++i)
      {
        m_listeners[i].first->operator()(structure);
      }
  }

};


