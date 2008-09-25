// -*- C++ -*-
/*!
 * @file  Condition_win32.h
 * @brief Condition variable class for Win32
 * @date  $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef COIL_CONDITION_H
#define COIL_CONDITION_H

#include <windows.h>
#include <algorithm>
#include <coil/Mutex.h>

namespace coil
{
  typedef struct
  {
    // Number of waiting threads.
    int waiters_count_;
    
    // Serialize access to <waiters_count_>.
    CRITICAL_SECTION waiters_count_lock_;

    // Semaphore used to queue up threads waiting for the condition to
    // become signaled. 
    HANDLE sema_;
    
    // An auto-reset event used by the broadcast/signal thread to wait
    // for all the waiting thread(s) to wake up and be released from the
    // semaphore. 
    HANDLE waiters_done_;
    
    // Keeps track of whether we were broadcasting or signaling.  This
    // allows us to optimize the code if we're just signaling.
    size_t was_broadcast_;

  } pthread_cond_t;

  
  int pthread_cond_init (pthread_cond_t *cv)
  {
    cv->waiters_count_ = 0;
    cv->was_broadcast_ = 0;
	cv->sema_ = ::CreateSemaphore (NULL,       // no security
                                  0,          // initially 0
                                  0x7fffffff, // max count
                                  NULL);      // unnamed 
    InitializeCriticalSection (&cv->waiters_count_lock_);
	cv->waiters_done_ = ::CreateEvent (NULL,  // no security
                                     FALSE, // auto-reset
                                     FALSE, // non-signaled initially
                                     NULL); // unnamed
	return 0;
  }
  
  
  int pthread_cond_wait (coil::pthread_cond_t *cv, pthread_mutex_t *external_mutex)
  {
    // Avoid race conditions.
    EnterCriticalSection (&cv->waiters_count_lock_);
    cv->waiters_count_++;
    LeaveCriticalSection (&cv->waiters_count_lock_);
    
    // This call atomically releases the mutex and waits on the
    // semaphore until <pthread_cond_signal> or <pthread_cond_broadcast>
    // are called by another thread.
    SignalObjectAndWait (*external_mutex, cv->sema_, INFINITE, FALSE);
    
    // Reacquire lock to avoid race conditions.
    EnterCriticalSection (&cv->waiters_count_lock_);
    
    // We're no longer waiting...
    cv->waiters_count_--;
    
    // Check to see if we're the last waiter after <pthread_cond_broadcast>.
    int last_waiter = cv->was_broadcast_ && cv->waiters_count_ == 0;
    
    LeaveCriticalSection (&cv->waiters_count_lock_);
    
    // If we're the last waiter thread during this particular broadcast
    // then let all the other threads proceed.
    if (last_waiter)
      // This call atomically signals the <waiters_done_> event and
      // waits until it can acquire the <external_mutex>.  This is
      // required to ensure fairness.
      SignalObjectAndWait (cv->waiters_done_, *external_mutex, INFINITE, FALSE);
    else
      // Always regain the external mutex since that's the guarantee we
      // give to our callers. 
	  ::WaitForSingleObject (*external_mutex, 0);
	return 0;
  }
  
  
  int pthread_cond_signal (pthread_cond_t *cv)
  {
    EnterCriticalSection (&cv->waiters_count_lock_);
    int have_waiters = cv->waiters_count_ > 0;
    LeaveCriticalSection (&cv->waiters_count_lock_);
    
    // If there aren't any waiters, then this is a no-op.  
    if (have_waiters)
      ReleaseSemaphore (cv->sema_, 1, 0);
	return 0;
  }
  
  
  int pthread_cond_broadcast (pthread_cond_t *cv)
  {
    // This is needed to ensure that <waiters_count_> and <was_broadcast_> are
    // consistent relative to each other.
    EnterCriticalSection (&cv->waiters_count_lock_);
    int have_waiters = 0;
    
    if (cv->waiters_count_ > 0) {
      // We are broadcasting, even if there is just one waiter...
      // Record that we are broadcasting, which helps optimize
      // <pthread_cond_wait> for the non-broadcast case.
      cv->was_broadcast_ = 1;
      have_waiters = 1;
    }
    
    if (have_waiters) {
      // Wake up all the waiters atomically.
      ReleaseSemaphore (cv->sema_, cv->waiters_count_, 0);
      
      LeaveCriticalSection (&cv->waiters_count_lock_);
      
      // Wait for all the awakened threads to acquire the counting
      // semaphore. 
      WaitForSingleObject (cv->waiters_done_, INFINITE);
      // This assignment is okay, even without the <waiters_count_lock_> held 
      // because no other waiter threads can wake up to access it.
      cv->was_broadcast_ = 0;
    }
    else
      LeaveCriticalSection (&cv->waiters_count_lock_);
	return 0;
  }
  

  template <class M>
  class Condition
  {
  public:
    Condition(M& mutex)
      : m_mutex(mutex)
    {
      coil::pthread_cond_init(&m_cond, 0);
    }
    ~Condition()
    {
      ::pthread_cond_destroy(&m_cond);
    }

    inline void signal()
    {
      m_mutex.trylock();
      coil::pthread_cond_signal(&m_cond);
    }

    inline void broadcast()
    {
      m_mutex.trylock();
      coil::pthread_cond_broadcast(&m_cond);
    }

    bool wait()
    {
      m_mutex.trylock();
      return 0 == coil::pthread_cond_wait(&m_cond, &m_mutex.mutex_);
    }

    bool wait(long second, long nano_second = 0)
    {
      m_mutex.trylock();
      timespec abstime;
      abstime.tv_sec = std::time(0) + second;
      abstime.tv_nsec = nano_second;
      return 0 == coil::pthread_cond_timedwait(m_cond,
                                               &m_mutex.mutex_,
                                               &abstime);
    }

  private:
    Condition(const Mutex&);
    Condition& operator=(const Mutex &);
    coil::pthread_cond_t m_cond;
    M& m_mutex;
  };




};
#endif // COIL_CONDITION_H
