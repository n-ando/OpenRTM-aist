// -*- C++ -*-
/*!
 *
 * @file BufferBase.h
 * @brief Buffer abstract class
 * @date $Date: 2007-12-31 03:06:12 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2007
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: BufferBase.h,v 1.2.4.3 2007-12-31 03:06:12 n-ando Exp $
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2.4.2  2007/09/21 09:18:12  n-ando
 * Documentation was modified.
 *
 * Revision 1.2  2006/12/02 18:24:15  n-ando
 * BufferBase's interfaces were changed.
 *
 * Revision 1.1  2006/11/27 09:44:34  n-ando
 * The first commitment.
 *
 */

#ifndef BufferBase_h
#define BufferBase_h

/*!
 * @if jp
 * @namespace RTC
 *
 * @brief RTコンポーネント
 *
 * @else
 *
 * @namespace RTC
 *
 * @endif
 */
namespace RTC
{
  /*!
   * @if jp
   * @class BufferBase
   * @brief BufferBase 抽象クラス
   * 
   * 種々のバッファのための抽象インターフェースクラス。
   * 具象バッファクラスは、以下の純粋仮想関数の実装を提供しなければならない。
   * \<DataType\>としてバッファ内で保持するデータ型を指定する。
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
   * @param DataType バッファに格納するデータ型
   *
   * @since 0.4.0
   *
   * @else
   * @class BufferBase
   * @brief BufferBase abstract class
   *
   * This is the abstract interface class for various Buffer.
   *
   * @param DataType Data type to be stored to the buffer.
   *
   * @since 0.4.0
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
     * バッファ長を取得するための純粋仮想関数
     * 
     * @return バッファ長
     * 
     * @else
     *
     * @brief Get the buffer length
     *
     * @return buffer length
     * 
     * @endif
     */
    virtual long int length() const = 0;
    
    /*!
     * @if jp
     *
     * @brief バッファにデータを書き込む
     * 
     * バッファにデータを書き込むための純粋仮想関数
     * 
     * @param value 書き込み対象データ
     *
     * @return データ書き込み結果(true:書き込み成功，false:書き込み失敗)
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
     * @brief バッファからデータを読み出す
     * 
     * バッファからデータを読み出すための純粋仮想関数
     * 
     * @param value 読み出しデータ
     *
     * @return データ読み出し結果(true:読み出し成功，false:読み出し失敗)
     * 
     * @else
     *
     * @brief Read data from the buffer
     *
     * @endif
     */
    virtual bool read(DataType& value) = 0;
    
    /*!
     * @if jp
     *
     * @brief バッファfullチェック
     * 
     * バッファfullチェック用純粋仮想関数
     *
     * @return fullチェック結果(true:バッファfull，false:バッファ空きあり)
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
     * @brief バッファemptyチェック
     * 
     * バッファemptyチェック用純粋仮想関数
     *
     * @return emptyチェック結果(true:バッファempty，false:バッファデータあり)
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
     * @brief バッファにデータを格納する
     * 
     * バッファへのデータ格納用純粋仮想関数
     * 
     * @param data 対象データ
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
     * バッファに格納されたデータ取得用純粋仮想関数
     *
     * @return 取得データ
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
     * @brief 次に書き込むバッファへの参照を取得する
     * 
     * 書き込みバッファへの参照取得用純粋仮想関数
     *
     * @return 次の書き込み対象バッファへの参照
     * 
     * @else
     *
     * @brief Get the buffer's reference to be written the next
     *
     * @endif
     */
    virtual DataType& getRef() = 0;
  };
  
  /*!
   * @if jp
   * @class NullBuffer
   * @brief ダミーバッファ実装クラス
   * 
   * バッファ長が１固定のダミーバッファ実装クラス。
   * \<DataType\>としてバッファ内で保持するデータ型を指定する。
   *
   * @param DataType バッファに格納するデータ型
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  template <class DataType>
  class NullBuffer
    : public BufferBase<DataType>
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     * 
     * コンストラクタ
     * バッファ長を１(固定)で初期化する。
     *
     * @param size バッファ長(ただし無効)
     * 
     * @else
     *
     * @endif
     */
    NullBuffer(long int size = 1)
      : m_length(1)
    {
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
     * @endif
     */
    virtual ~NullBuffer()
    {
    }
    
    /*!
     * @if jp
     *
     * @brief バッファ長(１固定)を取得する
     * 
     * バッファ長を取得する。(常に１を返す。)
     * 
     * @return バッファ長(１固定)
     * 
     * @else
     *
     * @brief Get the buffer length
     *
     * @return buffer length(always 1)
     * 
     * @endif
     */
    virtual long int length() const
    {
      return 1;
    }
    
    /*!
     * @if jp
     *
     * @brief バッファにデータを書き込む
     * 
     * 引数で与えられたデータをバッファに書き込む。
     * 
     * @param value 書き込み対象データ
     *
     * @return データ書き込み結果(true:書き込み成功，false:書き込み失敗)
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * @endif
     */
    virtual bool write(const DataType& value)
    {
      m_data = value;
      return true;
    }
    
    /*!
     * @if jp
     *
     * @brief バッファからデータを読み出す
     * 
     * バッファに格納されたデータを読み出す。
     * 
     * @param value 読み出したデータ
     *
     * @return データ読み出し結果(true:読み出し成功，false:読み出し失敗)
     * 
     * @else
     *
     * @brief Read data from the buffer
     *
     * @endif
     */
    virtual bool read(DataType& value)
    {
      value = m_data;
      return true;
    }
    
    /*!
     * @if jp
     *
     * @brief バッファfullチェック
     * 
     * バッファfullをチェックする。(常にfalseを返す。)
     *
     * @return fullチェック結果(常にfalse)
     * 
     * @else
     *
     * @brief Always false.
     *
     * @endif
     */
    virtual bool isFull() const
    {
      return false;
    }
    
    /*!
     * @if jp
     *
     * @brief バッファemptyチェック
     * 
     * バッファemptyをチェックする。(常にfalseを返す。)
     *
     * @return emptyチェック結果(常にfalse)
     * 
     * @else
     *
     * @brief Always false.
     *
     * @endif
     */
    virtual bool isEmpty() const
    {
      return false;
    }
    
  protected:
    /*!
     * @if jp
     *
     * @brief バッファにデータを格納
     * 
     * 引数で与えられたデータをバッファに格納する。
     * 
     * @param data 対象データ
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * @endif
     */
    virtual void put(const DataType& data)
    {
      m_data = data;
    }
    
    /*!
     * @if jp
     *
     * @brief バッファからデータを取得する
     * 
     * バッファに格納されたデータを取得する。
     *
     * @return 取得データ
     * 
     * @else
     *
     * @brief Get data from the buffer
     *
     * @endif
     */
    virtual const DataType& get()
    {
      return m_data;
    }
    
    /*!
     * @if jp
     *
     * @brief 次に書き込むバッファへの参照を取得する
     * 
     * 書き込みバッファへの参照を取得する。
     * 本バッファ実装ではバッファ長は固定で１であるため，
     * 常に同じ位置への参照を返す。
     *
     * @return 次の書き込み対象バッファへの参照(固定)
     * 
     * @else
     *
     * @brief Get the buffer's reference to be written the next
     *
     * @endif
     */
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
