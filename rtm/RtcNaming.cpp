// -*- C++ -*-
/*!
 * @file RtcNaming.cpp
 * @brief RT component naming class
 * @date $Date: 2006-09-11 18:26:08 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcNaming.cpp,v 1.3 2006-09-11 18:26:08 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2005/05/16 06:28:35  n-ando
 * - ACE_HAS_WINSOCK2 was defined for Windows port.
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#ifdef WIN32
#define ACE_HAS_WINSOCK2 0
#endif //WIN32

#include <iostream>
#include <boost/regex.hpp>

#include "rtm/RtcNaming.h"
//#include "rtm/RtcNameComponent.h"


namespace RTM
{
  RtcCorbaNaming::RtcCorbaNaming(CORBA::ORB_ptr orb,
				 const char* name_server)
    : m_varORB(orb), m_nameServer(name_server),
      m_rootContext(CosNaming::NamingContextExt::_nil()),
      m_blLength(100)
  {
    CORBA::Object_var obj;
    obj = orb->string_to_object(m_nameServer.c_str());
    m_rootContext = CosNaming::NamingContextExt::_narrow(obj);
    if (CORBA::is_nil(m_rootContext)) throw std::bad_alloc();
  }
  
  
  /*!
   * @if jp
   * @brief Object を bind する
   * @else
   * @brief Bind object on specified name component position
   * @endif
   */
  void RtcCorbaNaming::bind(const CosNaming::Name& name, CORBA::Object_ptr obj,
			    const bool force)
    throw(NotFound, CannotProceed, InvalidName, AlreadyBound)
  {
    try
      {
	m_rootContext->bind(name, obj);
      }
    catch (NotFound& e)
      {
	force ? bindRecursive(m_rootContext, name, obj) : throw e;
      }
    catch (CannotProceed& e)
      {
	force ? bindRecursive(e.cxt, e.rest_of_name, obj) : throw e;
      }
  }
  
  
  /*!
   * @if jp
   * @brief Object を bind する
   * @else
   * @brief Bind object on specified string name position
   * @endif
   */
  void RtcCorbaNaming::bindByString(const char* string_name, CORBA::Object_ptr obj,
			    const bool force)
    throw(NotFound, CannotProceed, InvalidName, AlreadyBound)
  {
    this->bind(toName(string_name), obj, force);
  }
  
  
  /*!
   * @if jp
   * @brief 途中のコンテキストを再帰的に bind しながら Object を bind する
   * @else
   * @brief Bind intermediate context recursively and bind object
   * @endif
   */
  void RtcCorbaNaming::bindRecursive(CosNaming::NamingContext_ptr context,
				     const CosNaming::Name& name,
				     CORBA::Object_ptr obj)
    throw(CannotProceed, InvalidName, AlreadyBound)
  {
    CORBA::ULong len(name.length());
    CosNaming::NamingContext_var cxt;
    cxt = CosNaming::NamingContext::_duplicate(context);
    
    for (CORBA::ULong i = 0; i < len; ++i)
      {
	if (i == (len - 1))
	  { // this operation may throw AlreadyBound, 
	    cxt->bind(subName(name, i, i), obj);
	    return;
	  }
	else
	  { // If the context is not a NamingContext, CannotProceed is thrown
	    if (isNamingContext(cxt))
	      cxt = bindOrResolveContext(cxt, subName(name, i, i));
	    else
	      throw CannotProceed(cxt, subName(name, i));
	  }
      }
    return;
  }
  
  
  /*!
   * @if jp
   * @brief Object を rebind する
   * @else
   * @brief Rebind object
   * @endif
   */
  void RtcCorbaNaming::rebind(const CosNaming::Name& name,
			      CORBA::Object_ptr obj,
			      const bool force)
    throw(NotFound, CannotProceed, InvalidName)
  {
    try
      {
	m_rootContext->rebind(name, obj);
      }
    catch (NotFound& e)
      {
	force ? rebindRecursive(m_rootContext, name, obj) : throw e;
      }
    catch (CannotProceed& e)
      {
	force ? rebindRecursive(e.cxt, e.rest_of_name, obj) : throw e;
      }
  }
  
  
  /*!
   * @if jp
   * @brief Object を rebind する
   * @else
   * @brief Rebind object
   * @endif
   */
  void RtcCorbaNaming::rebindByString(const char* string_name,
				      CORBA::Object_ptr obj,
				      const bool force)
    throw(NotFound, CannotProceed, InvalidName)
  {
    rebind(toName(string_name), obj, force);
  }
  
  
  /*!
   * @if jp
   * @brief Object を rebind する
   * @else
   * @brief Rebind object
   * @endif
   */
  void RtcCorbaNaming::rebindRecursive(CosNaming::NamingContext_ptr context,
				       const CosNaming::Name& name,
				       CORBA::Object_ptr obj)
    throw(CannotProceed, InvalidName)
  {
    CORBA::ULong len(name.length());
    CosNaming::NamingContext_var cxt;
    cxt = CosNaming::NamingContext::_duplicate(context);
    
    for (CORBA::ULong i = 0; i < len; ++i)
      {
	if (i == (len - 1))
	  {
	    cxt->rebind(subName(name, i, i), obj);
	    return;
	  }
	else
	  { // If the context is not a NamingContext, CannotProceed is thrown
	    if (isNamingContext(cxt))
	      cxt = cxt->bind_new_context(subName(name, i, i));
	    else
	      throw CannotProceed(cxt, subName(name, i));
	  }
      }
    return;
  }
  
  
  /*!
   * @if jp
   * @brief NamingContext を bind する
   * @else
   * @brief Bind NamingContext
   * @endif
   */
  void RtcCorbaNaming::bindContext(const CosNaming::Name& name,
				   CosNaming::NamingContext_ptr name_cxt,
				   const bool force)
    throw(NotFound, CannotProceed, InvalidName, AlreadyBound)
  {
    bind(name, name_cxt, force);
  }
  
  
  /*!
   * @if jp
   * @brief NamingContext を bind する
   * @else
   * @brief Bind NamingContext
   * @endif
   */
  void RtcCorbaNaming::bindContext(const char* string_name,
				   CosNaming::NamingContext_ptr name_cxt,
				   const bool force)
    throw(NotFound, CannotProceed, InvalidName, AlreadyBound)
  {
    bindContext(toName(string_name), name_cxt, force);
  }
  
  
  /*!
   * @if jp
   * @brief 途中のコンテキストを再帰的に bind し NamingContext を bind する
   * @else
   * @brief Rebind object
   * @endif
   */
  void
  RtcCorbaNaming::bindContextRecursive(CosNaming::NamingContext_ptr context,
				       const CosNaming::Name& name,
				       CosNaming::NamingContext_ptr name_cxt)
  {
    bindRecursive(context, name, name_cxt);
    return;
  }
  
  
  /*!
   * @if jp
   * @brief NamingContext を rebind する
   * @else
   * @brief Rebind NamingContext
   * @endif
   */
  void RtcCorbaNaming::rebindContext(const CosNaming::Name& name,
				     CosNaming::NamingContext_ptr name_cxt,
				     const bool force)
    throw(NotFound, CannotProceed, InvalidName)
  {
    rebind(name, name_cxt, force);
    return;
  }
  
  
  /*!
   * @if jp
   * @brief NamingContext を rebind する
   * @else
   * @brief Rebind NamingContext
   * @endif
   */
  void RtcCorbaNaming::rebindContext(const char* string_name,
				     CosNaming::NamingContext_ptr name_cxt,
				     const bool force)
    throw(NotFound, CannotProceed, InvalidName)
  {
    rebindContext(toName(string_name), name_cxt, force);
  }
  
  
  /*!
   * @if jp
   * @brief 途中のコンテキストを再帰的に rebind し NamingContext を rebind する
   * @else
   * @brief Create or resolve intermediate context and rebind NamingContext 
   * @endif
   */
  void
  RtcCorbaNaming::rebindContextRecursive(CosNaming::NamingContext_ptr context,
					 const CosNaming::Name& name,
					 CosNaming::NamingContext_ptr name_cxt)
  {
    rebindRecursive(context, name, name_cxt);
    return;
  }
  
  
  /*!
   * @if jp
   * @brief 与えられた NameComponent にバインドされている Object を返す
   * @else
   * @brief Return object bound on the specified NameComponent
   * @endif
   */
  CORBA::Object_ptr RtcCorbaNaming::resolve(const CosNaming::Name& name)
    throw(NotFound, CannotProceed, InvalidName)
  { 
    return m_rootContext->resolve(name);
  }
  
  
  /*!
   * @if jp
   * @brief 与えられた NameComponent にバインドされている Object を返す
   * @else
   * @brief Return object bound on the specified NameComponent
   * @endif
   */
  CORBA::Object_ptr RtcCorbaNaming::resolve(const char* string_name)
    throw(NotFound, CannotProceed, InvalidName)
  { 
    return resolve(toName(string_name));
  }
  
  
  /*!
   * @if jp
   * @brief 与えられた NameComponent のバインディングを削除する
   * @else
   * @brief Unbind a binding specified by NameComponent
   * @endif
   */   
  void RtcCorbaNaming::unbind(const CosNaming::Name& name)
    throw(NotFound, CannotProceed, InvalidName)
  {
    m_rootContext->unbind(name);
  }
  
  
  /*!
   * @if jp
   * @brief 与えられた NameComponent のバインディングを削除する
   * @else
   * @brief Unbind a binding specified by NameComponent
   * @endif
   */
  void RtcCorbaNaming::unbind(const char* string_name)
    throw(NotFound, CannotProceed, InvalidName)
  {
    unbind(toName(string_name));
  }
  
  
  /*!
   * @if jp
   * @brief 新しいコンテキストを生成する
   * @else
   * @brief Create new NamingContext
   * @endif
   */
  CosNaming::NamingContext_ptr RtcCorbaNaming::newContext()
  {
    return m_rootContext->new_context();
  }
  
  
  /*!
   * @if jp
   * @brief 新しいコンテキストを bind する
   * @else
   * pbrief Bind new namingContext
   * @endif
   */
  CosNaming::NamingContext_ptr
  RtcCorbaNaming::bindNewContext(const CosNaming::Name& name, bool force)
    throw(NotFound, CannotProceed, InvalidName, AlreadyBound)
  {
    try
      {
	return m_rootContext->bind_new_context(name);
      }
    catch (NotFound& e)
      {
	force ? bindRecursive(m_rootContext, name, newContext()) : throw e;
      }
    catch (CannotProceed& e)
      {
	force ? bindRecursive(e.cxt, e.rest_of_name, newContext()) : throw e;
      }
    return CosNaming::NamingContext::_nil();
  }
  
  
  /*!
   * @if jp
   * @brief 新しいコンテキストを bind する
   * @else
   * pbrief Bind new namingContext
   * @endif
   */
  CosNaming::NamingContext_ptr
  RtcCorbaNaming::bindNewContext(const char* string_name, bool force)
    throw(NotFound, CannotProceed, InvalidName, AlreadyBound)
  {
    return bindNewContext(toName(string_name));
  }
  
  
  /*!
   * @if jp
   * @brief NamingContext を非アクティブ化する
   * @else
   * @brief Destroy the naming context
   * @endif
   */
  void RtcCorbaNaming::destroy(CosNaming::NamingContext_ptr context)
    throw(NotEmpty)
  {
    context->destroy();
  }
  
  
  /*!
   * @if jp
   * @brief NamingContext を再帰的に下って非アクティブ化する
   * @else
   * @brief Destroy the naming context recursively
   * @endif
   */
  void RtcCorbaNaming::destroyRecursive(CosNaming::NamingContext_ptr context)
    throw(NotEmpty, NotFound, CannotProceed, InvalidName)
  {
    CosNaming::BindingList_var     bl;
    CosNaming::BindingIterator_var bi;
    CORBA::Boolean cont(true);
    
    context->list(m_blLength, bl, bi);
    
    while (cont)
      {
	CORBA::ULong len(bl->length());
	
	for (CORBA::ULong i = 0; i < len; ++i)
	  {
	    if (bl[i].binding_type == CosNaming::ncontext)
	      {	// If Object is context, destroy recursive.
		CosNaming::NamingContext_var next_context;
		next_context = CosNaming::NamingContext::
		  _narrow(context->resolve(bl[i].binding_name));
		
		// Recursive function call
		destroyRecursive(next_context); // +++ Recursive call +++
		context->unbind(bl[i].binding_name);
		next_context->destroy();
	      }
	    else if (bl[i].binding_type == CosNaming::nobject)
	      {	// If Object is object, unbind it.
		context->unbind(bl[i].binding_name);
	      }
	    else assert(0); // never comes here
	  }
	
	// no more binding -> do-while loop will be finished
	if (CORBA::is_nil(bi)) cont = false;
	else bi->next_n(m_blLength, bl);
      }
    
    if (!CORBA::is_nil(bi)) bi->destroy();
    return;
  }
  
  
  /*!
   * @if jp
   * @brief すべての Binding を削除する
   * @else
   * @brief Destroy all binding
   * @endif
   */
  void RtcCorbaNaming::clearAll()
  {
    destroyRecursive(m_rootContext);
  }
  
  
  /*!
   * @if jp
   * @brief 与えられた NamingContext の Binding を取得する
   * @else
   * @brief Get Binding on the NamingContextDestroy all binding
   * @endif
   */
  void RtcCorbaNaming::list(CosNaming::NamingContext_ptr name_cxt,
			    unsigned long how_many,
			    CosNaming::BindingList_var& bl,
			    CosNaming::BindingIterator_var& bi)
  {
    name_cxt->list(how_many, bl, bi);
  }
  
  
  /*!
   * @if jp
   * @brief 与えられた NameComponent の文字列表現を返す
   * @else
   * @brief Get string representation of given NameComponent
   * @endif
   */
  char* RtcCorbaNaming::toString(const CosNaming::Name& name)
    throw(InvalidName)
  {
    if (name.length() == 0)
      throw InvalidName();
    
    CORBA::ULong slen = 0;
    slen = getNameLength(name);
    
    char* string_name = CORBA::string_alloc(slen);
    nameToString(name, string_name, slen);
    
    return string_name;
  }
  
  
  /*!
   * @if jp
   * @brief 与えられた文字列表現を NameComponent に分解する
   * @else
   * @brief Get NameComponent from gien string name representation
   * @endif
   */
  CosNaming::Name RtcCorbaNaming::toName(const char* sname)
    throw(InvalidName)
  {
    if (!sname)         throw InvalidName();
    if (*sname == '\0') throw InvalidName();
    
    std::string string_name(sname);
    std::vector<std::string> name_comps;
    
    // String name should include 1 or more names
    CORBA::ULong nc_length = 0;
    nc_length = split(string_name, std::string("/"), name_comps);
    if (!(nc_length > 0)) throw InvalidName();
    
    // Name components are allocated
    CosNaming::Name*    namep = new CosNaming::Name;
    CosNaming::Name_var name(namep);
    name->length(nc_length);
    
    // Insert id and kind to name components
    for (CORBA::ULong i = 0; i < nc_length; ++i)
      {
	std::vector<std::string> id_kind;
	split(name_comps[i], std::string("."), id_kind);
	
	if (id_kind.size() == 2)
	  {
	    name[i].id   = CORBA::string_dup(id_kind[0].c_str());
	    name[i].kind = id_kind[1].c_str();
	  }
	else if (id_kind.size() == 1)
	  {
	    name[i].id   = id_kind[0].c_str();
	    name[i].kind = "";
	  }
	else
	  {
	    throw InvalidName();
	  }
      }
    return name;
  }
  
  
  /*!
   * @if jp
   * @brief 与えられた addre と string_name から URL表現を取得する
   * @else
   * @brief Get URL representation from given addr and string_name
   * @endif
   */
  char* RtcCorbaNaming::toUrl(char* addr, char* string_name)
    throw(InvalidAddress, InvalidName)
  {
    return m_rootContext->to_url(addr, string_name);
  }
  
  
  /*!
   * @if jp
   * @brief 与えられた文字列表現を resolve しオブジェクトを返す
   * @else
   * @brief Resolve from name of string representation and get object 
   * @endif
   */
  CORBA::Object_ptr RtcCorbaNaming::resolveStr(const char* string_name)
    throw(NotFound, CannotProceed, InvalidName, AlreadyBound)
  {
    return resolve(string_name);
  }
  
  
  
  //======================================================================
  // Util functions
  //======================================================================
  /*!
   * @if jp
   * @brief 
   * @else
   * @brief 
   * @endif
   */
  CORBA::Object_ptr
  RtcCorbaNaming::bindOrResolve(CosNaming::NamingContext_ptr context,
				const CosNaming::Name& name,
				CORBA::Object_ptr obj)
  {
    try
      {
	context->bind(name, obj);
	return obj;
      }
    catch (AlreadyBound& e)
      {
	return context->resolve(name);
      }
    return CORBA::Object::_nil();
  }
  
  
  /*!
   * @if jp
   * @brief 
   * @else
   * @brief 
   * @endif
   */
  CosNaming::NamingContext_ptr
  RtcCorbaNaming::bindOrResolveContext(CosNaming::NamingContext_ptr context,
				       const CosNaming::Name& name,
				       CosNaming::NamingContext_ptr new_context)
  {
    return CosNaming::NamingContext::_narrow(bindOrResolve(context, name, new_context));
  }
  
  
  /*!
   * @if jp
   * @brief 
   * @else
   * @brief 
   * @endif
   */
  CosNaming::NamingContext_ptr
  RtcCorbaNaming::bindOrResolveContext(CosNaming::NamingContext_ptr context,
				       const CosNaming::Name& name)
  {
    return bindOrResolveContext(context, name, newContext());
  }
  
  
  
  /*!
   * @if jp
   * @brief 
   * @else
   * @brief 
   * @endif
   */
  const char* RtcCorbaNaming::getNameServer()
  {
    return m_nameServer.c_str();
  }
  
  
  /*!
   * @if jp
   * @brief 
   * @else
   * @brief 
   * @endif
   */
  CosNaming::NamingContext_ptr RtcCorbaNaming::getRootContext()
  {
    return m_rootContext;
  }
  
  
  /*!
   * @if jp
   * @brief 
   * @else
   * @brief 
   * @endif
   */
  bool RtcCorbaNaming::isNamingContext(CORBA::Object_ptr obj)
  {
    CosNaming::NamingContext_var nc;
    nc = CosNaming::NamingContext::_narrow(obj);
    return CORBA::is_nil(nc) ? false : true;
  }
  
  
  /*!
   * @if jp
   * @brief 
   * @else
   * @brief 
   * @endif
   */
  bool RtcCorbaNaming::isNamingContext(const CosNaming::Name& name)
  {
    return isNamingContext(resolve(name));
  }
  
  
  /*!
   * @if jp
   * @brief 
   * @else
   * @brief 
   * @endif
   */
  bool RtcCorbaNaming::isNamingContext(const char* string_name)
  {
    return isNamingContext(resolve(string_name));
  }
  
  
  /*!
   * @if jp
   * @brief 
   * @else
   * @brief 
   * @endif
   */
  CosNaming::Name RtcCorbaNaming::subName(const CosNaming::Name& name,
					  long begin,
					  long end)
  {
    if (end < 0) end = name.length() - 1;
    
    CosNaming::Name sub_name;
    CORBA::ULong sub_len(end - (begin - 1));
    if (sub_len > 0)
      {
	sub_name.length(sub_len);
      }
    else
      {
	sub_name.length(0);
	return sub_name;
      }
    
    for (CORBA::ULong i = 0; i < sub_len; ++i)
      {
	sub_name[i] = name[begin + i];
      }
    return sub_name;
  }
  
  
  
  //------------------------------------------------------------
  // Protected member functions
  //------------------------------------------------------------
  /*!
   * @if jp
   * @brief 
   * @else
   * @brief 
   * @endif
   */
  void RtcCorbaNaming::nameToString(const CosNaming::Name& name,
				    char* string_name,
				    unsigned long slen)
  {
    char* s = string_name;
    for (CORBA::ULong i = 0; i < name.length(); ++i)
      {
	// Copy id to string_name
	for (const char* id = name[i].id; *id != '\0'; ++id)
	  {
	    if (*id == '/' || *id == '.' || *id == '\\') *s++ = '\\';
	    *s++ = *id;
	  }
	// '.' if there is a kind, or no id
	if (((const char*)(name[i].id  ))[0] == '\0' || 
	    ((const char*)(name[i].kind))[0] != '\0')
	  *s++ = '.';
	// Copy kind to string_name
	for (const char* kind = name[i].kind; *kind != '\0'; ++kind)
	  {
	    if (*kind == '/' || *kind == '.' || *kind == '\\')
	      *s++ = '\\';
	    *s++ = *kind;
	  }
	// The end of string_name will be overwritten by '\0'
	*s++ = '/';
      }
    string_name[slen-1] = '\0';
  }
  
  
  /*!
   * @if jp
   * @brief 
   * @else
   * @brief 
   * @endif
   */
  CORBA::ULong RtcCorbaNaming::getNameLength(const CosNaming::Name& name)
  {
    CORBA::ULong slen = 0;
    
    for (CORBA::ULong i = 0; i < name.length(); ++i)
      {
	// Count string length of id(s)
	for (const char* id = name[i].id; *id; ++id)
	  {
	    // Escape character '/', '.', '\' will convert to "\/", "\.", "\\".
	    if (*id == '/' || *id == '.' || *id == '\\') slen++;
	    slen++;
	  }
	// If kind exists, space for '.' is counted
	if (((const char*)(name[i].id  ))[0] == '\0' || 
	    ((const char*)(name[i].kind))[0] != '\0')
	  {
	    slen++;
	  }
	// Count string length of kind(s)
	for (const char* kind = name[i].kind; *kind; kind++)
	  {
	    if (*kind == '/' || *kind == '.' || *kind == '\\') slen++;
	    slen++;
	  }
	// Space for '/' or '\0'
	slen++;
      }
    return slen;
  }
  
  
  /*!
   * @if jp
   * @brief 
   * @else
   * @brief 
   * @endif
   */
  unsigned int RtcCorbaNaming::split(const std::string& input,
				     const std::string& delimiter,
				     std::vector<std::string>& results)
  {
    typedef std::string::size_type size;
    size delim_size = delimiter.size();
    size found_pos(0), begin_pos(0), pre_pos(0), substr_size(0);
    
    if (input.substr(0, delim_size) == delimiter)
      begin_pos = pre_pos = delim_size;
    
    while (1)
      {
      REFIND:
	found_pos = input.find(delimiter, begin_pos);
	if (found_pos == std::string::npos) 
	  {
	    results.push_back(input.substr(pre_pos));
	    break;
	  }
	if ('\\' == input.at(found_pos - 1))
	  {
	    begin_pos = found_pos + delim_size;
	    goto REFIND;
	  }
	
	substr_size = found_pos - pre_pos;
	
	if (substr_size > 0)
	  {
	    results.push_back(input.substr(pre_pos, substr_size));
	  }
	begin_pos = found_pos + delim_size;
	pre_pos   = found_pos + delim_size;
      }
    return results.size();
  }
}; //
