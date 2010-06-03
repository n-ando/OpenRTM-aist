#include "DummyModule2.h"

namespace RTC
{

class Manager;

class DummyModule2
{
public:
	static void InitProc(Manager* manager) { m_counter++; }
	static int getInitProcCount() { return m_counter; }
	static void resetInitProcCount() { m_counter = 0; }
	
private:
	static int m_counter;
};
int DummyModule2::m_counter = 0;

void InitProc(Manager* manager)
{
	DummyModule2::InitProc(manager);
}

int getInitProcCount()
{
	return DummyModule2::getInitProcCount();
}

void resetInitProcCount()
{
	DummyModule2::resetInitProcCount();
}

};
