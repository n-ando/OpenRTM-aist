// -*- C++ -*-
/*!
 * @file  TcpSockServer.h
 * @brief TcpSockServer class
 * @date  $Date: 2007-10-06 12:30:16 $
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
 * $Id: TcpSockServer.h,v 1.1.2.1 2007-10-06 12:30:16 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#ifndef TcpSockServer_h
#define TcpSockServer_h

#define RAWTCP_DEFAULT_BUFFER_SIZE 128

#include <ace/Reactor.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Event_Handler.h>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Stream.h>
#include <ace/Task.h>
#include <ace/OS.h>
#include <iostream>
#include <rtm/BufferBase.h>
#include <rtm/StringUtil.h>

namespace RTC
{

  //============================================================
  // TCP Server classes
  //============================================================
  template <class DataType> class TcpHandler;

  /*!
   * @if jp
   * @class TCP Acceptor
   * @brief TcpAcceptor クラス
   *
   * TCP サーバ用アクセプタクラス。
   *
   * @else
   *
   * @class TCP Acceptor
   * @brief TcpAcceptor class
   *
   * TCP Server acceptor class.
   * 
   * @param DataType data type of the class
   *
   * @endif
   */
  template <class DataType>
  class TcpAcceptor
    : public ACE_Event_Handler
  {
    friend class TcpHandler<DataType>;
    
  public:
    TcpAcceptor(BufferBase<DataType>& buffer, Properties& prop)
      : m_buffer(buffer), m_prop(prop)
    {
    }

    /*!
     * @if jp
     *
     * @brief 仮想デストラクタ
     * 
     * @else
     *
     * @brief virtual destractor
     *
     * @endif
     */
    virtual ~TcpAcceptor()
    {
    }

    /*!
     * @if jp
     *
     * @brief ソケットオープンとハンドラ登録
     * 
     * @else
     *
     * @brief Opening socket and registering handler
     *
     * @endif
     */
    int open(const ACE_INET_Addr& addr, ACE_Reactor* reactor)
    {
      if (this->m_peerAcceptor.open(addr, 1) == -1)
	{
	  return -1;
	}
      m_reactor = reactor;
	  
      // Getting real acceptor's address and port number.
      this->m_peerAcceptor.get_local_addr(m_addr);

      // Set handler
      int ret;
      ret = m_reactor->register_handler(this, ACE_Event_Handler::ACCEPT_MASK);
      return ret;
    }


    /*!
     * @if jp
     *
     * @brief アドレスの取得
     * 
     * オープン時に設定したアドレスを返す
     *
     * @else
     *
     * @brief Getting address
     *
     * This operation returns the given sock address 
     *
     * @endif
     */
    /*
    ACE_INET_Addr get_addr() const
    {
      return m_addr;
    }
    */
	
    /*!
     * @if jp
     *
     * @brief ポート番号の取得
     * 
     * オープン時に設定したポート番号を返す
     *
     * @else
     *
     * @brief Getting port number
     *
     * This operation returns the given port number
     *
     * @endif
     */

    unsigned short get_port_number() const
    {
      return m_addr.get_port_number();
    }

  private:
    /*!
     * @if jp
     *
     * @brief ハンドル取得
     * 
     * ピアアクセプタのハンドル取得。
     *
     * @else
     *
     * @brief Getting handle
     *
     * This operation returns the peer acceptor handle
     *
     * @endif
     */
    ACE_HANDLE get_handle(void) const
    { 
      return m_peerAcceptor.get_handle(); 
    }


    /*!
     * @if jp
     *
     * @brief 入力ハンドラ関数
     * 
     * ソケットに接続があった場合に呼ばれるハンドラ関数。
     *
     * @else
     *
     * @brief Getting handle
     *
     * This operation is a handler function to be called 
     * when sock connection is accepted.
     *
     * @endif
     */
    int handle_input(ACE_HANDLE)
    {
      std::cout << "handle_input" << std::endl;
      m_svcHandler = new TcpHandler<DataType>(m_buffer, m_prop);
      if (m_peerAcceptor.accept(*m_svcHandler, &m_remoteAddr) == -1)
	{
	  // accept faild
	  return -1;
	}

      // start service handler
      if (m_svcHandler->open(m_reactor) == -1)
	{
	  // connection closed
	  return -1;
	}
      return 0;
    }
    
  protected:
    BufferBase<DataType>& m_buffer;
    Properties& m_prop;

    ACE_INET_Addr m_addr;
    ACE_INET_Addr m_remoteAddr;
    ACE_SOCK_Acceptor m_peerAcceptor;     
    ACE_Reactor* m_reactor;
    TcpHandler<DataType>* m_svcHandler;
    unsigned short m_port;
  };
  



  //============================================================
  // TCP Server class
  //============================================================
  template <class DataType>
    class TcpServer
    : public ACE_Task<ACE_NULL_SYNCH>
  {
  public:
    TcpServer(BufferBase<DataType>& buffer, Properties& prop)
      : m_acceptor(buffer, prop), m_buffer(buffer), m_prop(prop),
	m_running(true)
    {
      if (m_prop["inport_addr"] != "")
	{
	  m_addr.set(m_prop["inport_addr"].c_str());
	}
      std::cout << "hostname: " << m_addr.get_host_name() << std::endl;
    }
    
    virtual ~TcpServer()
    {
    }
    
    /*
    void setAddr(const char* addr)
    {
      m_addr.set(addr);
    }
    */

    int start()
    {
      // open socket and acceptor
      if (m_acceptor.open(m_addr, &m_reactor) == -1)
	{
	  // opening accector fail
	  return -1;
	}

      // get real port number
      m_port = m_acceptor.get_port_number();

      return 0;
    }

    virtual int open(void *args)
    {
      start();
      activate();
      return 0;
    }
    
    virtual int svc(void)
    {
      m_reactor.owner(ACE_OS::thr_self()); 
      while (m_running)
	{
	  std::cout << "handle_event" << std::endl;
	  m_reactor.handle_events();
	}
      std::cout << "handle_event done" << std::endl;
      return 0;
    }
    
    void run()
    {
      while (m_running)
	{
	  std::cout << "handle_event run" << std::endl;
	  m_reactor.handle_events();
	}
	  std::cout << "handle_event run done" << std::endl;
    }	  
	
    unsigned short getPortNumber()
    {
      return m_port;
    }

    const char* getHostName()
    {
      return m_addr.get_host_name();
    }
    
  private:
    TcpAcceptor<DataType> m_acceptor;

    BufferBase<DataType>& m_buffer;
    Properties& m_prop;

    bool m_running;

    unsigned short m_port;
    ACE_INET_Addr m_addr;

    ACE_Reactor m_reactor;
  };
  
  
  


  //============================================================
  // TCP handler class
  //============================================================
  template <class DataType>
  class TcpHandler
    : public ACE_Event_Handler
  {
  public:
    TcpHandler(BufferBase<DataType>& buffer, Properties& prop)
      : m_buffer(buffer), m_prop(prop), m_pRecvBuffer(0),
	m_recvBufSize(1024), m_byteswap(true)
    {
      m_recvBufSize = atoi(m_prop.getProperty("buffer_size", "1024").c_str());
      std::cout << "m_recvBufSize: " << m_recvBufSize << std::endl;
      m_byteswap    = toBool(m_prop["byteswap"], "YES", "NO", true);
      std::cout << "m_byteswap: " << m_prop["byteswap"] << std::endl;
      m_pRecvBuffer = new char[m_recvBufSize];
    }


    virtual ~TcpHandler()
    {
      if (!m_pRecvBuffer)
	delete[] m_pRecvBuffer;
    }


    int open(ACE_Reactor* reactor)
    {
      //      std::cout << "Tcphandler::open()" << std::endl;
      m_reactor = reactor;

      if (m_reactor->register_handler(this, ACE_Event_Handler::READ_MASK) == -1)
	{
	  // can't register with reactor 
	  return -1;
	}
      
      return 0;
    }


    int close (void)
    {
      return this->handle_close(ACE_INVALID_HANDLE,
				ACE_Event_Handler::RWE_MASK);
    }
    
    
    operator ACE_SOCK_Stream &()
    {
      return this->m_clientStream;
    }
    
    
  protected:
    ACE_HANDLE get_handle (void) const
    {
      return this->m_clientStream.get_handle();
    }


    int handle_input(ACE_HANDLE)
    {
      // data format
      // [length][client data]
      // length = sizeof ULong + client data length

      // get CDR data size
      long int len(0);
      char tmpbuf[sizeof(CORBA::ULong)];
      CORBA::ULong datasize; // actual data size except header
      len = this->m_clientStream.recv(tmpbuf, sizeof(CORBA::ULong));

      if (len > 0)
	{
	  cdrMemoryStream cdrSize(tmpbuf);
	  cdrSize.setByteSwapFlag(m_byteswap);
	  datasize <<= cdrSize;
	  datasize -= sizeof(CORBA::ULong);
	  if ((long int)datasize > m_recvBufSize)
	    {
	      std::cout << "recv buffer reallocated" << std::endl;
	      delete[] m_pRecvBuffer;
	      m_recvBufSize = datasize;
	      m_pRecvBuffer = new char[m_recvBufSize];
	      std::cout << "new buffer size " << m_recvBufSize << std::endl;
	    }
	  
	  int recvd(0);
	  do 
	    {
	      recvd += this->m_clientStream.recv(m_pRecvBuffer + recvd,
						 datasize);
	    }
	  while (recvd < (int)datasize);
	  
	  if (recvd == (int)datasize)
	    {
	      cdrMemoryStream cdr(m_pRecvBuffer);
	      cdr.setByteSwapFlag(m_byteswap);
	      m_data <<= cdr;
	      m_buffer.write(m_data);
	    }
	  else
	    {
	      std::cout << "invalid data length" << std::endl;
	      std::cout << "recvs: " << recvd << std::endl;
	      std::cout << "cdrlen: " << datasize << std::endl;
	      return -1;
	    }
	}
      else return -1;

      return 0;
    }
    
    
    int handle_close(ACE_HANDLE, ACE_Reactor_Mask mask)
    {
      m_reactor->remove_handler(this, mask|ACE_Event_Handler::DONT_CALL);
      m_clientStream.close();
      delete this;          
      return 0;
    }
    
  protected:
    BufferBase<DataType>& m_buffer;
    Properties& m_prop;

    char* m_pRecvBuffer;
    long int m_recvBufSize;
    bool m_byteswap;

    ACE_SOCK_Stream m_clientStream; 
    ACE_Reactor* m_reactor;
    DataType m_data;
  };

}; // namespace RTC
#endif // TcpSockServer_h
