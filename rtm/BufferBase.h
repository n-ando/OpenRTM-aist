// -*- C++ -*-
/*!
 * @file BufferBase.h
 * @brief Buffer abstract class
 * @date $Date: 2007-08-20 05:11:15 $
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
 * $Id: BufferBase.h,v 1.2.4.1 2007-08-20 05:11:15 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2006/12/02 18:24:15  n-ando
 * BufferBase's interfaces were changed.
 *
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
   * 種々のバッファを実装するための抽象インターフェースクラス。
   * 具象バッファクラスは、以下の純粋仮想関数を実装しなければならない。
   *
   * publicインターフェースとして以下のものを提供する。
   * - init(): バッファを初期化する
   * - clear(): バッファをクリアする
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
   * 具象バッファクラスはバッファの状態を返す関数 isFull(), isEmpty() を自由に
   * 実装しても良いが、(常にfalseを返す実装等) 両者が同時にtrueを返してはなら
   * ない。また、これらの関数が true を返すことがある実装ならば、同時にwrite()
   * read()の実装もバッファ状態を反映した実装である必要がある。
   *
   * すなわち、
   * - isFull() = true ならば isEmpty() = flase
   * - isFull() = flase ならば isEmpty() = true
   * - isFull() = true ならば write() = false
   * - isEmpty() = true ならば read() = false
   * でなければならない。
   * 
   * @param DataType バッファに格納するデータ型
   *
   * @else
   *
   * @class BufferBase
   * @brief BufferBase abstract class
   *
   * This is the abstract interface class for various Buffer classes.
   * The conclete Buffer classes responsible to implement the following
   * virtual functions.
   *
   * The following functions should be provided as public interfaces.
   * - init(): Initializes the buffer.
   * - clear(): clears the buffer.
   * - length(): Returns the buffer length.
   * - write(): Writes a data to the buffer.
   * - read(): Reads a data from the buffer.
   * - isFull(): Returns if the buffer is full.
   * - isEmpty(): Returns if the buffer is empty.
   *
   * The following functions should be provided as protected interfaces.
   * - put(): puts data to the buffer
   * - get(): gets data from the buffer
   *
   * "isFull" and "isEmpty" functions of the concrete classes can be
   * implemented as non-effective functions that return always "false".
   * However, these functions never return "true" value at the same time.
   * And, if these functions return "true" value, write() and read() functions
   * should return appropriate values according to the buffer status.
   *
   * Therefore, the following constraints should be guaranteed.
   * - isFull() = true when isEmpty() = flase
   * - isFull() = flase when isEmpty() = true
   * - isFull() = true when write() = false
   * - isEmpty() = true when read() = false 
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
     * @brief バッファを初期化する
     * 
     * バッファ内の全ての要素が与えられた値で初期化される。初期化により、
     * 直後のバッファは読み出し可能となり、読み出される値は、初期化に用いた
     * 値に等しい。
     *
     * @pre    なし
     * @post   isEmpty() == false かつ read() == true であり、read(data) の
     *         戻り値は初期化に使用した値である
     * @param  data バッファの初期化に使用するデータ
     *
     * @else
     *
     * @brief Get the buffer length
     *
     * All of the buffer elements are initilized by the given data value.
     * As a consequence of initialization, the buffer can be readable and the
     * value to be read is equal to initialized value.
     *
     * @pre    None
     * @post   isEmpty() == false and read() == true, and return value of
     *         read(data) should return initialized data.
     * @param  data Data to be used to initialize the buffer.
     *
     * @endif
     */
    virutal void init(const DataType& data) = 0;

    /*!
     * @if jp
     *
     * @brief バッファをクリアする
     * 
     * バッファ内の全ての要素をクリアする。バッファはクリアされることにより、
     * 書込み可能となる。
     *
     * @pre    なし
     * @post   isFull() == false かつ write() == true である。
     * 
     * @else
     *
     * @brief Clear the buffer
     *
     * All of the buffer elements are cleared. As a consequence of clear
     * operation, the buffer can be writable.
     *
     * @pre    None
     * @post   isFull() == false and write() == true.
     *
     * @endif
     */
    virutal void clear() = 0;

    /*!
     * @if jp
     *
     * @brief バッファの長さを取得する
     *
     * 保持しているバッファのサイズを返す。
     *
     * @pre    なし
     * @post   なし
     * 
     * @else
     *
     * @brief Get the buffer length
     *
     * This operation returns the buffer length.
     *
     * @pre    なし
     * @post   なし
     *
     * @endif
     */
    virtual long int length() const = 0;

    /*!
     * @if jp
     *
     * @brief バッファにデータを書き込む
     *
     * バッファにデータを書き込む。バッファに何らかの理由で書き込めない場合
     * false を返す。また isFull() == true の場合にも false を返す。
     * 
     * @pre    なし
     * @pre    isEmpty() == false
     * @value  value バッファに書き込む値
     * @return バッファに書き込めない場合は偽を返す
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * This operation writes data to the buffer. This operation returns false,
     * if it cannot write to the buffer for any reason. This operation also
     * returns false if isFull() returns true.
     *
     * @pre    None
     * @post   isEmpty == false
     * @param  value Data to be written to the buffer
     * @return false would be returned when data writing to the buffer fails.
     *
     * @endif
     */
    virtual bool write(const DataType& value) = 0;

    /*!
     * @if jp
     *
     * @brief バッファからデータを読み出す
     * 
     * バッファからデータを読み出す。バッファから何らかの理由で読み出せない場合
     * false を返す。また isEmpty() == true の場合にも false を返す。
     *
     * @pre    なし
     * @post   isFull() == false
     * @param  value
     * @return バッファから読み出せない場合は偽を返す
     * 
     * @else
     *
     * @brief Read data from the buffer
     *
     * This operation reads data from the buffer. This operation returns false,
     * if it cannot read from the buffer for any reason. This operation also
     * returns false if isEmpty() returns true.
     *
     * @pre    None
     * @post   isFull() == false
     * @param  value Variable to be read from the buffer
     * @return false would be returned when data reading from the buffer fails.
     *
     * @endif
     */
    virtual bool read(DataType& value) = 0;

    /*!
     * @if jp
     *
     * @brief バッファが full であるかどうか
     *
     * バッファが full かどうか返す。バッファが full であれば true を、
     * そうでなければ false を返す。
     * バッファが full であるかどうかの定義は具象クラスの実装に依存する。
     * いかなる場合も full にならないバッファを実装してもよい。この場合、
     * この関数は常に false を返す。
     *
     * @pre    なし
     * @post   isFull() == true ならば isEmpty() == false
     * @return バッファが full であれば true を、そうでなければ false を返す。
     * 
     * @else
     *
     * @brief True if the buffer is full, else false.
     *
     * This operation returns boolean whether the buffer is full or not.
     * If the buffer is full it returns true, if it is not full it returns
     * false.
     * The definition of the "buffer full" depends on the concrete class's
     * implementation. The buffer that is never filled can be implemented.
     * In this case, this operation always returns false.
     *
     * @pre    None
     * @post   isEmpty() == false when isFull() == true
     * @return If the buffer is full, true is returned. Otherwise false is
     *         returned.
     *
     * @endif
     */
    virtual bool isFull() const = 0;

    /*!
     * @if jp
     *
     * @brief バッファが empty であるかどうか
     *
     * バッファが empty かどうか返す。バッファが empty であれば true を、
     * そうでなければ false を返す。
     * バッファが empty であるかどうかの定義は具象クラスの実装に依存する。
     * いかなる場合も empty にならないバッファを実装してもよい。この場合、
     * この関数は常に false を返す。
     *
     * @pre    なし
     * @post   isEmpty() == true ならば isFull() == false
     * @return バッファが empty であれば true を、そうでなければ false を返す。
     * 
     * @else
     *
     * @brief True if the buffer is empty, else false.
     *
     * This operation returns boolean whether the buffer is empty or not.
     * If the buffer is empty it returns true, if it is not empty it returns
     * false.
     * The definition of the "buffer empty" depends on the concrete class's
     * implementation. The buffer that is never emptied can be implemented.
     * In this case, this operation always returns false.
     *
     * @pre    None
     * @post   isFull() == false when isEmpty() == true
     * @return If the buffer is empty, true is returned. Otherwise false is
     *         returned.
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
     * バッファにデータを書き込むためのプリミティブな関数。
     * この関数は、BufferBaseクラスを継承した具象クラス内で、バッファへの書込み
     * を内部的に共通化するためのインターフェースとして存在する。
     *
     * この関数はバッファが書込み可能な場合にのみ呼び出し可能である。
     * ただし、バッファが書込み可能であるかどうかの定義、およびwrite()関数
     * 内で書込み可能であるかどうかチェックは、具象クラス実装者の責任である。
     *
     * @pre   isFull() == false
     * @post  isEmpty() == false
     * @param data バッファに書き込まれるデータ
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * This operation is primitive function to write data to the buffer.
     * This operation is used to unify writing method to the buffer internally
     * in the concrete classes which inherit this class.
     *
     * This operation can be called only when the buffer is writable.
     * The definition of the "writable" depends on each implementation.
     * The developer of the concrete class is responsible for checking whether
     * the buffer is writable in the "write()" function.
     *
     * @pre   isFull() == false
     * @post  isEmpty() == false
     * @param data Data to be written to the buffer
     *
     * @endif
     */
    virtual void put(const DataType& data) = 0;

    /*!
     * @if jp
     *
     * @brief バッファからデータを読みだす
     * 
     * バッファからデータを読み出すためのプリミティブな関数。
     * この関数は、BufferBaseクラスを継承した具象クラス内で、バッファからの
     * 読み込みを内部的に共通化するためのインターフェースとして存在する。
     *
     * この関数はバッファが読出し可能な場合にのみ呼び出し可能である。
     * ただし、バッファが読出し可能であるかどうかの定義、およびread()関数
     * 内で読出し可能であるかどうかチェックは、具象クラス実装者の責任である。
     *
     * @pre   isEmpty() == false
     * @post  isFull() == false
     * @param data バッファから読み出されるデータ
     * 
     * @else
     *
     * @brief Read data from the buffer
     *
     * This operation is primitive function to read data from the buffer.
     * This operation is used to unify reading method to the buffer internally
     * in the concrete classes which inherit this class.
     *
     * This operation can be called only when the buffer is readable.
     * The definition of the "readable" depends on each implementation.
     * The developer of the concrete class is responsible for checking whether
     * the buffer is readable in the "read()" function.
     *
     * @pre   isEmpty() == false
     * @post  isFull() == false
     * @param data Data to be read from the buffer
     *
     * @endif
     */
    virtual const DataType& get() = 0;

    /*!
     * @if jp
     *
     * @brief 次に書き込むバッファの参照を取得する
     *
     * 具象クラスで確保したバッファ領域のうち、put()で書き込まれる領域の
     * 参照を返す。
     *
     * @pre    なし
     * @post   なし
     * @return put()で書き込まれる領域の参照
     * 
     * @else
     *
     * @brief Get the buffer's reference to be written the next
     *
     * @pre    None
     * @post   None
     * @return The reference to the element to be written by put()
     *
     * @endif
     */
    virtual DataType& getRef() = 0;

  };



  //============================================================
  /*!
   * @if jp
   * @class NullBuffer
   * @brief NullBuffer クラス
   *
   * NullBuffer クラスは一つのバッファ領域を持つバッファ具象クラスである。
   * このクラスはfull状態もempty状態も検出しないバッファである。
   * 
   * 従って常に
   * - write() == true
   * - read()  == true
   * - isFull() == false
   * - isEmpty() == false
   * である。
   *
   * 未書込みの状態で read() が返す値は不定である。
   * このバッファクラスはBufferBaseの具象クラスの単純な例として定義されており、
   * 実用的な用途における使用は推奨されない。
   * 
   * @param DataType バッファに格納するデータ型
   *
   * @else
   *
   * @class NullBuffer
   * @brief NullBuffer class
   *
   * NullBuffer is concrete class that has only one element in the buffer.
   * This buffer class does not detect full status and empty status.
   *
   * Therefore this class methods always return the following
   * - write() == true
   * - read()  == true
   * - isFull() == false
   * - isEmpty() == false
   *
   * read() function returns undefined value before writing to the buffer.
   * Since this buffer class is defined as an example of a concrete class of
   * BufferBase, using it in practical purpose is not recommended.
   *
   * @param DataType Data type to be stored to the buffer.
   *
   * @endif
   */
  template <class DataType>
  class NullBuffer
    : public BufferBase<DataType>
  {
  public:
    NullBuffer(long int size = 1)
      : m_length(1), m_empty(true)
    {
    }

    virtual ~NullBuffer()
    {
    }

    /*!
     * @if jp
     *
     * @brief バッファを初期化する
     * 
     * バッファ内の全ての要素が与えられた値で初期化される。
     *
     * @pre    なし
     * @post   isEmpty() == false かつ read() == true であり、read(data) の
     *         戻り値は初期化に使用した値である
     * @param  data バッファの初期化に使用するデータ
     *
     * @else
     *
     * @brief Get the buffer length
     *
     * All of the buffer elements are initilized by the given data value.
     *
     * @pre    None
     * @post   isEmpty() == false and read() == true, and return value of
     *         read(data) should return initialized data.
     * @param  data Data to be used to initialize the buffer.
     *
     * @endif
     */
    virtual void init(const DataType& data)
    {
      put(data);
    }

    /*!
     * @if jp
     *
     * @brief バッファをクリアする
     * 
     * バッファ内の全ての要素をクリアする。
     *
     * @pre    なし
     * @post   なし
     * 
     * @else
     *
     * @brief Clear the buffer
     *
     * All of the buffer elements are cleared.
     *
     * @pre    None
     * @post   None
     *
     * @endif
     */
    virtual void clear()
    {
      m_empty = true;
    }

    /*!
     * @if jp
     *
     * @brief バッファの長さを取得する
     *
     * 保持しているバッファのサイズを返す。
     *
     * @pre    なし
     * @post   なし
     * 
     * @else
     *
     * @brief Get the buffer length
     *
     * This operation returns the buffer length.
     *
     * @pre    なし
     * @post   なし
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
     * バッファにデータを書き込む。
     * この関数は常に true を返す。
     * 
     * @pre    なし
     * @pre    isEmpty() == false
     * @value  value バッファに書き込む値
     * @return 常に true を返す
     * 
     * @else
     *
     * @brief Write data into the buffer
     *
     * This operation writes data to the buffer.
     * This operation always returns true.
     *
     * @pre    None
     * @post   isEmpty == false
     * @param  value Data to be written to the buffer
     * @return true is returned always
     *
     * @endif
     */
    virtual bool write(const DataType& value)
    {
      put(value);
      return true;
    }

    /*!
     * @if jp
     *
     * @brief バッファからデータを読み出す
     * 
     * バッファからデータを読み出す。
     * この関数は常に true を返す。
     *
     * @pre    なし
     * @post   isFull() == false
     * @param  value
     * @return 常に true を返す
     * 
     * @else
     *
     * @brief Read data from the buffer
     *
     * This operation reads data from the buffer.
     * This operation always returns true.
     *
     * @pre    None
     * @post   isFull() == false
     * @param  value Variable to be read from the buffer
     * @return true is returned always
     *
     * @endif
     */
    virtual bool read(DataType& value)
    {
      value = get();
      return true;
    }

    /*!
     * @if jp
     *
     * @brief バッファが full であるかどうか
     *
     * バッファが full かどうか返す。
     * この関数は常にfalse を返す。
     *
     * @pre    なし
     * @post   なし
     * @return 常に false を返す。
     * 
     * @else
     *
     * @brief True if the buffer is full, else false.
     *
     * This operation returns boolean whether the buffer is full or not.
     * This operation always returns false.
     *
     * @pre    None
     * @post   isEmpty() == false when isFull() == true
     * @return false is returned always
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
     * @brief バッファが empty であるかどうか
     *
     * バッファが empty かどうか返す。
     * この関数は常に false を返す。
     *
     * @pre    なし
     * @post   なし
     * @return 常に false を返す。
     * 
     * @else
     *
     * @brief True if the buffer is empty, else false.
     *
     * This operation returns boolean whether the buffer is empty or not.
     * If the buffer is empty it returns true, if it is not empty it returns
     * false.
     * The definition of the "buffer empty" depends on the concrete class's
     * implementation. The buffer that is never emptied can be implemented.
     * In this case, this operation always returns false.
     *
     * @pre    None
     * @post   isFull() == false when isEmpty() == true
     * @return false is returned always
     *
     * @endif
     */
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
