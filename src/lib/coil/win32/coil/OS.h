// -*- C++ -*-
/*!
 * @file OS.h
 * @brief 
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

#ifndef COIL_OS_H
#define COIL_OS_H



#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <process.h>
#include <stdlib.h>

extern "C"
{
  extern char *optarg;
};

namespace coil
{

#define COIL_UTSNAME_LENGTH 65
  struct utsname
  {
    char sysname[COIL_UTSNAME_LENGTH];
    char nodename[COIL_UTSNAME_LENGTH];
    char release[COIL_UTSNAME_LENGTH];
    char version[COIL_UTSNAME_LENGTH];
    char machine[COIL_UTSNAME_LENGTH];
  };

  inline int uname(utsname* name)
  {
    if (name == NULL) return 0;
    int ret(0);

    // name.sysname
    ::strcpy(name->sysname, "Win32");

    // name.release, name.version
    OSVERSIONINFO version_info;
    version_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    if (::GetVersionEx(&version_info) == false)
      ret = -1;

    const char *os;
    if (version_info.dwPlatformId == VER_PLATFORM_WIN32_NT)
      {
        os = "Windows NT %d.%d";
      }
    else
      {
        os = "Windows CE %d.%d";
      }
    
    sprintf(name->release, os,
            (int) version_info.dwMajorVersion,
            (int) version_info.dwMinorVersion);

    sprintf(name->version, "Build %d %s",
            (int) version_info.dwBuildNumber,
            version_info.szCSDVersion);

    // name.machine
    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);
    WORD arch = sys_info.wProcessorArchitecture;
    char cputype[COIL_UTSNAME_LENGTH/2];
    char subtype[COIL_UTSNAME_LENGTH/2];

    switch (arch)
      {
        case PROCESSOR_ARCHITECTURE_INTEL:
          strcpy(cputype, "Intel");
          if (sys_info.wProcessorLevel == 3)
            strcpy(subtype, "80386");
          else if (sys_info.wProcessorLevel == 4)
            strcpy(subtype, "80486");
          else if (sys_info.wProcessorLevel == 5)
            strcpy(subtype, "Pentium");
          else if (sys_info.wProcessorLevel == 6)
            strcpy(subtype, "Pentium Pro");
          else if (sys_info.wProcessorLevel == 7)
            strcpy(subtype, "Pentium II");
          else
            strcpy(subtype, "Pentium Family");
          break;
      default:
        strcpy(cputype, "Unknown");
        strcpy(subtype, "Unknown");
      }
    sprintf(name->machine, "%s %s", cputype, subtype);

    // name.nodename
    DWORD len = COIL_UTSNAME_LENGTH;
    if (GetComputerNameExA(ComputerNameDnsHostname,
							name->nodename,
                            &len) == false)
    ret = -1;
    return ret;
  }

  typedef int pid_t;
  inline pid_t getpid()
  {
    return ::_getpid();
  }
  inline pid_t getppid()
  {
    return 0;
  }

  inline char* getenv(const char* name)
  {
    return ::getenv(name);
  }

  int	opterr = 1,		/* if error message should be printed */
        optind = 1,		/* index into parent argv vector */
        optopt,			/* character checked for validity */
        optreset;		/* reset getopt */
  char	*optarg;		/* argument associated with option */

#define	BADCH	(int)'?'
#define	BADARG	(int)':'
#define	EMSG	""
  
  int getopt(int nargc, char * const *nargv, const char *ostr)
  {
    static char *place = EMSG;		/* option letter processing */
    const char *oli;			/* option letter list index */
    char *p;
    
    if (optreset || !*place) {		/* update scanning pointer */
      optreset = 0;
      /* Check that the scanning reached the last element. */
      if (optind >= nargc)
      { 
        place = EMSG;
        return(-1);
      }
      for(;;)
      {
        /* Check that the scanning reached the last element. */
        if (optind >= nargc)
        {                
          place = EMSG;
          return(-1);
        }
        place = nargv[optind];
        /* Check that the first character of the element is '-'. */
        if (*place != '-')
        {                  
          /* When the head of the element is not '-',        */
          /* Scan the next element disregarding the element. */
          optind++;
                   
        }
        else
        {
          break;
        }
      }
      if (place[1] && *++place == '-') {	/* found "--" */
        ++optind;
        place = EMSG;
        return(-1);
      }
    }					/* option letter okay? */
    if ((optopt = (int)*place++) == (int)':' ||
        !(oli = strchr(ostr, optopt))) {
      /*
       * if the user didn't specify '-' as an option,
       * assume it means -1 (EOF).
       */
      if (optopt == (int)'-')
        return(-1);
      if (!*place)
        ++optind;
      if (opterr && *ostr != ':') {
        if (!(p = strrchr(*nargv, '/')))
          p = *nargv;
        else
          ++p;
        fprintf(stderr, "%s: illegal option -- %c\n",
                p, optopt);
      }
      return(BADCH);
    }
    if (*++oli != ':') {			/* don't need argument */
      optarg = NULL;
      if (!*place)
        ++optind;
    }
    else {					/* need an argument */
      if (*place)			/* no white space */
        optarg = place;
      else if (nargc <= ++optind) {	/* no arg */
        place = EMSG;
        if (!(p = strrchr(*nargv, '/')))
          p = *nargv;
        else
          ++p;
        if (*ostr == ':')
          return(BADARG);
        if (opterr)
          fprintf(stderr,
                  "%s: option requires an argument -- %c\n",
                  p, optopt);
        return(BADCH);
      }
      else				/* white space */
        optarg = nargv[optind];
      place = EMSG;
      ++optind;
    }
    return(optopt);				/* dump back option letter */
  }

  class GetOpt
  {
  public:
    GetOpt(int argc, char* const argv[], const char* opt, int flag)
      : m_argc(argc), m_argv(argv), m_opt(opt), m_flag(flag), optind(1), opterr(1), optopt(0)

    {
      this->optarg = coil::optarg;
      coil::optind = 1;
    }

    ~GetOpt()
    {
      coil::optind = 1;
    }

    int operator()()
    {
      coil::opterr = opterr;
      coil::optind = optind;

      int result = getopt(m_argc, m_argv, m_opt);

      optarg = coil::optarg;
      optind = coil::optind;
      optopt = coil::optopt;

      return result;
    }
    char* optarg;     //! オプション引数
    int optind;       //! 処理対象引数
    int opterr;       //! エラー表示 0:抑止、1:表示
    int optopt;       //! オプション文字が足りない時、多い時にセットされる
 

  private:
    int m_argc;
    char* const * m_argv;
    const char* m_opt;
    int m_flag;

  };
    
};

#endif // COIL_OS_H
