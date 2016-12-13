// -*-C++-*-
/*!
 * @file  MyServiceSVC_impl.cpp
 * @brief Service implementation code of MyService.idl
 * @date  $Date: 2005-09-08 13:03:54 $
 *
 * $Id: MyServiceSVC_impl.cpp,v 1.1 2005-09-08 13:03:54 n-ando Exp $
 */

#include "MyServiceSVC_impl.h"

/*
 * Example implementational code for IDL interface MyService
 */
MyServiceSVC_impl::MyServiceSVC_impl()
  : m_gain(1)
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
void MyServiceSVC_impl::setGain(CORBA::Float gain)
{
  m_gain = gain;
}

CORBA::Float MyServiceSVC_impl::getGain()
{
  return m_gain;
}



// End of example implementational code



