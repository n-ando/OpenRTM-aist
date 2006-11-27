// -*- C++ -*-
/*!
 * @file BufferBase.h
 * @brief Buffer abstract class
 * @date $Date: 2006-11-27 09:44:34 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: BufferBase.h,v 1.1 2006-11-27 09:44:34 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#ifndef BufferBase_h
#define BufferBase_h

namespace RTC
{
  /*!
   * @if jp
   * @class BufferBase
   * @brief BufferBase 抽象クラス
   * 
   * 種々のバッファのための抽象インターフェースクラス。
   *
   * @param DataType バッファに格納するデータ型
   *
   * @else
   * @class BufferBase
   * @brief BufferBase abstract class
   *
   * This is the abstract interface class for various Buffer.
   *
   * @param DataType Data type to be stored to the buffer.
   *
   * @endif
   */
  template <class DataType>
  class BufferBase
  {
  public:
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
    virtual ~BufferBase(){};

    /*!
     * @if jp
     *
     * @brief バッファにデータを書き込む
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * @endif
     */
    virtual void write(const DataType& value) = 0;

    /*!
     * @if jp
     *
     * @brief バッファにデータを書き込む
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * @endif
     */
    virtual DataType read() = 0;

    /*!
     * @if jp
     *
     * @brief バッファにデータを書き込む
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * @endif
     */
    virtual void put(const DataType& data) = 0;

    /*!
     * @if jp
     *
     * @brief バッファからデータを取得する
     * 
     * @else
     *
     * @brief Get data from the buffer
     *
     * @endif
     */
    virtual const DataType& get() = 0;

    /*!
     * @if jp
     *
     * @brief 次に書き込むバッファの参照を取得する
     * 
     * @else
     *
     * @brief Get the buffer's reference to be written the next
     *
     * @endif
     */
    virtual DataType& getRef() = 0;

    /*!
     * @if jp
     *
     * @brief バッファの長さを取得する
     * 
     * @else
     *
     * @brief Get the buffer length
     *
     * @endif
     */
    virtual int length() const = 0;

    /*!
     * @if jp
     *
     * @brief 取得するべき新しいデータがある
     * 
     * @else
     *
     * @brief New data is exist to be get
     *
     * @endif
     */
    virtual bool isNew() const = 0;

    /*!
     * @if jp
     *
     * @brief バッファがfullである
     * 
     * @else
     *
     * @brief The buffer is full
     *
     * @endif
     */
    virtual bool isFull() const = 0;

    /*!
     * @if jp
     *
     * @brief バッファがemptyである
     * 
     * @else
     *
     * @brief The buffer is empty
     *
     * @endif
     */
    virtual bool isEmpty() const = 0;
  };


  template <class DataType>
  class NullBuffer
    : public BufferBase<DataType>
  {
  public:
    NullBuffer(int size)
    {
    }

    virtual ~NullBuffer()
    {
    }

    inline void put(const DataType& data)
    {
      m_data = data;
    }

    inline const DataType& get()
    {
      return m_data;
    }

    inline DataType& getRef()
    {
      return m_data;
    }

    inline int length()
    {
      return 1;
    }

    inline bool isNew()
    {
      return true;
    }

    inline bool isFull()
    {
      return false;
    }

    inline bool isEmpty()
    {
      return false;
    }

  private:
    DataType m_data;
  };


}; // namespace RTC
#endif // BufferBase_h
