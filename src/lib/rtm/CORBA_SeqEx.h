// -*- C++ -*-
/*!
 * @file CORBA_Util.h
 * @brief CORBA utility template classes
 * @date $Date: 2007-04-26 15:24:41 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef CORBA_Util_h
#define CORBA_Util_h

#include <rtm/RTC.h>
#include <ace/Guard_T.h>
#include <ace/Thread_Mutex.h>
#include <ace/Recursive_Thread_Mutex.h>


typedef ACE_Guard<ACE_Thread_Mutex> Guard;
typedef ACE_Read_Guard<ACE_Thread_Mutex> Read_Guard;
typedef ACE_Write_Guard<ACE_Thread_Mutex> Write_Guard;

typedef ACE_Guard<ACE_Recursive_Thread_Mutex> Guard_r;
typedef ACE_Read_Guard<ACE_Recursive_Thread_Mutex> Read_Guard_r;
typedef ACE_Write_Guard<ACE_Recursive_Thread_Mutex> Write_Guard_r;


/*!
 * CORBA sequence ヘルパーテンプレート関数
 *
 * for_each ()
 * find ()
 * push_back ()
 * insert ()
 * front()
 * back ()
 * erase ()
 * clear ()
 *
 */
namespace CORBA_Sequence_Util
{
  /*!
   * @if jp
   * @brief CORBA sequence に対して functor を適用する
   *
   * CORBA sequence 全ての要素に対して、与えられた functor を適用する。
   * functor は void functor(CORBA sequence の要素) の形式をとる必要がある。
   *
   * @param seq Functor を適用する CORBA sequence
   * @param f CORBA sequence の要素を処理する Functor
   *
   * @return 全ての要素を処理した Functor
   *
   * @else
   *
   * @brief Apply the functor to all CORBA sequence elements
   *
   * Apply the given functor to the given CORBA sequence.
   * functor should be void functor(CORBA sequence element).
   *
   * @param seq CORBA sequence to be applied the functor
   * @param f A functor to process CORBA sequence elements
   *
   * @return Functor that processed all CORBA sequence elements
   *
   * @endif
   */
  template <class CorbaSequence, class Functor>
  Functor for_each(const CorbaSequence& seq, Functor f)
  {
    CORBA::ULong len;
    len = seq.length();
    for (CORBA::ULong i = 0; i < len; ++i)
      {
	f(seq[i]);
      }
    return f;
  }


  /*!
   * @if jp
   * @brief CORBA sequence の中から functor に適合する要素のインデックスを返す
   *
   * CORBA sequence 全ての要素に対して、与えられた functor を適用し、
   * functor が true を返す要素のインデックスを返す。
   * functor は bool functor(const CORBA sequence の要素) の形式をとり、
   * 適合する要素に対して true を返す必要がある。
   *
   * @param seq Functor を適用する CORBA sequence
   * @param f CORBA sequence から要素を見つける Functor
   *
   * @return Functorに適合する要素のインデックス。
   *         見つからないときは -1 を返す。
   *
   * @else
   *
   * @brief Return the index of CORBA sequence element that functor matches 
   *
   * This operation applies the given functor to the given CORBA sequence,
   * and returns the index of the sequence element that the functor matches.
   * The functor should be bool functor(const CORBA sequence element) type,
   * and it would return true, if the element matched the functor.
   *
   * @param seq CORBA sequence to be applied the functor
   * @param f A functor to process CORBA sequence elements
   *
   * @return The index of the element that functor matches.
   *         If no element found, it would return -1.
   *
   * @endif
   */
  template <class CorbaSequence, class Functor>
  CORBA::Long find(const CorbaSequence& seq, Functor f)
  {
    CORBA::ULong len(seq.length());
    for (CORBA::ULong i = 0; i < len; ++i)
      {
	if (f(seq[i])) return (CORBA::Long)i;
      }
    return -1;
  }

  /*!
   * @if jp
   * @brief CORBA sequence の最後に要素を追加する
   *
   * CORBA sequence の最後に与えられた要素を追加する。
   * CORBA sequence の長さは自動的に拡張される。
   *
   * @param seq 要素を追加する CORBA sequence
   * @param elem 追加する要素
   *
   * @else
   *
   * @brief Push the new element back to the CORBA sequence
   *
   * Add the given element to the last of CORBA sequence.
   * The length of the CORBA sequence will be expanded automatically.
   *
   * @param seq CORBA sequence to be added a new element
   * @param elem The new element to be added to the CORBA sequence
   *
   * @endif
   */
  template <class CorbaSequence, class SequenceElement>
  void push_back(CorbaSequecne& seq, SequenceElement elem)
  {
    CORBA::ULong len(seq.length());
    seq.length(len + 1);
    seq[len] = item;
  }


  /*!
   * @if jp
   * @brief CORBA sequence に要素を挿入する
   *
   * CORBA sequence の index の位置に要素を加える。
   * index が 与えられた　CORBA sequence の最大の index より大きい場合
   * 最後の要素として加えられる。
   * CORBA sequence の長さは自動的に拡張される。
   *
   * @param seq 要素を追加する CORBA sequence
   * @param elem 追加する要素
   * @param index 要素を追加する位置
   *
   * @else
   *
   * @brief Insert the element to the CORBA sequence
   *
   * Insert a new element in the given position to the CORBA sequence.
   * If the given index is greater than the length of the sequence,
   * the given element is pushed back to the last of the sequence.
   * The length of the CORBA sequence will be expanded automatically.
   *
   * @param seq The CORBA sequence to be inserted a new element
   * @param elem The new element to be inserted the sequence
   * @param index The inserting position
   *
   * @endif
   */
  template <class CorbaSequence, class SequenceElement>
  void insert(CorbaSequence& seq, SequenceElement& elem, CORBA::ULong index)
  {
    CORBA::ULong len(seq.length());
    if (index > len) push_back(seq, elem);

    seq.length(len + 1);
    for (CORBA::ULong i = len; i >= index; --i)
      {
	seq[i + 1] = seq[i];
      }
    seq[index] = elem;
  }


  /*!
   * @if jp
   * @brief CORBA sequence の先頭要素を取得する
   *
   * CORBA sequence の先頭要素を取得する。seq[0] と同じ。
   *
   * @param seq 要素を取得する CORBA sequence
   *
   * @return 取得した要素
   *
   * @else
   *
   * @brief Get the front element of the CORBA sequence
   *
   * This operation returns seq[0].
   *
   * @param seq The CORBA sequence to be get the element
   *
   * @endif
   */
  template <class CorbaSequence, class SequenceElement>
  SequenceElement& front(CorbaSequence& seq)
  {
    return seq[0];
  }


  /*!
   * @if jp
   * @brief CORBA sequence の末尾要素を取得する
   *
   * CORBA sequence の末尾要素を取得する。seq[seq.length() - 1] と同じ。
   *
   * @param seq 要素を取得する CORBA sequence
   *
   * @return 取得した要素
   *
   * @else
   *
   * @brief Get the last element of the CORBA sequence
   *
   * This operation returns seq[seq.length() - 1].
   *
   * @param seq The CORBA sequence to be get the element
   *
   * @endif
   */	
  template <class CorbaSequence, class SequenceElement>
  SequenceElement& back(CorbaSequence& seq)
  {
    return seq[seq.length() - 1];
  }


  /*!
   * @if jp
   * @brief CORBA sequence の指定された位置の要素を削除する
   *
   * 指定されたインデックスの要素を削除する。
   * 削除された要素は詰められ、sequence の長さは1減る。
   *
   * @param seq 要素を削除する CORBA sequence
   * @param index 削除する要素のインデックス
   *
   * @else
   *
   * @brief Erase the element of the specified index
   *
   * This operation removes the element of the given index.
   * The other elements are closed up around the hole.
   *
   * @param seq The CORBA sequence to be get the element
   * @param index The index of the element to be removed
   *
   * @endif
   */
  template <class CorbaSequence>
  void erase(CorbaSequence& seq, CORBA::ULong index)
  {
    CORBA::ULong len(seq.length());
    if (index > len) return;

    for (CORBA::ULong i = index; i < len - 1; ++i)
      {
	seq[i] = seq[i + 1];
      }
    seq.length(len - 1);
  }

  /*!
   * @if jp
   * @brief CORBA sequence の全要素を削除
   *   
   * CORBA sequence の全要素を削除する。
   * seq.length(0) と同じ。
   *
   * @else
   *
   * @brief Erase all elements of the CORBA sequence
   *
   * same as seq.length(0).
   *
   * @endif
   */
  template <class CorbaSequence>
  void clear(CorbaSequence& seq)
  {
    seq.length(0);
  }
  // End of CORBA sequence helper functions



  //============================================================
  // CORBA sequence extention class
  //============================================================

  /*!
   * @if jp
   * @brief  ロック付きデータ
   * @else
   * @brief  Data with mutex lock
   * @endif
   */
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
   * 
   * @since 0.4.0
   *
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
   * @since 0.4.0
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
     * @else
     *
     * @brief Default constructor
     *
     * Default constructor. This default constructor sets the sequence length
     * of CorbaSequence base class.
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
     * @param _sq 代入元
     *
     * @return 代入結果
     *
     * @else
     *
     * @brief Assignment operator
     *
     * @param _sq Copy source.
     *
     * @return An assignment result
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
     * @param _sq 代入元
     *
     * @return 代入結果
     *
     * @else
     *
     * @brief Assignment operator from CorbaSequence
     *
     * @param _sq Copy source.
     *
     * @return An assignment result
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
     * 現在の長さより大きなサイズが与えられた場合、引数 item で、
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
     * @param item     Sequence element to be assigned to new rooms.
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
	    (*this)[i] = item;
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
     * sequence の長さは自動的に拡張される。
     *
     * @param position 新しい要素を挿入する場所
     * @param item 挿入するシーケンスの要素
     *
     * @else
     *
     * @brief Insert a new item to the sequence
     *
     * This operation inserts a new item to the sequence.
     * The length of the sequence will be expanded automatically.
     *
     * @param position The position of new inserted item.
     * @param item     Sequence element to be inserted.
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
      (*this)[position] = item;
    }
    
    
    /*!
     * @if jp
     *
     * @brief シーケンスの要素を削除する
     *
     * このオペレーションはシーケンスの要素を削除する
     * sequence の長さは自動的に縮小される。
     *
     * @param position 削除するシーケンス要素の場所
     *
     * @return 削除された要素
     *
     * @else
     *
     * @brief Erase an item of the sequence
     *
     * This operation erases an item from the sequence.
     *
     * @param position The position of erased item.
     *
     * @return The element which was removed
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
     * @brief シーケンスの要素を述語にしたがって削除する
     *
     * このオペレーションは述語として与えられた関数オブジェクトの
     * 条件が真のとき、そのシーケンスの要素を削除する。
     *
     * @param f 削除するシーケンスを決定する術語
     *
     * @return 削除された要素
     *
     * @else
     *
     * @brief Erase an item according to the given predicate
     *
     * This operation erases an item according to the given predicate.
     *
     * @param f The predicate functor to decide deletion.
     *
     * @return The element which was removed
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
     * sequence の長さは自動的に拡張される。
     *
     * @param item 追加するするオブジェクト
     *
     * @else
     *
     * @brief Append an item to the end of the sequence.
     *
     * This operation push back an item to the end of the sequence.
     * The length of the sequence will be expanded automatically.
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
      (*this)[len] = item;
    }

    /*!
     * @if jp
     *
     * @brief 最後尾の要素を削除する
     *
     * このオペレーションはシーケンスの最後尾の要素を削除する。
     * sequence の長さは自動的に縮小される。
     *
     * @else
     *
     * @brief Remove an item from the end of the sequence.
     *
     * This operation removes an item from the end of the sequence.
     * The length of the sequence will be diminished automatically.
     *
     * @endif
     */
    void pop_back()
    {
      ACE_Write_Guard<Mutex> gaurd(lock);
      CORBA::ULong len(this->length());
      this->len(len - 1);
    }

    /*!
     * @if jp
     * @brief sequence検索用functor
     * @else
     * @brief Functor for sequence searches
     * @endif
     */
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

    /*!
     * @if jp
     * @brief データロック用mutex
     * @else
     * @brief mutex for data locks
     * @endif
     */
    mutable Mutex lock;
  }; // class SequenceEx
  
  
}; // namespace CORBA_Sequence_Util

#endif // CORBA_Util_h
