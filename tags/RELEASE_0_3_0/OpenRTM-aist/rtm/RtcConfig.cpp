// -*- C++ -*-
/*!
 * @file RtcConfig.cpp
 * @brief RT component configuration handle class
 * @date $Date: 2005-05-16 06:04:49 $
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcConfig.cpp,v 1.2 2005-05-16 06:04:49 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

// standard lib
#include <fstream>
#include <iostream>
#include <algorithm>

// ACE/boost. The order is important!!
#include <ace/Get_Opt.h>
#include <boost/regex.hpp>
#include <ace/OS.h>

// RTM
#include "rtm/RtcConfig.h"
#include "rtm/RtcSystemLogger.h"


namespace RTM 
{

//------------------------------------------------------------
// Construct with command line arguments
//------------------------------------------------------------
RtcConfig::RtcConfig(int argc, char** argv)
  : m_DebugMode(false), m_BinName(std::string(argv[0]))
{
  if (!initConfig(argc, argv))
	{
	  cerr << "RtcConfig() throws std::bad_alloc()" << endl;
	  throw std::bad_alloc();
	}
}


RtcConfig::~RtcConfig()
{
  int i;
  for (i = 0; i < m_Argc; i++) {
	delete[] m_Argv[i];
  }
  delete[] m_Argv;
}


bool RtcConfig::initConfig(int argc, char** argv)
{
  if (!parseCommandArgs(argc, argv)) {
	cerr << "RtcConfig error: Invalid command line options." << endl;
	return false;
  }

  if (!findConfigFile()) {
	cerr << "RtcConfig error: Configuration file not found." << endl;
	return false;
  }

  if (!parseConfigFile()) {
	cerr << "RtcConfig error: Invalid configuraation file: ";
	cerr << m_ConfigFile << endl;
	return false;
  }

  if (!collectSysInfo()) {
	cerr << "RtcConfig error: Could not get system information" << endl;
	return false;
  }
  return true;
}



//==============================================================================
// Private member methods

//------------------------------------------------------------
// parseCommandArgs
//------------------------------------------------------------
bool RtcConfig::parseCommandArgs(int argc, char** argv)
{
  ACE_Get_Opt get_opts(argc, argv, "f:d", 0);
  int opt;

  //  if (argc == 0) return true;

  while ((opt = get_opts()) > 0) {
	switch (opt)
	  {
	  case 'f':
		m_ArgConfigFile = get_opts.optarg;
		break;
	  case 'd':
		m_DebugMode = true;
		break;
	  default:
		//		printUsage(argv[0]);
		//		exit(1);
		;
	  }
  }
  return true;
}

//------------------------------------------------------------
// findConfigFile
//------------------------------------------------------------
bool RtcConfig::findConfigFile()
{
  // Check existance of configuration file given command arg
  if (m_ArgConfigFile.size() != 0) 
	{
	  if (fileExist(m_ArgConfigFile.c_str()))
		{
		  m_ConfigFile = m_ArgConfigFile;
		  return true;
		}
	}

  // Search rtc configuration file from environment variable
  char* env = getenv("RTC_CONFIG");
  if (env != NULL) {
	if (fileExist(env)) {
	  m_ConfigFile = string(env);
	  return true;
	}
  }
  
  // Search rtc configuration file from default search path
  int i = 0;
  while (config_file_path[i] != NULL)
	{
	  if (fileExist(config_file_path[i]))
		{
		  m_ConfigFile = string(config_file_path[i]);
		  return true;
		}
	  ++i;
	}
  
  return false;
}


//------------------------------------------------------------
// parseConfigFile: Parse configuration file and collect configuration
//------------------------------------------------------------
bool RtcConfig::parseConfigFile()
{
  string cline;
  fstream config_file;
  boost::regex config_regex("([[:graph:]]+)[[:blank:]]+([[:graph:]][[:print:]]*?)");
  boost::smatch results;

  config_file.open(m_ConfigFile.c_str(), ios::in);

  if (config_file.fail())
	{
	  return false;
	}

  // Read configuration from rtc.conf
  if (config_file.is_open())
	{
	  while(!config_file.eof())
		{
		  getline(config_file, cline);

		  if (cline[0] == '#') continue;  // Skip comments 

		  if ( boost::regex_match(cline, results, config_regex) )
			{
			  m_Config[results.str(1)] = results.str(2);
			}
		}  
	}
  config_file.close();

  // Pickup configuration for ORB_init
  // config_map[i][0]: Key
  // config_map[i][1]: arg[n]
  // config_map[i][2]: arg[n+1] Pre-string
  // ARG: [Key]-> Pre-string + m_Config[Key] + Post-string
  int i = 0;
  m_NameServer = m_Config["NameServer"];
  while (config_map[i][0] != 0)
	{
	  if (m_Config.find(config_map[i][0]) != m_Config.end())
		{
		  m_Args.push_back(config_map[i][1]);
		  m_Config[config_map[i][0]].insert(0, config_map[i][2]);
		  m_Args.push_back(m_Config[config_map[i][0]]);
		}
	  ++i;
	}
  argsToArgv();

  if (m_Config.find("ComponentLoadPath") != m_Config.end())
	{
	  split(m_Config["ComponentLoadPath"], ":", m_ComponentLoadPath);
	}

  return true;
}


//------------------------------------------------------------
// Getting system information
//------------------------------------------------------------
bool RtcConfig::collectSysInfo()
{ 
  //
  // Get system information by using ACE_OS::uname (UNIX/Windows)
  // 
  ACE_utsname  sysinfo;
  if (ACE_OS::uname(&sysinfo) != 0) {
	return false;
  }
  m_OSname    = string(sysinfo.sysname);
  m_Hostname  = string(sysinfo.nodename);
  m_OSrelease = string(sysinfo.release);
  m_OSversion = string(sysinfo.version);
  m_Arch      = string(sysinfo.machine);

  //
  // Getting current proccess pid by using ACE_OS::getpid() (UNIX/Windows)
  //
  pid_t pid = ACE_OS::getpid();
  
  char pidc[8];
  sprintf(pidc, "%d", pid);
  
  m_Pid = pidc;
  return true;
}

string RtcConfig::getLogFileName()
{
  return m_Config["LogFile"];
}

string RtcConfig::getErrorLogFileName()
{
  return m_Config["ErrLogFile"];
}

int RtcConfig::getLogLevel()
{
  if (m_Config.find("LogLevel") == m_Config.end())
	{
	  return RtcLogStream::strToLogLevel("");
	}
  return RtcLogStream::strToLogLevel(m_Config["LogLevel"]);
}

struct Toupper
{
  void operator()(char &c)
  {
	c = toupper(c);
  }
};

int RtcConfig::getLogLock()
{
  if (m_Config.find("LogStreamLock") == m_Config.end())
	{
	  return -1;
	}
  std::string loglock(m_Config["LogStreamLock"]);

  for_each(loglock.begin(), loglock.end(), Toupper());

  if      (loglock == "YES" || loglock == "ENABLE") return 1;
  else if (loglock == "NO" || loglock == "DISABLE") return 0;
  
  return -1;
}

std::string RtcConfig::getLogTimeFormat()
{
  if (m_Config.find("LogTimeFormat") == m_Config.end())
	{
	  return std::string("[%Y-%m-%dT%H.%M.%S%Z]");
	}
  std::string fmt(m_Config["LogTimeFormat"]);

  for_each(fmt.begin(), fmt.end(), Toupper());

  if (fmt == "NO" || fmt == "DISABLE") return std::string("");

  return m_Config["LogTimeFormat"];
}

//------------------------------------------------------------
// printUsage
//------------------------------------------------------------
void RtcConfig::printUsage(char* arg)
{
  std::cout << "Usage: " << arg << " -f [_config_file_name_]" << " | -d" << std::endl;
  std::cout << "\t-f: set configuration file name" << std::endl;
  std::cout << "\t-d: Debug mode" << std::endl;
  return;
}


void RtcConfig::argsToArgv()
{
  m_Argc = m_Args.size();

  m_Argv = new char*[m_Argc];
  int i;
  vector<string>::iterator it;

  for (it = m_Args.begin(), i = 0; it != m_Args.end(); ++it, ++i)
	{
	  m_Argv[i] = new char[(*it).size() + 1];
	  m_Argv[i][(*it).size()] = '\0';
	  (*it).copy(m_Argv[i], (*it).size());
	}
  return;
}


bool RtcConfig::fileExist(const char *filename)
{
  std::ifstream infile;
  infile.open(filename, std::ios::in);
  // fial() 0: ok, !0: fail
  if (infile.fail() != 0) 
	{
	  infile.close();
	  return false;
	}
  else
	{
	  infile.close();
	  return true;
	}
  return false;
}


bool RtcConfig::split(const string& input, const string& delimiter,
					  list<string>& results)
{
  std::string::size_type input_size = input.size();
  std::string::size_type delim_size = delimiter.size();
  std::string::size_type new_pos = 0;
  std::string::size_type pre_pos = 0;
  std::string::size_type sub_size = 0;
  int ret_value = -1;
  bool search = true;

  while (search) {
	new_pos = input.find(delimiter, pre_pos);
	if (new_pos == std::string::npos) {
	  search = false;
	  sub_size = input_size - pre_pos;
	} else {
	  sub_size = new_pos - pre_pos;
	}
	if (sub_size > 0) {
	  results.push_back(input.substr(pre_pos, sub_size));
	  ret_value = results.size();
	}
	pre_pos = new_pos + delim_size;
  }
  return ret_value;
}

  /*
bool RtcConfig::splitBySpace(const string& input, list<string>& results)
{
  std::string::size_type input_size = input.size();
  std::string::size_type delim_size = delimiter.size();
  std::string::size_type new_pos = 0;
  std::string::size_type pre_pos = 0;
  std::string::size_type sub_size = 0;
  int ret_value = -1;
  bool search = true;

  while (search) {
	new_pos = input.find(delimiter, pre_pos);
	if (new_pos == std::string::npos) {
	  search = false;
	  sub_size = input_size - pre_pos;
	} else {
	  sub_size = new_pos - pre_pos;
	}
	if (sub_size > 0) {
	  results.push_back(input.substr(pre_pos, sub_size));
	  ret_value = results.size();
	}
	pre_pos = new_pos + delim_size;
  }
  return ret_value;
}
  */
}; // end of namespace RTM
