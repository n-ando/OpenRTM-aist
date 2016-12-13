// -*- C++ -*-
/*!
 * @file RtcFactoryPy.h
 * @brief RTComponent factory class for Python
 * @date $Date: 2005-05-12 09:06:18 $
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcFactoryPy.h,v 1.1.1.1 2005-05-12 09:06:18 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef RtcFactoryPy_h
#define RtcFactoryPy_h

#include <list>
#include "Python.h"
#include "rtm/RtcFactory.h"

namespace RTM 
{
  /*!
   * @if jp
   *
   * @class RtcFactoryPy
   *
   * @brief RtcFactoryPy クラス
   * 
   * Python で実装されたコンポーネントを生成するためのファクトリクラス。
   *
   * @else
   *
   * @class RtcFactoryPy
   *
   * @brief RtcFactoryPy class
   *
   * RTComponent factory class for RTComponent implemented in Python.
   *
   * @endif
   */
  class RtcFactoryPy
    : public RtcFactoryBase
  {
  public:
	
	/*!
	 * @if jp
	 *
	 * @brief RtcFactoryPy クラスコンストラクタ
	 *
	 * RtcFactoryPy クラスのコンストラクタ。
	 * パラメータとして与えられるモジュールのプロファイルと Python の callable
	 * オブジェクトを引数に取りPythonコンポーネントを生成する。
	 *
	 * @param profile コンポーネントのプロファイル
	 * @param callable Python の callable Object
	 *
	 * @else
	 *
	 * @brief RtcFactoryPy class constructor.
	 *
	 * RtcFactoryPy class constructor.
	 * Create RTComponent implemented in Python with two arguments: 
	 * component profile and Python callable object.
	 *
	 * @param profile component profile
	 * @param callable Python callable object
	 *
	 * @endif
	 */
    RtcFactoryPy(RtcModuleProfile profile, PyObject* callable)
      : RtcFactoryBase(profile), m_pyClass(callable)
    {
      if (!PyCallable_Check(m_pyClass))
		{
		  cout << "callable is not callable Python object." << endl;
		}
      else
		{
		  Py_INCREF(m_pyClass);
		}
      //PyEval_InitThreads();
      //PyThreadState *tstate = PyEval_SaveThread();
      //m_Interp = tstate->interp;
      //m_Interp = PyThreadState_Get()->interp;
      //PyEval_ReleaseLock();
      //PyEval_RestoreThread(tstate);
    };
	
	/*!
	 * @if jp
	 * @brief RtcFactoryPy クラスデストラクタ
	 * @else
	 * @brief RtcFactoryPy class destructor
	 * @endif
	 */
    ~RtcFactoryPy()
	{
	  Py_DECREF(m_pyClass);
	}
	
	
	/*!
	 * @if jp
	 *
	 * @brief コンポーネントの生成
	 *
	 * Python で実装された RTComponent のインスタンスを生成する。
	 *
	 * @param mgr RtcManager へのポインタ
	 *
	 * @else
	 *
	 * @brief Create component
	 *
	 * Create component implemented in Python
	 *
	 * @param mgr pointer to RtcManager
	 *
	 * @endif
	 */
    RtcBase* create(RtcManager* mgr)
	{
	  PyObject* pyMgr;
	  PyObject* pyArg;
	  PyObject* pyComponent;
	  //	  rtmPyBeginBlockThreads();
	  if (!PyCallable_Check(m_pyClass))
		{
		  cout << "callable is not callable Python object." << endl;
		}
	  
	  // Convert RtcManager* to python type RtcManager object
	  pyMgr = SWIG_NewPointerObj((void *) mgr,
								 SWIGTYPE_p_RTM__RtcManager, 1);
	  if (pyMgr == NULL) cerr << "pyMgr Object is NULL" << endl;
	  
	  // Build python type RtcManager as python argument object
	  pyArg = Py_BuildValue("(O)", pyMgr);
	  if (pyArg == NULL) cerr << "pyArg Object is NULL" << endl;
	  
	  //PyThreadState *tstate;
	  //	  m_Interp is reference to an interpreter object.
	  //tstate = PyThreadState_New(PyThreadState_Get()->interp);
	  //PyEval_AcquireThread(tstate);
	  //	  PyEval_InitThreads();
	  //Py_BEGIN_ALLOW_THREADS
	  
	  
	  // Construct new component from user defined class in python
	  pyComponent = PyEval_CallObject(m_pyClass, pyArg);
	  if (pyComponent == NULL)
		{
		  cerr << "m_pyComponent Object is NULL" << endl;
		  return NULL;
		}
	  
	  //	  Py_END_ALLOW_THREADS
	  ++m_Number;
	  
	  RtcBase* comp;
	  if ((SWIG_ConvertPtr(pyComponent, (void **)&comp,
						   SWIGTYPE_p_RTM__RtcBase,
						   SWIG_POINTER_EXCEPTION)) == -1)
		{
		  cerr << "conversion error" << endl;
		  return NULL;
		}
	  
	  //	  Py_INCREF(pyComponent);
	  m_pyComponents.push_back(pyComponent);
	  //	  Py_INCREF(pyComponent);
	  //	  Py_DECREF(pyArg);
	  //	  Py_DECREF(pyMgr);
	  
	  // Release thepython thread. No Python API allowed beyond this point.
	  //PyEval_ReleaseThread(tstate);
	  //PyThreadState_Delete(tstate);
	  //PyThreadState_Clear(tstate);
	  //PyThreadState_DeleteCurrent();
	  //	  rtmPyEndBlockThreads();
	  
	  return comp;
	};
	
	/*!
	 * @if jp
	 *
	 * @brief コンポーネントの破棄
	 *
	 * RTComponent のインスタンスを破棄する。
	 *
	 * @param comp RtcBase へのポインタ
	 *
	 * @else
	 *
	 * @brief Destroy component
	 *
	 * Destroy component instance
	 *
	 * @param comp pointer to RtcBase
	 *
	 * @endif
	 */
    void destroy(RtcBase* comp)
	{
	  --m_Number;
	  
	  delete comp;
	};
	
  protected:
	/*!
	 * @if jp
	 * @brief RTComponent を実装した Python クラスへのポインタ
	 * @else
	 * @brief The pointer to Python's RTComponent class object
	 * @endif
	 */
    PyObject* m_pyClass;
	
	/*!
	 * @if jp
	 * @brief RTComponent のインスタンスへのポインタのリスト
	 * @else
	 * @brief List of RTComponent instance pointer
	 * @endif
	 */
	std::list<PyObject*> m_pyComponents;
	/*!
	 * @if jp
	 * @brief Python インタプリタへのポインタ
	 * @else
	 * @brief The pointer to Python interpreter
	 * @endif
	 */
	PyInterpreterState *m_Interp;
  };
  
};



#endif // end of __RtcFactory_h__
