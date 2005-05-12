// -*- C++ -*-
/*!
 * @file RtcNaming.cpp
 * @brief RT component naming class
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
 * $Id: RtcNaming.cpp,v 1.1.1.1 2005-05-12 09:06:18 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#include <iostream>
#include <boost/regex.hpp>

#include "rtm/RtcNaming.h"
#include "rtm/RtcNameComponent.h"


namespace RTM
{
  using namespace std;
  
  RtcNaming::~RtcNaming()
  {
	ACE_TRACE("RtcNaming::~RtcNaming()");

	destroyHostContext();	
  }


  bool RtcNaming::initNaming(const CORBA::ORB_ptr orb)
  {
	ACE_TRACE("RtcNaming::initNaming()");

    // ネーミングサービスのルートコンテキストを取得
    try
      {	
		CORBA::Object_var obj;
		obj = orb->resolve_initial_references("NameService");
		m_rootContext = CosNaming::NamingContextExt::_duplicate(CosNaming::NamingContextExt::_narrow(obj));
		
		if( CORBA::is_nil(m_rootContext) )
		  {
			cerr << "RtcNaming::initNaming: Failed to narrow the root naming context." << endl;
			return false;
		  }
      }
    catch(CORBA::ORB::InvalidName& ex) 
      {
		// This should not happen!
		cerr << "Service required is invalid [does not exist]." << endl;
		return false;
      }
	catch(...)
	  {
		cerr << "Unknown exception." << endl;
		return false;
	  }
    return true;
  }
  
  
  
  //============================================================
  // << Create Methods >>
  //============================================================
  
  
  CosNaming::NamingContextExt_var
  RtcNaming::createContext(CosNaming::NamingContextExt_var context,
						   const std::string& id, const std::string& kind)
  {
	ACE_TRACE("RtcNaming::createContext()");

    // Create naming context
    CosNaming::Name contextName;
    contextName.length(1);
	//    contextName[0].id   = CORBA::string_dup(id.c_str());
	//    contextName[0].kind = CORBA::string_dup(kind.c_str());
    contextName[0].id   = id.c_str();
    contextName[0].kind = kind.c_str();
	
    CosNaming::NamingContextExt_var testContext;
	CORBA::Object_var obj;
	
    // Bind the context to specified context.
    try
      {
		obj = context->bind_new_context(contextName);
		testContext = CosNaming::NamingContextExt::_narrow(obj);
		
		if( CORBA::is_nil(testContext) )
		  {
			cerr << "Failed to narrow naming context." << endl;
			return NULL;
		  }
		return testContext;
      }
    catch (CosNaming::NamingContext::AlreadyBound& ex)
      {
		// If the context already exists, this exception will be raised.
		// In this case, just resolve the name and assign testContext
		// to the object returned:
		obj = context->resolve(contextName);
		testContext = CosNaming::NamingContextExt::_narrow(obj);
		
		if( CORBA::is_nil(testContext) )
		  {
			cerr << "Failed to narrow naming context." << endl;
			return NULL;
		  }
		return testContext;
      }
	catch (...)
	  {
		cerr << "createContext(): Unknown error" << endl;
	  }
    return NULL;
  }
  
  
  bool RtcNaming::createHostContext(const std::string& id)
  {
	ACE_TRACE("RtcNaming::createHostContext()");

    if (CORBA::is_nil(m_rootContext))
      {
		return false;
      }
	m_hostName = id;
    m_hostContext = createContext(m_rootContext, id, "host_cxt");
    if (CORBA::is_nil(m_hostContext))
      {
		return false;
      }
	
    return true;
  }
  
  
  bool RtcNaming::createManagerContext(const std::string& id)
  {
    if (CORBA::is_nil(m_hostContext))
      {
		return false;
      }
	m_mngrName = id;
    m_mngrContext = createContext(m_hostContext, id, "mgr_cxt");
    if (CORBA::is_nil(m_mngrContext))
      {
		return false;
      }
	
    return true;
  }
  
  
  bool RtcNaming::createCategoryContext(const std::string& category)
  {
	ACE_TRACE("RtcNaming::createCategoryContext()");

    if (CORBA::is_nil(m_mngrContext))
      {
		return false;
      }
	
    //! Create naming context of "Category" on the name server.
    if (m_cateContext.find(category) == m_cateContext.end())
      {
		CosNaming::NamingContextExt_var tmpContext;
		tmpContext = createContext(m_mngrContext, category, "cate_cxt");
		if (CORBA::is_nil(tmpContext))
		  {
			return false;
		  }
		m_cateContext[category] = tmpContext;
      }
    else 
      {
		return false;
      }
	
    return true;
  }
  
  
  bool RtcNaming::createModuleContext(const std::string& module,
									  const std::string& category)
  {
	ACE_TRACE("RtcNaming::createModuleContext()");

	// If "category" context is not created, create it.
    if (m_cateContext.find(category) == m_cateContext.end())
      {
		bool retval;
		retval = createCategoryContext(category);
		if (retval == false)
		  {
			return false;
		  }
	  }

	// create "module" context under "category" context
	CosNaming::NamingContextExt_var tmpContext;
	tmpContext = createContext(m_cateContext[category], module, "mod_cxt");
		
	if (CORBA::is_nil(tmpContext))
	  {
		return false;
	  }
	m_compContext[category][module] = tmpContext;

    return true;
  }
  
    
  bool RtcNaming::bindObject(CosNaming::NamingContextExt_var context,
							 const std::string& id, const std::string& kind,
							 CORBA::Object_ptr obj)
  {
	ACE_TRACE("RtcNaming::bindObject()");

    CosNaming::Name objectName;
    objectName.length(1);
    objectName[0].id   = CORBA::string_dup(id.c_str());
    objectName[0].kind = CORBA::string_dup(kind.c_str());
	
    try
      { // Bind the context to specified context.
		context->bind(objectName, obj);
      }
    catch (...)
      {
		cerr << "bindObject(): Unknown error" << endl;
		return false;
      }
	
    return true;
  }
  

  bool RtcNaming::bindObjectByFullPath(const std::string& full_path,
									   CORBA::Object_ptr obj)
  {
	ACE_TRACE("RtcNaming::bindObjectByFullPath()");

	// "path"  should not be started with "/"
	std::string path = full_path;

	if (path.find_first_of("/") == (std::string::size_type) 0)
      {
		path.erase(path.begin());
      }
	bindObjectRecursive(m_rootContext, path, obj);

    return true;
  }
  
  
  bool RtcNaming::bindComponent(const std::string& component, 
								const std::string& module,
								const std::string& category,
								CORBA::Object_ptr obj)
  {
	ACE_TRACE("RtcNaming::bindComponent()");

	if (!createModuleContext(module, category))
	  {
		return false;
	  }

	return bindObject(m_compContext[category][module], component, "rtc", obj);
  }
  
  
  bool RtcNaming::bindManager(const std::string& id, CORBA::Object_ptr obj)
  {
	ACE_TRACE("RtcNaming::bindManager()");

    if (CORBA::is_nil(m_mngrContext))
      {
		if (!createManagerContext(id))
		  {
			return false;
		  }
      }
	
    return bindObject(m_mngrContext, id, "mgr", obj);
  }
  
  
  
  //============================================================
  // << Destroy and Unbind methods >>
  //============================================================
  
  
  bool RtcNaming::destroyHostContext()
  {
	ACE_TRACE("RtcNaming::destroyHostContext()");
	bool ret = destroyRecursive(m_hostContext);
	CosNaming::Name hostName;
    hostName.length(1);
    hostName[0].id   = CORBA::string_dup(m_hostName.c_str());
    hostName[0].kind = CORBA::string_dup("host_cxt");
	m_rootContext->unbind(hostName);
    return ret;
  }
  
  
  bool RtcNaming::destroyManagerContext()
  {
	ACE_TRACE("RtcNaming::destroyManagerContext()");
	bool ret = destroyRecursive(m_mngrContext);

	CosNaming::Name mngrName;
    mngrName.length(1);
    mngrName[0].id   = CORBA::string_dup(m_mngrName.c_str());
    mngrName[0].kind = CORBA::string_dup("mgr_cxt");

	m_hostContext->unbind(mngrName);
    return ret;
  }
  
  
  bool RtcNaming::destroyCategoryContext(const std::string& id)
  {
	ACE_TRACE("RtcNaming::destroyCategoryContext()");

    return destroyRecursive(m_cateContext[id]);
  }
  
  
  bool RtcNaming::destroyModuleContext(const std::string& module,
									   const std::string& category)
  {
	ACE_TRACE("RtcNaming::destroyModuleContext()");

    return destroyRecursive(m_compContext[category][module]);
  }
  
  
  bool RtcNaming::unbindObject(CosNaming::NamingContextExt_var context,
							   const std::string& id, const std::string& kind)
  {
	ACE_TRACE("RtcNaming::unbindObject()");

    CosNaming::Name objectName;
    objectName.length(1);
    objectName[0].id   = CORBA::string_dup(id.c_str());
    objectName[0].kind = CORBA::string_dup(kind.c_str());
    try
      {
		context->unbind(objectName);
      }
    catch (...)
      {
		cerr << "" << std::endl;
		cerr << id << " " << kind << std::endl;
		cerr << "unbindObject(): Unknown error" << id << " " << kind << endl;
		return false;
      }
	
    return true;
  }
  

  bool RtcNaming::unbindObjectByFullPath(const std::string& full_path)
  {
	ACE_TRACE("RtcNaming::unbindObjectByFullPath()");

	RtcNameComponent name(full_path);
	int length = name.length();

	CosNaming::Name tmp;
	try
	  {
		for (int i = 0; i < length; i++)
		  {
			CORBA::Object_var obj = m_rootContext->resolve(name.get());
			CosNaming::NamingContextExt_var context;
			try
			  {
				context = CosNaming::NamingContextExt::_narrow(obj);

				// カレントコンテキストからバインディングリスト取得
				CosNaming::BindingList_var bl;
				CosNaming::BindingIterator_var bi;
				context->list(m_bindListNum, bl, bi);
				if (bl->length() == 0)
				  {
					context->destroy();
					m_rootContext->unbind(name.get());
				  }
				else
				  {
					return false;
				  }
				
			  }
			catch (...)
			  {
				if (CORBA::is_nil(context))
				  {
					m_rootContext->unbind(name.get());
				  }
			  }					
			tmp = name.pop();
		  }
	  }
	catch (...)
	  {
		std::cout << "Unbind exception" << std::endl;
		return false;
	  }
	return true;
  }


  bool RtcNaming::unbindLocalComponent(const std::string category,
									   const std::string module,
									   const std::string instance)
  {
	std::string id, kind;
	nodeToIdKind(instance, id, kind);
	kind = "rtc";

	if (m_compContext.count(category) > 0 &&
		m_compContext[category].count(module) > 0)
	  {
		unbindObject(m_compContext[category][module], id, kind);
	  }
	else
	  {
		return false;
	  }
	return true;
  }


  
  //============================================================
  // << Find methods >>
  //============================================================
  
  bool RtcNaming::findHostContext(const std::string& id_seq,
								  ContextList& context)
  {
	ACE_TRACE("RtcNaming::findHostContext()");

    const std::string path(makeFullPath(id_seq, HOST_CTXT_LEVEL));
    findContextRecursive(m_rootContext,
						 path,
						 context);
    return true;
  }
  
  
  bool RtcNaming::findCategoryContext(const std::string& id_seq, 
									  ContextList& context)
  {
	ACE_TRACE("RtcNaming::findCategoryContext()");

    const std::string path(makeFullPath(id_seq, CATEGORY_CTXT_LEVEL));
    findContextRecursive(m_rootContext,
						 path,
						 context);
    return true;
  }
  
  
  bool RtcNaming::findModuleContext(const std::string& id_seq,
									   ContextList& context)
  {
	ACE_TRACE("RtcNaming::findModuleContext()");

    const std::string path(makeFullPath(id_seq, MODULE_CTXT_LEVEL));
    findContextRecursive(m_rootContext,
						 path,
						 context);
    return true;
  }
  
  
  bool RtcNaming::findManagerContext(const std::string& id_seq,
									 ContextList& context)
  {
	ACE_TRACE("RtcNaming::findManagerContext()");

    const std::string path(makeFullPath(id_seq, MANAGER_CTXT_LEVEL));
    findContextRecursive(m_rootContext,
						 path,
						 context);
    return true;
  }
  
  
  bool RtcNaming::findManager(std::string& id_seq,
							  ObjectList& objects)
  {
	ACE_TRACE("RtcNaming::findManager()");

    const std::string path(makeFullPath(id_seq, MANAGER_LEVEL));
    findObjectsRecursive(m_rootContext,
						 path,
						 objects);
    return true;
  }
  
  
  bool RtcNaming::findComponents(const std::string& id_seq,
								 ObjectList& objects)
  {
	ACE_TRACE("RtcNaming::findComponents()");
    const std::string path(makeFullPath(id_seq, COMPONENT_LEVEL));
    findObjectsRecursive(m_rootContext,
						 path,
						 objects);
    return true;
  }
  
  
  //============================================================
  // << Protected members >>
  //============================================================
  
  bool RtcNaming::destroyRecursive(CosNaming::NamingContextExt_var context)
  {
	ACE_TRACE("RtcNaming::destroyRecursive()");

    CosNaming::BindingList_var bl;
    CosNaming::BindingIterator_var bi;
    context->list(m_bindListNum, bl, bi);
	
    for (int i = 0; i < bl->length(); i++)
      {
		// Binding name (id, kind)
		std::string pId   = (const char*) bl[i].binding_name[0].id;
		std::string pKind = (const char*) bl[i].binding_name[0].kind;

		if (bl[i].binding_type == CosNaming::nobject)
		  { // If Object is object, unbind it.
			try
			  {
				context->unbind(bl[i].binding_name);
			  }
			catch (...)
			  {
				cerr << "Hoge? excaption was cought: unbind()." << endl;
			  }
		  }
		else if (bl[i].binding_type == CosNaming::ncontext)
		  { // If Object is context, destroy recursive.
			CORBA::Object_ptr obj = context->resolve(bl[i].binding_name);
			CosNaming::NamingContextExt_var testContext;
			testContext = CosNaming::NamingContextExt::_narrow(obj);
			// Recursive function call
			destroyRecursive(testContext);
			try
			  {
				context->unbind(bl[i].binding_name);
				testContext->destroy();
			  }
			catch (CosNaming::NamingContext::NotFound e)
			  {
				cerr << "Exception cought. Unbinding Naming Context. ";
				cerr << "Not Found: " << bl[i].binding_name[0].id;
				cerr << "|" << bl[i].binding_name[0].kind << endl;
			  }
			catch (CosNaming::NamingContext::CannotProceed e)
			  {
				cerr << "Exception cought. Unbinding Naming Context. ";
				cerr << "Cannot Proceed." << endl;
			  }
			catch (CosNaming::NamingContext::InvalidName e)
			  {
				cerr << "Exception cought. Unbinding Naming Context. ";
				cerr << "Invalid Name: " << bl[i].binding_name[0].id;
				cerr << "|" << bl[i].binding_name[0].kind << endl;
			  }
			catch (...)
			  {
				;
			  }
		  }
		else
		  {
			cerr << "Invalid Name binding type: " << pId << endl;
		  }
      }

	//	context->destroy();
	return true;
  }
  

  
  void RtcNaming::findObjectsRecursive(CosNaming::NamingContextExt_ptr context,
									   const std::string& path,
									   ObjectList& obj_list)
  {
	ACE_TRACE("RtcNaming::findObjectsRecursive()");
    std::string node;
    std::string remain;
    pickupNode(path, node, remain);

    std::string kind;
    std::string id;
    nodeToIdKindAny(node, id, kind);
	
    // regex パターンを生成
    boost::regex id_regex(id), kind_regex(kind);
    boost::smatch id_results, kind_results;
	
    // カレントコンテキストからバインディングリスト取得
    CosNaming::BindingList_var bl;
    CosNaming::BindingIterator_var bi;
    if (CORBA::is_nil(context))
	  {
		return;
	  }
	context->list(m_bindListNum, bl, bi);
	
    for (unsigned int i = 0; i < bl->length(); i++)
      {
		// バインディング名 (id, kind)
		std::string pId   = (const char*)(bl[i].binding_name[0]).id;
		std::string pKind = (const char*)(bl[i].binding_name[0]).kind;

		if (regex_match(pId,   id_results,   id_regex) && 
			regex_match(pKind, kind_results, kind_regex))
		  { // id と kind がマッチ
			CORBA::Object_ptr obj = context->resolve(bl[i].binding_name);
			
			// If Object is object, store the object to object list
			if (bl[i].binding_type == CosNaming::nobject)
			  {
				if (remain.size() == 0)
				  {
					obj_list.push_back(obj);
				  }

			  }
			// if Object is naming context, find recursively.
			else if (bl[i].binding_type == CosNaming::ncontext)
			  {
				// Recursive function call
				CosNaming::NamingContextExt_var next_context;
				next_context = CosNaming::NamingContextExt::_narrow(obj);
				
				if (!CORBA::is_nil(next_context))
				  {
					findObjectsRecursive(next_context, remain, obj_list);
				  }
			  }
			
		  }
      }
    return;
  }
  
  
  void RtcNaming::findContextRecursive(CosNaming::NamingContextExt_var context,
									   const std::string& path,
									   ContextList& context_list)
  {
	ACE_TRACE("RtcNaming::findContextRecursive()");

    std::string node;
    std::string remain;
    pickupNode(path, node, remain);
	
    std::string kind;
    std::string id;
    nodeToIdKindAny(node, id, kind);
	
    // regex パターンを生成
    boost::regex id_regex(id), kind_regex(kind);
    boost::smatch id_results, kind_results;
	
    // カレントコンテキストからバインディングリスト取得
    CosNaming::BindingList_var bl;
    CosNaming::BindingIterator_var bi;
    context->list(m_bindListNum, bl, bi);
	
    for (unsigned int i = 0; i < bl->length(); i++)
      {
		// バインディング名 (id, kind)
		std::string pId   = (const char*)(bl[i].binding_name[0]).id;
		std::string pKind = (const char*)(bl[i].binding_name[0]).kind;

		if (regex_match(pId,   id_results,   id_regex) && 
			regex_match(pKind, kind_results, kind_regex))
		  { // id と kind がマッチ
			
			CORBA::Object_ptr Object = context->resolve(bl[i].binding_name);
			
			if (bl[i].binding_type == CosNaming::ncontext)
			  {
				// Recursive function call
				CosNaming::NamingContextExt_var next_context;
				next_context = CosNaming::NamingContextExt::_narrow(Object);
				
				if (!CORBA::is_nil(next_context) && remain.size() == 0)
				  {
					context_list.push_back(next_context);
				  } 
				else if (!CORBA::is_nil(next_context) && remain.size() > 0)
				  {
					findContextRecursive(next_context, remain, context_list);
				  }
			  }
			
		  }
      }
    return;
  }
  
  void RtcNaming::bindObjectRecursive(CosNaming::NamingContextExt_var context,
									  const std::string& path,
									  CORBA::Object_ptr obj)
  {
	ACE_TRACE("RtcNaming::findContextRecursive()");

    std::string node;
    std::string remain;
    pickupNode(path, node, remain);
    std::string kind;
    std::string id;
    nodeToIdKind(node, id, kind);

	CosNaming::Name_var name = new CosNaming::Name(1);
	name->length(1);
	name[0].id   = CORBA::string_dup(id.c_str());
	name[0].kind = CORBA::string_dup(kind.c_str());
	
	if (remain.size() == 0)
	  {
		try
		  {
			context->rebind(name, obj);
			return;
		  }
		catch (...)
		  {
			//cerr << "RtcNaming::bindObjectRecursive: Exception" << endl;
		  }
	  }
	else
	  {
		CosNaming::NamingContextExt_var next_cxt;
		CosNaming::NamingContext_var cxt;
		try
		  {
			cxt = context->bind_new_context(name);
			next_cxt = CosNaming::NamingContextExt::_narrow(cxt);
		  }
		catch (const CosNaming::NamingContext::AlreadyBound& e)
		  {
			CORBA::Object_var obj = context->resolve(name);
			next_cxt = CosNaming::NamingContextExt::_narrow(obj);
			if (CORBA::is_nil(next_cxt)) 
			  {
				cerr << "bindObjectRecursive(): next_cxt is nil!!" << endl;
				return;
			  }
		  }
		bindObjectRecursive(next_cxt, remain, obj);
	  }
    return;
  }
  
  
  
  //============================================================
  // << Private members >>
  //============================================================
  
  
  /*------------------------------------------------------------
   * Split string with a delimiter
   *------------------------------------------------------------*/
  int RtcNaming::split(const std::string& input, const std::string& delimiter,
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
  
  
  /*------------------------------------------------------------
   * Convert the given path to full path
   *
   * @param path path which have to converted to full path
   * @param level compensation level
   *
   * If given path is "hoge/munya" and level is 5,
   * it is converted to "*./*./*./hoge/munya".
   *------------------------------------------------------------*/
  std::string RtcNaming::makeFullPath(std::string path, int level)
  {
    std::string::size_type pos(0);
    std::string::size_type pos_end(path.size());
	
    // If first character is "/", path is fully qualified.
    // Then erase root "/" and return path immediately.
    if (path.find_first_of("/") == (std::string::size_type) 0)
      {
		path.erase(path.begin());
		return path;
      }
	
    int num(0);
    std::string comp_path(".*/");
	
    while (pos < pos_end)
      {
		pos = path.find_first_of("/", pos);
		if (pos == std::string::npos) break;
		++pos;
		++num;
      }
	
    --level;
    for (int i = 0; i < level - num; ++i)
      {
		path.insert(0, comp_path);
      }
    return path;
  }
  
  
  bool RtcNaming::pickupNode(const std::string& path, std::string& node, std::string& remain)
  {
    // path の先頭と残りを取り出す。
    std::string::size_type pos = path.find_first_of("/");
    if (pos == std::string::npos)
      { // this is leaf node
		node = path;
		remain = "";
      }
    else
      {
		node = path.substr(0, pos);
		remain = path.substr(pos + 1);
      }

  }
  
  
  
  void RtcNaming::nodeToIdKindAny(const std::string& node, std::string& id,
							   std::string& kind)
  {
    std::string::size_type pos;
    pos = node.find_first_of("|");
	
    if (pos == std::string::npos)
      {
		id = node;
		kind = ".*"; // kind がなければ任意のkindにマッチ
      }
    else 
      {
		id = node.substr(0, pos);
		kind = node.substr(pos + 1);
      }
  }
  
  void RtcNaming::nodeToIdKind(const std::string& node, std::string& id,
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
  
  
}; // end of namespace RTM
