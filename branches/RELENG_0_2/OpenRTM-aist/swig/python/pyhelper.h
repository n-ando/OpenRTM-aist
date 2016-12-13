// -*- C++ -*-
/*!
 * @file pyhelper.h
 * @brief swig python helper
 * @date $Date: 2005-05-12 09:06:19 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: pyhelper.h,v 1.1.1.1 2005-05-12 09:06:19 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */


#ifndef PYHELPER_H
#define PYHELPER_H

#include <Python.h>
#include <ace/Thread.h>
#include <ace/Thread_Mutex.h>
#include <ace/Guard_T.h>
#include <list>

#include <RtcBase.h>


class rtmPyThreadState
{
 public:
  rtmPyThreadState(){};
  rtmPyThreadState(ACE_thread_t _tid, PyThreadState* _tstate)
    : tid(_tid), tstate(_tstate) {};
  PyThreadState* tstate;
  ACE_thread_t tid;
};

static std::list<rtmPyThreadState> rtmPyTStates;    
static ACE_Thread_Mutex rtmPyTMutex;

#ifdef __THREAD__
inline
ACE_thread_t rtmPyGetCurrentThreadId()
{
  return ACE_Thread::self();
}

static PyThreadState* gs_shutdownTState;
static void rtmPySaveThreadState(PyThreadState* tstate);

static PyThreadState* rtmPyGetThreadState()
{

  //  if (rtmPyTMutex == NULL)
  //    return gs_shutdownTState;

  ACE_thread_t ctid = rtmPyGetCurrentThreadId();
  printf("ctid: %d\n",ctid);
  PyThreadState* tstate = NULL;
  
  {
    ACE_Guard<ACE_Thread_Mutex> guard(rtmPyTMutex);

    std::list<rtmPyThreadState>::iterator it;
    std::list<rtmPyThreadState>::iterator it_end;
    it     = rtmPyTStates.begin();
    it_end = rtmPyTStates.end();
    
    while (it != it_end)
      {
	rtmPyThreadState& info = (*it); //rtmPyTStates->Item(i);
	if (info.tid == ctid)
	  {
	    printf("ctid was found: tid: %d, ctid: %d\n", info.tid, ctid);
	    return info.tstate;
	    //	    break;
	  }
	++it;
      }
  }

  if (tstate == NULL)
    {
      printf("tstate is NULL!!!!!!");
      tstate = PyEval_SaveThread();  // Py_BEGIN_ALLOW_THREADS;
      rtmPySaveThreadState(tstate);
    }

  return tstate;
}

static void rtmPySaveThreadState(PyThreadState* tstate)
{
  /*
  if (rtmPyTMutex == NULL)
    { // Python is shutting down, assume a single thread...
      gs_shutdownTState = tstate;
      return;
    }
  */
  ACE_thread_t ctid = rtmPyGetCurrentThreadId();
  {
    printf("rtmPySaveThreadState() ctid: %d\n", ctid);
    ACE_Guard<ACE_Thread_Mutex> guard(rtmPyTMutex);
    //    rtmPyTMutex->Lock();
    std::list<rtmPyThreadState>::iterator it;
    std::list<rtmPyThreadState>::iterator it_end;
    it     = rtmPyTStates.begin();
    it_end = rtmPyTStates.end();
    int i(0);
    while (it != it_end)
      {
	printf("###%d\n", i);
	rtmPyThreadState& info = (*it);
        if (info.tid == ctid)
	  {
	    printf("#########ctid was found. info.tid: %d, ctid: %d\n",info.tid, ctid);
            return;
	  }
	++it;
	++i;
      }
  }
  // not found, so add it...
  rtmPyThreadState new_state(ctid, tstate);
  rtmPyTStates.push_back(new_state);
  printf("------------------------------------------------------------\n");
  printf("Thread state was added.\n");
  printf("------------------------------------------------------------\n");
}

#endif



// Calls from Python to RTM code are wrapped in calls to these
// functions:

PyThreadState* rtmPyBeginAllowThreads()
{
#ifdef __THREAD__
  PyThreadState* saved = PyEval_SaveThread();  // Py_BEGIN_ALLOW_THREADS;
  if (saved == NULL)
    {
      printf("rtmPyBeginAllowThreads(): saved is NULL!!!!\n");
    }
  printf("rtmPyBeginAllowThreads(): saved is not NULL!!!!\n");

  rtmPySaveThreadState(saved);
  return saved;
#else
  return NULL;
#endif
}

void rtmPyEndAllowThreads(PyThreadState* saved)
{
#ifdef __THREAD__
  PyEval_RestoreThread(saved);   // Py_END_ALLOW_THREADS;
#endif
}



// Calls from RTM back to Python code, or even any PyObject
// manipulations, PyDECREF's and etc. are wrapped in calls to these functions:

void rtmPyBeginBlockThreads()
{
#ifdef __THREAD__
  printf("rtmPyBeginBlockThreads()\n");
  PyThreadState* tstate = rtmPyGetThreadState();
  if (tstate == NULL)
    {
      printf("tstate is NULL!!!");
    }
  PyEval_RestoreThread(tstate);
#endif
}


void rtmPyEndBlockThreads()
{
#ifdef __THREAD__
  // Is there any need to save it again?
  // PyThreadState* tstate =
  PyEval_SaveThread();
#endif
}

#endif // end of __PYHELPER_H__

/*
int main(void)
{
  PyEval_InitThreads();
  //  rtmPyBeginAllowThreads();
  for (int i = 0; i < 100; i++)
    {
      printf("%d\n",i);
      rtmPyEndBlockThreads();
      printf("%d\n",i);
      rtmPyBeginBlockThreads();
      printf("%d\n",i);
    }
}
*/
 /*

namespace RTM
{

  class RtcBasePy
	: public RtcBase
  {
  public:
	RtcBasePy(RTM::RtcManager* manager):RtcBase(manager){};
	virtual ~RtcBasePy(){};
	int svc(void)
	{
	  PyThreadState* saved = rtmPyBeginAllowThreads();
	  RTM::RtcBase::svc();
	  rtmPyEndAllowThreads(saved);
	  return 0;
	};
  };
  
};
 */
