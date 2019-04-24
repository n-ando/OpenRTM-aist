// -*- C++ -*-
/*!
 * @file Timevalue.h
 * @brief Timevalue class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <coil/Time.h>

namespace coil
{
  // no implementation

  int sleep(TimeValue interval)
  {
    struct timeval tv;
    WSADATA wsa;
    SOCKET ssoc;
    fd_set mask;
    WORD ver;
    int iret;

    // The WSAStartup function initiates use of the Winsock DLL by a process.
    ver = MAKEWORD(2, 2);
    iret = ::WSAStartup(ver, &wsa);
    if ( iret != 0 )
      {
        return iret;
      }

    // The socket function creates a socket that is bound to
    // a specific transport service provider.
    // It is assumed AF_INET because there is no AF_UNIX for Windows.
    ssoc = ::socket(AF_INET,
                    SOCK_STREAM,
                    0);
    if (ssoc == INVALID_SOCKET)
      {
        iret = ::WSAGetLastError();
        ::WSACleanup();
        return iret;
      }


    // Initialize fd_set.
    FD_ZERO(&mask);
    // Register the reading socket.
    FD_SET(ssoc, &mask);

    tv.tv_sec = interval.sec();
    tv.tv_usec = interval.usec();
    iret = ::select(static_cast<int>(ssoc+1), &mask, nullptr, nullptr, &tv);
    if ( iret == SOCKET_ERROR )
      {
        iret = ::WSAGetLastError();
        // The closesocket function closes an existing socket.
        ::closesocket(ssoc);
        // The WSACleanup function terminates
        // use of the Winsock 2 DLL (Ws2_32.dll).
        ::WSACleanup();
        return iret;
      }

    // The closesocket function closes an existing socket.
    ::closesocket(ssoc);

    // The WSACleanup function terminates use of the Winsock 2 DLL (Ws2_32.dll).
    ::WSACleanup();
    return iret;
  }

  int usleep(unsigned int usec)
  {
    struct timeval tv;
    int iret;
    WORD ver;
    WSADATA wsa;
    fd_set mask;
    SOCKET ssoc;

    // The WSAStartup function initiates use of the Winsock DLL by a process.
    ver = MAKEWORD(2, 2);
    iret = ::WSAStartup(ver, &wsa);
    if ( iret != 0 )
      {
        return iret;
      }

    // The socket function creates a socket that is
    // bound to a specific transport service provider.
    ssoc = ::socket(AF_INET, SOCK_STREAM, 0);
    if (ssoc == INVALID_SOCKET)
      {
        iret = ::WSAGetLastError();
        ::WSACleanup();
        return iret;
      }
    FD_ZERO(&mask);
    FD_SET(ssoc, &mask);

    tv.tv_sec = static_cast<long>(usec) / 1000000;
    tv.tv_usec = static_cast<long>(usec) % 1000000;
    iret = ::select(static_cast<int>(ssoc+1), &mask, nullptr, nullptr, &tv);
    if ( iret == SOCKET_ERROR )
      {
        iret = ::WSAGetLastError();
        // The closesocket function closes an existing socket.
        ::closesocket(ssoc);
        // The WSACleanup function terminates
        // use of the Winsock 2 DLL (Ws2_32.dll).
        ::WSACleanup();
        return iret;
      }
    // The closesocket function closes an existing socket.
    ::closesocket(ssoc);
    // The WSACleanup function terminates use of the Winsock 2 DLL (Ws2_32.dll).
    ::WSACleanup();
    return iret;
  }

  int gettimeofday(struct timeval *tv, struct timezone *tz)
  {
      FILETIME        ftime;
      LARGE_INTEGER   lint;
      __int64         val64;
      static int      tzflag;
      if (tv != nullptr)
      {
          ::GetSystemTimeAsFileTime(&ftime);
          lint.LowPart = ftime.dwLowDateTime;
          lint.HighPart = static_cast<LONG>(ftime.dwHighDateTime);
          val64 = lint.QuadPart;
          val64 = val64 - EPOCHFILETIME;
          val64 = val64 / 10;
          tv->tv_sec = (long)(val64 / 1000000);
          tv->tv_usec = (long)(val64 % 1000000);
      }
      if (tz != nullptr)
      {
          if (tzflag == 0)
          {
             ::_tzset();
              ++tzflag;
          }
          long tzone = 0;
          ::_get_timezone(&tzone);
          tz->tz_minuteswest = tzone / 60;
          int dlight = 0;
          ::_get_daylight(&dlight);
          tz->tz_dsttime = dlight;
      }
      return 0;
  }

  int settimeofday(const struct timeval *tv , const struct timezone *tz)
  {

    SYSTEMTIME systime;
    FILETIME ftime;
    LARGE_INTEGER lint;
    __int64 val64;

    // tv,tz -> ftime
    if (tv != nullptr)
      {
        int bias(0);
        if (tz != nullptr)
          {
            bias = tz->tz_minuteswest;
          }

        val64 = (tv->tv_sec + bias * 60) * 1000000;
        val64 = val64 + tv->tv_usec;
        lint.QuadPart = val64;
        ftime.dwHighDateTime = static_cast<DWORD>(lint.LowPart);
        ftime.dwHighDateTime = static_cast<DWORD>(lint.HighPart);
        ::FileTimeToSystemTime(&ftime, &systime);
        ::SetSystemTime(&systime);
      }

    return 0;
  }

  int clock(TimeValue &tv)
  {
      LARGE_INTEGER frequency;
      BOOL ret = QueryPerformanceFrequency(&frequency);

      if (ret == 0)
      {
          return 1;
      }
      else
      {
          LARGE_INTEGER current;
          QueryPerformanceCounter(&current);
          LONGLONG current_time = (current.QuadPart * 1000000) / frequency.QuadPart;
          tv = TimeValue((long)(current_time / 1000000), (long)(current_time % 1000000));
          return 0;
      }
  }

  TimeValue clock()
  {
    TimeValue ret;
    if(coil::clock(ret) != 0)
    {
      timeval tv;
      coil::gettimeofday(&tv, nullptr);
      return TimeValue(tv.tv_sec, tv.tv_usec);
    }
    else
    {
      return ret;
    }
  }
};
