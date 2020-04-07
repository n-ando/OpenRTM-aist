// -*- C++ -*-
/*!
 * @file  DouboleToDoubleDeserializer.cpp
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
class DouboleToDoubleDeserializer : public RTC::CORBA_CdrSerializer<RTC::TimedDouble>
{
public:
    DouboleToDoubleDeserializer() = default;

    bool deserialize(RTC::TimedDouble& data) override
    {
        bool ret = m_cdr.deserializeCDR(data);
        return ret;
    }
private:
};

extern "C"
{
    //以下はモジュールロード時に呼び出される関数
    DLL_EXPORT void DouboleToDoubleDeserializerInit(RTC::Manager* /*manager*/)
    {
        //以下のファクトリはデータ型ごとに登録する必要がある
        RTC::addSerializer<RTC::TimedDouble, DouboleToDoubleDeserializer>("cdr:RTC/TimedDouble");
        //addSerializer関数の第1引数で登録名を設定。独自シリアライザを利用するときはこの名前を使用する。
    }
}
