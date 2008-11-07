// -*- C++ -*-
#ifdef WIN32
#pragma warning( push )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4290 )
#pragma warning( disable : 4311 )
#pragma warning( disable : 4312 )
#endif // WIN32

#include "OpenHRPExecutionContext.h"
#include <rtm/ECFactory.h>

#ifdef WIN32
#pragma warning( pop )
#endif // WIN32

namespace RTC
{
  OpenHRPExecutionContext::OpenHRPExecutionContext()
    : PeriodicExecutionContext()
  {
  }

  OpenHRPExecutionContext::~OpenHRPExecutionContext()
  {
  }

  void OpenHRPExecutionContext::tick()
    throw (CORBA::SystemException)
  {
    std::for_each(m_comps.begin(), m_comps.end(), invoke_worker());
    return;
  }

  int OpenHRPExecutionContext::svc(void)
  {
    return 0;
  }
};


extern "C"
{
  void OpenHRPExecutionContextInit(RTC::Manager* manager)
  {
    manager->registerECFactory("SynchExtTriggerEC",
			       RTC::ECCreate<RTC::OpenHRPExecutionContext>,
			       RTC::ECDelete<RTC::OpenHRPExecutionContext>);
    
  }
};
