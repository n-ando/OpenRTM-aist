// -*- C++ -*-
/*!
 * @file  ShortToDoubleDeserializer.cpp
 * @brief Convert short to double
 * $Date: 2019-06-25 07:33:08 $
 *
 * $Id$
 */

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/ByteDataStreamBase.h>
#include <rtm/CORBA_CdrMemoryStream.h>
#include <coil/Factory.h>
#include <rtm/Manager.h>

//以下はシリアライザの実装
class ShortToDoubleDeserializer : public RTC::CORBA_CdrSerializer<RTC::TimedDouble>
{
public:
    ShortToDoubleDeserializer() = default;

    bool deserialize(RTC::TimedDouble& data) override
    {
        RTC::TimedShort tmp_data;
        bool ret = m_cdr.deserializeCDR(tmp_data);
        data.tm.sec = tmp_data.tm.sec;
        data.tm.nsec = tmp_data.tm.nsec;
        data.data = static_cast<CORBA::Double>(tmp_data.data);
        return ret;
    }
private:
};

extern "C"
{
    //以下はモジュールロード時に呼び出される関数
    DLL_EXPORT void ShortToDoubleDeserializerInit(RTC::Manager* /*manager*/)
    {
        //以下のファクトリはデータ型ごとに登録する必要がある
        RTC::addSerializer<RTC::TimedDouble, ShortToDoubleDeserializer>("cdr:RTC/TimedShort:RTC/TimedDouble");
        //addSerializer関数の第1引数で登録名を設定。独自シリアライザを利用するときはこの名前を使用する。
    }
}
