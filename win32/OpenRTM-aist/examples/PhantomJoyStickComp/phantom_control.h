// -*- C++ -*-

#ifndef PHANTOM_CONTROL_H
#define PHANTOM_CONTROL_H

#include <iostream>
#include <vector>
#include <HD/hd.h>
#include <HDU/hduError.h>
#include <HDU/hduVector.h>

#define THRESHOLD 10.0 // Phantom Joystickモードでの閾値

using namespace std;

/*!
 * @brief the main scheduler callback for rendering the anchored spring force.
 * 力のセットやペン先の位置、姿勢を取得するためのコールバック関数
 * この関数の関数ポインタを使用するため、グローバルに宣言している。
 */
HDCallbackCode HDCALLBACK AnchoredSpringForceCallback(void *pUserData);


/******************************************************
 コールバック関数、メソッド間で共有する変数
 phantom_control.cpp内にて宣言
*******************************************************/
extern int g_calibrationStyle;
extern HDboolean g_bRenderForce;
extern HDboolean g_force_error_flag;
extern HDint g_button_1_flag, g_button_2_flag;
extern hduVector3Dd g_force;
extern hduVector3Dd g_cur_position;
extern hduVector3Dd g_cur_angle;


/*!
 * @class phantom_control
 * @brief PHANToMデバイスからのデータの取得と力のセットを行うクラス。
 */
class phantom_control 
{

 public:
  //! コンストラクタ
  phantom_control();

  //! デストラクタ
  ~phantom_control() {;}

  //! 初期化用メソッド
  bool initialize();

  //! 後処理用メソッド
  bool finalize();

  //! メンバ変数のリセット用メソッド
  void reset_member();

  /*!
   * @brief 力データセット用メソッド
   *    PHANToMにセットする力データを引数で指定する。
   * @param 力データのリスト(X,Y,Z)
   */
  void set_data(vector<float> force);

  /*!
   * @brief データ取得用メソッド
   *    PHANToMのペン先の基準位置と現在の位置の差分を返す。
   *    ペン先の基準位置はペンに付いているボタンを押した時のペン先位置。
   *
   * @return ペン先の基準位置と現在位置との差分のリスト(X,Y,Z)
   */
  vector<float> get_data();

  //! 速度データの要素数(X,Y,Z)
  typedef enum VELOCITY_VECTOR_ELEMENT {
    VelEle = 3
  };

  //! ペンの姿勢データの要素数(r,p,y)
  typedef enum ANGLE_VECTOR_ELEMENT {
    AngEle = 3
  };

  //! 力データの要素数(X,Y,Z)
  typedef enum FORCE_VECTOR_ELEMENT {
    ForceEle = 3
  };

  /*!
   * @brief ボタン操作に関するフラグ用定数
   * B_OFF  : 何もしない状態
   * B_ON   : ボタンを押した時点
   * B_PUSH : ボタンを押し続けている状態
   * B_FREE : ボタンを押した後、離したままの状態
   */
  typedef enum BUTTON_STATE {
    B_OFF  = 0,
    B_ON   = 1,
    B_PUSH = 2,
    B_FREE = 4
  };


 private:
  //! ペンの位置
  hduVector3Dd m_init_position;

  //! ペンの姿勢
  hduVector3Dd m_init_angle;

  //! ペンの基準位置と現在位置との差分
  hduVector3Dd m_vel;

  //! キャリブレーション状態
  int m_supportedCalibrationStyles;

  //! PHANToMデバイスハンドル
  HHD m_hHD;

  //! オペレーション用ハンドル
  HDSchedulerHandle m_gCallbackHandle; 

};


#endif //  PHANTOM_CONTROL_H
