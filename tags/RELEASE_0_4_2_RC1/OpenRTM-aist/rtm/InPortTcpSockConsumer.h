// -*- C++ -*-
/*!
 * @file  InPortTcpSockConsumer.h
 * @brief InPortTcpSockConsumer class
 * @date  $Date: 2007-10-06 12:28:53 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: InPortTcpSockConsumer.h,v 1.1.2.1 2007-10-06 12:28:53 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#ifndef InPortTcpSockConsumer_h
#define InPortTcpSockConsumer_h

#include <rtm/BufferBase.h>
#include <rtm/InPortConsumer.h>
#include <rtm/StringUtil.h>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Stream.h>
#include <ace/SOCK_Connector.h>
#include <ace/Log_Msg.h>
#include <ace/OS.h>
#include <iostream>

namespace RTC
{
  template <class DataType>
  class InPortTcpSockConsumer
    : public InPortConsumer
  {
  public:
    InPortTcpSockConsumer(BufferBase<DataType>& buffer, Properties& prop)
      : m_buffer(buffer), m_prop(prop), m_byteswap(true)
    {
      m_byteswap = toBool(m_prop["byteswap"], "YES", "NO", true);
      std::cout << "byteswap: " << m_byteswap << std::endl;
    }


    InPortTcpSockConsumer(const InPortTcpSockConsumer<DataType>& consumer)
      : m_buffer(consumer.m_buffer), m_prop(consumer.m_prop),
	m_byteswap(consumer.m_byteswap), m_stream(consumer.m_stream),
	m_addr(consumer.m_addr) 
    {
    }

    InPortTcpSockConsumer&
    operator=(const InPortTcpSockConsumer<DataType>& consumer)
    {
      m_buffer = consumer.m_buffer;
      m_prop   = consumer.m_prop;
      m_stream = consumer.m_stream;
      m_addr   = consumer.m_addr;
      m_byteswap = consumer.m_byteswap;
    }


    virtual ~InPortTcpSockConsumer()
    {}


    void push()
    {
      // read data from buffer
      DataType data;
      m_buffer.read(data);
      std::cout << "byteswap: " << m_byteswap << std::endl;

      CORBA::ULong size(0);
      cdrMemoryStream cdrData;
      cdrData.setByteSwapFlag(m_byteswap);
      size >>= cdrData;
      data >>= cdrData;

      cdrMemoryStream cdrSize;
      size = cdrData.bufSize();
      cdrSize.setByteSwapFlag(m_byteswap);
      size >>= cdrSize;

      // hmm... type-unsafe way.
      memcpy(cdrData.bufPtr(), cdrSize.bufPtr(), sizeof(CORBA::ULong));

      int send(0);
      send = m_stream->send_n(cdrData.bufPtr(), size);

      if (send != (int)size)
	{
	  std::cout << "data size: " << size << std::endl;
	  std::cout << "send size: " << send << std::endl;
	  std::cout << "invalid send" << std::endl;
	}
    }


    virtual InPortTcpSockConsumer* clone() const
    {
      return new InPortTcpSockConsumer<DataType>(*this);
    }


    virtual bool subscribeInterface(const SDOPackage::NVList& properties)
    {
      if (!NVUtil::isStringValue(properties,
				 "dataport.dataflow_type",
				 "Push"))
	{
	  return false;
	}
      
      CORBA::Long index;
      index = NVUtil::find_index(properties,
				 "dataport.tcp_any.inport_addr");
      if (index < 0)
	{
	  return false;
	}
      
      char* inport_addr;
      if (!(properties[index].value >>= inport_addr))
	{
	  return false;
	}

      std::vector<std::string> addr(split(inport_addr, ":"));

      if (addr.size() != 2)
	{
	  return false;
	}

      m_addr.set(addr[1].c_str(), addr[0].c_str());
	  std::cout << "addr: " << addr[0].c_str() << std::endl;
	  std::cout << "port: " << addr[1].c_str() << std::endl;
	  m_stream = new ACE_SOCK_Stream();
      if (m_connector.connect(*m_stream, m_addr) == -1)
	{
	  std::cout << "Connection failed." << std::endl;
	  return false;
	}

      // Disable Nagle's algorithm for small packaets
      int flag(1);
      m_stream->set_option(IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag));

      return true;
    }


    virtual void unsubscribeInterface(const SDOPackage::NVList& properties)
    {
      std::cout << "unsubscribe" << std::endl;
      m_stream->close();
    }


  private:
    BufferBase<DataType>& m_buffer;
    Properties& m_prop;
    bool m_byteswap;

    ACE_SOCK_Stream* m_stream;
    ACE_SOCK_Connector m_connector;
    ACE_INET_Addr m_addr;
  };
};     // namespace RTC
#endif // InPortTcpSockConsumer_h

