// -*- C++ -*-
/*!
 * @file TimeMeasure.cpp
 * @brief Periodic time measurement class
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

#ifndef LOGGER_H
#define LOGGER_H

#include <limits.h>
#include <iostream>
#include <coil/Mutex.h>
#include <coil/Guard.h>


#define BUFFER_LEN LINE_MAX

namespace coil
{
  template <typename _CharT, typename _Traits=std::char_traits<_CharT> >
  class log_streambuf
    : public ::std::basic_streambuf<_CharT, _Traits>
  {
  public:
    typedef _CharT                                       char_type;
    typedef _Traits                                      traits_type;
    typedef std::basic_streambuf<char_type, traits_type> streambuf_type;
    typedef coil::Mutex Mutex;
    typedef coil::Guard<coil::Mutex> Guard;

    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @endif
     */
    log_streambuf()
      : streambuf_type()
    {
      char *pStart = m_buf;
      char *pEnd = m_buf + (BUFFER_LEN - 1);
      this->setp(pStart, pEnd);
      this->setg(pStart, pStart, pEnd);
    }

    /*!
     * @if jp
     *
     * @brief デストラクタ
     *
     * デストラクタ。
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~log_streambuf()
    {
    }

    /*!
     * @if jp
     *
     * @brief ストリームを追加する
     *
     * log_streambuf に実際の出力先であるストリームを追加する。
     * ここで追加されたストリームの解体責任はユーザにあり、
     * log_streambuf 解体時には解体されることはない。
     * また追加されているストリームを log_streambuf の解体前に
     * 解体してはならない。ストリームの解体は log_streambuf の解体後に、
     * ユーザが解体しなければならない。
     *
     * @param stream std::basic_streambuf 型のストリームへのポインタ
     *
     * @else
     *
     * @brief Destructor
     *
     * This operation adds a stream that is actual output stream.
     * User has responsibility to destruct the stream object, since
     * this object never destructs the stream objects.  The added
     * stream objects should not be destructed before the destruction
     * of this object.  The stream destruction should be done by user
     * after removing it from this object or destructing this object.
     *
     * @param stream a pointer to std::basic_streambuf type stream object
     *
     * @endif
     */
    void addStream(streambuf_type* stream)
    {
      m_streams.push_back(Stream(stream));
    }

    /*!
     * @if jp
     *
     * @brief ストリームを削除する
     *
     * log_streambuf から出力先であるストリームを削除する。
     * ここで削除されたストリームの解体責任はユーザにある。
     *
     * @param stream std::basic_streambuf 型のストリームへのポインタ
     *
     * @else
     *
     * @brief Destructor
     *
     * This operation remove a stream that is actual output stream.
     * User has responsibility to destruct the stream object.
     *
     * @param stream a pointer to std::basic_streambuf type stream object
     * @return Whether removing the stream succeeded.
     *
     * @endif
     */
    bool removeStream(streambuf_type* stream)
    {
      for (int i(0), len(m_streams.size()); i < len; ++i)
        {
          m_streams[i].stream_ == stream;
          m_streams.erase(i);
          return true;
        }
      return false;
    }



   
  protected:
    /*!
     * @if jp
     *
     * @brief basic_streambuf::xsputn のオーバーライド
     *
     * @param s 入力文字列へのポインタ
     * @param n 入力文字数
     * @return 入力文字列のサイズ
     *
     * @else
     *
     * @brief override of basic_streambuf::xsputn
     *
     * @param s a pointer to input characters
     * @param n number of input characters
     * @return input stream size
     *
     * @endif
     */
    virtual std::streamsize xsputn(const char_type* s, std::streamsize n)
    {
      for (int i(0), len(m_streams.size()); i < len; ++i)
        {
          Guard gaurd(m_streams[i].mutex_);
          m_streams[i].stream_->sputn(s, n);
        }
      return n;
    }

    /*!
     * @if jp
     *
     * @brief basic_streambuf::overflow のオーバーライド
     *
     * @param c 入力文字
     * @return 返却値
     *
     * @else
     *
     * @brief override of basic_streambuf::overflow
     *
     * @param c input character
     * @return return value
     *
     * @endif
     */
    virtual int overflow (int c = traits_type::eof())
    {
      Guard guard(m_mutex);
//      if (traits_type::eq_int_type(c, traits_type::eof()))
//        return c;
//
//      char_type last_char = traits_type::to_char_type(c);
//      if (sputn(&last_char, 1) != 1)
//        return traits_type::eof();
//      else
//        return c;

      if (this->pbase())
        {
          if (this->pptr() > this->epptr() || this->pptr() < this->pbase())
            return traits_type::eof();
          // Add extra character to buffer if not EOF
          if (!traits_type::eq_int_type(c, traits_type::eof()))
            {
              *(this->pptr()) = traits_type::to_char_type(c);
              this->pbump(1);
            }
          // Number of characters to write to file
          int bytes_to_write = this->pptr() - this->pbase();
          // Overflow doesn't fail if nothing is to be written
          if (bytes_to_write > 0)
            {
              if (sputn(this->pbase(), bytes_to_write) != bytes_to_write)
                return traits_type::eof();
              // Reset next pointer to point to pbase on success
              this->pbump(-bytes_to_write);
            }
        }
      // Write extra character to file if not EOF
      else if (!traits_type::eq_int_type(c, traits_type::eof()))
        {
          // Impromptu char buffer (allows "unbuffered" output)
          char_type last_char = traits_type::to_char_type(c);
          // If gzipped file won't accept this character, fail
          if (sputn(&last_char, 1) != 1)
            return traits_type::eof();
        }
      // If you got here, you have succeeded (even if c was EOF)
      // The return value should therefore be non-EOF
      if (traits_type::eq_int_type(c, traits_type::eof()))
        return traits_type::not_eof(c);
      else
        return c;
    } 

    /*!
     * @if jp
     *
     * @brief basic_streambuf::sync のオーバーライド
     *
     * @return 返却値
     *
     * @else
     *
     * @brief override of basic_streambuf::sync
     *
     * @return return value
     *
     * @endif
     */
    virtual int sync()
    {
      if (this->pbase())
        {
          //          Guard guard(m_mutex);
          if (this->pptr() > this->epptr() || this->pptr() < this->pbase())
            return -1;

          int bytes_to_write = this->pptr() - this->pbase();
          if (bytes_to_write > 0)
            {
              if (sputn(this->pbase(), bytes_to_write) != bytes_to_write)
                {
                  return -1;
                }
              this->pbump(-bytes_to_write);
            }
        }
      else
        {
          this->overflow();
        }
      return 0;
    }

  private:
    log_streambuf(const log_streambuf& x);
    log_streambuf& operator=(const log_streambuf& x);

    struct Stream
    {
      Stream(streambuf_type* stream)
        : stream_(stream)
      {
      }
      virtual ~Stream() {}
      Stream(const Stream& x)
      {
        stream_ = x.stream_;
      }
      Stream& operator=(Stream& x)
      {
        streambuf_type* tmp(x.stream_);
        x.stream_ = stream_;
        stream_ = tmp;
        return *this;
      }
      Mutex mutex_;
      streambuf_type* stream_;
    };
    std::vector<Stream> m_streams;
    Mutex m_mutex;
    char m_buf[BUFFER_LEN];
  };



  template <typename _CharT, typename _Traits=std::char_traits<_CharT> >
  class log_stream
    : public std::basic_ostream<_CharT, _Traits>
  {
  public:
    // Types:
    typedef _CharT                                       char_type;
    typedef _Traits                                      traits_type;
    typedef std::basic_ostream<char_type, traits_type>   ostream_type;
    typedef std::basic_streambuf<char_type, traits_type> streambuf_type;
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @param streambuf basic_streambuf 型オブジェクト
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @param streambuf basic_streambuf type object
     *
     * @endif
     */
    log_stream(streambuf_type* sb, int level = 0)
      : ostream_type(sb),
        m_loglevel(level), m_lock(false), m_prefix("")
    {
      this->init(sb);
    }
    
    /*!
     * @if jp
     *
     * @brief デストラクタ
     *
     * デストラクタ。
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    ~log_stream()
    {
    }
    
    virtual std::string& prefix(std::string& prefix, int level)
    {
      return prefix;
    }

    /*!
     * @if jp
     *
     * @brief ログレベル設定
     *
     * ログレベルを設定する。
     *
     * @param level ログレベル
     *
     * @else
     *
     * @brief Set the log level
     *
     * Set the log level.
     *
     * @param level Log level
     *
     * @endif
     */
    void setLevel(int level)
    {
      m_loglevel = level;
    }
    
    /*!
     * @if jp
     *
     * @brief ロックモード設定
     *
     * ロックモードを有効にする。
     *
     * @else
     *
     * @brief Enable the lock mode
     *
     * Enable the lock mode.
     *
     * @endif
     */
    void enableLock()
    {
      m_lock = true;
    }
    
    /*!
     * @if jp
     *
     * @brief ロックモード解除
     *
     * ロックモードを無効にする。
     *
     * @else
     *
     * @brief Disable the lock mode
     *
     * Disable the lock mode.
     *
     * @endif
     */
    void disableLock()
    {
      m_lock = false;
    }
    
    /*!
     * @if jp
     *
     * @brief ログストリームの取得
     *
     * 指定されたログレベルを判断し、ログストリームを取得する。
     * 指定されたログレベルが設定されているログレベル以下の場合には、本クラスを
     * 返す。
     * 指定されたログレベルが設定されているログレベルを超えている場合には、
     * ダミーログクラスを返す。
     *
     * @param level 指定ログレベル
     *
     * @return 対象ログストリーム
     *
     * @else
     *
     * @brief Acquire log stream
     *
     * Investigate the specified log level and get its log stream.
     * If the specified log level is under the set log level, this class
     * will be returned.
     * If the specified log level exceeds the set log level, a dummy log class
     * will be returned.
     *
     * @param level The specified log level
     *
     * @return Target log stream
     *
     * @endif
     */
    ostream_type& log(int level)
    {
      if (m_loglevel >= level)
	{
          *this << prefix(m_prefix, level);
	  return *this;
	}
      else
	{
	  return m_dummy;
	}
    }
    
    /*!
     * @if jp
     *
     * @brief ログロック取得
     * ロックモードが設定されている場合、ログのロックを取得する。
     *
     * @else
     *
     * @brief Acquire log lock
     * Acquire log lock when the lock mode is set.
     *
     * @endif
     */
    inline void lock()
    {
      if (m_lock) m_mutex.lock();
    }
    
    /*!
     * @if jp
     *
     * @brief ログロック解放
     * ロックモードが設定されている場合に、ログのロックを解放する。
     *
     * @else
     *
     * @brief Release the log lock
     * Release the log lock when the lock mode is set.
     *
     * @endif
     */
    inline void release()
    {
      if (m_lock) m_mutex.unlock();
    }
    

    
  protected:
    log_stream();
    log_stream(const log_stream& x);
    log_stream& operator=(const log_stream& x);

  private:
    int m_loglevel;
    bool m_lock;
    std::string m_prefix;
    Mutex m_mutex;
    std::ofstream m_dummy;

    /*!
     * @if jp
     * @brief ダミーストリーム
     * @else
     * @brief Dummy log
     * @endif
     */

  };


  typedef log_streambuf<char> LogStreamBuffer;
  typedef log_stream<char> LogStream;

};
#endif // LOGGER_H
