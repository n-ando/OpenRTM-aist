// -*- C++ -*-
#ifndef OpenHRPExecutionContext_h
#define OpenHRPExecutionContext_h

#include <rtm/RTC.h>

#include <ace/Task.h>
#include <ace/Synch.h>

#include <rtm/Manager.h>
#include <rtm/PeriodicExecutionContext.h>

// for Windows DLL export 
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#   define DLL_EXPORT __declspec(dllexport)
#else 
#	define DLL_EXPORT 
#endif /* Windows */

namespace RTC
{
  class OpenHRPExecutionContext
    : public virtual PeriodicExecutionContext
  {
  public:
    OpenHRPExecutionContext();
    virtual ~OpenHRPExecutionContext();
    virtual void tick()
      throw (CORBA::SystemException);
    virtual int svc(void);

  private:
  };
};

extern "C"
{
  DLL_EXPORT void OpenHRPExecutionContextInit(RTC::Manager* manager);
};

#endif // OpenHRPExecutionContext_h

