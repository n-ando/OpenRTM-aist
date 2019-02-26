// -*- C++ -*-
/*!
 * @file Affinity.cpp
 * @brief Processor affinity operation class
 * @date $Date$
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2018
 *     Nobuhiko Miyamoto
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */


#include <windows.h>
#include <coil/stringutil.h>
#include <coil/Affinity.h>

namespace coil
{
  DWORD listToCUPNUM(CpuMask &cpu_mask)
  {
    DWORD cpu_num = 0;
    for(CpuMask::iterator itr = cpu_mask.begin(); itr != cpu_mask.end(); ++itr) {
      DWORD_PTR p = 0x01 << (*itr);
      cpu_num += p;
    }
    return cpu_num;
  }
  bool getProcCpuAffinity(CpuMask& cpu_mask)
  {
    DWORD cpu_num = listToCUPNUM(cpu_mask);
    DWORD processMask, systemMask = 0;
    HANDLE h = GetCurrentProcess();
	BOOL success = GetProcessAffinityMask(h, (PDWORD_PTR)&processMask, (PDWORD_PTR)&systemMask);
	if (success)
    {
		for (int i = 0; i < 32; i++)
		{
			if (processMask & (0x00000001 << i))
			{
				cpu_mask.push_back(i);
			}
		}
      return true;
    }
    else
    {
      return false;
    }
  }

  bool setProcCpuAffinity(std::vector<unsigned int> mask)
  {
    DWORD cpu_num = listToCUPNUM(mask);
    HANDLE h = GetCurrentProcess();
    BOOL success = SetProcessAffinityMask(h, cpu_num);
	if (success)
	{
		return true;
	}
	else
	{
		return false;
	}
  }

  bool setProcCpuAffinity(std::string cpu_mask)
  {
    coil::vstring tmp = coil::split(cpu_mask, ",", true);
    CpuMask mask;
    for (size_t i(0); i < tmp.size(); ++i)
      {
        int num;
        if (coil::stringTo(num, tmp[i].c_str()))
          {
            mask.push_back(num);
          }
      }
    return setProcCpuAffinity(mask);
  }

  bool getThreadCpuAffinity(CpuMask& cpu_mask)
  {
    return true;
  }

  bool setThreadCpuAffinity(std::vector<unsigned int> mask)
  {
    DWORD cpu_num = listToCUPNUM(mask);
    HANDLE h = GetCurrentThread();
    BOOL success = SetThreadAffinityMask(h, cpu_num);
	if (success)
	{
		return true;
	}
	else
	{
		return false;
	}
  }

  bool setThreadCpuAffinity(std::string cpu_mask)
  {
    coil::vstring tmp = coil::split(cpu_mask, ",", true);
    CpuMask mask;
    for (size_t i(0); i < tmp.size(); ++i)
      {
        int num;
        if (coil::stringTo(num, tmp[i].c_str()))
          {
            mask.push_back(num);
          }
      }
    return setThreadCpuAffinity(mask);
  }
}; // namespace coil
