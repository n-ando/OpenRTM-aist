// -*- C++ -*-
/*!
 * @file  MutexPosix.h
 * @brief RT-Middleware Service interface
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

#include <coil/Condition.h>

namespace coil
{
    int pthread_cond_init(pthread_cond_t *cv)
    {
        cv->waiters_count_ = 0;
        cv->was_broadcast_ = 0;
        cv->sema_ = ::CreateSemaphore(nullptr,       // no security
            0,           // initially 0
            0x7fffffff,  // max count
            nullptr);      // unnamed
        cv->waiters_done_ = ::CreateEvent(nullptr,  // no security
            FALSE,  // auto-reset
            FALSE,  // non-signaled initially
            nullptr);  // unnamed
        return 0;
    }

    DWORD pthread_cond_wait(coil::pthread_cond_t *cv,
        coil::Mutex *external_mutex, DWORD aMilliSecond)
    {
        DWORD result;

        // Avoid race conditions.
        cv->waiters_count_lock_.lock();
        cv->waiters_count_++;
        cv->waiters_count_lock_.unlock();

        // This call atomically releases the mutex and waits on the
        // semaphore until <pthread_cond_signal> or <pthread_cond_broadcast>
        // are called by another thread.
    //    std::cout << "Before SignalObjectAndWait [wait with time(" << milliSecond
    //              << ")]" << std::endl << std::flush ;
        result = SignalObjectAndWait(external_mutex->mutex_,
            cv->sema_, aMilliSecond, FALSE);

        //    char * p;
        //    switch (result) {
        //    case WAIT_ABANDONED :
        //        p = "Abandoned";
        //        break;
        //    case WAIT_OBJECT_0 :
        //        p = "Signaled";
        //        break;
        //    case WAIT_TIMEOUT :
        //        p = "Timeout";
        //        break;
        //    default :
        //        p = "Other !?";
        //        break;
        //    }
        //      std::cout << "After SignalObjectAndWait [wait with time("
        //                << milliSecond << ")]"
        //        << " result(" << result << ":" << p << ")"
        //        << std::endl << std::flush ;

            // Reacquire lock to avoid race conditions.
        cv->waiters_count_lock_.lock();

        // We're no longer waiting...
        cv->waiters_count_--;

        // Check to see if we're the last waiter after <pthread_cond_broadcast>.
        int last_waiter = (cv->was_broadcast_ != 0U) && (cv->waiters_count_ == 0);

        cv->waiters_count_lock_.unlock();

        // If we're the last waiter thread during this particular broadcast
        // then let all the other threads proceed.
        if (last_waiter != 0)
        {
            // This call atomically signals the <waiters_done_> event and
            // waits until it can acquire the <external_mutex>.  This is
            // required to ensure fairness.
            result = SignalObjectAndWait(cv->waiters_done_,
                external_mutex->mutex_,
                INFINITE, FALSE);
            //        std::cout << "result " << result << std::endl;
        }
        else
        {
            // Always regain the external mutex since that's the guarantee we
            // give to our callers.
            ::WaitForSingleObject(external_mutex->mutex_, 0);
        }
        return result;
    }

    int pthread_cond_signal(pthread_cond_t *cv)
    {
        cv->waiters_count_lock_.lock();
        bool have_waiters = cv->waiters_count_ > 0;
        cv->waiters_count_lock_.unlock();

        if (have_waiters)
        {
            // Release semaphore for the waiters.
            ReleaseSemaphore(cv->sema_, 1, nullptr);
        }
        return 0;
    }

    int pthread_cond_broadcast(pthread_cond_t *cv)
    {
        cv->waiters_count_lock_.lock();

        if (cv->waiters_count_ > 0)
        {
            cv->was_broadcast_ = 1;
            // Wake up all the waiters threads.
            ReleaseSemaphore(cv->sema_, cv->waiters_count_, nullptr);
            cv->waiters_count_lock_.unlock();

            // Wait for all the awakened threads to acquire the counting
            // semaphore.
            WaitForSingleObject(cv->waiters_done_, INFINITE);
            
            // Here waiters_count_lock_ is unneccesarry, because other
            // waiter threads cannot wake up to access it.
            cv->was_broadcast_ = 0;
        }
        else
        {
            cv->waiters_count_lock_.unlock();
        }
        return 0;
    }


} // namespace coil
