// -*- C++ -*-
/*!
 * @file typemaps_py.i
 * @brief swig typemaps
 * @date $Date: 2005-05-12 09:06:19 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

/*============================================================
 * Basic typemaps
 *============================================================*/
/*!
 * @brief Typemap of command arguments
 */
%typemap(python,in) (int argc, char **argv) {
  
  /* Check if is a list */
  if (PyList_Check($input))
    {
      int i;
      $1 = PyList_Size($input);
      $2 = (char **) malloc(($1+1)*sizeof(char *));
      for (i = 0; i < $1; i++)
		{
		  PyObject *o = PyList_GetItem($input,i);
		  if (PyString_Check(o))
			{
			  $2[i] = PyString_AsString(PyList_GetItem($input,i));
			}
		  else
			{
			  PyErr_SetString(PyExc_TypeError,"list must contain strings");
			  free($2);
			  return NULL;
			}
		}
      $2[i] = 0;
    }
  else 
    {
      PyErr_SetString(PyExc_TypeError,"not a list");
      return NULL;
    }
}

%typemap(python,freearg) (int argc, char **argv) {
  free((char *) $2);
}


/*!
 * @brief Typemap for std::string input
 */
%typemap(python,in) const std::string& InString (::std::string temp)
{
  if (PyString_Check($input))
    {
      temp = std::string(PyString_AsString($input),
			 PyString_Size($input));
      $1 = &temp;
    }
  else
    {
      PyErr_SetString(PyExc_TypeError,
		      "argument have to be string");
      return NULL;
    }
}

%typemap(python,in) std::string * {
  if (PyString_Check ($1))
  {
    $result = new String((char *)PyString_AsString($1));
  }
  else
  {
    PyErr_SetString (PyExc_TypeError, "not a String");
    return NULL;
  }
}

%typemap (python, freearg) std::string * {
  if (&EMPTY_STRING != $1)
  {
    delete $1;
  }
}

%typemap(python,argout) std::string& OutString
{
  //  $result = PyString_FromSingAndSize($1->data(), $1->length());
}

/*!
 * @brief Typemap for std::string output
 */

%typemap(python,in,numinputs=0) std::string& OutString (std::string temp)
{
  //  $result = PyString_FromSingAndSize($1->data(), $1->length());
  $1 = &temp;
}

%typemap(python,in,numinputs=0) char* OutChar
{
}
/*
  %typemap(python,argout) std::string& OutString
  {
  PyObject *o1, *o2; // o1: RtcBase*, o2: string&
  o1 = PyString_FromStringAndSize((*$1).c_str(), (*$1).size());
  
  if ((!$result) || ($result == Py_None))
  {
  return NULL;
  }
  else
  {
  if (!PyTuple_Check($result))
  {
  PyObject *o2 = $result;
  $result = PyTuple_New(2);
  PyTuple_SetItem($result,0,o2);
  PyTuple_SetItem($result,1,o1);
  Py_DECREF(o1);
  Py_DECREF(o2);
  }
  }
  }
*/

%typemap(python,out) std::string {
  $result = PyString_FromStringAndSize($1.data(), $1.size());
}

//%typemap(python, out) OutString, std::string 
//{
//  $result = PyString_FromStringAndSize($1.data(), $1.length());
//}





/*============================================================
 * SWIG typemaps for RTCBase
 *============================================================*/
/*!
 * @brief Typemap of RTCBase vector
 * 
 * RTCBase_ptr vector -> Python object: SWIGTYPE_p_RTM__RTCBase
 */
%typemap(python,out) std::vector<RTM::RTCBase_ptr>
{
  std::vector<RTM::RTCBase_ptr>::iterator it;
  std::vector<RTM::RTCBase_ptr>::iterator it_end;
  
  it = $1.begin();
  it_end = $1.end();
  $result = PyList_New($1.size());
  int i(0);
  while (it != it_end)
    {
      PyObject* x;
      // Convert pointer: C++ RTCBase_ptr -> Python pointer
      x = SWIG_NewPointerObj(RTCBase::_duplicate(*it),
			     SWIGTYPE_p_RTM__RTCBase, 0);
      PyList_SetItem($result, i, x);
	  // DECREF すると動かない：メモリリークの可能性あり
	  //      Py_DECREF(x);
      ++i;
      ++it;
    }
}


/*!
 * @brief Typemap of RTComponentList
 * 
 * RTCBase_ptr list -> Python object: SWIGTYPE_p_RTM__RTCBase
 */
%typemap(python,out) RTM::RTComponentList *
{
  int size = $1->length();

  $result = PyList_New(size);

  for (int i = 0; i < size; ++i)
    {
      PyObject* x;
      // Convert pointer: C++ RTCBase_ptr -> Python pointer
      x = SWIG_NewPointerObj(RTComponent::_duplicate((*$1)[i]),
							 SWIGTYPE_p_RTM__RTCBase, 0);
      PyList_SetItem($result, i, x);
	  // DECREF すると動かない：メモリリークの可能性あり
	  //      Py_DECREF(x);
    }
}

/*!
 * @brief Typemap of RTCBaseList
 * 
 * RTCBase_ptr list -> Python object: SWIGTYPE_p_RTM__RTCBase
 */
%typemap(python,out) RTM::RTCBaseList *
{
  int size = $1->length();

  $result = PyList_New(size);

  for (int i = 0; i < size; ++i)
    {
      PyObject* x;
      // Convert pointer: C++ RTCBase_ptr -> Python pointer
      x = SWIG_NewPointerObj(RTCBase::_duplicate((*$1)[i]),
							 SWIGTYPE_p_RTM__RTCBase, 0);
      PyList_SetItem($result, i, x);
	  // DECREF すると動かない：メモリリークの可能性あり
	  //      Py_DECREF(x);
    }
}





/*============================================================
 * SWIG typemaps for RtcFactory
 *============================================================*/
/*!
 * @brief Typemap of command arguments
 * 
 * Python (callable obj, profile dict) -> RtcFactoryPy(RtcFactoryBase)
 */
%typemap(python,in) (RtcFactoryBase* factory)
{
  PyObject* pyProfile = 0;
  PyObject* pyCallable = 0;
  RTM::RtcModuleProfile* profile;
  
  if (!PyTuple_Check($input)) {
    PyErr_SetString(PyExc_TypeError,"expected a tuple.");
    return NULL;
  }
  
  if (!PyArg_ParseTuple($input, (char *)"OO", &pyProfile, &pyCallable))
    {
      PyErr_SetString(PyExc_TypeError, "tuple must have 2 elements");
      return NULL;
    }
  
  RtcModuleProfSpec* spec;
  
  if ((SWIG_ConvertPtr(pyProfile, (void **)&profile,
		       $descriptor(RTM::RtcModuleProfile *),
		       SWIG_POINTER_EXCEPTION)) == -1)
    {
      // if pointer conversion is faild, try dictionary 
      if (PyDict_Check(pyProfile))
		{
		  PyObject *key, *value;
		  int pos = 0;
		  int i = 0;
		  int size = PyDict_Size(pyProfile);
		  
		  RtcModuleProfSpec* spec = new RtcModuleProfSpec[size + 1];
		  while (PyDict_Next(pyProfile, &pos, &key, &value))
			{
			  PyObject* o;
	      o = PyDict_GetItem(pyProfile, key);
	      cout << "key: " << PyInt_AsLong(key);
	      cout << " value: " << PyString_AsString(o) << endl;
	      
	      if (PyInt_Check(key) && PyString_Check(o))
			{
			  spec[i].type =
				static_cast<RtcModuleProfileType>(PyInt_AsLong(key));
			  if (spec[i].type >= RTC_MODULE_NAME && 
				  spec[i].type <= RTC_MODULE_SPEC_END)
				{
				  spec[i].value = PyString_AsString(o);
				}
			}
	      else
			{
			  PyErr_SetString(PyExc_TypeError,
							  "invalid dictionary for RtcModuleProfile");
			  return NULL;
			}
	      ++i;
			}
		  spec[i].type = RTC_MODULE_SPEC_END;
		  spec[i].value = "";
		  
		  profile = new RtcModuleProfile(spec);
		}
      else
		{
		  PyErr_SetString(PyExc_TypeError,
		  "1st argument must be a dictionaly or RtcModureProfile.");
		  return NULL;
		}
    }
  
  
  if (!PyCallable_Check(pyCallable))
    {
      PyErr_SetString(PyExc_TypeError,
					  "2nd argument must be a callable Python object.");
      return NULL;
    }
  
  $1 = new RtcFactoryPy(*profile, pyCallable);
}


/*============================================================
 * SWIG typemaps for ModuleProfile object references
 *============================================================*/
/*!
 * @brief Typemap for RtcModuleProfSpec* 
 *
 * Python(List, Tuple) -> RtcModuleProfile
 */
%typemap(python,in) RTM::RtcModuleProfSpec*
{
  /* Check if is a dictionary */
  if (PyDict_Check($input))
	{
	  PyObject *key, *value;
	  int pos = 0;
	  int i = 0;
	  int size = PyDict_Size($input);
	  
	  $1 = new RtcModuleProfSpec[size + 1];
	  while (PyDict_Next($input, &pos, &key, &value))
		{
		  PyObject* o;
		  o = PyDict_GetItem($input, key);
		  
		  if (PyInt_Check(key) && PyString_Check(o))
			{
			  $1[i].type = static_cast<RtcModuleProfileType>(PyInt_AsLong(key));
			  if ($1[i].type >= RTC_MODULE_NAME && 
				  $1[i].type <= RTC_MODULE_SPEC_END)
				{
				  $1[i].value = PyString_AsString(o);
				}
			}
		  else
			{
			  PyErr_SetString(PyExc_TypeError,
							  "invalid dictionary for RtcModuleProfile");
			  return NULL;
			}
		  ++i;
		}
	  $1[i].type = RTC_MODULE_SPEC_END;
	  $1[i].value = "";
	}
  else
	{
	  PyErr_SetString(PyExc_TypeError,
					  "invalid dictionaly for RtcModureProfile");
	  return NULL;
	}
}

%typemap(freearg) (RtcModuleProfSpec *spec) 
{
  delete [] $1;
}




/*============================================================
 * SWIG typemaps for PortProfile object references
 *============================================================*/
%typemap(python,out) RTM::PortProfile*
{
  // dictionary への変換
}






/*============================================================
 * SWIG typemaps for InPort object references
 *============================================================*/
/*
 * @brief Return value of RTM::InPort_ptr object reference
 *
 * RTM::InPort_ptr -> Python object: SWIGTYPE_p_RTM__InPort
 */
%typemap(python,out) RTM::InPort_ptr
{
  if (!CORBA::is_nil($1))
	{	
	  PyObject* x;
	  $result = SWIG_NewPointerObj(RTM::InPort::_duplicate($1),
								   SWIGTYPE_p_RTM__InPort, 0);
	}
  else
	{
	  return NULL;
	}
}


/*
 * @brief Return value of RTM::InPort_ptr object reference
 *
 * RTM::InPortList (sequence) -> Python List object of SWIGTYPE_p_RTM__InPort
 */
%typemap(python,out) RTM::InPortList*
{
  PyObject* x;
  int size($1->length());
  $result = PyList_New(size);

  for (int i = 0; i < size; ++i)
    {
      // Convert pointer: C++ InPortBase* -> Python pointer
	  if (!CORBA::is_nil((*$1)[i]))
		{
		  PyObject* x;
		  x = SWIG_NewPointerObj(RTM::InPort::_duplicate((*$1)[i]),
								 SWIGTYPE_p_RTM__InPort, 0);
		  PyList_SetItem($result, i, x);
		}
	  // DECREF すると動かない：メモリリークの可能性あり
	  //      Py_DECREF(x);
    }
}


/*============================================================
 * @brief SWIG typemaps for OutPort object references
 *============================================================*/
/*
 * @brief Return value of RTM::OutPort_ptr object reference
 *
 * RTM::OutPort_ptr -> Python object: SWIGTYPE_p_RTM__OutPort
 */
%typemap(python,out) RTM::OutPort_ptr
{

  if (!CORBA::is_nil($1))
	{
	  PyObject* x;
	  $result = SWIG_NewPointerObj(RTM::OutPort::_duplicate($1),
								   SWIGTYPE_p_RTM__OutPort, 0);
	}
  else
	{
	  return NULL;
	}
}


/*
 * @brief Return value of RTM::OutPort_ptr object reference
 *
 * RTM::OutPortList (sequence) -> Python List object of SWIGTYPE_p_RTM__OutPort
 */
%typemap(python,out) RTM::OutPortList*
{
  PyObject* x;
  int size($1->length());
  $result = PyList_New(size);

  for (int i = 0; i < size; ++i)
    {
	  // Convert pointer: C++ OutPortBase* -> Python pointer
	  if (!CORBA::is_nil((*$1)[i]))
		{
		  PyObject* x;
		  x = SWIG_NewPointerObj(RTM::OutPort::_duplicate((*$1)[i]),
								 SWIGTYPE_p_RTM__OutPort, 0);
		  
		  PyList_SetItem($result, i, x);
		}
	  // DECREF すると動かない：メモリリークの可能性あり
	  //      Py_DECREF(x);
    }
}


%define To_TimedDataPy(CTimed, BType)
  TimedDataPy<RTM::CTimed, BType> pydata($1);
  $result = SWIG_NewPointerObj(&pydata,
            SWIGTYPE_p_RTM__TimedDataPyTRTM__ ## CTimed ## _ ## BType ## _t,
            0);
%enddef

%define To_TimedDataPy2(CTimed, BType1, BType2)
  TimedDataPy<RTM::CTimed, BType1 BType2> pydata($1);
  $result = SWIG_NewPointerObj(&pydata,
            SWIGTYPE_p_RTM__TimedDataPyTRTM__ ## CTimed ## _ ## BType1 ## _ ## BType2 ## _t,
            0);
%enddef

%define To_TimedDataSeqPy(CTimed, BType)
  TimedDataSeqPy<RTM::CTimed, BType> *pydata;
  pydata = new TimedDataSeqPy<RTM::CTimed, BType>($1);
//std::cout << "org data size: " << $1.data.length() << endl;
//std::cout << "py data size: " << pydata->data.size() << endl;
//std::cout << "org data[0]: " << $1.data[0] << endl;
//std::cout << "py data[0]: " << pydata.data[0] << endl;
  $result = SWIG_NewPointerObj(pydata,
            SWIGTYPE_p_RTM__TimedDataSeqPyTRTM__ ## CTimed ## _ ## BType ## _t,
            0);
%enddef

%define To_TimedDataSeqPy2(CTimed, BType1, BType2)
  TimedDataSeqPy<RTM::CTimed, BType1 BType2> pydata($1);
  $result = SWIG_NewPointerObj(&pydata,
            SWIGTYPE_p_RTM__TimedDataSeqPyTRTM__ ## CTimed ## _ ## BType1 ## _ ##BType2 ## _t,
            0);
%enddef


/*============================================================
 * @brief SWIG typemaps for InPort data
 *============================================================*/

%typemap(python,out) RTM::TimedState
{
  To_TimedDataPy(TimedState, short);
}

%typemap(python,out) RTM::TimedShort
{
  To_TimedDataPy(TimedShort, short);
}

%typemap(python,out) RTM::TimedLong
{
  To_TimedDataPy(TimedLong, long);
}

%typemap(python,out) RTM::TimedUShort
{
  To_TimedDataPy2(TimedUShort, unsigned, short);
}

%typemap(python,out) RTM::TimedULong
{
  To_TimedDataPy2(TimedULong, unsigned, long);
}

%typemap(python,out) RTM::TimedFloat
{
  To_TimedDataPy(TimedFloat, float);
}

%typemap(python,out) RTM::TimedDouble
{
  To_TimedDataPy(TimedDouble, double);
}

%typemap(python,out) RTM::TimedChar
{
  To_TimedDataPy(TimedChar, char);
}

%typemap(python,out) RTM::TimedBoolean
{
  To_TimedDataPy(TimedBoolean, bool);
}

%typemap(python,out) RTM::TimedOctet
{
  To_TimedDataPy(TimedOctet, char);
}

/*
%typemap(python,out) RTM::TimedString
{
  $result = Py_BuildValue((char*)"(sd)",
						  CORBA::string_dup($1.data),
						  $1.tm.sec + ($1.tm.sec / 1000000000L));
}
*/



%typemap(python,out) RTM::TimedShortSeq
{
  To_TimedDataSeqPy(TimedShortSeq, short);
}

%typemap(python,out) RTM::TimedLongSeq
{
  To_TimedDataSeqPy(TimedLongSeq, long);
}

%typemap(python,out) RTM::TimedUShortSeq
{
  To_TimedDataSeqPy2(TimedUShortSeq, unsigned, short);
}

%typemap(python,out) RTM::TimedULongSeq
{
  To_TimedDataSeqPy2(TimedULongSeq, unsigned, long);
}

%typemap(python,out) RTM::TimedFloatSeq
{
  To_TimedDataSeqPy(TimedFloatSeq, float);
}

%typemap(python,out) RTM::TimedDoubleSeq
{
  To_TimedDataSeqPy(TimedDoubleSeq, double);
}

%typemap(python,out) RTM::TimedCharSeq
{
  To_TimedDataSeqPy(TimedCharSeq, char);
}

%typemap(python,out) RTM::TimedBooleanSeq
{
  To_TimedDataSeqPy(TimedBooleanSeq, bool);
}

%typemap(python,out) RTM::TimedOctetSeq
{
  To_TimedDataSeqPy(TimedOctetSeq, char);
}

/*
%typemap(python,out) RTM::TimedStringSeq
{
}
*/



/*============================================================
 * @brief SWIG typemaps for OutPort data
 *============================================================*/
%define Seq_FromPySeq(Conv_Func, Err_Msg)
  if (PyTuple_Check($input))
	{
	  int size = PyTuple_Size($input);
	  $1.data.length(size);
	  for (int i = 0; i < size; ++i)
		{
		  if (!Conv_Func(PyTuple_GetItem($input, i), $1.data[i]))
			{
			  PyErr_SetString(PyExc_TypeError, Err_Msg);
			  return NULL;
			}
		}
	}
  else if (PyList_Check($input))
	{
	  int size = PyList_Size($input);
	  $1.data.length(size);
	  for (int i = 0; i < size; ++i)
		{
		  if (!Conv_Func(PyList_GetItem($input, i), $1.data[i]))
			{
			  PyErr_SetString(PyExc_TypeError, Err_Msg);
			  return NULL;
			}
		}
	}
  else
	{
	  PyErr_SetString(PyExc_TypeError, "not a sequence object");
	  return NULL;
	}
%enddef

%typemap(python,in) RTM::TimedShort
{
  if (!Short_FromPy($input, $1.data))
	{
	  PyErr_SetString(PyExc_TypeError, "not a numeric object");
	  return NULL;
	}
}

%typemap(python,in) RTM::TimedLong
{
  if (!Long_FromPy($input, $1.data))
	{
	  PyErr_SetString(PyExc_TypeError, "not a numeric object");
	  return NULL;
	}
}

%typemap(python,in) RTM::TimedUShort
{
  if (!UShort_FromPy($input, $1.data))
	{
	  PyErr_SetString(PyExc_TypeError, "not a numeric object");
	  return NULL;
	}
}

%typemap(python,in) RTM::TimedULong
{
  if (!ULong_FromPy($input, $1.data))
	{
	  PyErr_SetString(PyExc_TypeError, "not a numeric object");
	  return NULL;
	}
}

%typemap(python,in) RTM::TimedFloat
{
  if (!Float_FromPy($input, $1.data))
	{
	  PyErr_SetString(PyExc_TypeError, "not a numeric object");
	  return NULL;
	}
}

%typemap(python,in) RTM::TimedDouble
{
  
  if (!Double_FromPy($input, $1.data))
	{
	  PyErr_SetString(PyExc_TypeError, "not a numeric object");
	  return NULL;
	}
}

%typemap(python,in) RTM::TimedChar
{
  if (!Char_FromPy($input, $1.data))
	{
	  PyErr_SetString(PyExc_TypeError, "cannot comvert to char object");
	  return NULL;
	}
}

%typemap(python,in) RTM::TimedBoolean
{
  
  if (!Boolean_FromPy($input, $1.data))
	{
	  PyErr_SetString(PyExc_TypeError, "not a bllean object");
	  return NULL;
	}
}

%typemap(python,in) RTM::TimedOctet
{
  
  if (!Octet_FromPy($input, $1.data))
	{
	  PyErr_SetString(PyExc_TypeError, "cannot comvert to char object");
	  return NULL;
	}
}

%typemap(python,in) RTM::TimedString
{
  if (!String_FromPy($input, $1.data))
	{
	  PyErr_SetString(PyExc_TypeError, "not a string object");
	  return NULL;
	}
}




%typemap(python,in) RTM::TimedShortSeq
{
  Seq_FromPySeq(Short_FromPy, "not a numeric object")
}


%typemap(python,in) RTM::TimedLongSeq
{
  Seq_FromPySeq(Long_FromPy, "not a numeric object")
}


%typemap(python,in) RTM::TimedUShortSeq
{
  Seq_FromPySeq(UShort_FromPy, "not a numeric object")
}


%typemap(python,in) RTM::TimedULongSeq
{
  Seq_FromPySeq(ULong_FromPy, "not a numeric object")
}


%typemap(python,in) RTM::TimedFloatSeq
{
  Seq_FromPySeq(Float_FromPy, "not a numeric object")
}


%typemap(python,in) RTM::TimedDoubleSeq
{
  Seq_FromPySeq(Double_FromPy, "not a numeric object")
}


%typemap(python,in) RTM::TimedCharSeq
{
  Seq_FromPySeq(Char_FromPy, "not a numeric object")
}


%typemap(python,in) RTM::TimedBooleanSeq
{
  Seq_FromPySeq(Boolean_FromPy, "not a numeric object")
}


%typemap(python,in) RTM::TimedOctetSeq
{
  Seq_FromPySeq(Octet_FromPy, "not a numeric object")
}


%typemap(python,in) RTM::TimedStringSeq
{
  Seq_FromPySeq(String_FromPy, "not a numeric object")
}




/*============================================================
 * CORBA Any type
 *============================================================*/
/*
 * Convert macro: From PyObject to TimedXXXX
 */
%define CONV_PY_TO_TIMED(var_type, var_subtype, swig_type)
{
  TimedDataPy<var_type, var_subtype>* var_ptr;
  if ((SWIG_ConvertPtr($input, (void **)&var_ptr,
					   $descriptor(var_type *),			
					   SWIG_POINTER_EXCEPTION)) != -1)	
	{
	  var_type timedd;
	  timedd.tm.sec = var_ptr->tm.sec;
	  timedd.tm.nsec = var_ptr->tm.nsec;
	  timedd.data = var_ptr->data;
	  (*$1) <<= timedd;
	  goto END;
	}
}
%enddef

/*
 * Convert macro: From PyObject to TimedXXXXSeq
 */
%define CONV_PY_TO_TIMEDSEQ(var_type, var_subtype, swig_type)
{
  TimedDataSeqPy<var_type, var_subtype>* var_ptr;
  if ((SWIG_ConvertPtr($input, (void **)&var_ptr,
					   $descriptor(var_type *),			
					   SWIG_POINTER_EXCEPTION)) != -1)	
	{
	  var_type timedd;
	  timedd.tm.sec = var_ptr->tm.sec;
	  timedd.tm.nsec = var_ptr->tm.nsec;

	  int size(var_ptr->data.size());
	  timedd.data.length(size);
	  for (int i = 0; i < size; ++i)
		{
		  timedd.data[i] = var_ptr->data[i];
		}
	  (*$1) <<= timedd;
	  goto END;
	}
}
%enddef


/*
 * typemap for const CORBA::Any& input
 */
%typemap(python,in) const CORBA::Any&
{
  CONV_PY_TO_TIMED(RTM::TimedShort, short, SWIGTYPE_p_RTM__TimedShort);
  CONV_PY_TO_TIMED(RTM::TimedLong,  long, SWIGTYPE_p_RTM__TimedLong);
  CONV_PY_TO_TIMED(RTM::TimedUShort, unsigned short, SWIGTYPE_p_RTM__TimedUShort);
  CONV_PY_TO_TIMED(RTM::TimedULong, unsigned long, SWIGTYPE_p_RTM__TimedULong);
  CONV_PY_TO_TIMED(RTM::TimedFloat, float, SWIGTYPE_p_RTM__TimedFloat);
  CONV_PY_TO_TIMED(RTM::TimedDouble, double, SWIGTYPE_p_RTM__TimedDouble);
  CONV_PY_TO_TIMED(RTM::TimedChar, char, SWIGTYPE_p_RTM__TimedChar);
  CONV_PY_TO_TIMED(RTM::TimedOctet, char, SWIGTYPE_p_RTM__TimedOctet);
  CONV_PY_TO_TIMED(RTM::TimedBoolean, bool, SWIGTYPE_p_RTM__TimedBoolean);
  //  CONV_PY_TO_TIMED(RTM::TimedString, char*, SWIGTYPE_p_RTM__TimedString);


  CONV_PY_TO_TIMEDSEQ(RTM::TimedShortSeq, short, SWIGTYPE_p_RTM__TimedShortSeq);
  CONV_PY_TO_TIMEDSEQ(RTM::TimedLongSeq,  long, SWIGTYPE_p_RTM__TimedLongSeq);
  CONV_PY_TO_TIMEDSEQ(RTM::TimedUShortSeq, unsigned short, SWIGTYPE_p_RTM__TimedUShortSeq);
  CONV_PY_TO_TIMEDSEQ(RTM::TimedULongSeq, unsigned long, SWIGTYPE_p_RTM__TimedULongSeq);
  CONV_PY_TO_TIMEDSEQ(RTM::TimedFloatSeq, float, SWIGTYPE_p_RTM__TimedFloatSeq);
  CONV_PY_TO_TIMEDSEQ(RTM::TimedDoubleSeq, double, SWIGTYPE_p_RTM__TimedDoubleSeq);
  CONV_PY_TO_TIMEDSEQ(RTM::TimedCharSeq, char, SWIGTYPE_p_RTM__TimedCharSeq);
  CONV_PY_TO_TIMEDSEQ(RTM::TimedOctetSeq, char, SWIGTYPE_p_RTM__TimedOctetSeq);
  CONV_PY_TO_TIMEDSEQ(RTM::TimedBooleanSeq, bool, SWIGTYPE_p_RTM__TimedBooleanSeq);
  //  CONV_PY_TO_TIMEDSEQ(RTM::TimedStringSeq, char*, SWIGTYPE_p_RTM__TimedStringSeq);
 END: ;
}

/*
 * Convert macro: From TimedXXXX to PyObject
 */
%define CONV_TIMED_TO_PY(val_type, val_subtype, swig_type)
{
  val_type* timedValue;
  if ((*$1) >>= timedValue)
	{
	  TimedDataPy<val_type, val_subtype> timedValuePy(*timedValue);
	  $result = SWIG_NewPointerObj((void *) &timedValuePy,
								   swig_type, 0);
	  goto END;
	}
}
%enddef

/*
 * Convert macro: From TimedXXXXSeq to PyObject
 */
%define CONV_TIMEDSEQ_TO_PY(val_type, val_subtype, swig_type)
{
  val_type* timedValue;
  if ((*$1) >>= timedValue)
	{
	  TimedDataSeqPy<val_type, val_subtype> timedValuePy(*timedValue);
	  $result = SWIG_NewPointerObj((void *) &timedValuePy,
								   swig_type, 0);
	  goto END;
	}
}
%enddef
	

/*
 * typemap for const CORBA::Any* output
 */
%typemap(python,out) CORBA::Any*
{

  CONV_TIMED_TO_PY(RTM::TimedShort, short, SWIGTYPE_p_RTM__TimedShort);
  CONV_TIMED_TO_PY(RTM::TimedLong,  long, SWIGTYPE_p_RTM__TimedLong);
  CONV_TIMED_TO_PY(RTM::TimedUShort, unsigned short, SWIGTYPE_p_RTM__TimedUShort);
  CONV_TIMED_TO_PY(RTM::TimedULong, unsigned long, SWIGTYPE_p_RTM__TimedULong);
  CONV_TIMED_TO_PY(RTM::TimedFloat, float, SWIGTYPE_p_RTM__TimedFloat);
  CONV_TIMED_TO_PY(RTM::TimedDouble, double, SWIGTYPE_p_RTM__TimedDouble);
  CONV_TIMED_TO_PY(RTM::TimedChar, char, SWIGTYPE_p_RTM__TimedChar);
  CONV_TIMED_TO_PY(RTM::TimedOctet, char, SWIGTYPE_p_RTM__TimedOctet);
  CONV_TIMED_TO_PY(RTM::TimedBoolean, bool, SWIGTYPE_p_RTM__TimedBoolean);
  //  CONV_TIMED_TO_PY(RTM::TimedString, char*, SWIGTYPE_p_RTM__TimedString);


  CONV_TIMEDSEQ_TO_PY(RTM::TimedShortSeq, short, SWIGTYPE_p_RTM__TimedShortSeq);
  CONV_TIMEDSEQ_TO_PY(RTM::TimedLongSeq,  long, SWIGTYPE_p_RTM__TimedLongSeq);
  CONV_TIMEDSEQ_TO_PY(RTM::TimedUShortSeq, unsigned short, SWIGTYPE_p_RTM__TimedUShortSeq);
  CONV_TIMEDSEQ_TO_PY(RTM::TimedULongSeq, unsigned long, SWIGTYPE_p_RTM__TimedULongSeq);
  CONV_TIMEDSEQ_TO_PY(RTM::TimedFloatSeq, float, SWIGTYPE_p_RTM__TimedFloatSeq);
  CONV_TIMEDSEQ_TO_PY(RTM::TimedDoubleSeq, double, SWIGTYPE_p_RTM__TimedDoubleSeq);
  CONV_TIMEDSEQ_TO_PY(RTM::TimedCharSeq, char, SWIGTYPE_p_RTM__TimedCharSeq);
  CONV_TIMEDSEQ_TO_PY(RTM::TimedOctetSeq, char, SWIGTYPE_p_RTM__TimedOctetSeq);
  CONV_TIMEDSEQ_TO_PY(RTM::TimedBooleanSeq, bool, SWIGTYPE_p_RTM__TimedBooleanSeq);
  //  CONV_TIMEDSEQ_TO_PY(RTM::TimedStringSeq, char*, SWIGTYPE_p_RTM__TimedStringSeq);

 END: ;

}
