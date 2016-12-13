// -*- C++ -*-
/*!
 * @file Listener.h
 * @brief Listener class
 * @date $Date: 2007-04-13 16:12:52 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Listener.h,v 1.1 2007-04-13 16:12:52 n-ando Exp $
 *
 */

#ifndef Listener_h
#define Listener_h


class ListenerBase
{
public:
  virtual ~ListenerBase(){}
  virtual void invoke() = 0;
};



template <class ListenerClass,
	  class CallbackFunc = void (ListenerClass::*)()>
  class ListenerObject
  : public ListenerBase
{
public:
  ListenerObject(ListenerClass* obj, CallbackFunc cbf)
    : m_obj(obj), m_cbf(cbf)
  {
  }


  virtual ~ListenerObject()
  {
  }


  virtual void invoke()
  {
    (m_obj->*m_cbf)();
  }


private:
  ListenerClass* m_obj;
  CallbackFunc m_cbf;
};




typedef void (*CallbackFunc)();
  class ListenerFunc
  : public ListenerBase
{
public:
  ListenerFunc(CallbackFunc cbf)
    : m_cbf(cbf)
  {
  }

  virtual ~ListenerFunc(){}


  virtual void invoke()
  {
    (*m_cbf)();
  }


private:
  CallbackFunc m_cbf;
};

#endif // Listener_h
