// -*- C++ -*-
/*!
 * @file LogstreamFile.h
 * @brief File logger stream class
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

#ifndef RTC_LOGSTREAMFILE_H
#define RTC_LOGSTREAMFILE_H

#include <string>
#include <fstream>
#include <iostream>
#include <coil/stringutil.h>
#include <rtm/LogstreamBase.h>

namespace RTC
{
  /*!
   * @if jp
   *
   * @class PublisherBase
   *
   * @brief Publisher 基底クラス
   * 
   * データ送出タイミングを管理して送出を駆動するPublisher* の基底クラス。
   * 各種 Publisher はこのクラスを継承して詳細を実装する。
   *
   * @since 0.4.0
   *
   * @else
   *
   * @class PublisherBase
   *
   * @brief Base class of Publisher.
   *
   * This is a base class of Publisher*. This class manages data send timing.
   * Variation of Publisher* which implements details of Publisher inherits
   * this PublisherBase class.
   *
   * @endif
   */
  class LogstreamFile
    : public LogstreamBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * @else
     *
     * @brief Constructor
     *
     * @endif
     */
    LogstreamFile();

    /*!
     * @if jp
     *
     * @brief デストラクタ
     *
     * @else
     *
     * @brief Destructor
     *
     * @endif
     */
    virtual ~LogstreamFile(void);

    /*!
     * @if jp
     * @brief 設定初期化
     *
     * Logstreamクラスの各種設定を行う。実装クラスでは、与えられた
     * Propertiesから必要な情報を取得して各種設定を行う。
     *
     * @param prop 設定情報
     *
     * @else
     *
     * @brief Initializing configuration
     *
     * This operation would be called to configure in initialization.
     * In the concrete class, configuration should be performed
     * getting appropriate information from the given Properties data.
     *
     * @param prop Configuration information
     *
     * @endif
     */
    virtual bool init(const coil::Properties& prop);

    /*!
     * @if jp
     * @brief basic_strembuf へのポインタを返す
     *
     * Loggerで使用する basic_streambuf へのポインタを返す。
     *
     * @return basic_streambuf (coil::LogStreambuf) へのポインタ
     *
     * @else
     *
     * @brief Returns a pointer to the basic_streambuf 
     *
     * This operation would returns a pointer to the basic_streambuf
     * or its subclass that is kept in this class.
     *
     * @return pointer to the basic_streambuf (coil::LogStreambuf)
     *
     * @endif
     */
    virtual StreambufType* getStreamBuffer();

  protected:
    static coil::vstring s_files;
    std::string m_fileName;
    StreambufType* m_stdout;
    std::filebuf* m_fileout;
  };
}; // namespace RTC

extern "C"
{
  void DLL_EXPORT LogstreamFileInit();
};

#endif // RTC_LOGSTREAMFILE_H
