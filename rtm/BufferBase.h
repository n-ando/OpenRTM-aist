// -*- C++ -*-
/*!
 * @file BufferBase.h
 * @brief Buffer abstract class
 * @date $Date: 2006-12-02 18:24:15 $
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
 * $Id: BufferBase.h,v 1.2 2006-12-02 18:24:15 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/11/27 09:44:34  n-ando
 * The first commitment.
 *
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
   * 具象バッファクラスは、以下の純粋仮想関数の実装を提供しなければならない。
   *
   * publicインターフェースとして以下のものを提供する。
   * - write(): バッファに書き込む
   * - read(): バッファから読み出す
   * - length(): バッファ長を返す
   * - isFull(): バッファが満杯である
   * - isEmpty(): バッファが空である
   *
   * protectedインターフェースとして以下のものを提供する。
   * - put(): バッファにデータを書き込む
   * - get(): バッファからデータを読み出す
   *
   *
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
     * @brief バッファの長さを取得する
     * 
     * @else
     *
     * @brief Get the buffer length
     *
     * @endif
     */
    virtual long int length() const = 0;

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
    virtual bool write(const DataType& value) = 0;

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
    virtual bool read(DataType& value) = 0;

    /*!
     * @if jp
     *
     * @brief バッファがfullである
     * 
     * @else
     *
     * @brief True if the buffer is full, else false.
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
     * @brief True if the buffer is empty, else false.
     *
     * @endif
     */
    virtual bool isEmpty() const = 0;

  protected:
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

  };




  template <class DataType>
  class NullBuffer
    : public BufferBase<DataType>
  {
  public:
    NullBuffer(long int size = 1)
      : m_length(1)
    {
    }

    virtual ~NullBuffer()
    {
    }

    virtual long int length() const
    {
      return 1;
    }

    virtual bool write(const DataType& value)
    {
      m_data = value;
      return true;
    }

    virtual bool read(DataType& value)
    {
      value = m_data;
      return true;
    }

    virtual bool isFull() const
    {
      return false;
    }

    virtual bool isEmpty() const
    {
      return false;
    }
    
  protected:
    virtual void put(const DataType& data)
    {
      m_data = data;
    }

    virtual const DataType& get()
    {
      return m_data;
    }

    virtual DataType& getRef()
    {
      return m_data;
    }

  private:
    DataType m_data;
    long int m_length;
  };


}; // namespace RTC
#endif // BufferBase_h
