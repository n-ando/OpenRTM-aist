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
 * $Id$
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
   * @brief Output base class.
   *
   * The base class of OutPort<T> which are implementations of OutPort
   *
   * Form a kind of Observer pattern with OutPortBase and PublisherBase.
   * attach(), detach(), notify() of OutPortBase and
   * push() of PublisherBase are methods associated with the Observer pattern.
   *
   * @since 0.2.0
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
     * @brief Constructor
     *
     * Constructor
     *
     * @param name Port name
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
     * @brief Destructor
     *
     * Destructor
     * Detach all subscribed Publishers.
     *
     * @endif
     */
    virtual ~OutPortBase(void);
    
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
     * @brief Retrieve OutPort name
     *
     * Retrieve OutPort name
     *
     * @return the port name
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
     * @brief Attach the publisher
     *
     * Attach the specified publisher as the destination of the data update
     * notification to the end of the Publisher list.
     * This function is similar to attach_back().
     *
     * @param id ID assigned to the Publisher that is specified
     * @param publisher The target Publisher object for attachment
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
     * @brief Attach the publisher to the top of the Publisher list.
     *
     * Attach the publisher to the top of the Publisher list.
     *
     * @param id ID assigned to the Publisher that is specified
     * @param publisher The target Publisher object for attachment
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
     * @brief Attach the publisher at the end of the Publisher list.
     *
     * Attach the publisher to the end of the Publisher list.
     *
     * @param id ID assigned to the Publisher that is specified
     * @param publisher The target Publisher object for attachment
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
     * @brief Detach the publisher
     *
     * Detach the specified Publisher from the update notification list
     *
     * @param id ID of the deleted Publisher
     *
     * @return The deleted publisher object if the deletion completed
     *         successfully.
     *         Null if the specified Publisher does not exist.
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
     * @brief Notify the data updates
     *
     * Notify data updates to all registered Publishers
     *
     * @endif
     */
    void notify();

    virtual void onConnect(const char* id, PublisherBase* publisher){};
    virtual void onDisconnect(const char* id){};
    
  protected:
    /*!
     * @if jp
     * @brief ポート名
     * @else
     * @brief Port name
     * @endif
     */
    std::string m_name;
    
    /*!
     * @if jp
     * @brief Publisher 用構造体
     * @else
     * @brief Structure of Publisher
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
     * @brief Registered Publisher list
     * @endif
     */
    std::vector<Publisher*> m_publishers;
    
    /*!
     * @if jp
     * @brief Publisher を ID によって検索するための Functor
     * @else
     * @brief Functor to find Publisher by id
     * @endif
     */
    // Functor to find Publisher by id
    struct find_id;
    
    /*!
     * @if jp
     * @brief Publisher にデータ更新を通知するための Functor
     * @else
     * @brief Functor to notify updates to Publishers
     * @endif
     */
    // Functor to notify update to Publishers
    struct pub_push;
    
    /*!
     * @if jp
     * @brief Publisher を削除するための Functor
     * @else
     * @brief Functor to delete Publishers
     * @endif
     */
    // Functor to delete Publishers
    struct pub_del;
  };
}; // End of namespace RTM
#endif // RtcOutPortBase_h
