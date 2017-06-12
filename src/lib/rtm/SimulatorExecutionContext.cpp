#include "SimulatorExecutionContext.h"
#include <rtm/ECFactory.h>

#ifdef OPENRTM_VERSION110
#else
#include <rtm/RTObjectStateMachine.h>
#endif



namespace RTC
{

	SimulatorExecutionContext::SimulatorExecutionContext()
		: RTC::OpenHRPExecutionContext()
  {
	  
	  
	
  }


  SimulatorExecutionContext::~SimulatorExecutionContext()
  {

  }



  RTC::ReturnCode_t SimulatorExecutionContext::
	  activate_component(RTC::LightweightRTObject_ptr comp)
	  throw (CORBA::SystemException)
  {
	Guard guard(m_tickmutex);

	RTC_impl::RTObjectStateMachine* rtobj = m_worker.findComponent(comp);

	if (rtobj == NULL)
	{
		return RTC::BAD_PARAMETER;
	}
	if (!(rtobj->isCurrentState(RTC::INACTIVE_STATE)))
	{
		return RTC::PRECONDITION_NOT_MET;
	}
	m_syncActivation = false;

	RTC::ReturnCode_t ret = ExecutionContextBase::activateComponent(comp);
	invokeWorkerPreDo();
	if ((rtobj->isCurrentState(RTC::ACTIVE_STATE)))
	{
		return RTC::RTC_OK;
	}
	return RTC::RTC_ERROR;

  }


  RTC::ReturnCode_t SimulatorExecutionContext::
  deactivate_component(RTC::LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
	Guard guard(m_tickmutex);

	RTC_impl::RTObjectStateMachine* rtobj = m_worker.findComponent(comp);

	if (rtobj == NULL)
	{
		  return RTC::BAD_PARAMETER;
	}
	if (!(rtobj->isCurrentState(RTC::ACTIVE_STATE)))
	{
		  return RTC::PRECONDITION_NOT_MET;
	}
	m_syncDeactivation = false;
	RTC::ReturnCode_t ret = ExecutionContextBase::deactivateComponent(comp);
	invokeWorkerPreDo();
	invokeWorkerDo();
	invokeWorkerPostDo();

	if ((rtobj->isCurrentState(RTC::INACTIVE_STATE)))
	{
		return RTC::RTC_OK;
	}
	return RTC::RTC_ERROR;

  }

  RTC::ReturnCode_t SimulatorExecutionContext::
  reset_component(RTC::LightweightRTObject_ptr comp)
    throw (CORBA::SystemException)
  {
	Guard guard(m_tickmutex);

	RTC_impl::RTObjectStateMachine* rtobj = m_worker.findComponent(comp);

	if (rtobj == NULL)
	{
		return RTC::BAD_PARAMETER;
	}
	if (!(rtobj->isCurrentState(RTC::ERROR_STATE)))
	{
		return RTC::PRECONDITION_NOT_MET;
	}
	m_syncReset = false;
	RTC::ReturnCode_t ret = ExecutionContextBase::resetComponent(comp);
	invokeWorkerPreDo();
	invokeWorkerDo();
	invokeWorkerPostDo();

	if ((rtobj->isCurrentState(RTC::INACTIVE_STATE)))
	{
		return RTC::RTC_OK;
	}
	return RTC::RTC_ERROR;


  }

};




extern "C"
{
  void SimulatorExecutionContextInit(RTC::Manager* manager)
  {
    RTC::ExecutionContextFactory::
      instance().addFactory("SimulatorExecutionContext",
                            ::coil::Creator< ::RTC::ExecutionContextBase,
                            ::RTC::SimulatorExecutionContext>,
                            ::coil::Destructor< ::RTC::ExecutionContextBase,
                            ::RTC::SimulatorExecutionContext>);
  }
};