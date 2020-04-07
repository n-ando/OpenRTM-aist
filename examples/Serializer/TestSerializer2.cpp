// -*- C++ -*-
/*!
 * @file  TestSerializer2.cpp
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
class TestSerializer2Short : public RTC::CORBA_CdrSerializer<RTC::TimedShort>
{
public:
    TestSerializer2Short() = default;

    bool serialize(const RTC::TimedShort& data) override
    {
        RTC::TimedFloat tmp_data;
        tmp_data.tm.sec = data.tm.sec;
        tmp_data.tm.nsec = data.tm.nsec;
        tmp_data.data = static_cast<CORBA::Float>(data.data);
        return m_cdr.serializeCDR(tmp_data);
    }

    bool deserialize(RTC::TimedShort& data) override
    {
        RTC::TimedFloat tmp_data;
        bool ret = m_cdr.deserializeCDR(tmp_data);
        data.tm.sec = tmp_data.tm.sec;
        data.tm.nsec = tmp_data.tm.nsec;
        data.data = static_cast<CORBA::Short>(tmp_data.data);
        return ret;
    }
private:
};


class TestSerializer2Double : public RTC::CORBA_CdrSerializer<RTC::TimedDouble>
{
public:
    TestSerializer2Double() = default;

    bool serialize(const RTC::TimedDouble& data) override
    {
        RTC::TimedFloat tmp_data;
        tmp_data.tm.sec = data.tm.sec;
        tmp_data.tm.nsec = data.tm.nsec;
        tmp_data.data = static_cast<CORBA::Float>(data.data);
        return m_cdr.serializeCDR(tmp_data);
    }

    bool deserialize(RTC::TimedDouble& data) override
    {
        RTC::TimedFloat tmp_data;
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
    DLL_EXPORT void TestSerializer2Init(RTC::Manager* /*manager*/)
    {
        //以下のファクトリはデータ型ごとに登録する必要がある
        RTC::addSerializer<RTC::TimedShort, TestSerializer2Short>("test:dummydata2");
        RTC::addSerializer<RTC::TimedDouble, TestSerializer2Double>("test:dummydata2");
        //addSerializer関数の第1引数で登録名を設定。独自シリアライザを利用するときはこの名前を使用する。
    }
}
