// -*- C++ -*-
/*!
 * @file File_win32.cpp
 * @brief File functions
 * @date $Date$
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2019
 *     Robot Innovation Research Center,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <coil/File.h>

namespace coil
{
  const unsigned int MaxPathLength(1024);

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
  std::string dirname(const char* path)
  {
    char return_dirname[MaxPathLength + 1];

    size_t len = strlen(path);
    if (len > (sizeof(return_dirname) / sizeof(char)))
    {
      len = sizeof(return_dirname) / sizeof(char);
    }
    strncpy_s(return_dirname, sizeof(return_dirname), path, len);
    return_dirname[len] = '\0';

    const char delimiter('/');
    char *p = std::strrchr(return_dirname, delimiter);

    std::string dir_name;
    if (p != nullptr)
      {
        if (p != return_dirname)
          {
            if (*(p+1) == '\0')
              {
                *p = '\0';
                dir_name = dirname(return_dirname);
              }
            else
              {
                *p = '\0';
                dir_name = return_dirname;
              }
          }
        else
          {
            *(p+1) = '\0';
            dir_name = return_dirname;
          }
      }
    else
      {
        dir_name = ".";
      }
    return dir_name;
  }

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
  std::string basename(const char* path)
  {
    char p[MaxPathLength + 1];

    size_t len = strlen(path);
    if (len > (sizeof(p) / sizeof(char)))
    {
      len = sizeof(p) / sizeof(char);
    }
    strncpy_s(p, sizeof(p), path, len);
    p[len] = '\0';

    const char delimiter('/');
    char *pdelimiter = std::strrchr(p, delimiter);

    std::string base_name(p);
    if (pdelimiter != nullptr)
      {
        if (pdelimiter != p)
          {
            if (*(pdelimiter+1) == '\0')
              {
                *pdelimiter = '\0';
                base_name = basename(p);
              }
            else
              {
                pdelimiter++;
                base_name = pdelimiter;
              }
          }
        else
          {
            if (*(pdelimiter+1) != '\0')
              {
                pdelimiter++;
                base_name = pdelimiter;
              }
            else
              {
                base_name = pdelimiter;
              }

          }
      }
    return base_name;
  }

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
  DIR* opendir(const char *name)
  {
    if (name == nullptr) { return nullptr; }
    std::string path(name);
    if (path.empty()) { return nullptr; }

    // path has at least one or more path characters
    if (*(path.end() - 1) != '\\' && *(path.end() - 1) != '/')
      {
        std::string::size_type pos(path.find('/'));
        if (pos == std::string::npos)
          {
            path.push_back('\\');  // delim = '\'
          }
        else
          {
            path.push_back('/');  // delim = '/'
          }
      }
    path.push_back('*');  // now path is "/dir/dir/../*"

    // fd will be held by DIR structure
    HANDLE dhandle;
    WIN32_FIND_DATAA* fd;
    try
      {
        fd = new WIN32_FIND_DATAA();
        dhandle = FindFirstFileA(path.c_str(), fd);
        if (dhandle == INVALID_HANDLE_VALUE) { delete fd; return nullptr; }

      }
    catch (...)
      {
        return nullptr;
      }

    DIR* dir;
    try
      {
        dir = new DIR();
        dir->h = dhandle;
        dir->fd = fd;
        dir->has_next = TRUE;
      }
    catch (...)
      {
        delete fd;
        return nullptr;
      }
    return dir;
  }


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
  dirent* readdir(DIR *dir)
  {
    if (dir == nullptr) { return nullptr; }
    if (dir->fd == nullptr) { return nullptr;}
    if (dir->has_next == 0) { return nullptr; }

    strcpy_s(dir->entry.d_name, _MAX_PATH, dir->fd->cFileName);
    dir->has_next = FindNextFileA(dir->h, dir->fd);

    return &dir->entry;
  }

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
  int closedir(DIR *dir)
  {
    if (dir == nullptr) { return -1; }
    if (dir->h != nullptr && dir->h != INVALID_HANDLE_VALUE)
      {
        FindClose(dir->h);
      }
    delete dir->fd; 
    delete dir;

    return 0;
  }



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
  coil::vstring filelist(const char* path, const char* glob_str)
  {
    struct dirent* ent;
    coil::vstring flist;
    bool has_glob(false);

    if (path == nullptr) { return flist; }
    if (glob_str[0] != '\0') { has_glob = true; }

    DIR* dir_ptr(coil::opendir(path));
    if (dir_ptr == nullptr) { return flist; }

    while ((ent = coil::readdir(dir_ptr)) != nullptr)
      {
        std::string fname(ent->d_name);
        bool match(true);
        if (has_glob)
          {
            const char* globc(glob_str);
            for (size_t i(0); i < fname.size() && *globc != '\0'; ++i, ++globc)
              {
                if (*globc == '*')
                  {
                    // the last '*' matches every thing
                    if (globc[1] == '\0') { break; }
                    // consecutive * or + are skiped, but fname keeps pointer
                    if (globc[1] == '*' || globc[1] == '+') { --i; continue; }

                    // advance pointer and find normal characters
                    ++globc;
                    size_t pos(fname.find(*globc, i));
                    if (pos == std::string::npos) { match = false; break; }
                    // matched, and advance i to pos
                    i = pos;
                  }
                else if (*globc == '+')
                  {
                    // the last '+' matches last one or more characters
                    if (globc[1] == '\0' && !(i + 1 < fname.size())) { break; }
                    // consecutive * or + are skiped, but fname keeps pointer
                    if (globc[1] == '*' || globc[1] == '+') { --i; continue; }

                    // advance pointer and find normal characters
                    ++globc;
                    size_t pos(fname.find(*globc, i + 1));
                    if (pos == std::string::npos) { match = false; break; }
                    // matched, and advance i to pos
                    i = pos;
                  }
                else
                  {
                    if (fname[i] != *globc) { match = false; }
                  }

                // in the last fname character, if glob is not end,
                // or *, fname is not matched.
                if (i + 1 == fname.size() &&
                    globc[1] != '\0' && globc[1] != '*') { match = false; }
              }
          }
        if (match) { flist.emplace_back(std::move(fname)); }
      }
    coil::closedir(dir_ptr);

    return flist;
  }

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
  void findFile(const std::string& dir, const std::string& filename, coil::vstring &filelist)
  {
      {
          HANDLE hFind;
          WIN32_FIND_DATA win32fd;
          std::string dir_fff = dir + "\\*";
          hFind = FindFirstFile(dir_fff.c_str(), &win32fd);

          if (hFind == INVALID_HANDLE_VALUE) {
              return;
          }
          do {
              if ((win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0U) {
                std::string name(win32fd.cFileName);
                  if (name != "." && name != "..")
                  {
                      std::string next_dir = dir + "\\" + win32fd.cFileName;
                      findFile(next_dir, name, filelist);
                  }
              }
              else {
              }
          } while (FindNextFile(hFind, &win32fd));
      }

      {
          std::string file_fff = dir + "\\" + filename;
          std::ifstream ifs(file_fff.c_str());
        
          if (ifs.is_open())
          {
              filelist.emplace_back(file_fff);
          }
        
      }
  }



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
  void getFileList(const std::string& dir, const std::string& ext, coil::vstring &filelist)
  {
      {
          HANDLE hFind;
          WIN32_FIND_DATA win32fd;
          std::string dir_fff = dir + "\\*";
          hFind = FindFirstFile(dir_fff.c_str(), &win32fd);

          if (hFind == INVALID_HANDLE_VALUE) {
              return;
          }
          do {
              if ((win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0U) {
                  std::string filename = win32fd.cFileName;
                  if (filename != "." && filename != "..")
                  {
                      std::string next_dir = dir + "\\" + win32fd.cFileName;
                      getFileList(next_dir, ext, filelist);
                  }
              }
              else {
              }
          } while (FindNextFile(hFind, &win32fd));
      }

      {
          HANDLE hFind;
          WIN32_FIND_DATA win32fd;
          std::string file_fff = dir + "\\*." + ext;
          hFind = FindFirstFile(file_fff.c_str(), &win32fd);
          if (hFind == INVALID_HANDLE_VALUE) {
                return;
          }
          do {
              if ((win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0U) {

              }
              else {
                  std::string ret = dir + "\\" + win32fd.cFileName;
                  filelist.emplace_back(ret);
              }
          } while (FindNextFile(hFind, &win32fd));
      }


  }


} // namespace coil
