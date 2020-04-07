// -*- C++ -*-
/*!
 * @file  ShortToShortSerializer.cpp
 * @brief Convert short to double
 * $Date: 2020-04-01 07:33:08 $
 *
 * $Id$
 */

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/ByteDataStreamBase.h>
#include <rtm/CORBA_CdrMemoryStream.h>
#include <coil/Factory.h>
#include <rtm/Manager.h>

//以下はシリアライザの実装
class ShortToShortSerializer : public RTC::CORBA_CdrSerializer<RTC::TimedShort>
{
public:
    ShortToShortSerializer() = default;

    bool serialize(const RTC::TimedShort& data) override
    {
        return m_cdr.serializeCDR(data);
    }
private:
};

extern "C"
{
    //以下はモジュールロード時に呼び出される関数
    DLL_EXPORT void ShortToShortSerializerInit(RTC::Manager* /*manager*/)
    {
        //以下のファクトリはデータ型ごとに登録する必要がある
        RTC::addSerializer<RTC::TimedShort, ShortToShortSerializer>("cdr:RTC/TimedShort");
        //addSerializer関数の第1引数で登録名を設定。独自シリアライザを利用するときはこの名前を使用する。
    }
}
