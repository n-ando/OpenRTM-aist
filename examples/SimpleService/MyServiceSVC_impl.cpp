// -*-C++-*-
/*!
 * @file  MyServiceSVC_impl.cpp
 * @brief Service implementation code of MyService.idl
 *
 */

#include "MyServiceSVC_impl.h"
#include <rtm/CORBA_SeqUtil.h>
#include <iostream>

template <class T>
struct seq_print
{
  seq_print() : m_cnt(0) {};
  void operator()(T val)
  {
    std::cout << m_cnt << ": " << val << std::endl;
    ++m_cnt;
  }
  int m_cnt;
};

/*
 * Example implementational code for IDL interface MyService
 */
MyServiceSVC_impl::MyServiceSVC_impl()
{
  // Please add extra constructor code here.
}


MyServiceSVC_impl::~MyServiceSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
char* MyServiceSVC_impl::echo(const char* msg)
  throw (CORBA::SystemException)
{
  CORBA_SeqUtil::push_back(m_echoList, msg);
  std::cout << "MyService::echo() was called." << std::endl;
  std::cout << "Message: " << msg << std::endl;
  return CORBA::string_dup(msg);
}

EchoList* MyServiceSVC_impl::get_echo_history()
  throw (CORBA::SystemException)
{
  std::cout << "MyService::get_echo_history() was called." << std::endl;
  CORBA_SeqUtil::for_each(m_echoList, seq_print<const char*>());
  
  EchoList_var el;
  el = new EchoList(m_echoList);
  return el._retn();
}

void MyServiceSVC_impl::set_value(CORBA::Float value)
  throw (CORBA::SystemException)
{
  CORBA_SeqUtil::push_back(m_valueList, value);
  m_value = value;

  std::cout << "MyService::set_value() was called." << std::endl;
  std::cout << "Current value: " << m_value << std::endl;

  return;
}

CORBA::Float MyServiceSVC_impl::get_value()
  throw (CORBA::SystemException)
{
  std::cout << "MyService::get_value() was called." << std::endl;
  std::cout << "Current value: " << m_value << std::endl;

  return m_value;
}

ValueList* MyServiceSVC_impl::get_value_history()
  throw (CORBA::SystemException)
{
  std::cout << "MyService::get_value_history() was called." << std::endl;
  CORBA_SeqUtil::for_each(m_valueList, seq_print<CORBA::Float>());

  ValueList_var vl;
  vl = new ValueList(m_valueList);
  return vl._retn();
}



// End of example implementational code



