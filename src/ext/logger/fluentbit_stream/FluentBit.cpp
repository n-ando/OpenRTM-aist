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
#include <coil/stringutil.h>
#include "FluentBit.h"

namespace RTC
{
  // Static variables initialization
  flb_ctx_t* FluentBitStream::s_flbContext = NULL;
  int FluentBitStream::s_instance = 0;

  //============================================================
  // FluentBitStream class
  FluentBitStream::FluentBitStream()
    : m_pos(0)
  {
    for (size_t i(0); i < BUFFER_LEN; ++i) { m_buf[i] = '\0'; }
    if (s_flbContext == NULL)
      {
        s_flbContext = flb_create();
      }
  }

  FluentBitStream::~FluentBitStream()
  {
    --s_instance;
    if (s_instance == 0)
      {
        flb_stop(s_flbContext);
        flb_destroy(s_flbContext);
      }
  }

  bool FluentBitStream::init(const coil::Properties& prop)
  {
    flb_stop(s_flbContext);

    // Default lib-input setting
    FlbHandler flbhandler = flb_input(s_flbContext, (char*)"lib", NULL);
    flb_input_set(s_flbContext, flbhandler, "tag", prop.getName(), NULL);
    m_flbIn.push_back(flbhandler);

    const std::vector<coil::Properties*>& leaf(prop.getLeaf());

    for (size_t i(0); i < leaf.size(); ++i)
      {
        std::string key(leaf[i]->getName());
        if (key.find("output") != std::string::npos)
          {
            createOutputStream(*leaf[i]);
          }
        else if (key.find("input") != std::string::npos)
          {
            createInputStream(*leaf[i]);
          }
      }
    // Start the background worker
    flb_start(s_flbContext);
    return true;
  }

  bool FluentBitStream::createOutputStream(const coil::Properties& prop)
  {
    std::string plugin = prop["plugin"];
    FlbHandler flbout = flb_output(s_flbContext,
                                   (char*)plugin.c_str(), NULL);
    m_flbOut.push_back(flbout);
    const std::vector<Properties*>& leaf = prop.getLeaf();
    for (size_t i(0); i < leaf.size(); ++i)
      {
        flb_output_set(s_flbContext, flbout,
                       leaf[i]->getName(), leaf[i]->getValue(), NULL);
      }
    return true;
  }
  
  bool FluentBitStream::createInputStream(const coil::Properties& prop)
  {
    std::string plugin = prop["plugin"];
    FlbHandler flbin = flb_input(s_flbContext,
                                 (char*)plugin.c_str(), NULL);
    m_flbIn.push_back(flbin);
    const std::vector<Properties*>& leaf = prop.getLeaf();
    for (size_t i(0); i < leaf.size(); ++i)
      {
        flb_input_set(s_flbContext, flbin,
                      leaf[i]->getName(), leaf[i]->getValue(), NULL);
      }
    return true;
  }

  std::streamsize FluentBitStream::pushLogger()
  {
    char tmp[BUFFER_LEN];
    std::streamsize n(0);
    for (size_t i(0); i < m_flbIn.size(); ++i)
      {
        n = snprintf(tmp, sizeof(tmp) - 1,
                     "[%lu, {\"msg\": \"%s\"}]",
                     time(NULL), m_buf);
        flb_lib_push(s_flbContext, m_flbIn[i], tmp, n);
      }
    return n;
  }
  
  std::streamsize FluentBitStream::xsputn(const char_type* str,
                                          std::streamsize insize)
  {
    std::streamsize outsize(insize);
    for (std::streamsize i(0); i < insize; ++i, ++m_pos)
      {
        m_buf[m_pos] = str[i];
        if (str[i] == '\n' || str[i] == '\r' || m_pos == (BUFFER_LEN - 1))
          {
            m_buf[m_pos] = '\0';
            outsize = pushLogger();
            m_pos = 0;
          }
      }
    return outsize;
  }
  // end of FluentBitStream class
  //============================================================

  //============================================================
  // FluentBit class
  FluentBit::FluentBit()
  {
  }

  FluentBit::~FluentBit()
  {
  }

  bool FluentBit::init(const coil::Properties& prop)
  {
    return m_fbstream.init(prop);
  }

  StreambufType* FluentBit::getStreamBuffer()
  {
    return &m_fbstream;
  }
  // end of FluentBit class
  //============================================================
};

extern "C"
{
  void FluentBitInit()
  {
    ::RTC::LogstreamFactory::
      instance().addFactory("fluentd",
                            ::coil::Creator< ::RTC::LogstreamBase,
                                             ::RTC::FluentBit>,
                            ::coil::Destructor< ::RTC::LogstreamBase,
                                                ::RTC::FluentBit>);
  }
};

