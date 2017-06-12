#ifndef TEST_EC_H
#define TEST_EC_H



#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <rtm/RTC.h>
#include <rtm/ExecutionContextBase.h>
#include <rtm/OpenHRPExecutionContext.h>


namespace RTC
{
  class SimulatorExecutionContext
	  : public virtual RTC::OpenHRPExecutionContext
  {
	  typedef coil::Mutex Mutex;
	  typedef coil::Guard<coil::Mutex> Guard;
  public:
    SimulatorExecutionContext();
    virtual ~SimulatorExecutionContext(void);

    virtual RTC::ReturnCode_t
    activate_component(RTC::LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    virtual RTC::ReturnCode_t
    deactivate_component(RTC::LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    virtual RTC::ReturnCode_t
    reset_component(RTC::LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);

  private:

  };
};



#ifdef WIN32
#pragma warning( default : 4290 )
#endif

extern "C"
{
  DLL_EXPORT void SimulatorExecutionContextInit(RTC::Manager* manager);
};

#endif