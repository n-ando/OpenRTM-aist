// -*- C++ -*-
/*!
 * @file SeqOut.cpp
 * @brief SeqOut component
 * @date $Date: 2005-05-12 09:06:20 $
 *
 * $Id: SeqOut.cpp,v 1.1.1.1 2005-05-12 09:06:20 n-ando Exp $
 */



#include "SeqOut.h"

using namespace std;

SeqOut::SeqOut(RtcManager* manager)
  : RtcBase(manager) ,
	m_DoubleOut("Double", m_Double),
    m_FloatOut("Float", m_Float),
    m_LongOut("Long", m_Long),
    m_ShortOut("Short", m_Short)
{
  registerOutPort(m_DoubleOut);
  registerOutPort(m_FloatOut);
  registerOutPort(m_LongOut);
  registerOutPort(m_ShortOut);

  m_Double.data.length(10);
  m_Float.data.length(10);
  m_Long.data.length(10);
  m_Short.data.length(10);

  appendAlias("example/SeqOut|rtc");
}

/*
RtmRes SeqOut::rtc_init_entry()
{
  return RTM_OK;
}
*/



/*
RtmRes SeqOut::rtc_ready_entry()
{
  return RTM_OK;
}
*/



/*
RtmRes SeqOut::rtc_ready_do()
{
  return RTM_OK;
}
*/



/*
RtmRes SeqOut::rtc_ready_exit()
{
  return RTM_OK;
}
*/



/*
RtmRes SeqOut::rtc_starting_entry()
{
  return RTM_OK;
}
*/



/*
RtmRes SeqOut::rtc_active_entry()
{
  return RTM_OK;
}
*/




RtmRes SeqOut::rtc_active_do()
{
  int r;
  r = rand();

  for (unsigned long int i = 0; i < 10; i++)
	{
	  m_Double.data[i] = rand();
	  m_Float.data[i] = rand();
	  m_Long.data[i] = rand();
	  m_Short.data[i] = rand();
	  std::cout << i << ": ";
	  std::cout << m_Double.data[i] << " ";
	  std::cout << m_Float.data[i] << " ";
	  std::cout << m_Long.data[i] << " ";
	  std::cout << m_Short.data[i] << endl;
	  
	}
  
  std::cout << "[A\r[A\r[A\r[A\r[A\r[A\r[A\r[A\r[A\r[A\r";
  
  m_DoubleOut.write();
  m_FloatOut.write();
  m_LongOut.write();
  m_ShortOut.write();
  usleep(1000);
  return RTM_OK;
}




/*
RtmRes SeqOut::rtc_active_exit()
{
  return RTM_OK;
}
*/



/*
RtmRes SeqOut::rtc_stopping_entry()
{
  return RTM_OK;
}
*/



/*
RtmRes SeqOut::rtc_aborting_entry()
{
  return RTM_OK;
}
*/



/*
RtmRes SeqOut::rtc_error_entry()
{
  return RTM_OK;
}
*/



/*
RtmRes SeqOut::rtc_error_do()
{
  return RTM_OK;
}
*/



/*
RtmRes SeqOut::rtc_error_exit()
{
  return RTM_OK;
}
*/



/*
RtmRes SeqOut::rtc_fatal_entry()
{
  return RTM_OK;
}
*/



/*
RtmRes SeqOut::rtc_fatal_do()
{
  return RTM_OK;
}
*/



/*
RtmRes SeqOut::rtc_fatal_exit()
{
  return RTM_OK;
}
*/



/*
RtmRes SeqOut::rtc_exiting_entry()
{
  return RTM_OK;
}
*/



extern "C" {
  
  RtcBase* SeqOutNew(RtcManager* manager)
  {
	return new SeqOut(manager);
  }
  
  
  void SeqOutDelete(RtcBase* p)
  {
	delete (SeqOut *)p;
	return;
  }
  
  
  void SeqOutInit(RtcManager* manager)
  {
	RtcModuleProfile profile(seqout_spec);
	manager->registerComponent(profile, SeqOutNew, SeqOutDelete);
  }
};

