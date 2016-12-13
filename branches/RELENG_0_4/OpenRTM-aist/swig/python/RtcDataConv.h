// -*- C++ -*-
/*!
 * @file RtcDataConv.h
 * @brief data convert functions for python
 * @date $Data$
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

#ifndef RtcDataConv_h
#define RtcDataConv_h


namespace RTM
{
  template <class T, class U>
  class TimedDataPy
  {
  public:
	TimedDataPy(){};
	TimedDataPy(T& value) : tm(value.tm), data(value.data) {};
	RTM::Time tm;
	U data;
  };
  
  
  template <class T, class U>
  class TimedDataSeqPy
  {
  public:
	TimedDataSeqPy(){};
	TimedDataSeqPy(T& value) : tm(value.tm)
	{
	  int size(value.data.length());
	  //	  std::cout << "size: " << size << endl;
	  for (int i = 0; i < size; ++i)
		{
		  //		  std::cout << i << ": " << value.data[i] << endl;
		  data.push_back(value.data[i]);
		}
	  //	  cout << "vector size: " << data.size() << endl;
	};
	RTM::Time tm;
	std::vector<U> data;
  };
};



bool Short_FromPy(PyObject* o, CORBA::Short& data)
{
  if (PyInt_Check(o))
	{
	  data = (CORBA::Short) PyInt_AS_LONG(o);
	  return true;
	}
  else if (PyLong_Check(o))
	{
	  data = (CORBA::Short) PyLong_AsLong(o);
	  return true;
	}
  else if (PyFloat_Check(o))
	{
	  data = (CORBA::Short) PyFloat_AsDouble(o);
	  return true;
	}
  return false;
}


bool Long_FromPy(PyObject* o, CORBA::Long& data)
{
  if (PyLong_Check(o))
	{
	  data = (CORBA::Long) PyLong_AsLong(o);
	  return true;
	}
  else if (PyInt_Check(o))
	{
	  data = (CORBA::Long) PyInt_AS_LONG(o);
	  return true;
	}
  else if (PyFloat_Check(o))
	{
	  data = (CORBA::Long) PyFloat_AsDouble(o);
	  return true;
	}
  return false;
}

bool UShort_FromPy(PyObject* o, CORBA::UShort& data)
{
  if (PyInt_Check(o))
	{
	  data = (CORBA::UShort) PyInt_AS_LONG(o);
	  return true;
	}
  else if (PyLong_Check(o))
	{
	  data = (CORBA::UShort) PyLong_AsLong(o);
	  return true;
	}
  else if (PyFloat_Check(o))
	{
	  data = (CORBA::UShort) PyFloat_AsDouble(o);
	  return true;
	}
  return false;
}

bool ULong_FromPy(PyObject* o, CORBA::ULong& data)
{
  if (PyLong_Check(o))
	{
	  data = (CORBA::ULong) PyLong_AsLong(o);
	  return true;
	}
  else if (PyInt_Check(o))
	{
	  data = (CORBA::ULong) PyInt_AS_LONG(o);
	  return true;
	}
  else if (PyFloat_Check(o))
	{
	  data = (CORBA::ULong) PyFloat_AsDouble(o);
	  return true;
	}
  return false;
}

bool Float_FromPy(PyObject* o, CORBA::Float& data)
{
  if (PyFloat_Check(o))
	{
	  data = (CORBA::Float) PyFloat_AsDouble(o);
	  return true;
	}
  else if (PyLong_Check(o))
	{
	  data = (CORBA::Float) PyLong_AsDouble(o);
	  return true;
	}
  else if (PyInt_Check(o))
	{
	  data = (CORBA::Float) PyInt_AS_LONG(o);
	  return true;
	}
  return false;
}

bool Double_FromPy(PyObject* o, CORBA::Double& data)
{
  if (PyFloat_Check(o))
	{
	  data = (CORBA::Double) PyFloat_AsDouble(o);
	  return true;
	}
  else if (PyLong_Check(o))
	{
	  data = (CORBA::Double) PyLong_AsDouble(o);
	  return true;
	}
  else if (PyInt_Check(o))
	{
	  data = (CORBA::Double) PyInt_AS_LONG(o);
	  return true;
	}
  return false;
}


bool Char_FromPy(PyObject* o, CORBA::Char& data)
{
  if (PyInt_Check(o))
	{
	  data = (CORBA::Char) PyInt_AS_LONG(o);
	  return true;
	}
  else if (PyLong_Check(o))
	{
	  data = (CORBA::Char) PyLong_AsDouble(o);
	  return true;
	}
  else if (PyString_Check(o) && (PyString_Size(o) == 1))
	{
	  char* c;
	  c = PyString_AsString(o);
	  data = (CORBA::Char) *c;
	  return true;
	}
  return false;
}

bool Boolean_FromPy(PyObject* o, CORBA::Boolean& data)
{
  if (PyBool_Check(o))
	{
	  data = (CORBA::Boolean) ((PyBoolObject *)o)->ob_ival;
	  return true;
	}
  return false;
}

bool Octet_FromPy(PyObject* o, CORBA::Octet& data)
{
  if (PyInt_Check(o))
	{
	  data = (CORBA::Char) PyInt_AS_LONG(o);
	  return true;
	}
  else if (PyLong_Check(o))
	{
	  data = (CORBA::Char) PyLong_AsDouble(o);
	  return true;
	}
  else if (PyString_Check(o) && (PyString_Size(o) == 1))
	{
	  char* c;
	  c = PyString_AsString(o);
	  data = (CORBA::Char) *c;
	  return true;
	}
  return false;
  
}

bool String_FromPy(PyObject* o, char* data)
{
  if (PyString_Check(o))
	{
	  data = CORBA::string_dup(PyString_AsString(o));
	  return true;
	}
  return false;
}



#endif // RtcDataConv_h
