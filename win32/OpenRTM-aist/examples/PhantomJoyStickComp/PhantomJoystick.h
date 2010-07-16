// -*- C++ -*-
/*!
 * @file  PhantomJoystick.h
 * @brief PhantomJoystick component
 * @date  $Date$
 *
 * $Id$
 */

#ifndef PHANTOMJOYSTICK_H
#define PHANTOMJOYSTICK_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>

#include "phantom_control.h"

using namespace RTC;

/*!
 * @class PhantomJoystickコンポーネントクラス
 *   PHANToMデバイスをジョイスティックとして使用するコンポーネントクラ
 *   ス
 */
class PhantomJoystick
  : public RTC::DataFlowComponentBase
{
public:
  //! コンストラクタ
  PhantomJoystick(RTC::Manager* manager);

  //! デストラクタ
  ~PhantomJoystick() {delete m_pc;}

  // The initialize action (on CREATED->ALIVE transition)
  virtual RTC::ReturnCode_t onInitialize();

  // The activated action (Active state entry action)
  virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  // The deactivated action (Active state exit action)
  virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  // The execution action that is invoked periodically
  virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /*!
   * @brief リストデータの積算を行うテンプレート関数
   * @param val1 : 結果を格納するためのリスト
   * @param val2 : 元のデータリスト
   * @param val3 : 掛ける値のリスト
   * @param size : 対象データのデータ数
   */
  template<class X, class Y, class Z>
  void data_mul(X &val1, Y &val2, Z &val3, int size) {
    for(int i = 0; i < size; i++) {
      val1[i] = val2[i] * val3[i];
    }
  }

  /*!
   * @brief リストデータのコピーを行うテンプレート関数
   * @param x : コピー先データリスト
   * @param y : コピー元データリスト
   * @param ins_point : コピー先リストの挿入ポイント(要素番号)
   */
  template<class X, class Y>
  void data_copy(X &x, Y &y,int ins_point) {
    for(int i = 0; i < VelEle; i++) {
      x[i+ins_point] = y[i];
    }
  }

  /*!
   * @brief リストデータのコピーを行うテンプレート関数
   * @param x : コピー先データリスト
   * @param y : コピー元データリスト
   * @param insPtr  : コピー先リストの挿入ポイント(要素番号)
   * @param readPtr : コピー元リストの読み込みポイント(要素番号)
   * @param size    : コピーするデータ数
   */
  template<class X, class Y>
  void data_copy(X &x, Y &y, int insPtr, int readPtr, int size) {
    for(int i = 0; i < size; i++) {
      x[i+insPtr] = y[i+readPtr];
    }
  }

protected:
  // Configuration variable declaration
  std::vector<float> m_force_gain;
  std::vector<float> m_vel_gain;
  
  // DataInPort declaration
  TimedFloatSeq m_force;
  InPort<TimedFloatSeq> m_forceIn;
  
  // DataOutPort declaration
  TimedFloatSeq m_vel;
  OutPort<TimedFloatSeq> m_velOut;
  
private:
  int dummy;
  //! phantom_controlクラスのインスタンス
  phantom_control *m_pc;

};


extern "C"
{
  void PhantomJoystickInit(RTC::Manager* manager);
};

#endif // PHANTOMJOYSTICK_H
