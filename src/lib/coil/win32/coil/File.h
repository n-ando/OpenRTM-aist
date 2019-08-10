// -*- C++ -*-
/*!
 * @file File_win32.h
 * @brief File functions
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef COIL_FILE_H
#define COIL_FILE_H

#include <fstream>
#include <coil/config_coil.h>
#include <coil/stringutil.h>

#include <Windows.h>
#include <string>

namespace coil
{

  /*!
  *  @note like ACE.
  */
  /*!
   * @if jp
   *
   * @brief ファイルパスよりディレクトリ部分を取得する
   *
   * ファイルパスよりディレクトリ部分を取得する。
   *
   * @param path ファイルパス
   *
   * @return ディレクトリ名称
   *
   * @else
   *
   * @brief Get a directory part than a file pass
   *
   * Get a directory part than a file pass.
   *
   * @param path File path
   *
   * @return Directory name
   *
   * @endif
   */
  std::string dirname(const char* path);

  /*!
   * @if jp
   *
   * @brief ファイルパスよりファイル名部分を取得する
   *
   * ファイルパスよりファイル名部分を取得する。
   *
   * @param path ファイルパス
   *
   * @return ファイル名称
   *
   * @else
   *
   * @brief Get a file name part than a file pass
   *
   * Get a directory part than a file pass.
   *
   * @param path File path
   *
   * @return File name
   *
   * @endif
   */
  std::string basename(const char* path);


  using ino_t = unsigned int;

  /*!
   * @if jp
   *
   * @brief ディレクトリエントリ用構造体
   *
   * @else
   *
   * @brief Structure for directory entry
   *
   * @endif
   */
  struct dirent
  {
    ino_t          d_ino;
    char           d_name[_MAX_PATH];
  };

  /*!
   * @if jp
   *
   * @brief ディレクトリストリーム用構造体
   *
   * @else
   *
   * @brief Structure for directory stream
   *
   * @endif
   */
  typedef struct
  {
    HANDLE h;
    WIN32_FIND_DATAA *fd;
    BOOL has_next;
    struct dirent entry;
  } DIR;


  /*!
   * @if jp
   *
   * @brief ディレクトリストリームをオープンする
   *
   * ディレクトリストリームをオープンする。
   *
   * @param name ファイルパス
   *
   * @return DIR 構造体ポインタ
   *
   * @else
   *
   * @brief Open a directory stream
   *
   * Open a directory stream.
   *
   * @param name File path
   *
   * @return DIR Structure pointer
   *
   * @endif
   */
  DIR* opendir(const char *name);


  /*!
   * @if jp
   *
   * @brief ディレクトリエントリポインタを取得する
   *
   * ディレクトリエントリポインタを取得する。
   *
   * @param dir DIR 構造体ポインタ
   *
   * @return DIR エントリポインタ
   *
   * @else
   *
   * @brief Get a directory entry pointer
   *
   * Get a directory entry pointer.
   *
   * @param dir DIR Structure pointer
   *
   * @return DIR entry pointer
   *
   * @endif
   */
  dirent* readdir(DIR *dir);

  /*!
   * @if jp
   *
   * @brief ディレクトリストリームを閉じる
   *
   * ディレクトリストリームを閉じる。
   *
   * @param dir DIR 構造体ポインタ
   *
   * @return 0: 成功, -1: 失敗
   *
   * @else
   *
   * @brief Close a directory stream
   *
   * Close a directory stream.
   *
   * @param dir DIR Structure pointer
   *
   * @return 0: successful, -1: failed
   *
   * @endif
   */
  int closedir(DIR *dir);


  /*!
   * @if jp
   *
   * @brief ファイルリストを取得する
   *
   * ディレクトリパスの中で指定ファイルにマッチするリストを取得する。
   *
   * @param path ディレクトリパス
   * @param glob_str ファイル名
   *
   * @return ファイルリスト
   *
   * @else
   *
   * @brief Get file list
   *
   * Get a list matching a file designated than a directory path.
   *
   * @param path Directory path
   * @param glob_str File name
   *
   * @return File list
   *
   * @endif
   */
  coil::vstring filelist(const char* path, const char* glob_str = "");

  /*!
  * @if jp
  *
  * @brief 指定ファイル名を指定ディレクトリから探査する
  *
  * @param dir ディレクトリパス
  * @param filename ディレクトリパス
  * @param filelist ファイル一覧
  *
  *
  * @else
  *
  * @brief 
  * 
  * @param dir 
  * @param filename 
  * @param filelist 
  *
  * @endif
  */
  void findFile(const std::string& dir, const std::string& filename, coil::vstring &filelist);


  /*!
  * @if jp
  *
  * @brief ファイル一覧を指定ディレクトリから探査する
  *
  * @param dir ディレクトリパス
  * @param ext 拡張子
  * @param filelist ファイル一覧
  *
  *
  * @else
  *
  * @brief
  *
  * @param dir
  * @param ext
  * @param filelist
  *
  * @endif
  */
  void getFileList(const std::string& dir, const std::string& ext, coil::vstring &filelist);

};

#endif // COIL_FILE_H
