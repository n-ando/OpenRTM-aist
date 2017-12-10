// -*- C++ -*-
/*!
 * @file ConnectorListener.h
 * @brief connector listener class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009-2017
 *     Noriaki Ando
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
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <rtm/RTC.h>
#include <rtm/ConnectorBase.h>

class cdrMemoryStream;

namespace RTC
{
  class ConnectorInfo;
  /*!
   * @if jp
   * @class ConnectorListenerStatus mixin class
   * @brief ConnectorListenerStatus mixin •Ø•È•π
   *
   * §≥§Œ•Ø•È•π§œ°¢enumƒÅE¡§µ§ÅEø•ÅEø°º•Û•≥°º•…§Ú°¢ConnectorListener¥ÿ
   * œ¢§Œ•µ•÷•Ø•È•π§«∂¶ƒÃÕ¯Õ—§π§ÅEø§·§Œ mixin •Ø•È•π§«§¢§ÅE£§≥§Œ•ÅEø°º
   * •Û•≥°º•…§Úª»Õ—§π§ÅEØ•È•π§«§œ°¢ConnectorListenerStatus •Ø•È•π§ÅE   * public ∑—æµ§∑°¢≤º§Àdefine §∑§∆§¢§ÅECONNLISTENER_STATUS_ENUM §Ú•Ø•ÅE   * •π∆‚§Àµ≠Ω“§π§ÅE≥§»§«Õ¯Õ—≤ƒ«Ω§»§ §ÅE£§≥§ÅEÀ§Ë§Í°¢enum §ÅE   * ReturnCode ∑ø§»§∑§∆ typedef §∑°¢∞ ∏ÅEReturnCode §ÚÕ¯Õ—§«§≠§ÅEË§¶§À
   * §π§ÅE»§»§‚§À°¢Ãæ¡∞∂ı¥÷§À enum ƒÅE¡§µ§ÅEø≥∆º± Ãª“§Ú≈ˆ≥∫•Ø•È•πÃæ¡∞∂ÅE   * ¥÷∆‚§À∆≥∆˛§π§ÅE£
   *
   * @else
   * @class DataPortStatus mixin class
   * @brief DataPortStatus mixin class
   *
   * This is a mixin class to provide enumed return codes that are
   * commonly utilised in connector listener related sub-classes. To
   * use this class, sub-class should inherit this class as a public
   * super class, and declare CONNLISTENERSTATUS_ENUM defined
   * below. Consequently, ReturnCode type that is typedefed by this
   * macro can be used in the sub-class, and enumed identifiers are
   * imported to the class's namespace.
   *
   * @endif
   */
  class ConnectorListenerStatus
  {
  public:
    enum Enum
      {
        NO_CHANGE    = 0,
        INFO_CHANGED = 1 << 0,
        DATA_CHANGED = 1 << 1,
        BOTH_CHANGED = INFO_CHANGED | DATA_CHANGED
      };
  };
  ConnectorListenerStatus::Enum operator|(ConnectorListenerStatus::Enum L,
                                          ConnectorListenerStatus::Enum R);
  ConnectorListenerStatus::Enum operator&(ConnectorListenerStatus::Enum L,
                                          ConnectorListenerStatus::Enum R);

  /*!
   * @if jp
   *

  /*!
   * @if jp
   * §§§∆°¢•Ø•È•π¿ÅE¿§Œ¿Ë∆¨§À§™§§§∆ DATAPORTSTATUS_ENUM §Úµ≠∫‹§π§ÅE¿§±§«°¢
   * DataPortStatus §«¿ÅE¿§µ§ÅE∆§§§ÅEenum •·•Û•–§¨Ãæ¡∞≤Ú∑Ë±Èªªª“§ §∑§À•¢
   * •Ø•ª•π≤ƒ«Ω§À§ §ÅE£
   *
   * @else
   *
   * @brief Importing ::RTC::DataPortStatus macro
   *
   * This macro imports all the member of enum declared in
   * ::RTC::DataPortStatus into the current namespace.  Inserting at the
   * head of class declaration, classes which utilize DataPortStatus can
   * access Enum members of DataPortStatus without using namespace
   * resolve operator.
   *
   * @endif
   */
#define USE_CONNLISTENER_STATUS                             \
  typedef ::RTC::ConnectorListenerStatus::Enum ReturnCode;  \
  using ::RTC::ConnectorListenerStatus::NO_CHANGE;          \
  using ::RTC::ConnectorListenerStatus::INFO_CHANGED;       \
  using ::RTC::ConnectorListenerStatus::DATA_CHANGED;       \
  using ::RTC::ConnectorListenerStatus::BOTH_CHANGED;

  /*!
   * @if jp
   * @brief ConnectorDataListener §Œ•ø•§•◊
   *
   * - ON_BUFFER_WRITE:          •–•√•’•°ΩÒ§≠π˛§ﬂª˛
   * - ON_BUFFER_FULL:           •–•√•’•°•’•ÅE˛
   * - ON_BUFFER_WRITE_TIMEOUT:  •–•√•’•°ΩÒ§≠π˛§ﬂ•ø•§•‡•¢•¶•»ª˛
   * @brief ConnectorDataListener §Œ•ø•§•◊
   *
   * - ON_BUFFER_WRITE:          •–•√•’•°ΩÒ§≠π˛§ﬂª˛
   * - ON_BUFFER_FULL:           •–•√•’•°•’•ÅE˛
   * - ON_BUFFER_WRITE_TIMEOUT:  •–•√•’•°ΩÒ§≠π˛§ﬂ•ø•§•‡•¢•¶•»ª˛
   * - ON_BUFFER_OVERWRITE:      •–•√•’•°æÂΩÒ§≠ª˛
   * - ON_BUFFER_READ:           •–•√•’•°∆…§ﬂΩ–§∑ª˛
   * - ON_SEND:                  InProt§ÿ§Œ¡˜øÆª˛
   * - ON_RECEIVED:              InProt§ÿ§Œ¡˜øÆ¥∞Œªª˛
   * - ON_RECEIVER_FULL:         InProt¬¶•–•√•’•°•’•ÅE˛
   * - ON_RECEIVER_TIMEOUT:      InProt¬¶•–•√•’•°•ø•§•‡•¢•¶•»ª˛
   * - ON_RECEIVER_ERROR:        InProt¬¶•®•È°ºª˛
   *
   * @else
   * @brief The types of ConnectorDataListener
   * - ON_BUFFER_READ:           At the time of buffer read
   * - ON_BUFFER_WRITE:          At the time of buffer write
   * - ON_BUFFER_FULL:           At the time of buffer full
   * - ON_BUFFER_WRITE_TIMEOUT:  At the time of buffer write timeout
   * - ON_BUFFER_OVERWRITE:      At the time of buffer overwrite
   * - ON_BUFFER_READ:           At the time of buffer read
   * - ON_SEND:                  At the time of sending to InPort
   * - ON_RECEIVED:              At the time of finishing sending to InPort
   * - ON_RECEIVER_FULL:         At the time of bufferfull of InPort
   * - ON_RECEIVER_TIMEOUT:      At the time of timeout of InPort
   * - ON_RECEIVER_ERROR:        At the time of error of InPort
   *
   * @endif
   */
  enum ConnectorDataListenerType
    {
      ON_SEND,
      ON_RECEIVED,
      ON_RECEIVER_FULL,
      ON_RECEIVER_TIMEOUT,
      ON_RECEIVER_ERROR,
      CONNECTOR_DATA_LISTENER_NUM
      ON_RECEIVED,

  /*!
      ON_RECEIVER_ERROR,
      CONNECTOR_DATA_LISTENER_NUM
    };

  /*!
   * @if jp
   * @class ConnectorDataListener •Ø•È•π
   * @brief ConnectorDataListener •Ø•È•π
   *
   * •«°º•ø•›°º•»§Œ Connector §À§™§§§∆»Ø¿∏§π§ÅE∆ºÅE§•Ÿ•Û•»§À¬–§π§ÅE≥°º
   * •ÅE–•√•Ø§Úº¬∏Ω§π§ÅEÅEπ• •Ø•È•π§Œ¥ƒÅEØ•È•π°£
   *
   * •≥•¢•˙¡∏•√•Ø§¨OutPort§À¬–§∑§∆•«°º•øΩÒ§≠π˛§ﬂ°¢InPort¬¶§«•«°º•ø§¨ºÅE   * ∆¿§µ§ÅEÅEﬁ§«§Œ¥÷§«»Ø¿∏§π§ÅE∆ºÅE§•Ÿ•Û•»§Ú•’•√•Ø§π§ÅE≥°º•ÅE–•√•Ø§Ú¿ﬂ
   * ƒÍ§π§ÅE≥§»§¨§«§≠§ÅE£§ §™°¢•ÅEπ• °º•Ø•È•π§œ2ºÅE‡¬∏∫ﬂ§∑°¢•–•√•’•°•’
   * •ÅE‰¡˜øÆª˛§Œ•≥°º•ÅE–•√•Ø§«°¢§Ω§Œª˛≈¿§«Õ≠∏˙§ •«°º•ø§Ú•’•°•Û•Ø•ø§Œ∞ÅE   * øÙ§»§∑§∆ºı§±ºË§ÅEConnectorDataListener §«§¢§Í°¢§‚§¶∞ÅE˝§œ•«°º•ø•®
   * •Û•◊•∆•£§‰•–•√•’•°∆…§ﬂπ˛§ﬂª˛§Œ•ø•§•‡•¢•¶•»§ §…•«°º•ø§¨ºË∆¿§«§≠§ §§
   * æÅEÁ§ §…§À•≥°º•ÅEµ§ÅEÅE’•°•Û•Ø•ø§Œ∞˙øÙ§À≤ø§‚§»§È§ §È§§
   * ConnecotorListener §¨§¢§ÅE£
   *
   * •«°º•ø•›°º•»§À§œ°¢¿‹¬≥ª˛§À•«°º•ø§Œ¡˜ºıøÆ ˝À°§À§ƒ§§§∆•«°º•ø•’•˙Ωº∑ø°¢
   * •µ•÷•π•Ø•ÅE◊•∑•Á•Û∑ø≈˘§Ú¿ﬂƒÍ§π§ÅE≥§»§¨§«§≠§ÅE£
   *
   * <pre>
   * class MyDataListener
   *   : public ConnectorDataListenerT<RTC::TimedLong>
   * {
   * public:
   *   MyDataListener(const char* name) : m_name(name) {}
   *   virtual ~MyDataListener() {}
   *   virtual ReturnCode operator()(ConnectorInfo& info, TimedLong& data)
   * -  Push∑ø: Subscription Type§À§Ë§Í§µ§È§À•§•Ÿ•Û•»§ŒºÅE‡§¨ ¨§´§ÅEÅE£
   *     std::cout << "Data Listener: " << m_name       << std::endl;
   *     std::cout << "Data:          " << data.data    << std::endl;
   *     std::cout << "Profile::name: " << info.name    << std::endl;
   *     std::cout << "Profile::id:   " << info.id      << std::endl;
   *     std::cout << "Profile::properties: "           << std::endl;
   *     std::cout << info.properties;
   *   };
   *   std::string m_name;
   * };
   * </pre>
   *
   * §≥§Œ§Ë§¶§À§∑§∆ƒÅE¡§µ§ÅEø•ÅEπ• •Ø•È•π§œ°¢∞ ≤º§Œ§Ë§¶§À•«°º•ø•›°º•»§À
   * ¬–§∑§∆°¢∞ ≤º§Œ§Ë§¶§À•ª•√•»§µ§ÅEÅE£
   *
   * <pre>
   * RTC::ReturnCode_t ConsoleIn::onInitialize()
   * {
   *     m_outOut.
   *         addConnectorDataListener(ON_BUFFER_WRITE,
   *                                  new MyDataListener("ON_BUFFER_WRITE"));
   *    :
   * </pre>
   *
   * ¬ÅE∞˙øÙ§Œ "ON_BUFFER_WRITE" §œ°¢•≥°º•ÅE–•√•Ø§Ú•’•√•Ø§π§ÅE›•§•Û•»§«
   * §¢§Í°¢∞ ≤º§ÀŒÛµÛ§π§ÅEÕ§ÚºË§ÅE≥§»§¨≤ƒ«Ω§«§¢§ÅE£•«°º•ø•›°º•»§À§œ°¢¿‹
   * ¬≥ª˛§À•«°º•ø§Œ¡˜ºıøÆ ˝À°§À§ƒ§§§∆°¢•§•Û•ø°º•’•ß°º•π∑ø°¢•«°º•ø•’•˙Ωº
   * ∑ø°¢•µ•÷•π•Ø•ÅE◊•∑•Á•Û∑ø≈˘§Ú¿ﬂƒÍ§π§ÅE≥§»§¨§«§≠§ÅE¨°¢§≥§ÅEÈ§Œ¿ﬂƒÍ§À
   * §Ë§ÅE’•√•Ø§µ§ÅEÅE›•§•Û•»§œ∞€§ §ÅE£∞ ≤º§À°¢•§•Û•ø°º•’•ß°º•π§¨CORBA
   * CDR∑ø§ŒæÅEÁ§Œ•≥°º•ÅE–•√•Ø∞ÅE˜§Úº®§π°£
   *
   * OutPort:
   * -  Push∑ø: Subscription Type§À§Ë§Í§µ§È§À•§•Ÿ•Û•»§ŒºÅE‡§¨ ¨§´§ÅEÅE£
   *   - Flush: Flush∑ø§À§œ•–•√•’•°§¨§ §§§ø§ÅEON_BUFFER ∑œ§Œ•§•Ÿ•Û•»§œ»Ø¿∏§∑§ §§
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     .
   *   - Flush: Flush∑ø§À§œ•–•√•’•°§¨§ §§§ø§ÅEON_BUFFER ∑œ§Œ•§•Ÿ•Û•»§œ»Ø¿∏§∑§ §§
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     - ON_BUFFER_WRITE
   *     - ON_BUFFER_FULL
   *     - ON_BUFFER_WRITE_TIMEOUT
   *     - ON_BUFFER_OVERWRITE
   *     - ON_BUFFER_READ
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     - ON_SENDER_ERROR
   *     - ON_CONNECT
   *     - ON_BUFFER_WRITE
   *     - ON_BUFFER_FULL
   *     - ON_BUFFER_WRITE_TIMEOUT
   *     - ON_BUFFER_READ
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     - ON_BUFFER_EMPTY
   *     - ON_SENDER_EMPTY
   * - Pull∑ø
   *   - ON_BUFFER_READ
   *   - ON_SEND
   *     - ON_BUFFER_WRITE
   *     - ON_BUFFER_FULL
   *     - ON_BUFFER_WRITE_TIMEOUT
   *     - ON_BUFFER_WRITE_OVERWRITE
   *   - ON_BUFFER_EMPTY
   *   - ON_BUFFER_READ_TIMEOUT
   *     - ON_RECEIVED
   *     - ON_BUFFER_WRITE
   *     - ON_BUFFER_FULL
   *     - ON_BUFFER_WRITE_TIMEOUT
   *     - ON_BUFFER_WRITE_OVERWRITE
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *
   * @else
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *
   * @class ConnectorDataListener class
   * @brief ConnectorDataListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in the data port's
   * connectors.
   * such as buffer-empty event, buffer-read-timeout event and so on.
   * @endif
   */
   * ConnectorDataListener, a class which inherits this class should
   * be defined, and the functor should receive a connector
   * information and a data value as arguments. And then, the defined
   * class must be set to data-port object through its member
   * function, as follows.  Two types of ConnectorDataListeners are
   * available. One is "ConnectorDataListener" which receives
   * marshalled data as data value, the other is
   * "ConnectorDataListenerT" which receives unmarshalled data as data
   * value. The following example is the use of ConnectorDataListenerT.
   *
   * <pre>
   * class MyDataListener
   *   : public ConnectorDataListenerT<RTC::TimedLong>
   * {
   * public:
   *   MyDataListener(const char* name) : m_name(name) {}
   *   virtual ~MyDataListener() {}
   *   virtual ReturnCode operator()(ConnectorInfo& info, TimedLong& data)
   *   {
   *     std::cout << "Data Listener: " << m_name       << std::endl;
   *     std::cout << "Data:          " << data.data    << std::endl;
   *     std::cout << "Profile::name: " << info.name    << std::endl;
   *     std::cout << "Profile::id:   " << info.id      << std::endl;
   *     std::cout << "Profile::properties: "           << std::endl;
   *     std::cout << info.properties;
   *   };
   *   std::string m_name;
   * };
   * </pre>
   *
   * The listener class defained as above can be attached to a
   * data-port as follows.
   *
   * <pre>
   * RTC::ReturnCode_t ConsoleIn::onInitialize()
   * {
   *     m_outOut.
   *         addConnectorDataListener(ON_BUFFER_WRITE,
   *                                  new MyDataListener("ON_BUFFER_WRITE"));
   *    :
   * </pre>
   *
   * The first argument "ON_BUFFER_WRITE" specifies hook point of
   * callback, and the following values are available. Data-port can
   * be specified some properties such as interface-type,
   * dataflow-type, subscription type and so on. Available hook points
   * vary by the those settings. The following hook points are
   * available when interface type is CORBA CDR type.
   *
   * OutPort:
   * -  Push type: Available hook event varies by subscription type.
   *   - Flush: No ON_BUFFER* events since flush-type has no buffer.
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     .
   *   - New type:
   *     - ON_BUFFER_WRITE
   *     - ON_BUFFER_FULL
   *     - ON_BUFFER_WRITE_TIMEOUT
   *     - ON_BUFFER_OVERWRITE
   *     - ON_BUFFER_READ
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     .
   *   - Periodic type:
   *     - ON_BUFFER_WRITE
   *     - ON_BUFFER_FULL
   *     - ON_BUFFER_WRITE_TIMEOUT
   *     - ON_BUFFER_READ
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     .
   *   .
   * - Pull type:
   *   - ON_BUFFER_WRITE
   *   - ON_BUFFER_FULL
   *   - ON_BUFFER_WRITE_TIMEOUT
   *   - ON_BUFFER_OVERWRITE
   *   - ON_BUFFER_READ
   *   - ON_SEND
   *   .
   * InPort:
   * - Push type:
   *     - ON_BUFFER_WRITE
   *     - ON_BUFFER_FULL
   *     - ON_BUFFER_WRITE_TIMEOUT
   *     - ON_BUFFER_WRITE_OVERWRITE
   *     - ON_BUFFER_READ
   *     - ON_BUFFER_READ_TIMEOUT
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   *     .
   * - Pull type
   *     - ON_BUFFER_READ
   *
   * @endif
   */
  class ConnectorDataListener
    : public ConnectorListenerStatus
  {
  public:
    USE_CONNLISTENER_STATUS;
    /*!
     * @if jp
  class ConnectorDataListener
  {
  public:
     * ConnectorDataListenerType §Ú ∏ª˙ŒÛ§À —¥π§π§ÅE     *
    /*!
     * @if jp
     * @return  ∏ª˙ŒÛ —¥π∑ÅEÃ
     *
     * @brief ConnectorDataListenerType §Ú ∏ª˙ŒÛ§À —¥π
     *
     * ConnectorDataListenerType §Ú ∏ª˙ŒÛ§À —¥π§π§ÅE     *
     * @param type  —¥π¬–æ› ConnectorDataListenerType
     *
     * @return  ∏ª˙ŒÛ —¥π∑ÅEÃ
     *
     * @else
     *
     * @brief Convert ConnectorDataListenerType into the string.
     *
     * Convert ConnectorDataListenerType into the string.
     *
     * @param type The target ConnectorDataListenerType for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(ConnectorDataListenerType type)
    {
      static const char* typeString[] =
        {
          "ON_BUFFER_WRITE",
          "ON_BUFFER_FULL",
          "ON_BUFFER_WRITE_TIMEOUT",
          "ON_BUFFER_OVERWRITE",
          "ON_BUFFER_READ", 
          "ON_SEND", 
          "ON_RECEIVED",
          "ON_RECEIVER_FULL", 
          "ON_RECEIVER_TIMEOUT", 
          "ON_RECEIVER_ERROR",
          "CONNECTOR_DATA_LISTENER_NUM"
        };
      if (type < CONNECTOR_DATA_LISTENER_NUM) { return typeString[type]; }
      return "";
    }

    /*!
     * @if jp
     * @brief •«•π•»•È•Ø•ø
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ConnectorDataListener();

    /*!
     * @if jp
     *
     * @brief ≤æ¡€•≥°º•ÅE–•√•Ø•·•Ω•√•…
     *
     * •«°º•ø•›°º•»§Œ Connector §À§™§§§∆»Ø¿∏§π§ÅE∆ºÅE§•Ÿ•Û•»§À¬–§π§ÅE≥°º
     * •ÅE–•√•Ø•·•Ω•√•…
     *
     * @else
     *
     * @brief Virtual Callback method
     *
     * This is a the Callback method to various events generated in Connector. 
     *
     * @endif
     */
    virtual void operator()(const ConnectorInfo& info,
                            const cdrMemoryStream& data) = 0;
   * •ÅE–•√•Ø§Úº¬∏Ω§π§ÅEÅEπ• •Ø•È•π§Œ¥ƒÅEØ•È•π°£
   * 

  /*!
   * @if jp
   * @class ConnectorDataListenerT •Ø•È•π
   * @brief ConnectorDataListenerT •Ø•È•π
   *
   * •«°º•ø•›°º•»§Œ Connector §À§™§§§∆»Ø¿∏§π§ÅE∆ºÅE§•Ÿ•Û•»§À¬–§π§ÅE≥°º
   * •ÅE–•√•Ø§Úº¬∏Ω§π§ÅEÅEπ• •Ø•È•π§Œ¥ƒÅEØ•È•π°£
   * 
   * §≥§Œ•Ø•È•π§œ°¢operator()() §Œ¬ÅE∞˙øÙ§À cdrMemoryStream ∑ø§«§œ§ §Ø°¢
   * º¬∫›§À•«°º•ø•›°º•»§«ª»Õ—§µ§ÅEÅE—øÙ∑ø§Ú•∆•Û•◊•ÅEº•»∞˙øÙ§»§∑§∆
   * ≈œ§π§≥§»§¨§«§≠§ÅE£
   *
   * @else
   * @class ConnectorDataListenerT class
   * @brief ConnectorDataListenerT class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in the data port's
   * connectors.
   *
   * This class template can have practical data types that are used
   * as typed variable for DataPort as an argument of template instead
   * of cdrMemoryStream.
   *
   * @endif
   */
  template <class DataType>
  class ConnectorDataListenerT
    : public ConnectorDataListener
  {
  public:
    /*!
     * @if jp
     * @brief •«•π•»•È•Ø•ø
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ConnectorDataListenerT(){}

    /*!
     * @if jp
     *
     * @brief •≥°º•ÅE–•√•Ø•·•Ω•√•…
     *
     * •«°º•ø§Ú•«°º•ø•›°º•»§«ª»Õ—§µ§ÅEÅE—øÙ∑ø§À —¥π§∑§∆ ConnectorDataListenerT
     * §Œ•≥°º•ÅE–•√•Ø•·•Ω•√•…§Ú∏∆§”Ω–§π°£
     *
     * @param info ConnectorInfo 
     * @param cdrdata cdrMemoryStream∑ø§Œ•«°º•ø
     *
     * @else
     *
     * @brief Callback method
     *
     * This method invokes the callback method of ConnectorDataListenerT. 
     * Data is converted into the variable type used in DataPort.
     *
     * @param info ConnectorInfo 
     * @param cdrdata Data of cdrMemoryStream type
     *
     * @endif
     */
    virtual void operator()(const ConnectorInfo& info,
                            const cdrMemoryStream& cdrdata)
    {
      DataType data;
#ifdef ORB_IS_ORBEXPRESS
      cdrMemoryStream cdr(cdrdata);
#elif defined(ORB_IS_TAO)
      cdrMemoryStream cdr(cdrdata);
#else
      cdrMemoryStream cdr(cdrdata.bufPtr(), cdrdata.bufSize());
#endif
      // endian type check
      std::string endian_type;
      endian_type = info.properties.getProperty("serializer.cdr.endian",
                                                "little");
      coil::normalize(endian_type);
      std::vector<std::string> endian(coil::split(endian_type, ","));

#ifdef ORB_IS_ORBEXPRESS
      if (endian[0] == "little")
        {
          cdr.cdr.is_little_endian(true);
        }
      else if (endian[0] == "big")
        {
          cdr.cdr.is_little_endian(false);
        }
       cdr.cdr >> data;
#elif defined(ORB_IS_TAO)
       TAO_InputCDR tao_cdr = TAO_InputCDR(cdr.cdr);
       tao_cdr >> data;
#else
      if (endian[0] == "little")
        {
          cdr.setByteSwapFlag(true);
        }
      else if (endian[0] == "big")
        {
          cdr.setByteSwapFlag(false);
        }
      data <<= cdr;
#endif





      this->operator()(info, data);
    }

    /*!
     * @if jp
     *
     * @brief ≤æ¡€•≥°º•ÅE–•√•Ø•·•Ω•√•…
     *
     * •«°º•ø•›°º•»§Œ Connector §À§™§§§∆»Ø¿∏§π§ÅE∆ºÅE§•Ÿ•Û•»§À¬–§π§ÅE≥°º
     * •ÅE–•√•Ø•·•Ω•√•…
     *
     * @else
     *
     * @brief Virtual Callback method
     *
     * This method invokes the callback method of ConnectorDataListenerT. 
     * Data is converted into the variable type used in DataPort.
     *
     * @endif
     */
    virtual void operator()(const ConnectorInfo& info,
                            const DataType& data) = 0;
                            
   * - ON_SENDER_ERROR:       OutPort¬¶•®•È°ºª˛
   * - ON_CONNECT:            ¿‹¬≥≥ŒŒ©ª˛
  /*!
   * @if jp
   * @brief ConnectorListener §Œ•ø•§•◊
   *  
   * - ON_BUFFER_EMPTY:       •–•√•’•°§¨∂ı§ŒæÅEÅE   * - ON_BUFFER_READTIMEOUT: •–•√•’•°§¨∂ı§«•ø•§•‡•¢•¶•»§∑§øæÅEÅE   * - ON_SENDER_EMPTY:       OutPort¬¶•–•√•’•°§¨∂ÅE   * - ON_SENDER_TIMEOUT:     OutPort¬¶•ø•§•‡•¢•¶•»ª˛
   * - ON_SENDER_ERROR:       OutPort¬¶•®•È°ºª˛
   * - ON_CONNECT:            ¿‹¬≥≥ŒŒ©ª˛
   * - ON_DISCONNECT:         ¿‹¬≥¿⁄√«ª˛
   *
   * @else
   * @brief The types of ConnectorListener
   * 
   * - ON_BUFFER_EMPTY:       At the time of buffer empty
   * - ON_BUFFER_READTIMEOUT: At the time of buffer read timeout
   * - ON_BUFFER_EMPTY:       At the time of empty of OutPort
   * - ON_SENDER_TIMEOUT:     At the time of timeout of OutPort
   * - ON_SENDER_ERROR:       At the time of error of OutPort
   * - ON_CONNECT:            At the time of connection
   * - ON_DISCONNECT:         At the time of disconnection
   *
   * @endif
   */
  enum ConnectorListenerType
    {
      ON_BUFFER_EMPTY = 0,
      ON_BUFFER_READ_TIMEOUT,
      ON_SENDER_EMPTY, 
      ON_SENDER_TIMEOUT, 
      ON_SENDER_ERROR, 
      ON_CONNECT,
      ON_DISCONNECT,
      CONNECTOR_LISTENER_NUM
   * •«°º•ø•›°º•»§Œ Connector §À§™§§§∆»Ø¿∏§π§ÅE∆ºÅE§•Ÿ•Û•»§À¬–§π§ÅE≥°º
   * •ÅE–•√•Ø§Úº¬∏Ω§π§ÅEÅEπ• •Ø•È•π§Œ¥ƒÅEØ•È•π°£
   *
   * @if jp
   * @class ConnectorListener •Ø•È•π
   * @brief ConnectorListener •Ø•È•π
   *
   * •«°º•ø•›°º•»§Œ Connector §À§™§§§∆»Ø¿∏§π§ÅE∆ºÅE§•Ÿ•Û•»§À¬–§π§ÅE≥°º
   * •ÅE–•√•Ø§Úº¬∏Ω§π§ÅEÅEπ• •Ø•È•π§Œ¥ƒÅEØ•È•π°£
   *
   * •≥•¢•˙¡∏•√•Ø§¨OutPort§À¬–§∑§∆•«°º•øΩÒ§≠π˛§ﬂ°¢InPort¬¶§«•«°º•ø§¨ºÅE   * ∆¿§µ§ÅEÅEﬁ§«§Œ¥÷§«»Ø¿∏§π§ÅE∆ºÅE§•Ÿ•Û•»§Ú•’•√•Ø§π§ÅE≥°º•ÅE–•√•Ø§Ú¿ﬂ
   * ƒÍ§π§ÅE≥§»§¨§«§≠§ÅE£§ §™°¢•ÅEπ• °º•Ø•È•π§œ2ºÅE‡¬∏∫ﬂ§∑°¢•–•√•’•°•’
   * •ÅE‰¡˜øÆª˛§Œ•≥°º•ÅE–•√•Ø§«°¢§Ω§Œª˛≈¿§«Õ≠∏˙§ •«°º•ø§Ú•’•°•Û•Ø•ø§Œ∞ÅE   * øÙ§»§∑§∆ºı§±ºË§ÅEConnectorDataListener §«§¢§Í°¢§‚§¶∞ÅE˝§œ•«°º•ø•®
   * •Û•◊•∆•£§‰•–•√•’•°∆…§ﬂπ˛§ﬂª˛§Œ•ø•§•‡•¢•¶•»§ §…•«°º•ø§¨ºË∆¿§«§≠§ §§
   * æÅEÁ§ §…§À•≥°º•ÅEµ§ÅEÅE’•°•Û•Ø•ø§Œ∞˙øÙ§À≤ø§‚§»§È§ §È§§
   * ConnecotorListener §¨§¢§ÅE£
   *
   * •«°º•ø•›°º•»§À§œ°¢¿‹¬≥ª˛§À•«°º•ø§Œ¡˜ºıøÆ ˝À°§À§ƒ§§§∆•«°º•ø•’•˙Ωº∑ø°¢
   * •µ•÷•π•Ø•ÅE◊•∑•Á•Û∑ø≈˘§Ú¿ﬂƒÍ§π§ÅE≥§»§¨§«§≠§ÅE£
   * ConnectorDaataListener/ConnectorListener §œ∂¶§À§À°¢ÕÕ°π§ •§•Ÿ•Û•»
   * §À¬–§π§ÅE≥°º•ÅE–•√•Ø§Ú¿ﬂƒÍ§π§ÅE≥§»§¨§«§≠§ÅE¨°¢§≥§ÅEÈ•«°º•ø•’•˙Ωº∑ø
   * §™§Ë§”•µ•÷•π•Ø•ÅE◊•∑•Á•Û∑ø§Œ¿ﬂƒÍ§À±˛§∏§∆°¢Õ¯Õ—§«§≠§ÅE‚§Œ°¢§«§≠§ §§
   * §‚§Œ°¢§ﬁ§ø∏∆§”Ω–§µ§ÅEÅEø•§•ﬂ•Û•∞§¨∞€§ §ÅE£∞ ≤º§À°¢•§•Û•ø°º•’•ß°º•π
   * §¨CORBA CDR∑ø§ŒæÅEÁ§Œ•≥°º•ÅE–•√•Ø∞ÅE˜§Úº®§π°£
   *
   *     std::cout << "Profile::name: " << info.name    << std::endl;
   *     std::cout << "Profile::id:   " << info.id      << std::endl;
   *     std::cout << "Profile::properties: "           << std::endl;
   *     std::cout << info.properties;
   *     - ON_RECEIVER_ERROR
   *   std::string m_name;
   * };
   * </pre>
   *
   * §≥§Œ§Ë§¶§À§∑§∆ƒÅE¡§µ§ÅEø•ÅEπ• •Ø•È•π§œ°¢∞ ≤º§Œ§Ë§¶§À•«°º•ø•›°º•»§À
   * ¬–§∑§∆°¢∞ ≤º§Œ§Ë§¶§À•ª•√•»§µ§ÅEÅE£
   *
   * <pre>
   * RTC::ReturnCode_t ConsoleIn::onInitialize()
   * {
   *     m_outOut.
   *         addConnectorListener(ON_BUFFER_EMPTY,
   *                              new MyListener("ON_BUFFER_EMPTY"));
   *    :
   * </pre>
   *
   * ¬ÅE∞˙øÙ§Œ "ON_BUFFER_EMPTY" §œ°¢•≥°º•ÅE–•√•Ø§Ú•’•√•Ø§π§ÅE›•§•Û•»§«
   * §¢§Í°¢∞ ≤º§ÀŒÛµÛ§π§ÅEÕ§ÚºË§ÅE≥§»§¨≤ƒ«Ω§«§¢§ÅE£•«°º•ø•›°º•»§À§œ°¢¿‹
   * ¬≥ª˛§À•«°º•ø§Œ¡˜ºıøÆ ˝À°§À§ƒ§§§∆°¢•§•Û•ø°º•’•ß°º•π∑ø°¢•«°º•ø•’•˙Ωº
   * ∑ø°¢•µ•÷•π•Ø•ÅE◊•∑•Á•Û∑ø≈˘§Ú¿ﬂƒÍ§π§ÅE≥§»§¨§«§≠§ÅE¨°¢§≥§ÅEÈ§Œ¿ﬂƒÍ§À
   * §Ë§ÅE’•√•Ø§µ§ÅEÅE›•§•Û•»§œ∞€§ §ÅE£∞ ≤º§À°¢•§•Û•ø°º•’•ß°º•π§¨CORBA
   * CDR∑ø§ŒæÅEÁ§Œ•≥°º•ÅE–•√•Ø∞ÅE˜§Úº®§π°£
   *
   * OutPort:
   * -  Push∑ø: Subscription Type§À§Ë§Í§µ§È§À•§•Ÿ•Û•»§ŒºÅE‡§¨ ¨§´§ÅEÅE£
   *   - Flush: Flush∑ø§À§œ•–•√•’•°§¨§ §§§ø§ÅEON_BUFFER ∑œ§Œ•§•Ÿ•Û•»§œ»Ø¿∏§∑§ §§
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     .
   *   - New∑ø
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     .
   *   - Periodic∑ø
   *     - ON_BUFFER_EMPTY
   *     - ON_BUFFER_READ_TIMEOUT
   *     - ON_SENDER_EMPTY
   *     - ON_SENDER_ERROR
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     .
   *     - ON_BUFFER_READ
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_SEND
   *     - ON_RECEIVED
   *     - ON_RECEIVER_FULL
   *     - ON_RECEIVER_TIMEOUT
   *   - ON_BUFFER_READ
   *   .
   *   - ON_SEND
   *   - ON_BUFFER_EMPTY
   *   - ON_BUFFER_READ_TIMEOUT
   *   - ON_SENDER_EMPTY
   *   - ON_SENDER_TIMEOUT
   *   - ON_SENDER_ERROR
   *   - ON_CONNECT
   * InPort:
   * - Push∑ø:
   *     - ON_BUFFER_WRITE
   *     - ON_BUFFER_FULL
   *     - ON_BUFFER_WRITE_TIMEOUT
   *     - ON_BUFFER_WRITE_OVERWRITE
   *     - ON_RECEIVED
   *
   *     - ON_RECEIVER_TIMEOUT
   *     - ON_RECEIVER_ERROR
   * connectors.
   *
   * @class ConnectorListener class
   * @brief ConnectorListener class
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
   * class must be set to data-port object through its member
     * @if jp
     *
   * <pre>
   * class MyListener
   *   : public ConnectorListener
   * {
   * public:
   *   MyListener(const char* name) : m_name(name) {}
   *   virtual ~MyListener() {}
   *   virtual ReturnCode operator()(ConnectorInfo& info)
   *   {
   *     std::cout << "Data Listener: " << m_name       << std::endl;
   *     std::cout << "Profile::name: " << info.name    << std::endl;
   *     std::cout << "Profile::id:   " << info.id      << std::endl;
   *     std::cout << "Profile::properties: "           << std::endl;
   *     std::cout << info.properties;
   *   };
   *   std::string m_name;
   * };
   * </pre>
   *
   * The listener class defained as above can be attached to a
   * data-port as follows.
   *
   * <pre>
   * RTC::ReturnCode_t ConsoleIn::onInitialize()
   * {
   *     m_outOut.
   *         addConnectorListener(ON_BUFFER_EMPTY,
   *                              new MyDataListener("ON_BUFFER_EMPTY"));
   *    :
   * </pre>
   *
   * The first argument "ON_BUFFER_EMPTY" specifies hook point of
   * callback, and the following values are available. Data-port can
   * be specified some properties such as interface-type,
   * dataflow-type, subscription type and so on. Available hook points
   * vary by the those settings. The following hook points are
   * available when interface type is CORBA CDR type.
   *
   * OutPort:
   * -  Push type: Available hook event varies by subscription type.
   *   - Flush: No ON_BUFFER* events since flush-type has no buffer.
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     .
   *   - New type:
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     .
   *   - Periodic type:
   *     - ON_BUFFER_EMPTY
   *     - ON_BUFFER_READ_TIMEOUT
   *     - ON_SENDER_EMPTY
   *     - ON_SENDER_ERROR
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     .
   *   .
   * - Pull type:
   *   - ON_BUFFER_EMPTY
   *   - ON_BUFFER_READ_TIMEOUT
   *   - ON_SENDER_EMPTY
   *   - ON_SENDER_TIMEOUT
   *   - ON_SENDER_ERROR
   *   - ON_CONNECT
   *   - ON_DISCONNECT
   *   .
   * InPort:
   * - Push type:
   *     - ON_BUFFER_EMPTY
   *     - ON_BUFFER_READ_TIMEOUT
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *     .
   * - Pull type:
   *     - ON_CONNECT
   *     - ON_DISCONNECT
   *
   * @endif
   */
  class ConnectorListener
    : public ConnectorListenerStatus
  {
  public:
    USE_CONNLISTENER_STATUS;
    /*!
     * @if jp
     *
     * @brief ConnectorListenerType §Ú ∏ª˙ŒÛ§À —¥π
     *
     * ConnectorListenerType §Ú ∏ª˙ŒÛ§À —¥π§π§ÅE     *
     * @param type  —¥π¬–æ› ConnectorListenerType
     *
     * @brief ConnectorListenerType §Ú ∏ª˙ŒÛ§À —¥π
     *
     * ConnectorListenerType §Ú ∏ª˙ŒÛ§À —¥π§π§ÅE     *
     *
     * @param type  —¥π¬–æ› ConnectorListenerType
     *
     * Convert ConnectorListenerType into the string.
     * @return  ∏ª˙ŒÛ —¥π∑ÅEÃ
     *
     * @else
     *
     * @brief Convert ConnectorListenerType into the string.
     *
     * Convert ConnectorListenerType into the string.
     *
     * @param type The target ConnectorListenerType for transformation
     *
     * @return Trnasformation result of string representation
     *
     * @endif
     */
    static const char* toString(ConnectorListenerType type)
    { 
      static const char* typeStr[] =
        {
          "ON_BUFFER_EMPTY",
          "ON_BUFFER_READ_TIMEOUT",
          "ON_SENDER_EMPTY", 
          "ON_SENDER_TIMEOUT", 
          "ON_SENDER_ERROR", 
          "ON_CONNECT",
          "ON_DISCONNECT",
          "CONNECTOR_LISTENER_NUM"
        };
      if (type < CONNECTOR_LISTENER_NUM) { return typeStr[type]; }
      return "";
    }

    /*!
     * @if jp
     * @brief •«•π•»•È•Ø•ø
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ConnectorListener();

    /*!
     * @if jp
     *
     * @brief ≤æ¡€•≥°º•ÅE–•√•Ø•·•Ω•√•…
     *
     * •«°º•ø•›°º•»§Œ Connector §À§™§§§∆»Ø¿∏§π§ÅE∆ºÅE§•Ÿ•Û•»§À¬–§π§ÅE≥°º
     * •ÅE–•√•Ø•·•Ω•√•…
     *
     * @else
     *
     * @brief Virtual Callback method
     *
     * This method invokes the callback method of ConnectorDataListenerT. 
     * Data is converted into the variable type used in DataPort.
     *
     * @endif
     */
    virtual void operator()(const ConnectorInfo& info) = 0;
  };


  /*!
   * @if jp
   * @class ConnectorDataListenerHolder
   * @brief ConnectorDataListener •€•ÅE¿•Ø•È•π
   *
   *
   *
   * @else
   * @class ConnectorDataListenerHolder
   * @brief ConnectorDataListener holder class
   *
   * This class manages one ore more instances of ConnectorDataListener class.
   *
   * @endif
   */
  class ConnectorDataListenerHolder
  {
    typedef std::pair<ConnectorDataListener*, bool> Entry;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief •≥•Û•π•»•È•Ø•ø
     * @else
     * @brief Constructor
     * @brief •«•π•»•È•Ø•ø
     * @endif
     */
    ConnectorDataListenerHolder();
    /*!
    virtual ~ConnectorDataListenerHolder();
     * @if jp
     * @brief •«•π•»•È•Ø•ø
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ConnectorDataListenerHolder();
    
    /*!
     * @if jp
     *
     * @brief •ÅEπ• °º§Œƒ…≤√
     *
     * •ÅEπ• °º§Úƒ…≤√§π§ÅE£
     *
     * @param listener ƒ…≤√§π§ÅEÅEπ• 
     * @param autoclean true:•«•π•»•È•Ø•ø§«∫ÅEÅEπ§ÅE
     *                  false:•«•π•»•È•Ø•ø§«∫ÅEÅE∑§ §§
     * @else
     *
     * @brief Add the listener.
     *
     * This method adds the listener. 
     *
     * @param listener Added listener
     * @param autoclean true:The listener is deleted at the destructor.,
     *                  false:The listener is not deleted at the destructor. 
     * @endif
     */
    void addListener(ConnectorDataListener* listener, bool autoclean);
    
    /*!
     * @if jp
     *
     * @brief •ÅEπ• °º§Œ∫ÅEÅE     *
     * •ÅEπ• §Ú∫ÅEÅEπ§ÅE£
     *
     * @param listener ∫ÅEÅEπ§ÅEÅEπ• 
     * @else
     *
     * @brief Remove the listener. 
     *
     * This method removes the listener. 
     *
     * @param listener Removed listener
     * @endif
     */
    void removeListener(ConnectorDataListener* listener);
    
    /*!
     * @if jp
     *
     * @brief •ÅEπ• °º§ŒøÙ§Ú∆¿§ÅE     *
     * ∏Ω∫ﬂ≈–œø§µ§ÅE∆§§§ÅEÅEπ• °ºøÙ§Ú∆¿§ÅE£
     *
     * @return listenerøÅE     * @else
     *
     * @brief Getting number of listeners.
     *
     * This method returns current number of listenrs.
     *
     * @return number of listeners
     * @endif
     */
    size_t size();

    /*!
     * @if jp
     *
     * @brief •ÅEπ• °º§ÿƒÃ√Œ§π§ÅE     *
     * ≈–œø§µ§ÅE∆§§§ÅEÅEπ• §Œ•≥°º•ÅE–•√•Ø•·•Ω•√•…§Ú∏∆§”Ω–§π°£
     *
     * @param info ConnectorInfo
     * @param cdrdata •«°º•ø
     * @else
     *
     * @brief Notify listeners. 
     *
     * This calls the Callback method of the registered listener. 
     *
     * @param info ConnectorInfo
     * @param cdrdata Data
     * @endif
     */
    void notify(const ConnectorInfo& info,
                const cdrMemoryStream& cdrdata);

    /*!
     * @if jp
     *
     * @brief •ÅEπ• °º§ÿƒÃ√Œ§π§ÅE•«°º•ø∑øªÿƒÅE«)
     *
     * ≈–œø§µ§ÅE∆§§§ÅEÅEπ• §Œ•≥°º•ÅE–•√•Ø•·•Ω•√•…§Ú∏∆§”Ω–§π°£
     * COnnectorDataListenerT ∑ø§Œ•≥°º•ÅE–•√•Ø§Œ§ﬂ•≥°º•ÅEµ§ÅEÅE£
     *
     * @param info ConnectorInfo
     * @param typeddata •«°º•ø° •«°º•ø∑øªÿƒÍ§¢§Í°À
     * @param info ConnectorInfo
     * @param typeddata Data
     * @brief Notify listeners. (Typed data version)
     *
     * This calls the Callback method of the registered listener.
     * This operation calls only ConnectorDataListenerT type callback.
     *
     * @param info ConnectorInfo
     * @param typeddata Data
      for (int i(0), len(m_listeners.size()); i < len; ++i)
     */
    template <class DataType>
    void notify(const ConnectorInfo& info, const DataType& typeddata)
    {
      Guard guard(m_mutex);
      for (int i(0), len(m_listeners.size()); i < len; ++i)
        {
          ConnectorDataListenerT<DataType>* listener(0);
          listener =
          dynamic_cast<ConnectorDataListenerT<DataType>*>(m_listeners[i].first);
          if (listener != 0)
            {
              listener->operator()(info, typeddata);
            }
        }
      return ret;

  private:
  private:
    std::vector<Entry> m_listeners;
    coil::Mutex m_mutex;
  };


  /*!
   * @if jp
   * @class ConnectorListenerHolder 
   * @brief ConnectorListener •€•ÅE¿•Ø•È•π
   *
   *  £øÙ§Œ ConnectorListener §Ú ›ª˝§∑¥…Õ˝§π§ÅEØ•È•π°£
   *
   * @else
   * @class ConnectorListenerHolder
   * @brief ConnectorListener holder class
   *
   * This class manages one ore more instances of ConnectorListener class.
   *  £øÙ§Œ ConnectorListener §Ú ›ª˝§∑¥…Õ˝§π§ÅEØ•È•π°£
   *
   * @else
   * @class ConnectorListenerHolder
   * @brief ConnectorListener holder class
   *
   * This class manages one ore more instances of ConnectorListener class.
   *
   * @endif
   */
  class ConnectorListenerHolder
  {
    typedef std::pair<ConnectorListener*, bool> Entry;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief •≥•Û•π•»•È•Ø•ø
     * @else
     * @brief Constructor
     * @endif
     */
    ConnectorListenerHolder();
    
     * @endif
    /*!
     * @if jp
     * @brief •«•π•»•È•Ø•ø
     * @else
     * @if jp
     * @brief Destructor
     * @endif
     */
    virtual ~ConnectorListenerHolder();
    
    /*!
     * @if jp
     *
     * @brief •ÅEπ• °º§Œƒ…≤√
     *
     * •ÅEπ• °º§Úƒ…≤√§π§ÅE£
     *
     * @param listener ƒ…≤√§π§ÅEÅEπ• 
     * @param autoclean true:•«•π•»•È•Ø•ø§«∫ÅEÅEπ§ÅE
     *                  false:•«•π•»•È•Ø•ø§«∫ÅEÅE∑§ §§
     * @else
     *
     * @brief Add the listener.
     *
     * This method adds the listener. 
     *
     * @param listener Added listener
     * @param autoclean true:The listener is deleted at the destructor.,
     *                  false:The listener is not deleted at the destructor. 
     * @endif
     */
    void addListener(ConnectorListener* listener, bool autoclean);
    
    /*!
     * @if jp
     *
     * @brief •ÅEπ• °º§Œ∫ÅEÅE     *
     * •ÅEπ• §Ú∫ÅEÅEπ§ÅE£
     *
     * @param listener ∫ÅEÅEπ§ÅEÅEπ• 
     * @else
     *
     * @brief Remove the listener. 
     *
     * This method removes the listener. 
     *
     * @param listener Removed listener
     * @endif
     */
    void removeListener(ConnectorListener* listener);

    /*!
     * @if jp
     *
     * @brief •ÅEπ• °º§ŒøÙ§Ú∆¿§ÅE     *
     * ∏Ω∫ﬂ≈–œø§µ§ÅE∆§§§ÅEÅEπ• °ºøÙ§Ú∆¿§ÅE£
     *
     * @return listenerøÅE     * @else
     *
     * @brief Getting number of listeners.
     *
     * This method returns current number of listenrs.
     *
     * @return number of listeners
     * @endif
     */
    size_t size();

    /*!
     * @if jp
     *
     * @brief •ÅEπ• °º§ÿƒÃ√Œ§π§ÅE     *
     * ≈–œø§µ§ÅE∆§§§ÅEÅEπ• §Œ•≥°º•ÅE–•√•Ø•·•Ω•√•…§Ú∏∆§”Ω–§π°£
     *
     * @param info ConnectorInfo
     * @else
     *
     * @brief Notify listeners. 
     *
     * This calls the Callback method of the registered listener. 
     *
     * @param info ConnectorInfo
     * @endif
     */
    void notify(const ConnectorInfo& info);
      
  private:
    std::vector<Entry> m_listeners;
    coil::Mutex m_mutex;
  };
  
  /*!
   * @if jp
   * @class ConnectorListeners
   * @brief ConnectorListeners •Ø•È•π
   *
   *
   * @else
   * @class ConnectorListeners
   * @brief ConnectorListeners class
   *
     * @if jp
   * @endif
   */
  class ConnectorListeners
  {
  public:
    /*!
     * @if jp
     * @brief ConnectorDataListenerType•ÅEπ• «€ŒÅE     * ConnectorDataListenerType•ÅEπ• §Ú≥ «º
     * @else
     * @brief ConnectorDataListenerType listener array
     * The ConnectorDataListenerType listener is stored.
     * @endif
     */
    ConnectorDataListenerHolder connectorData_[CONNECTOR_DATA_LISTENER_NUM];
    /*!
     * @if jp
     * @brief ConnectorListenerType•ÅEπ• «€ŒÅE     * ConnectorListenerType•ÅEπ• §Ú≥ «º
     * @else
     * @brief ConnectorListenerType listener array
     * The ConnectorListenerType listener is stored. 
     * @endif
