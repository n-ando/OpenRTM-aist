// -*- C++ -*-
/*!
 * @file OutPortBase.h
 * @brief InPortBase base class
 * @date $Date: 2007-12-31 03:08:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: OutPortBase.h,v 1.1.4.1 2007-12-31 03:08:05 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/12/02 18:46:13  n-ando
 * The first commitment.
 *
 * Revision 1.3  2005/05/27 07:34:21  n-ando
 * - InPort/OutPort interface was changed.
 *   subscribe/unsubscribe were completely changed.
 *
 * Revision 1.2  2005/05/16 06:37:11  n-ando
 * - OutPortBase class was DLL exported for Windows port.
 * - m_Profile.name should be initialized with empty string.
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#ifndef RtcOutPortBase_h
#define RtcOutPortBase_h

#include <vector>
#include <string>

namespace RTC
{
  class PublisherBase;
  /*!
   * @if jp
   *
   * @class OutPortBase
   *
   * @brief OutPort 基底クラス
   * 
   * OutPort の実装である OutPort<T> の基底クラス。
   *
   * OutPortBase と PublisherBase は一種の Observer パターンを形成している。
   * OutPortBase の attach(), detach(), notify() および
   * PublisherBase の push() は Observer パターンに関連したメソッドである。
   *
   * @since 0.2.0
   *
   * @else
   *
   * @class OutPortBase
   *
   * @brief Output port base class.
   *
   * The base class of OutPort<T> s which are implementations of OutPort  
   *
   * @endif
   */
  class OutPortBase
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ。
     *
     * @param name ポート名
     *
     * @else
     *
     * @brief A constructor of OutPortBase class.
     *
     * Constructor of OutPortBase.
     *
     * @endif
     */
    OutPortBase(const char* name)
      : m_name(name)
    {
    };
    
    /*!
     * @if jp
     * @brief デストラクタ
     *
     * デストラクタ。
     * 登録された全ての Publisher を削除する。
     *
     * @else
     *
     * @brief destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~OutPortBase();
    
    /*!
     * @if jp
     * @brief OutPort名称の取得
     *
     * OutPortの名称を取得する。
     *
     * @return ポート名称
     *
     * @else
     *
     * @brief OutPort's name
     *
     * This operation returns OutPort's name
     *
     * @endif
     */
    inline const char* name() {return m_name.c_str();}
    
    /*!
     * @if jp
     * @brief Publisherの追加
     *
     * 指定したPublisherをデータ更新通知先としてリストの最後尾に追加する。
     * attach_back() と同様な機能。
     *
     * @param id 指定されたPublisherに割り当てるID
     * @param publisher 登録対象Publisherオブジェクト
     *
     * @else
     *
     * @brief Attach a publisher
     *
     * Attach a publisher to observe OutPort.
     *
     * @endif
     */
    void attach(const char* id, PublisherBase* publisher);
    
    /*!
     * @if jp
     * @brief リスト先頭へのPublisherの追加
     *
     * Publisherをリストの先頭に追加する。
     *
     * @param id 指定されたPublisherに割り当てるID
     * @param publisher 登録対象Publisherオブジェクト
     *
     * @else
     *
     * @brief Attach a publisher
     *
     * Attach a publisher to the head of the Publisher list.
     *
     * @endif
     */
    void attach_front(const char* id, PublisherBase* publisher);
    
    /*!
     * @if jp
     * @brief リスト最後尾へのPublisherの追加
     *
     * Publisherをリストの最後尾に追加する。
     *
     * @param id 指定されたPublisherに割り当てるID
     * @param publisher 登録対象Publisherオブジェクト
     *
     * @else
     *
     * @brief Attach a publisher
     *
     * Attach a publisher to the taile of the Publisher list.
     *
     * @endif
     */
    void attach_back(const char* id, PublisherBase* publisher);
    
    /*!
     * @if jp
     * @brief Publisherの削除
     *
     * 指定された Publisher をデータ更新通知先リストから削除する。
     *
     * @param id 削除対象 Publisher のID
     *
     * @return 削除に成功した場合は、削除した Publisher オブジェクト
     *         指定した Publisher が存在しない場合は null
     *
     * @else
     *
     * @brief Detach a publisher
     *
     * Detach a publisher to observe OutPort.
     *
     * @endif
     */
    PublisherBase* detach(const char* id);
    
    /*!
     * @if jp
     * @brief 更新の通知
     *
     * 登録されている全ての Publisher にデータ更新を通知する。
     *
     * @else
     *
     * @brief Notify data update
     *
     * This operation notify data update to Publishers
     *
     * @endif
     */
    void notify();
    
  protected:
    /*!
     * @if jp
     * @brief ポート名
     * @else
     *
     * @endif
     */
    std::string m_name;
    
    /*!
     * @if jp
     * @brief Publisher 用構造体
     * @else
     *
     * @endif
     */
    struct Publisher
    {
      Publisher(const char* _id, PublisherBase* _publisher)
	: id(_id), publisher(_publisher){};
      std::string id;
      PublisherBase* publisher;
    };
    
    /*!
     * @if jp
     * @brief 登録された Publisher リスト
     * @else
     *
     * @endif
     */
    std::vector<Publisher*> m_publishers;
    
    /*!
     * @if jp
     * @brief Publisher を ID によって検索するための Functor
     * @else
     *
     * @endif
     */
    // Functor to find Publisher by id
    struct find_id;
    
    /*!
     * @if jp
     * @brief Publisher にデータ更新を通知するための Functor
     * @else
     *
     * @endif
     */
    // Functor to notify update to Publishers
    struct pub_push;
    
    /*!
     * @if jp
     * @brief Publisher を削除するための Functor
     * @else
     *
     * @endif
     */
    // Functor to delete Publishers
    struct pub_del;
  };
}; // End of namespace RTM
#endif // RtcOutPortBase_h
