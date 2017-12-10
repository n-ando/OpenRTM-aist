// -*- C++ -*-
/*!
 * @file LogstreamBase.h
 * @brief Logger stream buffer base class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2017
 *     Noriaki Ando
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */
#include <algorithm>

#include <rtm/LogstreamBase.h>
#include <rtm/LogstreamFile.h>
#include <coil/stringutil.h>

namespace RTC
{
  coil::vstring LogstreamFile::s_files;
  
  LogstreamFile::LogstreamFile()
    : m_stdout(NULL), m_fileout(NULL)
  {
  }

  LogstreamFile::~LogstreamFile()
  {
    s_files.erase(std::remove(s_files.begin(), s_files.end(), m_fileName),
                  s_files.end());
    if (m_fileout != NULL)
      {
        m_fileout->close();
      }
  }

  bool LogstreamFile::init(const coil::Properties& prop)
  {
    coil::vstring files = coil::split(prop["file_name"], ",");

    for (size_t i(0); i < files.size(); ++i)
      {
        std::cout << "#### file: " << files[i] << std::endl;
        if (std::count(s_files.begin(), s_files.end(), files[i]) > 0) { continue; }
        m_fileName = files[i];
        s_files.push_back(files[i]);

        std::string fname(files[i]);
        coil::normalize(fname);
        if (fname == "stdout")
          {
            std::cout << "##### STDOUT!! #####" << std::endl;
            m_stdout = std::cout.rdbuf();
            return true;
          }
        else if (fname == "stderr")
          {
            std::cout << "##### STDOUT!! #####" << std::endl;
            m_stdout = std::cerr.rdbuf();
            return true;
          }
        else
          {
            std::cout << "##### file #####" << std::endl;
            m_fileout = new std::filebuf();
            m_fileout->open(files[i].c_str(), std::ios::out | std::ios::app);
            if (m_fileout->is_open()) { return true; }
          }
      }
    return false;
  }

  StreambufType* LogstreamFile::getStreamBuffer()
  {
    if (m_stdout != NULL)
      {
        return m_stdout;
      }
    else if (m_fileout != NULL)
      {
        return m_fileout;
      }
    return std::cout.rdbuf();
  }

};

extern "C"
{
  void LogstreamFileInit()
  {
    ::RTC::LogstreamFactory::
      instance().addFactory("file",
                            ::coil::Creator< ::RTC::LogstreamBase,
                                             ::RTC::LogstreamFile>,
                            ::coil::Destructor< ::RTC::LogstreamBase,
                                                ::RTC::LogstreamFile>);
  }
};

