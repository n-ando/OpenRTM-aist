// -*- C++ -*-
/*!
 * @file  ShortToDoubleSerializer.cpp
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
class ShortToDoubleSerializer : public RTC::CORBA_CdrSerializer<RTC::TimedShort>
{
public:
    ShortToDoubleSerializer() = default;

    bool serialize(const RTC::TimedShort& data) override
    {
        RTC::TimedDouble tmp_data;
        tmp_data.tm.sec = data.tm.sec;
        tmp_data.tm.nsec = data.tm.nsec;
        tmp_data.data = static_cast<CORBA::Double>(data.data);
        return m_cdr.serializeCDR(tmp_data);
    }
private:
};

extern "C"
{
    //以下はモジュールロード時に呼び出される関数
    DLL_EXPORT void ShortToDoubleSerializerInit(RTC::Manager* /*manager*/)
    {
        //以下のファクトリはデータ型ごとに登録する必要がある
        RTC::addSerializer<RTC::TimedShort, ShortToDoubleSerializer>("cdr:RTC/TimedDouble:RTC/TimedShort");
        //addSerializer関数の第1引数で登録名を設定。独自シリアライザを利用するときはこの名前を使用する。
    }
}
