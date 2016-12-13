// -*- C++ -*-

#include "OpenHRPExecutionContext.h"
#include <rtm/ECFactory.h>

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
