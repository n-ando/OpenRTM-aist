/**
 * \file defs.h
 * \brief システム共用マクロ集
 *
 * Copyright 2010 Honda R&D Co.,Ltd.
 */

#ifndef HRTM_DEFS_H_
#define HRTM_DEFS_H_


#ifdef _MSC_VER
#ifdef HRTM_DLL
#ifdef HRTM_EXPORTS
#define EXPORT_DLL __declspec(dllexport)
#ifndef EXTERN
#define EXTERN
#endif
#else
#define EXPORT_DLL __declspec(dllimport)
#ifndef EXTERN
#define EXTERN extern
#endif
#endif
#else
#define EXPORT_DLL
#ifndef EXTERN
#define EXTERN
#endif
#endif
#else
#define EXPORT_DLL
#ifndef EXTERN
#define EXTERN extern
#endif
#endif

#ifdef _MSC_VER
#define __attribute__(attribute)
#else
#ifndef __pragma
#define __pragma(x)
#endif
#endif

#ifdef ORB_IS_ORBEXPRESS
#  ifndef ORBEXPRESS
#    define ORBEXPRESS
#  endif
#elif defined ORB_IS_TAO
#  ifndef TAO
#    define TAO
#  endif
#elif defined ORB_IS_OMNIORB
#  ifndef OMNIORB
#    define OMNIORB
#  endif
#endif

#ifdef WIN32

#  ifdef ORBEXPRESS
#    pragma comment(lib, "OEbridge")
#    pragma comment(lib, "OEipmc")
#    pragma comment(lib, "OEmirror")
#    pragma comment(lib, "OEorb")
#    pragma comment(lib, "OErudp")
#    pragma comment(lib, "OEshrmem")
#    pragma comment(lib, "OEtcp")
#    pragma comment(lib, "OEtcpv6")
#    pragma comment(lib, "OEudp")
#  elif defined TAO
#  elif defined OMNIORB
#    ifdef _WINSTATIC
#      ifdef NDEBUG
#        pragma comment(lib, "omniORB4")
#        pragma comment(lib, "omnithread")
#        pragma comment(lib, "omniDynamic4")
#      else
#        pragma comment(lib, "omniORB4d")
#        pragma comment(lib, "omnithreadd")
#        pragma comment(lib, "omniDynamic4d")
#      endif
#      pragma comment(lib, "ws2_32")
#      pragma comment(lib, "advapi32")
#    else
#      ifdef NDEBUG
#        pragma comment(lib, "omniORB4_rt")
#        pragma comment(lib, "omnithread_rt")
#        pragma comment(lib, "omniDynamic4_rt")
#      else
#        pragma comment(lib, "omniORB4_rtd")
#        pragma comment(lib, "omnithread_rtd")
#        pragma comment(lib, "omniDynamic4_rtd")
#      endif
#    endif
#  endif
#  if !defined(HRTM_NO_AUTOMATIC_LINK) && !defined(HRTM_EXPORTS)
#    if defined(HRTM_STATIC)
#      if defined(NDEBUG)
#        pragma comment(lib, "HRTMmd")
#      else
#        pragma comment(lib, "HRTMmdd")
#      endif
#    else
#      if defined(NDEBUG)
#        pragma comment(lib, "HRTM")
#      else
#        pragma comment(lib, "HRTMd")
#      endif
#    endif
#  endif
#endif



/**
 * \def IF_WIN32
 * \brief Windows の時だけコードを実行する
 */
#ifdef _WIN32
#define IF_WIN32(sentence) sentence
#else
#define IF_WIN32(sentence)
#endif

/**
 * \def IF_MSC_VER
 * \brief VC の時だけコードを実行する
 */
#ifdef _MSC_VER
#define IF_MSC_VER(sentence) sentence
#else
#define IF_MSC_VER(sentence)
#endif

/**
 * \def IF__GNUC__
 * \brief GNU C の時だけコードを実行する
 */
#ifdef __GNUC__
#define IF__GNUC__(sentence) sentence
#else
#define IF__GNUC__(sentence)
#endif

/**
 * \def IF__GNUG__
 * \brief GNU C++ の時だけコードを実行する
 */
#ifdef __GNUG__
#define IF__GNUG__(sentence) sentence
#else
#define IF__GNUG__(sentence)
#endif

/**
 * \def IF__linux
 * \brief Linux の時だけコードを実行する
 */
#if defined(linux) || defined(__linux) || defined(__linux__)
#define IF__linux(sentence) sentence
#else
#define IF__linux(sentence)
#endif

/**
 \~Japanese
 \brief class \a TypeName の複製構築子と，代入演算子のダミー宣言
 \~English
 \brief Dummy declarations of copy constructor and assign operator.
*/
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  TypeName& operator=(const TypeName&)

#endif  // HRTM_DEFS_H_
