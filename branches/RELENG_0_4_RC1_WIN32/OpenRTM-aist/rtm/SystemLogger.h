// -*- C++ -*-
/*!
 * @file SystemLogger.h
 * @brief RT component logger class
 * @date $Date: 2007-01-21 10:37:55 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SystemLogger.h,v 1.3 2007-01-21 10:37:55 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2006/11/04 20:54:09  n-ando
 * classes were renamed and soruce code was re-formatted.
 *
 * Revision 1.1  2006/11/02 15:14:24  n-ando
 * RtcSystemLogger.h was moved to SystemLogger.h.
 *
 * Revision 1.2  2005/05/16 06:40:19  n-ando
 * - Dummy macro "__restrict" was defined for Windows port.
 * - Some bugs were fixed.
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#ifndef SystemLogger_h
#define SystemLogger_h

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <time.h>
#include <errno.h>

// ACE
#include <ace/Mutex.h>

#include "rtm/config_rtc.h"

#ifdef RTM_GCC2
#define NO_LOGGING
#endif

#ifdef WIN32
// It's dummy
#define __restrict
#endif

namespace RTC
{
  
#ifndef NO_LOGGING 
  template <typename _CharT, typename _Traits=std::char_traits<_CharT> >
  class EXPORTS sync_callback
  {
  public:
    virtual ~sync_callback(){}
    virtual int operator()(const _CharT* s) = 0;
  };
  
  /*!
   * @if jp
   *
   * @class basic_logbuf
   *
   * @brief ロガーバッファクラス
   *
   * basic_filebuf ライクなログバッファクラス。ローカルファイルへのログ吐き出し
   * を管理するバッファクラス。
   *
   * @else
   *
   * @class basic_logbuf
   *
   * @brief Logger buffer class
   *
   *
   * @endif
   */
  template <typename _CharT, typename _Traits=std::char_traits<_CharT> >
  class EXPORTS basic_logbuf
    : public std::basic_filebuf<_CharT, _Traits>
  {
  public:
    // Types:
    typedef _CharT                                     char_type;
    typedef _Traits                                    traits_type;
    typedef std::basic_filebuf<char_type, traits_type> __filebuf_type;
    
    /*!
     * @if jp
     *
     * @brief basic_logbuf クラスコンストラクタ
     *
     * デフォルトコンストラクタ
     *
     * @else
     *
     * @brief basic_logbuf class constructor.
     *
     * @endif
     */
    basic_logbuf()
      : __filebuf_type(), m_pCallBack(NULL)
    {;}
    
    /*!
     * @if jp
     *
     * @brief basic_logbuf クラスコンストラクタ
     *
     * ファイル名およびオープンモードを指定してコンストラクトするコンストラクタ
     *
     * @else
     *
     * @brief basic_logbuf class constructor.
     *
     * @endif
     */
    basic_logbuf(const char_type* s,
		 std::ios_base::openmode mode = std::ios_base::out, 
		 long protection = 0666)
      : __filebuf_type(), m_pCallBack(NULL)
    {
      this->open(s, mode);
    }
    
    /*!
     * @if jp
     *
     * @brief basic_logbuf クラスデストラクタ
     *
     * デストラクタ。ファイルをクローズする。
     *
     * @else
     *
     * @brief basic_logbuf class destractor.
     *
     * @endif
     */
    virtual ~basic_logbuf()
    {
      this->sync();
      this->close();
    };
    
    virtual std::streamsize sputn(const char_type* s, std::streamsize n)
    {
      ACE_Guard<ACE_Thread_Mutex> gaurd(m_Mutex);
      //	  std::string ss(s, n);
      //	  std::string sss;
      //	  sss = "HogeDara" + ss;
      std::streamsize ssize = this->xsputn(s, n);
      /*
	if (m_pCallBack != NULL)
	{
	(*m_pCallBack)(sss.c_str());
	}
      */
      this->sync();
      return ssize;
    }
    
    void setSyncCallBack(sync_callback<char_type>& cb)
    {
      m_pCallBack = &cb;
    }
    
  protected:
    /*!
     * @if jp
     *
     * @brief バッファ同期
     *
     * バッファがフラッシュされた際に呼ばれる同期関数。
     *
     * @else
     *
     * @brief synchronize buffer
     *
     * @endif
     */
    virtual int sync()
    {
      std::string::basic_string<_CharT> s(this->pbase(),
					  this->pptr() - this->pbase());
      if (m_pCallBack != NULL)
	{
	  (*m_pCallBack)(s.c_str());
	}
      
      // __filebuf_type::sync() resets the pointer
      int ret = __filebuf_type::sync();
      
      return ret;
    }
    
  private:
    ACE_Thread_Mutex m_Mutex;
    sync_callback<char_type>* m_pCallBack;
    
  };
  
  
  
  /*!
   * @if jp
   *
   * @class basic_medlogbuf
   *
   * @brief 仲介ロガーバッファクラス
   *
   * basic_streambuf ライクなログバッファクラス。basic_filebuf への仲介をする。
   * stream から受け取った文字列にヘッダなどを付加し basic_filebuf へ渡す。
   *
   * @else
   *
   * @class basic_medlogbuf
   *
   * @brief Logger buffer class
   *
   *
   * @endif
   */
  template <typename _CharT, typename _Traits=std::char_traits<_CharT> >
  class EXPORTS basic_medlogbuf
    : public std::basic_streambuf<_CharT, _Traits>
  {
  public:
    // Types:
    typedef _CharT                                       char_type;
    typedef _Traits                                      traits_type;
    typedef std::basic_streambuf<char_type, traits_type> __streambuf_type;
    typedef std::basic_filebuf<char_type, traits_type>   __filebuf_type;
    
    /*!
     * @if jp
     *
     * @brief basic_medlogbuf クラスコンストラクタ
     *
     * 引数に basic_filebuf オブジェクトを受け取る。
     * 受け取った filebuf に対してヘッダ等を付加した文字列を渡す。
     *
     * @else
     *
     * @brief basic_medlogbuf class constructor.
     *
     * @endif
     */
    basic_medlogbuf()
      : __streambuf_type(), m_pLogbuf(NULL)
    {
      // W3C standard date and time format.
      m_DateFmt = "[%Y-%m-%dT%H.%M.%S%Z]";
    }
    
    basic_medlogbuf(__filebuf_type& filebuf)
      : __streambuf_type(), m_pLogbuf(&filebuf)
    {
      char *pStart = m_Data;
      char *pEnd = m_Data + (LINE_MAX - 1);
      this->setp(pStart, pEnd);            // 書き込みポインタ。
      this->setg(pStart, pStart, pEnd);    // 読み取りポインタ。
      
      // W3C standard date and time format.
      m_DateFmt = "[%Y-%m-%dT%H.%M.%S%Z]";
    }
    
    /*!
     * @if jp
     *
     * @brief basic_medlogbuf クラスデストラクタ
     *
     * デストラクタ。
     *
     * @else
     *
     * @brief basic_medlogbuf class destractor.
     *
     * @endif
     */
    virtual ~basic_medlogbuf()
    {
      this->sync();
    }
    
    void setBuffer(__filebuf_type& filebuf)
    {
      m_pLogbuf = &filebuf;
      char *pStart = m_Data;
      char *pEnd = m_Data + (LINE_MAX - 1);
      this->setp(pStart, pEnd);            // 書き込みポインタ。
      this->setg(pStart, pStart, pEnd);    // 読み取りポインタ。
    }
    
    /*!
     * @if jp
     *
     * @brief ヘッダに付加する日時フォーマットを指定する。
     *
     * フォーマット指定文字列は以下のとおり。
     * %a abbreviated weekday name 
     * %A full weekday name 
     * %b abbreviated month name 
     * %B full month name 
     * %c the standard date and time string 
     * %d day of the month, as a number (1-31) 
     * %H hour, 24 hour format (0-23) 
     * %I hour, 12 hour format (1-12) 
     * %j day of the year, as a number (1-366) 
     * %m month as a number (1-12).
     *    Note: some versions of Microsoft Visual C++ may use values that range
     *    from 0-11. 
     * %M minute as a number (0-59) 
     * %p locale's equivalent of AM or PM 
     * %S second as a number (0-59) 
     * %U week of the year, sunday as the first day 
     * %w weekday as a decimal (0-6, sunday=0) 
     * %W week of the year, monday as the first day 
     * %x standard date string 
     * %X standard time string 
     * %y year in decimal, without the century (0-99) 
     * %Y year in decimal, with the century 
     * %Z time zone name 
     * %% a percent sign 
     *
     * @else
     *
     * @brief Set date/time format.
     *
     * @endif
     */
    void setDateFmt(char* fmt)
    {
      m_DateFmt = std::string(fmt);
    }
    
    /*!
     * @if jp
     *
     * @brief ヘッダに付加する日時フォーマットを指定する。
     *
     * @else
     *
     * @brief Set date/time format
     *
     * @endif
     */
    void setDateFmt(const std::string& fmt)
    {
      m_DateFmt = fmt;
    }
    
    /*!
     * @if jp
     *
     * @brief フォーマットされた現在日時文字列を取得する。
     *
     * @else
     *
     * @brief Get formatted date/time string.
     *
     * @endif
     */
    std::string getFmtDate()
    {
      const int maxsize = 256;
      char buf[maxsize];
      
      /*
	struct timeval tp;
	struct timezone tzp;
	gettimeofday(&tp, &tzp);
      */
      time_t timer;
      struct tm* date;
      
      timer = time(NULL);
      date = localtime(&timer);
      strftime(buf, maxsize, m_DateFmt.c_str(), date);
      
      std::string ret(buf);
      return ret;
    }
    
    /*!
     * @if jp
     *
     * @brief ヘッダの日時の後に付加する文字列を設定する。
     *
     * @else
     *
     * @brief Set suffix of date/time string of header.
     *
     * @endif
     */
    void setSuffix(char* suffix)
    {
      m_Suffix = std::string(suffix);
    }
    
    /*!
     * @if jp
     *
     * @brief ヘッダの日時の後に付加する文字列を設定する。
     *
     * @else
     *
     * @brief Set suffix of date/time string of header.
     *
     * @endif
     */
    void setSuffix(const std::string& suffix)
    {
      m_Suffix = suffix;
    }
    
    /*!
     * @if jp
     *
     * @brief ヘッダの日時の後に付加する文字列を取得する。
     *
     * @else
     *
     * @brief Get suffix of date/time string of header.
     *
     * @endif
     */
    std::string getSuffix()
    {
      return m_Suffix;
    }
    
    /*
      void setCallBack(void (*call_back)(std::string s))
      {
      
      }
    */
    
  protected:
    /*!
     * @if jp
     *
     * @brief バッファ同期
     *
     * バッファがフラッシュされた際に呼ばれる同期関数。
     *
     * @else
     *
     * @brief synchronize buffer
     *
     * @endif
     */
    virtual int sync()
    {
      int ret(0); 
      if (m_pLogbuf != NULL &&
	  (this->pptr() - this->pbase()) > 0)
	{
	  {
	    ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);
	    *(this->pptr()) = '\0';
	    std::string::basic_string<_CharT> tmp(this->pbase(),
						  this->pptr() - 
						  this->pbase());
	    
	    std::string s = getFmtDate();
	    s += ( s.size() > 0 ? " " : "" ) + getSuffix();
	    s += ( getSuffix().size() > 0 ? " " : "" ) + tmp;
	    // s += (getSuffix().size() > 0 ? " " : "" ) + getSuffix();
	    // s += (s.size() > 0 ? " " : "") + tmp;
	    m_pLogbuf->sputn(s.c_str(), s.size());
	    m_pLogbuf->pubsync();
	    // Reset pptr() pointer to pbase()
	    // __streambuf_type::sync() resets the pointer
	    ret = __streambuf_type::sync();
	    pbump( this->pbase() - this->pptr() );
	  }
	}
      return ret;
    }
    
  private:
    __filebuf_type* m_pLogbuf;
    char m_Data[LINE_MAX];
    std::string m_DateFmt;
    std::string m_Suffix;
    ACE_Thread_Mutex m_Mutex;
  };
  
  
  /*!
   * @if jp
   *
   * @class basic_dummybuf
   *
   * @brief ダミーバッファクラス
   *
   * 何もしないダミーバッファ。
   *
   * @else
   *
   * @class basic_dammybuf
   *
   * @brief Dummy buffer class
   *
   *
   * @endif
   */
  template <typename _CharT, typename _Traits=std::char_traits<_CharT> >
  class EXPORTS basic_dummybuf
    : public std::basic_streambuf<_CharT, _Traits>
  {
  public:
    // Types:
    typedef _CharT                               char_type;
    typedef _Traits                              traits_type;
    typedef typename traits_type::int_type       int_type;
    typedef typename traits_type::pos_type       pos_type;
    typedef typename traits_type::off_type       off_type;
    typedef std::basic_streambuf<char_type, traits_type> __streambuf_type;
    typedef std::basic_filebuf<char_type, traits_type>   __filebuf_type;
    
    basic_dummybuf()
    {
      char *pStart = m_Data;
      char *pEnd = m_Data + (LINE_MAX - 1);
      this->setp(pStart, pEnd);
      this->setg(pStart, pStart, pEnd);
    }

    ~basic_dummybuf()
    {
    }
    
    int_type overflow(int_type c = _Traits::eof() )
    {
      pbump( this->pbase() - this->pptr() );
      return _Traits::not_eof(c);
    }
    
    virtual int sync()
    {
      pbump( this->pbase() - this->pptr() );
      return 0;
    }
    
  private:
    char m_Data[255];
  };
  
  
  /*!
   * @if jp
   *
   * @class basic_logstream
   *
   * @brief ロガーフォーマットクラス
   *
   * basic_ostream ライクなログフォーマットクラス。
   *
   * @else
   *
   * @class basic_logstream
   *
   * @brief Logger format class
   *
   *
   * @endif
   */
  template <typename _CharT, typename _Traits=std::char_traits<_CharT> >
  class EXPORTS basic_logstream
    : public std::basic_ostream<_CharT, _Traits>
  {
  public:
    // Loglevel
    enum
      {          // No: Write out messages include the following.
	RTL_SILENT,  // 0: ()
	RTL_ERROR,   // 1: (ERROR)
	RTL_WARN,    // 2: (ERROR, WARN)
	RTL_INFO,    // 3: (ERROR, WARN, INFO)
	RTL_NORMAL,  // 4: (ERROR, WARN, INFO, NORMAL)
	RTL_DEBUG,   // 5: (ERROR, WARN, INFO, NORMAL, DEBUG)
	RTL_TRACE,   // 6: (ERROR, WARN, INFO, NORMAL, DEBUG, TRACE)
	RTL_VERBOSE, // 7: (ERROR, WARN, INFO, NORMAL, DEBUG, TRACE, VERBOSE)
	RTL_PARANOID,// 8: (ERROR, WARN, INFO, NORMAL, DEBUG, TRACE, VERBOSE, PARA)
	RTL_MANDATORY// This level is used for only LogLockLevel
      };
    
    static int strToLogLevel(const std::string& lv)
    {
      if (lv == "SILENT")
	return basic_logstream::RTL_SILENT;
      else if (lv == "ERROR")
	return basic_logstream::RTL_ERROR;
      else if (lv == "WARN")
	return basic_logstream::RTL_WARN;
      else if (lv == "INFO")
	return basic_logstream::RTL_INFO;
      else if (lv == "NORNAL")
	return basic_logstream::RTL_NORMAL;
      else if (lv == "DEBUG")
	return basic_logstream::RTL_DEBUG;
      else if (lv == "TRACE")
	return basic_logstream::RTL_TRACE;
      else if (lv == "VERBOSE")
	return basic_logstream::RTL_VERBOSE;
      else if (lv == "PARANOID")
	return basic_logstream::RTL_PARANOID;
      else if (lv == "MANDATORY")
	return basic_logstream::RTL_MANDATORY;
      else
	return basic_logstream::RTL_NORMAL;
    }
    
    // Types:
    typedef _CharT                                       char_type;
    typedef _Traits                                      traits_type;
    typedef basic_logbuf<char_type, traits_type>         __logbuf_type;
    typedef basic_dummybuf<char_type, traits_type>       __dummybuf_type;
    typedef basic_logstream<char_type, traits_type>      __logstream_type;
    typedef std::basic_ostream<char_type, traits_type>   __ostream_type;
    typedef std::basic_streambuf<char_type, traits_type> __streambuf_type;
    
    /*!
     * @if jp
     *
     * @brief basic_logstream クラスコンストラクタ
     *
     * デフォルトコンストラクタ
     *
     * @param streambuf basic_streambuf 型オブジェクト
     *
     * @else
     *
     * @brief basic_logbuf class constructor.
     *
     * @endif
     */
    basic_logstream(__streambuf_type& streambuf)
      : __ostream_type(&streambuf),
	m_DummyStream(new __dummybuf_type()),
	m_LogLevel(RTL_NORMAL), m_LogLock(false)
    {
      this->init(&streambuf);
    }
    
    /*!
     * @if jp
     *
     * @brief basic_logstream クラスデストラクタ
     *
     * デストラクタ。
     *
     * @else
     *
     * @brief basic_logstream class destractor.
     *
     * @endif
     */
    ~basic_logstream()
    {
    }
    
    /*!
     * @if jp
     *
     * @brief 現在保持しているバッファへのポインタを返す。
     *
     * @else
     *
     * @brief return a pointer of a current buffer.
     *
     * @endif
     */
    /*
      __logbuf_type*	rdbuf() const
      {
      return const_cast<__logbuf_type*>(&m_Streambuf);
      }
    */
    
    /*!
     * @if jp
     *
     * @brief printf フォーマット出力
     *
     * printfライクな書式でログ出力する。
     *
     * @else
     *
     * @brief Formatted output like printf
     *
     * @endif
     */
    static std::string printf(char const * __restrict fmt, ...)
    {
      char str[LINE_MAX];
      va_list ap;
      
      va_start(ap, fmt);
#ifdef WIN32
      _vsnprintf(str, LINE_MAX - 1, fmt, ap);
#else
      vsnprintf(str, LINE_MAX - 1, fmt, ap);
#endif
      va_end(ap);
      std::string s(str);
      
      return s;
    }
    
    
    void setLogLevel(const std::string& level)
    {
      m_LogLevel = strToLogLevel(level);
    }

    void setLogLevel(int level)
    {
      m_LogLevel = level;
    }
    
    void setLogLock(bool lock)
    {
      m_LogLock = lock;
    }
    
    
    void enableLogLock()
    {
      m_LogLock = true;
    }
    
    void disableLogLock()
    {
      m_LogLock = false;
    }
    
    __ostream_type& level(int level)
    {
      if (m_LogLevel >= level)
	{
	  return *this;
	}
      else
	{
	  return m_DummyStream;
	}
      
    }
    
    inline void acquire()
    {
      if (m_LogLock) m_Mutex.acquire();
    }
    
    inline void release()
    {
      if (m_LogLock) m_Mutex.release();
    }
    
    __ostream_type m_DummyStream;
    
  private:
    int m_LogLevel;
    bool m_LogLock;
    ACE_Thread_Mutex m_Mutex;
    
  };
  typedef sync_callback<char>   SyncCallback;
  typedef basic_logbuf<char>    Logbuf;
  typedef basic_medlogbuf<char> MedLogbuf;
  typedef basic_logstream<char> LogStream;
  
#else //// NO_LOGGING  
  
  class EXPORTS SyncCallback
  {
  public:
    SyncCallback() {;};
    virtual int operator()(const char* s) {;};
  };
  
  class EXPORTS Logbuf
  {
  public:
    Logbuf() {;};
    Logbuf(const char* s, int m) {;};
    void open(const char* s, int m) {;};
    void setSyncCallBack(SyncCallback& cb) {;};
  };
  
  class EXPORTS MedLogbuf
  {
  public:
    MedLogbuf() {;};
    MedLogbuf(Logbuf& f) {;};
    void setDateFmt(char* fmt) {;};
    void setDateFmt(const std::string& fmt) {;};
    void setSuffix(const char* suffix) {;};
    void setSuffix(const std::string& suffix) {;};
  };
  
  class EXPORTS LogStream
    : public ostream
  {
  public:
    enum {SILENT, ERROR, WARN, INFO, NORMAL, DEBUG, TRACE, VERBOSE, PARANOID, MANDATORY };
    static int strToLogLevel(const std::string& lv){return NORMAL;}
    LogStream(MedLogbuf& buf) {;};
    void setLogLevel(int level) {;};
    void setLogLock(int lock) {;};
    LogStream& level(int level) {return *this;};
    /*
      LogStream& operator<<(const char* s) {return *this;};
      LogStream& operator<<(const string s) {return *this;};
      LogStream& operator<<(const ostream& o) {return *this;};
      LogStream& operator<<(const ostream o) {return *this;};
    */
  };
  
#endif // NO_LOGGING  
  
  
  // __VA_ARGS__ cannot be used in VC	
#if 0
#define RTC_LOG(LV, fmt, ...) \
  rtcout.level(LV) << rtcout.printf(fmt, __VA_ARGS__) << std::endl;
#define RTC_ERROR(fmt, ...) \
  RTC_LOG(LogStream::RTL_ERROR, fmt, __VA_ARGS__)
#define RTC_WARN(fmt, ...) \
  RTC_LOG(LogStream::RTL_WARN, fmt, __VA_ARGS__)
#define RTC_NORMAL(fmt, ...) \
  RTC_LOG(LogStream::RTL_NORMAL, fmt, __VA_ARGS__)
#define RTC_INFO(fmt, ...) \
  RTC_LOG(LogStream::RTL_INFO, fmt, __VA_ARGS__)
#define RTC_DEBUG(fmt, ...) \
  RTC_LOG(LogStream::RTL_DEBUG, fmt, __VA_ARGS__)
#define RTC_TRACE(fmt, ...) \
  RTC_LOG(LogStream::RTL_TRACE, fmt, __VA_ARGS__)
#define RTC_VERBOSE(fmt, ...) \
  RTC_LOG(LogStream::RTL_VERBOSE, fmt, __VA_ARGS__)
#define RTC_PARANOID(fmt, ...) \
  RTC_LOG(LogStream::RTL_PARANOID, fmt, __VA_ARGS__)
#endif
  
#ifndef NO_LOGGING
  
  /*!
   * @if jp
   *
   * @brief 汎用ログ出力マクロ
   *
   * ログレベルおよび出力フォーマット文字列を引数としてとる。
   *
   * @else
   *
   * @brief Log output macro
   *
   * @endif
   */
#define RTC_LOG(LV, fmt) \
  rtcout.acquire(); \
  rtcout.level(LV) << rtcout.printf fmt << std::endl; \
  rtcout.release()
  
  /*!
   * @if jp
   *
   * @brief エラーログ出力マクロ。
   *
   * エラーレベルのログ出力マクロ。ログレベルが
   * ERROR, WARN, INFO, NORMAL, DEBUG, TRACE, VERBOSE, PARANOID
   * の場合にログ出力される。
   *
   * @else
   *
   * @brief Error log output macro.
   *
   * @endif
   */
#define RTC_ERROR(fmt) \
  rtcout.acquire(); \
  rtcout.level(LogStream::RTL_ERROR)  << rtcout.printf fmt << std::endl; \
  rtcout.release()
  
  /*!
   * @if jp
   *
   * @brief ワーニングログ出力マクロ。
   *
   * ウォーニングレベルのログ出力マクロ。ログレベルが
   * ( WARN, INFO, NORMAL, DEBUG, TRACE, VERBOSE, PARANOID )
   * の場合にログ出力される。
   *
   * @else
   *
   * @brief Warning log output macro.
   *
   * If logging levels are
   * ( WARN, INFO, NORMAL, DEBUG, TRACE, VERBOSE, PARANOID ),
   * message will be output to log.
   *
   * @endif
   */
#define RTC_WARN(fmt) \
  rtcout.acquire(); \
  rtcout.level(LogStream::RTL_WARN) << rtcout.printf fmt << std::endl;\
  rtcout.release()
  
  /*!
   * @if jp
   *
   * @brief インフォログ出力マクロ。
   *
   * インフォレベルのログ出力マクロ。ログレベルが
   * ( INFO, NORMAL, DEBUG, TRACE, VERBOSE, PARANOID )
   * の場合にログ出力される。
   *
   * @else
   *
   * @brief Infomation level log output macro.
   *
   *  If logging levels are
   * ( INFO, NORMAL, DEBUG, TRACE, VERBOSE, PARANOID ),
   * message will be output to log.
   *
   * @endif
   */
#define RTC_INFO(fmt) \
  rtcout.acquire(); \
  rtcout.level(LogStream::RTL_INFO) << rtcout.printf fmt << std::endl;\
  rtcout.release()
  
  /*!
   * @if jp
   *
   * @brief ノーマルログ出力マクロ。
   *
   * ノーマルレベルのログ出力マクロ。ログレベルが
   * ( NORMAL, DEBUG, TRACE, VERBOSE, PARANOID )
   * の場合にログ出力される。
   *
   * @else
   *
   * @brief Normal level log output macro.
   *
   * If logging levels are
   * ( NORMAL, DEBUG, TRACE, VERBOSE, PARANOID ),
   * message will be output to log.
   *
   * @endif
   */
#define RTC_NORMAL(fmt)	\
  rtcout.acquire();	\
  rtcout.level(LogStream::RTL_NORMAL) << rtcout.printf fmt << std::endl;\
  rtcout.release()
  
  /*!
   * @if jp
   *
   * @brief デバッグログ出力マクロ。
   *
   * デバッグレベルのログ出力マクロ。ログレベルが
   * ( DEBUG, TRACE, VERBOSE, PARANOID )
   * の場合にログ出力される。
   *
   * @else
   *
   * @brief Debug level log output macro.
   *
   * If logging levels are
   * ( DEBUG, TRACE, VERBOSE, PARANOID ),
   * message will be output to log.
   *
   * @endif
   */
#define RTC_DEBUG(fmt) \
  rtcout.acquire(); \
  rtcout.level(LogStream::RTL_DEBUG) << rtcout.printf fmt << std::endl; \
  rtcout.release()
  
  /*!
   * @if jp
   *
   * @brief トレースログ出力マクロ。
   *
   * トレースレベルのログ出力マクロ。ログレベルが
   * ( TRACE, VERBOSE, PARANOID )
   * の場合にログ出力される。
   *
   * @else
   *
   * @brief Trace level log output macro.
   *
   * If logging levels are
   * ( TRACE, VERBOSE, PARANOID ),
   * message will be output to log.
   *
   * @endif
   */
#define RTC_TRACE(fmt) \
  rtcout.acquire(); \
  rtcout.level(LogStream::RTL_TRACE) << rtcout.printf fmt << std::endl; \
  rtcout.release()
  
  /*!
   * @if jp
   *
   * @brief ベルボーズログ出力マクロ。
   *
   * ベルボーズレベルのログ出力マクロ。ログレベルが
   * ( VERBOSE, PARANOID )
   * の場合にログ出力される。
   *
   * @else
   *
   * @brief Verbose level log output macro.
   *
   * If logging levels are
   * ( VERBOSE, PARANOID ),
   * message will be output to log.
   *
   * @endif
   */
#define RTC_VERBOSE(fmt) \
  rtcout.acquire(); \
  rtcout.level(LogStream::RTL_VERBOSE) << rtcout.printf fmt << std::endl; \
  rtcout.release()
  
  /*!
   * @if jp
   *
   * @brief パラノイドログ出力マクロ。
   *
   * パラノイドレベルのログ出力マクロ。ログレベルが
   * ( PARANOID )
   * の場合にログ出力される。
   *
   * @else
   *
   * @brief Paranoid level log output macro.
   *
   * If logging levels are
   * ( PARANOID ),
   * message will be output to log.
   *
   * @endif
   */
#define RTC_PARANOID(fmt) \
  rtcout.acquire(); \
  rtcout.level(LogStream::RTL_PARANOID) << rtcout.printf fmt << std::endl; \
  rtcout.release()
  
#else
#define RTC_ERROR(fmt)
#define RTC_WARN(fmt)
#define RTC_NORMAL(fmt)
#define RTC_INFO(fmt)
#define RTC_DEBUG(fmt)
#define RTC_TRACE(fmt)
#define RTC_VERBOSE(fmt)
#define RTC_PARANOID(fmt)
#endif
  
}; // namespace RTC

#endif  // SystemLogger_h
