// -*-C++-*-
/*!
 * @file  MyServiceSVC_impl.h
 * @brief Service implementation header of MyService.idl
 * @date  $Date: 2005-09-08 13:04:04 $
 *
 * $Id: MyServiceSVC_impl.h,v 1.1 2005-09-08 13:04:04 n-ando Exp $
 */

#include <rtm/RtcServiceBase.h>
#include "MyServiceSkel.h"


#ifndef MYSERVICESVC_IMPL_H
#define MYSERVICESVC_IMPL_H
 
/*
 * Example class implementing IDL interface MyService
 */
class MyServiceSVC_impl
 : public virtual RTM::RtcServiceBase,
   public virtual POA_MyService,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~MyServiceSVC_impl();

 public:
   // standard constructor
   MyServiceSVC_impl();
   virtual ~MyServiceSVC_impl();

   // attributes and operations
   void setGain(CORBA::Float gain);
   CORBA::Float getGain();

 private:
  float m_gain;
};



#endif // MYSERVICESVC_IMPL_H


