// -*- C++ -*-
/*!
 * @file  TestSerializer.cpp
 * @brief Sample Serializer
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
class TestSerializerShort : public RTC::CORBA_CdrSerializer<RTC::TimedShort>
{
public:
    TestSerializerShort() = default;

    bool serialize(const RTC::TimedShort& data) override
    {
        RTC::TimedLong tmp_data;
        tmp_data.tm.sec = data.tm.sec;
        tmp_data.tm.nsec = data.tm.nsec;
        tmp_data.data = static_cast<CORBA::Long>(data.data);
        return m_cdr.serializeCDR(tmp_data);
    }

    bool deserialize(RTC::TimedShort& data) override
    {
        RTC::TimedLong tmp_data;
        bool ret = m_cdr.deserializeCDR(tmp_data);
        data.tm.sec = tmp_data.tm.sec;
        data.tm.nsec = tmp_data.tm.nsec;
        data.data = static_cast<CORBA::Short>(tmp_data.data);
        return ret;
    }
private:
};


class TestSerializerDouble : public RTC::CORBA_CdrSerializer<RTC::TimedDouble>
{
public:
    TestSerializerDouble() = default;

    bool serialize(const RTC::TimedDouble& data) override
    {
        RTC::TimedLong tmp_data;
        tmp_data.tm.sec = data.tm.sec;
        tmp_data.tm.nsec = data.tm.nsec;
        tmp_data.data = static_cast<CORBA::Long>(data.data);
        return m_cdr.serializeCDR(tmp_data);
    }

    bool deserialize(RTC::TimedDouble& data) override
    {
        RTC::TimedLong tmp_data;
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
    DLL_EXPORT void TestSerializerInit(RTC::Manager* /*manager*/)
    {
        //以下のファクトリはデータ型ごとに登録する必要がある
        RTC::addSerializer<RTC::TimedShort, TestSerializerShort>("test:dummydata");
        RTC::addSerializer<RTC::TimedDouble, TestSerializerDouble>("test:dummydata");
        //addSerializer関数の第1引数で登録名を設定。独自シリアライザを利用するときはこの名前を使用する。
    }
}
