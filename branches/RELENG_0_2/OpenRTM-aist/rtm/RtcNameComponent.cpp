/*!
 * @file RtcNameCOmponent.h
 * @brief Name component helper class
 * @date $Date: 2005-05-12 09:06:18 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcNameComponent.cpp,v 1.1.1.1 2005-05-12 09:06:18 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#include "rtm/RtcNameComponent.h"

namespace RTM
{

  RtcNameComponent::RtcNameComponent()
	: m_Length(0)
  {
	m_Name.length(0);
  }


  RtcNameComponent::RtcNameComponent(const std::string path)
  {
	m_Name = stringToNameComponent(path);
	m_Length = m_Name.length();
  }
	

  RtcNameComponent::RtcNameComponent(const char* path)
  {
	m_Name = stringToNameComponent(std::string(path));
	m_Length = m_Name.length();
  }
  
  CosNaming::Name RtcNameComponent::get()
  {
	return m_Name;
  }

  CosNaming::Name RtcNameComponent::pop()
  {
	CosNaming::Name name;
	--m_Length;
	name.length(1);
	name[0] = m_Name[m_Length];
	m_Name.length(m_Length);
	return name;
  }
  
  CosNaming::Name RtcNameComponent::push(const std::string& path)
  {
	CosNaming::Name name0, name1;
	int len0, len1;
	
	name0 = m_Name;
	name1 = RtcNameComponent::stringToNameComponent(path);
	len0 = name0.length();
	len1 = name1.length();
	
	m_Length = len0 + len1;
	m_Name.length(m_Length);
	
	for (int i = 0; i < len0; i++)
	  {
		m_Name[i].id   = CORBA::string_dup(name0[i].id);
		m_Name[i].kind = CORBA::string_dup(name0[i].kind);
	  }
	
	for (int i = 0; i < len1; i++)
	  {
		m_Name[len0 + i].id   = CORBA::string_dup(name1[i].id);
		m_Name[len0 + i].kind = CORBA::string_dup(name1[i].kind);
	  }
	
	return m_Name;
  }
  

  void RtcNameComponent::erase()
  {
	m_Length = 0;
	m_Name.length(0);
	return;
  }

  CosNaming::Name
  RtcNameComponent::stringToNameComponent(const std::string& path)
  {
	std::string path_string(path);
	CosNaming::Name name;
	int length;
	
	if (path_string.find_first_of("/") == (std::string::size_type) 0)
	  {
		path_string.erase(path_string.begin());
	  }
	
	std::vector<std::string> node_list;
	length = split(path_string, "/", node_list);
	
	if (length == -1)
	  {
		return name;
	  }
	name.length(length);
	
	for (int i = 0; i < length; ++i)
	  {
		std::string id, kind;
		nodeToIdKind(node_list[i], id, kind);
		name[i].id   = CORBA::string_dup(id.c_str());
		name[i].kind = CORBA::string_dup(kind.c_str());
	  }
	return name;
  }
  
  
  int RtcNameComponent::split(const std::string& input,
									 const std::string& delimiter,
									 std::vector<std::string>& results)
  {
	std::string::size_type input_size = input.size();
	std::string::size_type delim_size = delimiter.size();
	std::string::size_type new_pos = 0;
	std::string::size_type pre_pos = 0;
	std::string::size_type sub_size = 0;
	int ret_value = -1;
	bool search = true;
	
	while (search)
	  {
		new_pos = input.find(delimiter, pre_pos);
		if (new_pos == std::string::npos)
		  {
			search = false;
			sub_size = input_size - pre_pos;
		  }
		else
		  {
			sub_size = new_pos - pre_pos;
		  }
		if (sub_size > 0)
		  {
			results.push_back(input.substr(pre_pos, sub_size));
			ret_value = results.size();
		  }
		pre_pos = new_pos + delim_size;
	  }
	return ret_value;
  }
	
	
  void RtcNameComponent::nodeToIdKind(const std::string& node,
											 std::string& id,
											 std::string& kind)
  {
	std::string::size_type pos;
	pos = node.find_first_of("|");
	
	if (pos == std::string::npos)
	  {
		id = node;
	  }
	else 
	  {
		id = node.substr(0, pos);
		kind = node.substr(pos + 1);
	  }
  }
  
};

