// -*- C++ -*-
/*!
 * @file PortAdmin.h
 * @brief RTC's Port administration class
 * @date $Date: 2006-12-02 18:49:43 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PortAdmin.h,v 1.4 2006-12-02 18:49:43 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2006/11/06 01:19:04  n-ando
 * CORBA sequence manipulation has been rewritten by using CORBA_SeqUtil.
 *
 * Revision 1.2  2006/10/17 19:16:40  n-ando
 * registerPort() was modified to store Port's object reference in PortProfile.
 *
 * Revision 1.1  2006/10/17 10:22:01  n-ando
 * The first commitment.
 *
 */

#ifndef PortAdmin_h
#define PortAdmin_h

#include <rtm/idl/RTCSkel.h>
#include <rtm/PortBase.h>
#include <rtm/ObjectManager.h>
// 68608 10 17 23:51 PortAdmin.o
// 54272 10 29 00:53 PortAdmin.o
// 54132 10 29 00:54 PortAdmin.o
namespace RTC
{


  class PortAdmin
  {
  public:
    PortAdmin(CORBA::ORB_ptr, PortableServer::POA_ptr poa);
    virtual ~PortAdmin(){};

    /*!
     * @if jp
     *
     * @brief PortList の取得
     *
     * registerPort() により登録された Port の PortList へのポインタを返す。
     *
     * @return PortList* PortList へのポインタ
     *
     * @else
     *
     * @brief Get PortList
     *
     * This operation returns the pointer to the PortList of Ports regsitered
     * by registerPort().
     *
     * @return PortList+ The pointer points PortList
     *
     * @endif
     */
    PortList* getPortList() const;

    /*!
     * @if jp
     *
     * @brief Port のオブジェクト参照の取得
     *
     * port_name で指定した Port のオブジェクト参照を返す。
     * port_name で指定する Port はあらかじめ registerPort() で登録されてい
     * なければならない。
     *
     * @param port_name 参照を返すPortの名前
     * @return Port_ptr Portのオブジェクト参照
     *
     * @else
     *
     * @brief Get PortList
     *
     * This operation returns the pointer to the PortList of Ports regsitered
     * by registerPort().
     *
     * @param port_name The name of Port to be returned the reference.
     * @return Port_ptr Port's object reference.
     *
     * @endif
     */
    Port_ptr getPortRef(const char* port_name) const;


    /*!
     * @if jp
     *
     * @brief Port のサーバントのポインタの取得
     *
     * port_name で指定した Port のサーバントのポインタを返す。
     * port_name で指定する Port はあらかじめ registerPort() で登録されてい
     * なければならない。
     *
     * @param port_name 参照を返すPortの名前
     * @return PortBase* Portサーバント基底クラスのポインタ
     *
     * @else
     *
     * @brief Getpointer to the Port's servant
     *
     * This operation returns the pointer to the PortBase servant regsitered
     * by registerPort().
     *
     * @param port_name The name of Port to be returned the servant pointer.
     * @return PortBase* Port's servant's pointer.
     *
     * @endif
     */
    PortBase* getPort(const char* port_name) const;


    /*!
     * @if jp
     *
     * @brief Port を登録する
     *
     * 引数 port で指定された Port のサーバントを登録する。
     * 登録された Port のサーバントはコンストラクタで与えられたPOA 上で
     * activate され、そのオブジェクト参照はPortのProfileにセットされる。
     *
     * @param port Port サーバント
     *
     * @else
     *
     * @brief Regsiter Port
     *
     * This operation registers the Port's servant given by argument.
     * The given Port's servant will be activated on the POA that is given
     * to the constructor, and the created object reference is set
     * to the Port's profile.
     *
     * @param port The Port's servant.
     *
     * @endif
     */
    void registerPort(PortBase& port);


    /*!
     * @if jp
     *
     * @brief Port の登録を削除する
     *
     * 引数 port で指定された Port の登録を削除する。
     * 削除時に Port は deactivate され、PortのProfileのリファレンスには、
     * nil値が代入される。
     *
     * @param port Port サーバント
     *
     * @else
     *
     * @brief Delete the Port's registration
     *
     * This operation unregisters the Port's registration.
     * When the Port is unregistered, Port is deactivated, and the object
     * reference in the Port's profile is set to nil.
     *
     * @param port The Port's servant.
     *
     * @endif
     */
    void deletePort(PortBase& port);

    /*!
     * @if jp
     *
     * @brief Port の登録を削除する
     *
     * 引数で指定された名前を持つ Port の登録を削除する。
     * 削除時に Port は deactivate され、PortのProfileのリファレンスには、
     * nil値が代入される。
     *
     * @param port_name Port の名前
     *
     * @else
     *
     * @brief Delete the Port' registration
     *
     * This operation delete the Port's registration specified by port_ name.
     * When the Port is unregistered, Port is deactivated, and the object
     * reference in the Port's profile is set to nil.
     *
     * @param port_name The Port's name.
     *
     * @endif
     */
    void deletePortByName(const char* port_name);


    /*!
     * @if jp
     *
     * @brief 全ての Port をdeactivateし登録を削除する
     *
     * 登録されている全てのPortに対して、サーバントのdeactivateを行い、
     * 登録リストから削除する。
     *
     * @else
     *
     * @brief Unregister the Port
     *
     * This operation deactivates the all Port and deletes the all Port's
     * registrations from the list.
     *
     * @endif
     */
    void finalizePorts();

  private:
    // ORB へのポインタ
    CORBA::ORB_var m_pORB;

    // POA へのポインタ
    PortableServer::POA_var m_pPOA;

    // Portのオブジェクトリファレンスのリスト. PortList
    PortList m_portRefs;


    template <class T>
    class comp_op
    {
    public:
      comp_op(std::string _name) : m_name(_name) {};
      comp_op(T* obj) : m_name(obj->getName()) {};
      bool operator()(T* obj)
      {
	std::string name(obj->getName());
	return m_name == name;
      }
      std::string m_name;
    };
    
    struct find_port_name;
    struct del_port;

    // サーバントを直接格納するオブジェクトマネージャ
    ObjectManager<std::string, PortBase, comp_op<PortBase> > m_portServants;


  };
};     // namespace RTC
#endif // PortAdmin_h
