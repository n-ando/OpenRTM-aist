// -*- C++ -*-
/*!
 * @file ByteDataStreamBase.h
 * @brief Data Stream Buffer Base class
 * @date $Date: 2019-1-26 03:08:06 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2006-2019
 *     Noriaki Ando
 *     Robot Innovation Research Center,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTC_BYTEDATASTREAMBASE_H
#define RTC_BYTEDATASTREAMBASE_H

#include <coil/Properties.h>
#include <coil/Factory.h>



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
 * @brief RT-Component
 *
 * @endif
 */
namespace RTC
{
  /*!
   * @if jp
   * @class ByteDataStreamBase
   * @brief シリアライザの基底クラス
   *
   *
   * @param 
   *
   * @since 2.0.0
   *
   * @else
   * @class ByteDataStreamBase
   * @brief 
   *
   *
   * @since 2.0.0
   *
   * @endif
   */
  class ByteDataStreamBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     *
     *
     * @else
     *
     * @brief Constructor
     *
     *
     * @endif
     */
     ByteDataStreamBase();

    /*!
     * @if jp
     *
     * @brief 仮想デストラクタ
     *
     * 仮想デストラクタ。
     *
     * @else
     *
     * @brief Virtual destractor
     *
     * Virtual destractor
     *
     * @endif
     */
    virtual ~ByteDataStreamBase();

    /*!
     * @if jp
     * @brief 初期化関数(未使用)
     *
     * @param prop プロパティ(コネクタプロファイルから取得)
     *
     * @else
     * @brief
     *
     * @param prop
     *
     * @endif
     */
    virtual void init(const coil::Properties& prop);
    /*!
     * @if jp
     * @brief 保持しているバッファにデータを書き込む
     *
     * @param buffer 書き込み元のバッファ
     * @param length データのサイズ
     *
     * @else
     * @brief
     *
     * @param buffer 
     * @param length 
     *
     *
     * @endif
     */
    virtual void writeData(const unsigned char* buffer, unsigned long length) = 0;
    /*!
     * @if jp
     * @brief 引数のバッファにデータを書き込む
     *
     * @param buffer 書き込み先のバッファ
     * @param length データのサイズ
     *
     * @else
     * @brief
     *
     * @param buffer
     * @param length
     *
     *
     * @endif
     */
    virtual void readData(unsigned char* buffer, unsigned long length) const = 0;
    /*!
     * @if jp
     * @brief データの長さを取得
     *
     * @return データの長さ
     *
     * @else
     * @brief
     *
     * @return
     *
     * @endif
     */
    virtual unsigned long getDataLength() const = 0;
    /*!
     * @if jp
     * @brief エンディアンの設定
     *
     * @param little_endian リトルエンディアン(True)、ビッグエンディアン(False)
     *
     * @else
     * @brief
     *
     * @param little_endian
     *
     * @endif
     */
    virtual void isLittleEndian(bool little_endian);
  };



  /*!
   * @if jp
   * @class ByteDataStream
   * @brief シリアライザのテンプレートクラス
   * シリアライザを実装する場合は必ずこのクラスを継承する必要がある
   * coil::GlobalFactory <::RTC::ByteDataStream<DataType>>にシリアライザを登録すると使用可能
   * 使用するデータ型全てに対してファクトリに登録する必要がある
   *
   *
   * @param 
   *
   * @since 2.0.0
   *
   * @else
   * @class ByteDataStream
   * @brief 
   *
   *
   * @since 2.0.0
   *
   * @endif
   */
  template <typename DataType>
  class ByteDataStream : public ByteDataStreamBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     *
     *
     * @else
     *
     * @brief Constructor
     *
     *
     * @endif
     */
    ByteDataStream() = default;

    /*!
     * @if jp
     *
     * @brief 仮想デストラクタ
     *
     * 仮想デストラクタ。
     *
     * @else
     *
     * @brief Virtual destractor
     *
     * Virtual destractor
     *
     * @endif
     */
    ~ByteDataStream() override = default;

    /*!
     * @if jp
     * @brief データの符号化
     *
     * @param data 符号化前のデータ
     * @return True：成功、False：失敗
     *
     * @else
     * @brief
     *
     * @param data 
     * @return
     *
     * @endif
     */
    virtual bool serialize(const DataType& data) = 0;
    /*!
     * @if jp
     * @brief データの復号化
     *
     * @param data 復号前のデータ
     * @return True：成功、False：失敗
     *
     * @else
     * @brief
     *
     * @param data
     * @return
     *
     * @endif
     */
    virtual bool deserialize(DataType& data) = 0;
    

  };



} // namespace RTC



#ifndef LIBRARY_EXPORTS
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedState> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedShort> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedLong> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedUShort> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedULong> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedFloat> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedDouble> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedChar> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedWChar> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedBoolean> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedOctet> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedString> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedWString> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedShortSeq> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedLongSeq> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedUShortSeq> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedULongSeq> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedFloatSeq> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedDoubleSeq> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedCharSeq> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedWCharSeq> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedBooleanSeq> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedOctetSeq> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedStringSeq> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedWStringSeq> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedRGBColour> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedPoint2D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedVector2D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedPose2D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedVelocity2D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedAcceleration2D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedPoseVel2D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedSize2D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedGeometry2D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedCovariance2D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedPointCovariance2D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedCarlike> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedSpeedHeading2D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedPoint3D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedVector3D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedOrientation3D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedPose3D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedVelocity3D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedAngularVelocity3D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedAcceleration3D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedAngularAcceleration3D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedPoseVel3D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedSize3D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedGeometry3D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedCovariance3D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedSpeedHeading3D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedOAP> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedQuaternion> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::ActArrayActuatorPos> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::ActArrayActuatorSpeed> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::ActArrayActuatorCurrent> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::ActArrayState> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::CameraImage> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::Fiducials> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::GPSData> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::GripperState> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::INSData> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::LimbState> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::Hypotheses2D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::Hypotheses3D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::Features> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::MultiCameraImages> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::Path2D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::Path3D> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::PointCloud> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::PanTiltAngles> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::PanTiltState> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::RangeData> >;
EXTERN template class DLL_PLUGIN coil::GlobalFactory < ::RTC::ByteDataStream<RTC::IntensityData> >;
#endif



#endif  // RTC_BYTEDATASTREAMBASE_H
