#include "DummyModule.h"

namespace RTC
{

class Manager;

class DummyModule
{
public:
	static void InitProc(Manager* manager) { m_counter++; }
	static int getInitProcCount() { return m_counter; }
	static void resetInitProcCount() { m_counter = 0; }
	
private:
	static int m_counter;
};
int DummyModule::m_counter = 0;

void InitProc(Manager* manager)
{
	DummyModule::InitProc(manager);
}

int getInitProcCount()
{
	return DummyModule::getInitProcCount();
}

void resetInitProcCount()
{
	DummyModule::resetInitProcCount();
}

};
