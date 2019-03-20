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
 * @file CORBACdrData.cpp
 * This source file contains the definition of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifdef _WIN32
// Remove linker warning LNK4221 on Visual Studio
namespace { char dummy; }
#endif

#include "CORBACdrData.h"

#include <fastcdr/Cdr.h>

#include <fastcdr/exceptions/BadParamException.h>

#include <utility>

RTC::CORBACdrData::CORBACdrData()
{
}

RTC::CORBACdrData::~CORBACdrData()
{
}

RTC::CORBACdrData::CORBACdrData(const CORBACdrData &x)
{
    m_data = x.m_data;
}

RTC::CORBACdrData::CORBACdrData(CORBACdrData &&x)
{
    m_data = std::move(x.m_data);
}

RTC::CORBACdrData& RTC::CORBACdrData::operator=(const CORBACdrData &x)
{
    m_data = x.m_data;
    
    return *this;
}

RTC::CORBACdrData& RTC::CORBACdrData::operator=(CORBACdrData &&x)
{
    m_data = std::move(x.m_data);
    
    return *this;
}

size_t RTC::CORBACdrData::getMaxCdrSerializedSize(size_t current_alignment)
{
    size_t initial_alignment = current_alignment;
            
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);
    current_alignment += (100 * 1) + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    return current_alignment - initial_alignment;
}

size_t RTC::CORBACdrData::getCdrSerializedSize(const RTC::CORBACdrData& data, size_t current_alignment)
{
    size_t initial_alignment = current_alignment;
            
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);
    current_alignment += (data.data().size() * 1) + eprosima::fastcdr::Cdr::alignment(current_alignment, 1);


    return current_alignment - initial_alignment;
}

void RTC::CORBACdrData::serialize(eprosima::fastcdr::Cdr &scdr) const
{
    scdr << m_data;
}

void RTC::CORBACdrData::deserialize(eprosima::fastcdr::Cdr &dcdr)
{
    dcdr >> m_data;
}

size_t RTC::CORBACdrData::getKeyMaxCdrSerializedSize(size_t current_alignment)
{
    size_t current_align = current_alignment;
            

    return current_align;
}

bool RTC::CORBACdrData::isKeyDefined()
{
    return false;
}

void RTC::CORBACdrData::serializeKey(eprosima::fastcdr::Cdr &/*scdr*/) const
{
	 
}
