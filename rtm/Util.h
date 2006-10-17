// -*- C++ -*-
/*!
 * @file SdoConfiguration.cpp
 * @brief SDO's Configuration implementation class
 * @date $Date: 2006-10-17 10:12:18 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Util.h,v 1.2 2006-10-17 10:12:18 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/09/11 18:14:53  n-ando
 * The first commit.
 *
 *
 */

#ifndef Util_h
#define Util_h


#include <ace/Guard_T.h>
#include <ace/Thread_Mutex.h>
#include <ace/Recursive_Thread_Mutex.h>
#include <rtm/RTC.h>

typedef ACE_Guard<ACE_Thread_Mutex> Guard;
typedef ACE_Read_Guard<ACE_Thread_Mutex> Read_Guard;
typedef ACE_Write_Guard<ACE_Thread_Mutex> Write_Guard;

typedef ACE_Guard<ACE_Recursive_Thread_Mutex> Guard_r;
typedef ACE_Read_Guard<ACE_Recursive_Thread_Mutex> Read_Guard_r;
typedef ACE_Write_Guard<ACE_Recursive_Thread_Mutex> Write_Guard_r;


template <class T>
struct LockedStruct
{
  ACE_Thread_Mutex lock;
  T                data;
};

/*!
 * @if jp
 * @class SequenceEx
 * @brief CORBA::sequence 拡張クラス
 *
 * このクラスは CORBA の sequence 型を拡張し std::vector のインターフェースを
 * 提供する (例えば size(), max_size(), empty(), resize(), insert(),
 * erase(), erase_if(), push_back(), pop_back(), find()).
 * CORBA の sequence 型を継承しているため、CORBA の sequence 型の
 * オペレーション(like operator=(), maximum(), length(), operator[])も
 * 使用可能である。
 * .
 * @else
 *
 * @brief CORBA::sequence extention class
 *
 * This class extends CORBA sequence type, and provides std::vector like
 * interfaces (like size(), max_size(), empty(), resize(), insert(),
 * erase(), erase_if(), push_back(), pop_back(), find()).
 * Since this class inherits CORBA sequence class, user can also use CORBA
 * sequence interfaces (like operator=(), maximum(), length(), operator[]).
 *
 * @endif
 */ 
template <class CorbaSequence, class SequenceItem, class Mutex>
class SequenceEx
  : public CorbaSequence
{
public:
  /*!
   * @if jp
   *
   * @brief デフォルトコンストラクタ
   *
   * デフォルトコンストラクタ。デフォルトコンストラクタでは、
   * 基底クラスのCORBA::sequence の長さを 0 にセットする。
   * 
   * @param CorbaSequence CORBA IDL で定義される sequence 形
   * @param SeuenceItem CorbaSequence の要素型
   * @param Mutex Mutexの型
   *
   * @else
   *
   * @brief Default constructor
   *
   * Default constructor. This default constructor sets the sequence length
   * of CorbaSequence base class.
   *
   * @param CorbaSequence Sequence type defined in CORBA IDL
   * @param SeuenceItem The item type of CorbaSequence
   * @param Mutex The type of mutex
   *
   * @endif
   */
  SequenceEx(): CorbaSequence(0) {};


  /*!
   * @if jp
   *
   * @brief CorbaSequence からのコピーコンストラクタ
   *
   * CorbaSequence型からのコピーコンストラクタ。
   * 与えられた CorbaSequence の内容をコピーする。
   *
   * @param _sq CorbaSequence 形のコピー元
   *
   * @else
   *
   * @brief Copy constructor from CorbaSequence
   *
   * This constructor copies sequence contents from given CorbaSequence
   * to this object.
   *
   * @param _sq Copy source of CorbaSequence type
   *
   * @endif
   */
  SequenceEx(const CorbaSequence& _sq)
    : CorbaSequence(0)
  {
    this->length(_sq.length());
    CORBA::ULong len(this->length());
    for (CORBA::ULong i = 0; i < len; ++i)
      (*this)[i] = _sq[i];
  };


  /*!
   * @if jp
   *
   * @brief コピーコンストラクタ
   *
   * @param _sq コピー元
   *
   * @else
   *
   * @brief Copy constructor
   *
   * @param _sq Copy source.
   *
   * @endif
   */
  SequenceEx(const SequenceEx& _sq)
    : CorbaSequence(0)
  {
    this->length(_sq.length());
    CORBA::ULong len(this->length());
    for (CORBA::ULong i = 0; i < len; ++i)
      (*this)[i] = _sq[i];
  };


  /*!
   * @if jp
   *
   * @brief 代入演算子
   *
   * @param _sq コピー元
   *
   * @else
   *
   * @brief Assignment operator
   *
   * @param _sq Copy source.
   *
   * @endif
   */
  SequenceEx& operator=(const SequenceEx& _sq)
  {
    this->length(_sq.length());
    CORBA::ULong len(this->length());
    for (CORBA::ULong i = 0; i < len; ++i)
      (*this)[i] = _sq[i];
    return *this;
  };


  /*!
   * @if jp
   *
   * @brief CorbaSequence からの代入演算子
   *
   * @param _sq コピー元
   *
   * @else
   *
   * @brief Assignment operator from CorbaSequence
   *
   * @param _sq Copy source.
   *
   * @endif
   */
  SequenceEx& operator=(const CorbaSequence& _sq)
  {
    this->length(_sq.length());
    CORBA::ULong len(this->length());
    for (CORBA::ULong i = 0; i < len; ++i)
      (*this)[i] = _sq[i];
    return *this;
  };


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
  virtual ~SequenceEx()
  {
    this->length(0);
  };


  /*!
   * @if jp
   *
   * @brief サイズを取得する
   *
   * このオペレーションはシーケンスのサイズを返す。
   * CorbaSequence::length() と同じ。
   *
   * @return シーケンスのサイズ
   *
   * @else
   *
   * @brief Get size of this sequence
   *
   * This operation returns the size of the sequence.
   * This is same as CorbaSequence::length().
   *
   * @return The size of the sequence.
   *
   * @endif
   */
  inline CORBA::ULong size() { return this->length(); }


  /*!
   * @if jp
   *
   * @brief 格納可能な最大のサイズを取得する
   *
   * このオペレーションはシーケンスの現在の格納可能な最大のサイズを返す。
   * CorbaSequence::maximum() と同じ。
   *
   * @return シーケンスに格納可能な最大のサイズ
   *
   * @else
   *
   * @brief Get current maximum size of this sequence
   *
   * This operation returns the current maximum size of the sequence.
   * This is same as CorbaSequence::maximum().
   *
   * @return The maximum size of the sequence.
   *
   * @endif
   */
  inline CORBA::ULong max_size() { return this->maximum(); }


  /*!
   * @if jp
   *
   * @brief シーケンスが空かどうか調べる
   *
   * このオペレーションはシーケンスが空かどうかを bool 値で返す。
   * サイズが 0 なら true、そうでなければ false を返す。
   *
   * @return シーケンスが空かどうかの bool 値
   *
   * @else
   *
   * @brief Test whether the sequence is empty
   *
   * This operation returns bool value whether the sequence is empty.
   * If the size of the sequence is 0, this operation returns true,
   * and in other case this operation returns false.
   *
   * @return The bool value whether the sequence is empty.
   *
   * @endif
   */
  inline bool empty() { return (this->length() == 0) ? true : false; }


  /*!
   * @if jp
   *
   * @brief シーケンスをリサイズする
   *
   * このオペレーションはシーケンスの長さを変更する。
   * 現在の長さより大きなサイズが与えられた場合、引数 x で、
   * 新たにアロケートされた部分が埋められる。
   * 現在の長さより小さいサイズが与えられた場合、CorabSequence と同様に
   * 余分なシーケンスの要素は削除される。
   *
   * @param new_size 新しいシーケンスのサイズ
   * @param item　長くなった分のシーケンスを埋める要素
   *
   * @else
   *
   * @brief Resize the length of the sequence
   *
   * This operation resizes the length of the sequence.
   * If longer length than current sequence length is given,
   * newly allocated rooms will be assigned by element given by the argument.
   * If shorter length than current sequence length is given,
   * the excessive element of a sequence is deleted like behavior of
   * CorabSequence
   *
   * @param new_size The new size of the sequence
   * @param item　   Sequence element to be assigned to new rooms.
   *
   * @endif
   */
  void resize(CORBA::ULong new_size, SequenceItem& item)
  {
    ACE_Write_Guard<Mutex> gaurd(lock);
    CORBA::ULong len(this->length);
    if (new_size > len) // Widen sequence
      {
	this->length(new_size);
	for (CORBA::ULong i = len; i < new_size; ++i)
	  (*this)[i] = x;
      }
    else if (new_size < len) // shorten sequence
      {
	this->length(new_size);
      }
  }


  /*!
   * @if jp
   *
   * @brief シーケンスに要素を挿入する
   *
   * このオペレーションはシーケンスの途中に要素を挿入する。
   *
   * @param position 新しい要素を挿入する場所
   * @param item　挿入するシーケンスの要素
   *
   * @else
   *
   * @brief Insert a new item to the sequence
   *
   * This operation inserts a new item to the sequence.
   *
   * @param position The position of new inserted item.
   * @param item　   Sequence element to be inserted.
   *
   * @endif
   */
  void insert(CORBA::ULong position, const SequenceItem& item)
  {
    ACE_Write_Guard<Mutex> gaurd(lock);
    CORBA::ULong len(this->length());
    // allowed position: [0, len]
    if (position > len) throw; // InvalidParameter("Invalid index");
    
    // widen sequence
    this->length(len + 1);
    // shift items
    for (CORBA::ULong i = (len - 1); i > position; --i)
      {
	(*this)[i] = (*this)[i-1];
      }
    (*this)[position] = x;
  }


  /*!
   * @if jp
   *
   * @brief シーケンスの要素を削除する
   *
   * このオペレーションはシーケンスの要素を削除する
   *
   * @param position 削除するシーケンス要素の場所
   *
   * @else
   *
   * @brief Erase an item of the sequence
   *
   * This operation erases an item from the sequence.
   *
   * @param position The position of erased item.
   *
   * @endif
   */
  SequenceItem erase(CORBA::ULong position)
  {
    ACE_Write_Guard<Mutex> gaurd(lock);
    CORBA::ULong len(this->length());
    // allowed position: [0, len)
    if (position > (len - 1)) throw; // InvalidParameter("Invalid index");
    
    // keep erased item
    SequenceItem erased((*this)[position]);
    // shift remaining items
    for (CORBA::ULong i = position; i < (len - 1); ++i)
      {
	(*this)[i] = (*this)[i+1];
      }
    // shorten sequence
    this->length(len - 1);
    return erased;
  }

  /*!
   * @if jp
   *
   * @brief シーケンスの要素を述語のしたがって削除する
   *
   * このオペレーションは述語として与えられた関数オブジェクトの
   * 条件が真のとき、そのシーケンスの要素を削除する。
   *
   * @param f 削除するシーケンスを決定する術語
   *
   * @else
   *
   * @brief Erase an item according to the given predicate
   *
   * This operation erases an item according to the given predicate.
   *
   * @param f The predicate functor to decide deletion.
   *
   * @endif
   */
  template <class Predicate>
  SequenceItem erase_if(Predicate f)
  {
    ACE_Write_Guard<Mutex> gaurd(lock);
    CORBA::ULong len(this->length());
    for (CORBA::ULong i = 0; i < len; ++i)
      if (f((*this)[i]))
	return erase(i);
    throw;
  }

  
  /*!
   * @if jp
   *
   * @brief 要素を最後尾に追加する
   *
   * このオペレーションは与えられた要素をシーケンスの最後に追加する。
   *
   * @param item 追加するするオブジェクト
   *
   * @else
   *
   * @brief Append an item to the end of the sequence.
   *
   * This operation push back an item to the of the sequence.
   *
   * @param item The object to be added to the end of the sequnce.
   *
   * @endif
   */ 
  void push_back(const SequenceItem& item)
  {
    ACE_Write_Guard<Mutex> gaurd(lock);
    CORBA::ULong len(this->length());
    this->length(len + 1);
    (*this)[len] = x;
  }

  void pop_back()
  {
    ACE_Write_Guard<Mutex> gaurd(lock);
    CORBA::ULong len(this->length());
    this->len(len - 1);
  }

  template <class F>
  SequenceItem find(F f) const
  {
    ACE_Read_Guard<Mutex> guard(lock);
    CORBA::ULong len(this->length());
    for (CORBA::ULong i = 0; i < len; ++i)
      if (f((*this)[i]))
	return (*this)[i];
    throw; // InvalidParameter("Not found.");
  }

  mutable Mutex lock;
};

/*
template <class CorbaSequence, class F, class SequenceItem>
SequenceItem& erase_if(CorbaSequence& t, F& f)
{
ACE_Write_Guard<Mutex> gaurd(t.lock);
  CORBA::ULong len(t.length());
  for (CORBA::ULong i = 0; i < len; ++i)
    if (f(t[i]))
      return t.erase(i);
}
*/

#endif // Util_h
