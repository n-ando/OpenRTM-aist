﻿// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*! 
 * @file CORBACdrDataPubSubTypes.cpp
 * This header file contains the implementation of the serialization functions.
 *
 * This file was generated by the tool fastcdrgen.
 */


#include <fastcdr/FastBuffer.h>
#include <fastcdr/Cdr.h>
#include <fastcdr/exceptions/BadParamException.h>
#include <rtm/ByteData.h>
#include <algorithm>

#include "CORBACdrDataPubSubTypes.h"



namespace RTC
{
    CORBACdrDataPubSubType::CORBACdrDataPubSubType()
        : m_endian(true), m_header_enable(false)
    {
    }

    CORBACdrDataPubSubType::~CORBACdrDataPubSubType() {
        delete[] m_keyBuffer;
    }

    void CORBACdrDataPubSubType::init(std::string name, bool header_enable) {
        setName(name.c_str());
        m_typeSize = (uint32_t)CORBACdrData::getMaxCdrSerializedSize() + 4 /*encapsulation*/;
        m_isGetKeyDefined = CORBACdrData::isKeyDefined();
        m_keyBuffer = new unsigned char[std::max(CORBACdrData::getKeyMaxCdrSerializedSize(), (size_t)16)];
        m_header_enable = header_enable;
    }

    void CORBACdrDataPubSubType::setEndian(bool endian)
    {
        m_endian = endian;
    }

    bool CORBACdrDataPubSubType::serialize(void *data, eprosima::fastrtps::rtps::SerializedPayload_t *payload)
    {
        RTC::ByteData* p_type = (RTC::ByteData*) data;
        if (!m_header_enable)
        {
            eprosima::fastcdr::FastBuffer fastbuffer((char*)payload->data, payload->max_size); // Object that manages the raw buffer.
            eprosima::fastcdr::Cdr::Endianness endian;
            if (m_endian)
            {
                endian = eprosima::fastcdr::Cdr::LITTLE_ENDIANNESS;
            }
            else
            {
                endian = eprosima::fastcdr::Cdr::BIG_ENDIANNESS;
            }
            eprosima::fastcdr::Cdr ser(fastbuffer, endian,
                eprosima::fastcdr::Cdr::DDS_CDR); // Object that serializes the data.
            payload->encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;
            // Serialize encapsulation
            try
            {
                ser.serialize_encapsulation();
            }
            catch (eprosima::fastcdr::exception::NotEnoughMemoryException& e)
            {
                std::cout << "NotEnoughMemoryException:" << e.what() << std::endl;
                return false;
            }
            catch (eprosima::fastcdr::exception::BadParamException& e)
            {
                std::cout << "BadParamException:" << e.what() << std::endl;
                return false;
            }
            uint32_t data_size = p_type->getDataLength() + (uint32_t)ser.getSerializedDataLength();
            try
            {
                payload->reserve(data_size);
            }
            catch (std::bad_alloc& e)
            {
                std::cout << "bad_alloc:" << e.what() << std::endl;
                return false;
            }
            payload->length = data_size;
            if (payload->max_size >= data_size)
            {
                memcpy(payload->data + ser.getSerializedDataLength(), p_type->getBuffer(), p_type->getDataLength());
            }
        }
        else
        {
            try
            {
                payload->reserve(p_type->getDataLength());
            }
            catch (std::bad_alloc& e)
            {
                std::cout << "bad_alloc:" << e.what() << std::endl;
                return false;
            }
            payload->length = p_type->getDataLength();
            if (payload->max_size >= p_type->getDataLength())
            {
                memcpy(payload->data, p_type->getBuffer(), p_type->getDataLength());
            }
        }
        return true;
    }

    bool CORBACdrDataPubSubType::deserialize(eprosima::fastrtps::rtps::SerializedPayload_t* payload, void* data)
    {

        RTC::ByteData* p_type = (RTC::ByteData*) data; 	//Convert DATA to pointer of your type
        eprosima::fastcdr::FastBuffer fastbuffer((char*)payload->data, payload->length); // Object that manages the raw buffer.
        eprosima::fastcdr::Cdr::Endianness endian;
        if (m_endian)
        {
            endian = eprosima::fastcdr::Cdr::LITTLE_ENDIANNESS;
        }
        else
        {
            endian = eprosima::fastcdr::Cdr::BIG_ENDIANNESS;
        }
        eprosima::fastcdr::Cdr deser(fastbuffer, endian,
                                      eprosima::fastcdr::Cdr::DDS_CDR); // Object that deserializes the data.
                                              // Deserialize encapsulation.
        try
        {
            deser.read_encapsulation();
        }
        catch (eprosima::fastcdr::exception::NotEnoughMemoryException& e)
        {
            std::cout << "NotEnoughMemoryException:" << e.what() << std::endl;
            return false;
        }
        catch (eprosima::fastcdr::exception::BadParamException& e)
        {
            std::cout << "BadParamException:" << e.what() << std::endl;
            return false;
        }
        payload->encapsulation = deser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

        if (!m_header_enable)
        {
            if (payload->length >= (uint32_t)deser.getSerializedDataLength())
            {
                p_type->writeData(payload->data + deser.getSerializedDataLength(), payload->length - (uint32_t)deser.getSerializedDataLength());
            }
        }
        else
        {
            p_type->writeData(payload->data, payload->length);
        }

        return true;
    }

    std::function<uint32_t()> CORBACdrDataPubSubType::getSerializedSizeProvider(void* data) {
        return [data]() -> uint32_t
        {
            return (uint32_t)static_cast<RTC::ByteData*>(data)->getDataLength() + 4 /*encapsulation*/;
        };
    }

    void* CORBACdrDataPubSubType::createData() {
        return (void*)new RTC::ByteData();
    }

    void CORBACdrDataPubSubType::deleteData(void* data) {
        delete static_cast<RTC::ByteData*>(data);
    }
#if (FASTRTPS_VERSION_MAJOR <= 1) && (FASTRTPS_VERSION_MINOR == 6)
    bool CORBACdrDataPubSubType::getKey(void * /*data*/, eprosima::fastrtps::rtps::InstanceHandle_t* handle) {
#else
    bool CORBACdrDataPubSubType::getKey(void * /*data*/, eprosima::fastrtps::rtps::InstanceHandle_t* handle, bool force_md5) {
#endif
        if(!m_isGetKeyDefined)
            return false;
        if (m_keyBuffer == nullptr)
        {
            return false;
        }
        eprosima::fastcdr::FastBuffer fastbuffer((char*)m_keyBuffer,CORBACdrData::getKeyMaxCdrSerializedSize()); 	// Object that manages the raw buffer.
        eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::BIG_ENDIANNESS); 	// Object that serializes the data.
        
        if(CORBACdrData::getKeyMaxCdrSerializedSize()>16)	{
            m_md5.init();
            m_md5.update(m_keyBuffer,(unsigned int)ser.getSerializedDataLength());
            m_md5.finalize();
            for(uint8_t i = 0;i<16;++i)    	{
                handle->value[i] = m_md5.digest[i];
            }
        }
        else    {
            for(uint8_t i = 0;i<16;++i)    	{
                handle->value[i] = m_keyBuffer[i];
            }
        }
        return true;
    }


} //End of namespace RTC
