// -*- C++ -*-
/*!
 * @file ConnectorListener.h
 * @brief connector listener class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTC_CONNECTORLISTENER_H
#define RTC_CONNECTORLISTENER_H

#include <vector>
#include <utility>

class cdrStream;

namespace RTC
{
  class ConnectorInfo;

  /*!
   * @if jp
   * @brief ConnectorDataListener のタイプ
   *
   * - ON_BUFFER_WRITE:          バッファ書き込み時
   * - ON_BUFFER_FULL:           バッファフル時
   * - ON_BUFFER_WRITETIMEOUT:   バッファ書き込みタイムアウト時
   * - ON_BUFFER_WRITEOVERWRITE: バッファ上書き時
   * - ON_BUFFER_READ:           バッファ読み出し時
   * - ON_SEND:                  InProtへの送信時
   * - ON_RECEIVED:              InProtへの送信完了時
   * - ON_SENDER_TIMEOUT:        OutPort側タイムアウト時
   * - ON_SENDER_ERROR:          OutPort側エラー時
   * - ON_RECEIVER_FULL:         InProt側バッファフル時
   * - ON_RECEIVER_TIMEOUT:      InProt側バッファタイムアウト時
   * - ON_RECEIVER_ERROR:        InProt側エラー時
   *
   * @else
   * @brief The types of ConnectorDataListener
   * 
   * - ON_BUFFER_WRITE:          At the time of buffer write
   * - ON_BUFFER_FULL:           At the time of buffer full
   * - ON_BUFFER_WRITETIMEOUT:   At the time of buffer write timeout
   * - ON_BUFFER_WRITEOVERWRITE: At the time of buffer overwrite
   * - ON_BUFFER_READ:           At the time of buffer read
   * - ON_SEND:                  At the time of sending to InPort
   * - ON_RECEIVED:              At the time of finishing sending to InPort
   * - ON_SENDER_TIMEOUT:        At the time of timeout of OutPort
   * - ON_SENDER_ERROR:          At the time of error of OutPort
   * - ON_RECEIVER_FULL:         At the time of bufferfull of InPort
   * - ON_RECEIVER_TIMEOUT:      At the time of timeout of InPort
   * - ON_RECEIVER_ERROR:        At the time of error of InPort
   *
   * @endif
   */
  enum ConnectorDataListenerType
    {
      ON_BUFFER_WRITE = 0, 
      ON_BUFFER_FULL, 
      ON_BUFFER_WRITETIMEOUT, 
      ON_BUFFER_WRITEOVERWRITE, 
      ON_BUFFER_READ, 
      ON_SEND, 
      ON_RECEIVED,
      ON_SENDER_TIMEOUT, 
      ON_SENDER_ERROR, 
      ON_RECEIVER_FULL, 
      ON_RECEIVER_TIMEOUT, 
      ON_RECEIVER_ERROR,
      CONNECTOR_DATA_LISTENER_NUM
    };

  /*!
   * @if jp
   * @class ConnectorDataListener クラス
   *
   * データポートの Connector において発生する各種イベントに対するコー
   * ルバックを実現するリスナクラスの基底クラス。
   *
   * @else
   * @class ConnectorDataListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in the data port's
   * connectors.
   *
   * @endif
   */
  class ConnectorDataListener
  {
  public:
    virtual ~ConnectorDataListener();
    virtual void operator()(const ConnectorInfo& info,
                            const cdrStream& data) = 0;
  };

  /*!
   * @if jp
   * @class ConnectorDataListenerT クラス
   *
   * データポートの Connector において発生する各種イベントに対するコー
   * ルバックを実現するリスナクラスの基底クラス。
   * 
   * このクラスは、operator()() の第2引数に cdrStream 型ではなく、
   * 実際にデータポートで使用される変数型をテンプレート引数として
   * 渡すことができる。
   *
   * @else
   * @class ConnectorDataListenerT class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in the data port's
   * connectors.
   *
   * This class template can have practical data types that are used
   * as typed variable for DataPort as an argument of template instead
   * of cdrStream.
   *
   * @endif
   */
  template <class DataType>
  class ConnectorDataListenerT
    : public ConnectorDataListener
  {
  public:
    virtual ~ConnectorDataListenerT(){}
    virtual void operator()(const ConnectorInfo& info,
                            const cdrStream& cdrdata)
    {
      DataType data;
      cdrdata >>= data;
      this->operator()(info, data);
    }

    virtual void operator()(const ConnectorInfo& info,
                            const DataType& data) = 0;
                            
  };


  /*!
   * @if jp
   * @brief ConnectorListener のタイプ
   *  
   * - ON_BUFFER_EMPTY:       バッファが空の場合
   * - ON_BUFFER_READTIMEOUT: バッファが空でタイムアウトした場合
   *
   * @else
   * @brief The types of ConnectorListener
   * 
   * - ON_BUFFER_EMPTY:       At the time of buffer empty
   * - ON_BUFFER_READTIMEOUT: At the time of buffer read timeout
   *
   * @endif
   */
  enum ConnectorListenerType
    {
      ON_BUFFER_EMPTY = 0,
      ON_BUFFER_READ_TIMEOUT,
      CONNECTOR_LISTENER_NUM
    };

  /*!
   * @if jp
   * @class ConnectorListener クラス
   *
   * データポートの Connector において発生する各種イベントに対するコー
   * ルバックを実現するリスナクラスの基底クラス。
   *
   * @else
   * @class ConnectorListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in the data port's
   * connectors.
   *
   * @endif
   */
  class ConnectorListener
  {
  public:
    virtual ~ConnectorListener();
    virtual void operator()(const ConnectorInfo& info) = 0;
  };


  /*!
   * @if jp
   * @class ConnectorDataListener ホルダクラス
   *
   * 複数の ConnectorDataListener を保持し管理するクラス。
   *
   * @else
   * @class ConnectorDataListener holder class
   *
   * This class manages one ore more instances of ConnectorDataListener class.
   *
   * @endif
   */
  class ConnectorDataListenerHolder
  {
    typedef std::pair<ConnectorDataListener*, bool> Entry;
  public:
    ConnectorDataListenerHolder();
    virtual ~ConnectorDataListenerHolder();
    
    void addListener(ConnectorDataListener* listener, bool autoclean);
    
    void removeListener(ConnectorDataListener* listener);
    
    void notify(const ConnectorInfo& info,
                const cdrStream& cdrdata);
    
  private:
    std::vector<Entry> m_listeners;
  };


  /*!
   * @if jp
   * @class ConnectorListener ホルダクラス
   *
   * 複数の ConnectorListener を保持し管理するクラス。
   *
   * @else
   * @class ConnectorListener holder class
   *
   * This class manages one ore more instances of ConnectorListener class.
   *
   * @endif
   */
  class ConnectorListenerHolder
  {
    typedef std::pair<ConnectorListener*, bool> Entry;
  public:
    ConnectorListenerHolder();
    
    virtual ~ConnectorListenerHolder();
    
    void addListener(ConnectorListener* listener, bool autoclean);
    
    void removeListener(ConnectorListener* listener);

    void notify(const ConnectorInfo& info);
      
  private:
    std::vector<Entry> m_listeners;
  };
  
  class ConnectorListeners
  {
  public:
    ConnectorDataListenerHolder connectorData_[CONNECTOR_DATA_LISTENER_NUM];
    ConnectorListenerHolder connector_[CONNECTOR_LISTENER_NUM];
  }
;
};

#endif // RTC_CONNECTORLISTENER_H
