// -*- C++ -*-
/*!
 * @file SdoConfiguration.cpp
 * @brief SDO's Configuration implementation class
 * @date $Date: 2006-09-11 18:14:53 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Util.h,v 1.1 2006-09-11 18:14:53 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef Util_h
#define Util_h


#include <ace/Guard_T.h>
#include <ace/Thread_Mutex.h>
#include <ace/Recursive_Thread_Mutex.h>
#include "idl/SDOPackageSkel.h"

typedef ACE_Guard<ACE_Thread_Mutex> Guard;
typedef ACE_Read_Guard<ACE_Thread_Mutex> Read_Guard;
typedef ACE_Write_Guard<ACE_Thread_Mutex> Write_Guard;

typedef ACE_Guard<ACE_Recursive_Thread_Mutex> Guard_r;
typedef ACE_Read_Guard<ACE_Recursive_Thread_Mutex> Read_Guard_r;
typedef ACE_Write_Guard<ACE_Recursive_Thread_Mutex> Write_Guard_r;


template <class T>
struct LockedStruct
{
  ACE_Thread_Mutex lock;
  T                data;
};


template <class T, class X, class M>
class SequenceEx
  : public T
{
public:
  SequenceEx(): T(0) {};
  SequenceEx(const T& _sq) : T(0) { (*this) = _sq; };
  SequenceEx(const SequenceEx& _sq) : T(0) { (*this) = _sq; };
  virtual ~SequenceEx() {};

  inline CORBA::ULong size() { return this->length(); }
  inline CORBA::ULong max_size() { return this->maximum(); }
  inline bool empty() { return (this->length() == 0) ? true : false; }

  void resize(CORBA::ULong new_size, X& x)
  {
    ACE_Write_Guard<M> gaurd(lock);
    CORBA::ULong len(this->length);
    if (new_size > len) // Widen sequence
      {
	this->length(new_size);
	for (CORBA::ULong i = len; i < new_size; ++i)
	  (*this)[i] = x;
      }
    else if (new_size < len) // shorten sequence
      {
	this->length(new_size);
      }
  }

  void insert(CORBA::ULong position, const X& x)
  {
    ACE_Write_Guard<M> gaurd(lock);
    CORBA::ULong len(this->length());
    // allowed position: [0, len]
    if (position > len) throw; // InvalidParameter("Invalid index");
    
    // widen sequence
    this->length(len + 1);
    // shift items
    for (CORBA::ULong i = (len - 1); i > position; --i)
      {
	(*this)[i] = (*this)[i-1];
      }
    (*this)[position] = x;
  }

  X erase(CORBA::ULong position)
  {
    ACE_Write_Guard<M> gaurd(lock);
    CORBA::ULong len(this->length());
    // allowed position: [0, len)
    if (position > (len - 1)) throw; // InvalidParameter("Invalid index");
    
    // keep erased item
    X erased((*this)[position]);
    // shift remaining items
    for (CORBA::ULong i = position; i < (len - 1); ++i)
      {
	(*this)[i] = (*this)[i+1];
      }
    // shorten sequence
    this->length(len - 1);
    return erased;
  }

  template <class F>
  X erase_if(F f)
  {
    ACE_Write_Guard<M> gaurd(lock);
    CORBA::ULong len(this->length());
    for (CORBA::ULong i = 0; i < len; ++i)
      if (f((*this)[i]))
	return erase(i);
    throw;
  }
  
  void push_back(const X& x)
  {
    ACE_Write_Guard<M> gaurd(lock);
    CORBA::ULong len(this->length());
    this->length(len + 1);
    (*this)[len] = x;
  }

  void pop_back()
  {
    ACE_Write_Guard<M> gaurd(lock);
    CORBA::ULong len(this->length());
    this->len(len - 1);
  }

  template <class F>
  X& find(F f)
  {
    ACE_Read_Guard<M> guard(lock);
    CORBA::ULong len(this->length());
    for (CORBA::ULong i = 0; i < len; ++i)
      if (f((*this)[i]))
	return (*this)[i];
    throw; // InvalidParameter("Not found.");
  }

  M lock;
};

template <class T, class F, class X>
X& erase_if(T& t, F& f)
{
  //  ACE_Write_Guard<M> gaurd(t.lock);
  CORBA::ULong len(t.length());
  for (CORBA::ULong i = 0; i < len; ++i)
    if (f(t[i]))
      return t.erase(i);
}


#endif // Util_h
