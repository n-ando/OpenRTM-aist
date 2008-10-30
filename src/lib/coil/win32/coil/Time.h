// -*- C++ -*-
/*!
 * @file Time_posix.h
 * @brief Time functions
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

#ifndef COIL_TIME_H
#define COIL_TIME_H


#include <windows.h>
#include <winsock.h>
//#include <winsock2.h>
//#pragma comment(lib, "WS2_32.LIB")
#include <time.h>
#include <coil/config_coil.h>
#include <coil/TimeValue.h>

namespace coil
{
	#define EPOCHFILETIME (116444736000000000i64)
struct timezone {
	  int tz_minuteswest;
	  int tz_dsttime;
  };
inline unsigned int sleep(unsigned int seconds)
  {

    ::Sleep( seconds *1000 );
    return 0;
  }

//static short m_time_DLLinit_count = 0;
  inline int sleep(TimeValue& interval)
  {
    struct timeval tv;
    WSADATA wsa;
    SOCKET ssoc;
    fd_set mask;
    WORD ver;
    int iret;

    //The WSAStartup function initiates use of the Winsock DLL by a process.
    ver = MAKEWORD(2,2);
    iret = ::WSAStartup(ver,&wsa);
    if( iret != 0 ) 
    {
        return iret;
    }

    //The socket function creates a socket that is bound to a specific transport service provider.
    ssoc = ::socket(AF_INET,      //It is assumed AF_INET because there is no AF_UNIX for Windows.
                    SOCK_STREAM,
                    0);
    if(ssoc==INVALID_SOCKET){
      iret = ::WSAGetLastError();
      ::WSACleanup();
      return iret;  
    }


    //Initialize fd_set. 
    FD_ZERO(&mask);
    //Register the reading socket.
    FD_SET(ssoc,&mask);

    tv.tv_sec = interval.sec();
    tv.tv_usec = interval.usec();
    iret = ::select((int)ssoc+1, &mask, NULL, NULL, &tv);
    if( iret == SOCKET_ERROR ) 
    {
      iret = ::WSAGetLastError();
      //The closesocket function closes an existing socket.
      ::closesocket(ssoc);
      //The WSACleanup function terminates use of the Winsock 2 DLL (Ws2_32.dll).
      ::WSACleanup();
      return iret;  
    }

    //The closesocket function closes an existing socket.
    ::closesocket(ssoc);

    //The WSACleanup function terminates use of the Winsock 2 DLL (Ws2_32.dll).
    ::WSACleanup();
    return iret;
  }

  inline int usleep(unsigned int usec)
  {
    struct timeval tv;
    int iret;
    WORD ver;
    WSADATA wsa;
    fd_set mask;
    SOCKET ssoc;

    //The WSAStartup function initiates use of the Winsock DLL by a process.
    ver = MAKEWORD(2,2);
    iret = ::WSAStartup(ver,&wsa);
    if( iret != 0 ) 
    {
        return iret;
    }

    //The socket function creates a socket that is bound to a specific transport service provider.
    ssoc = ::socket(AF_INET,SOCK_STREAM,0);
    if(ssoc==INVALID_SOCKET){
      iret = ::WSAGetLastError();
      ::WSACleanup();
      return iret;  
    }
    FD_ZERO(&mask);
    FD_SET(ssoc,&mask);
    
    tv.tv_sec = usec / 1000000;
    tv.tv_usec = usec % 1000000;
    iret = ::select((int)ssoc+1, &mask, NULL, NULL, &tv);
    if( iret == SOCKET_ERROR ) 
    {
      iret = ::WSAGetLastError();
      //The closesocket function closes an existing socket.
      ::closesocket(ssoc);
      //The WSACleanup function terminates use of the Winsock 2 DLL (Ws2_32.dll).
      ::WSACleanup();
      return iret;  
    }
    //The closesocket function closes an existing socket.
    ::closesocket(ssoc);
    //The WSACleanup function terminates use of the Winsock 2 DLL (Ws2_32.dll).
    ::WSACleanup();
    return iret;

  }

  inline int gettimeofday(struct timeval *tv, struct timezone *tz)
  {
	  FILETIME        ftime;
	  LARGE_INTEGER   lint;
	  __int64         val64;
	  static int      tzflag;
	  if (tv != NULL)
	  {
		  ::GetSystemTimeAsFileTime(&ftime);
		  lint.LowPart  = ftime.dwLowDateTime;
		  lint.HighPart = ftime.dwHighDateTime;
		  val64 = lint.QuadPart;
		  val64 = val64 - EPOCHFILETIME;
		  val64 = val64 / 10;
		  tv->tv_sec  = (long)(val64 / 1000000);
		  tv->tv_usec = (long)(val64 % 1000000);
	  }
	  if (tz)
	  {
		  if (!tzflag)
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

  inline TimeValue gettimeofday()
  {
    timeval tv;
    coil::gettimeofday(&tv, 0);
    return TimeValue(tv.tv_sec, tv.tv_usec);
  }

  inline int settimeofday(const struct timeval *tv , const struct timezone *tz)
  {

	  SYSTEMTIME systime;
	  FILETIME ftime;
	  LARGE_INTEGER lint;
	  __int64 val64;
	  int bias(0);

	// tv,tz -> ftime
	if (tv != NULL)
	{
		if (tz != NULL)
		{
			bias = tz->tz_minuteswest;
		}

		val64 = (tv->tv_sec + bias * 60) * 1000000;
		val64 = val64 + tv->tv_usec;
		lint.QuadPart = val64;
		ftime.dwHighDateTime = lint.LowPart;
		ftime.dwHighDateTime = lint.HighPart;
		::FileTimeToSystemTime(&ftime, &systime);
		::SetSystemTime(&systime);
	}

    return 0;
  }


};

#endif // COIL_TIME_H
