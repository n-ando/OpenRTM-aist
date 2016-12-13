// -*- C++ -*-
/*!
 * @file ModulesManager.h
 * @brief Loadable modules manager class
 * @date $Date: 2006-10-17 10:06:47 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ModuleManager.h,v 1.2 2006-10-17 10:06:47 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/09/20 08:47:33  n-ando
 * The first commit of module management class.
 *
 *
 */

#ifndef ModuleManager_h
#define ModuleManager_h

// STL includes
#include <string>
#include <vector>
#include <map>

// ACE includes
#include <ace/DLL.h>

// RTC includes
#include <rtm/Properties.h>


#define CONFIG_EXT    "manager.modules.config_ext"
#define CONFIG_PATH   "manager.modules.config_path"
#define DETECT_MOD    "manager.modules.detect_loadable"
#define MOD_LOADPTH   "manager.modules.load_path"
#define INITFUNC_SFX  "manager.modules.init_func_suffix"
#define INITFUNC_PFX  "manager.modules.init_func_prefix"
#define ALLOW_ABSPATH "manager.modules.abs_path_allowed"
#define ALLOW_URL     "manager.modules.download_allowed"
#define MOD_DWNDIR    "manager.modules.download_dir"
#define MOD_DELMOD    "manager.modules.download_cleanup"
#define MOD_PRELOAD   "manager.modules.preload"

namespace RTC
{
  /*!
   * @if jp
   *
   * @brief モジュールマネージャクラス
   *
   * @else
   *
   * @biref ModuleManager class
   *
   *
   * @endif
   */
  class ModuleManager
  {
  public:
    ModuleManager(Properties& prop);
    
    ~ModuleManager();
    
    struct Error
    {
      Error(const std::string& _reason)
	: reason(_reason) {}
      std::string reason;
    };
    
    struct NotFound
    {
      NotFound(const std::string& _name)
	: name(_name) {}
      std::string name;
    };
    
    struct FileNotFound
      : public NotFound
    {
      FileNotFound(const std::string& _name)
	: NotFound(_name) {}
    };
    
    struct ModuleNotFound
      : public NotFound
    {
      ModuleNotFound(const std::string& _name)
	: NotFound(_name) {}
    };
    
    struct SymbolNotFound
      : public NotFound
    {
      SymbolNotFound(const std::string& _name)
	: NotFound(_name) {}
    };
    
    struct NotAllowedOperation
      : public Error
    {
      NotAllowedOperation(const std::string& _reason)
	: Error(_reason) {}
    };
    
    struct InvalidArguments
      : public Error
    {
      InvalidArguments(const std::string& _reason)
	: Error(_reason) {}
    };
    
    struct InvalidOperation
      : public Error
    {
      InvalidOperation(const std::string& _reason)
	: Error(_reason) {}
    };
    typedef void (*ModuleInitFunc)(void);
    /*!
     * @if jp
     *
     * @brief モジュールのロード
     *
     * file_name をDLL もしくは共有ライブラリとしてロードする。
     * file_name は既定のロードパス (manager.modules.load_path) に対する
     * 相対パスで指定する。
     *
     * Property manager.modules.abs_path_allowed が yes の場合、
     * ロードするモジュールを絶対パスで指定することができる。
     * Property manager.modules.download_allowed が yes の場合、
     * ロードするモジュールをURLで指定することができる。
     *
     * file_name は絶対パスで指定することができる。
     * manager.modules.allowAbsolutePath が no の場合、
     * 既定のモジュールロードパスから、file_name のモジュールを探しロードする。
     * 
     * @else
     *
     * @brief Load module
     *
     *
     * @endif
     */
    std::string load(const std::string& file_name);
    std::string load(const std::string& file_name, const std::string& init_func);
    
    /*!
     * @if jp
     * @brief モジュールのアンロード
     * @else
     * @brief Unload module
     * @endif
     */
    void unload(const std::string& file_name);
    
    
    /*!
     * @if jp
     * @brief 全モジュールのアンロード
     * @else
     * @brief Unload all modules
     * @endif
     */
    void unloadAll();
    
    
    /*!
     * @if jp
     * @brief モジュールのシンボルの参照
     * @else
     * @brief Look up a named symbol in the module
     * @endif
     */
    void* symbol(const std::string& file_name, const std::string& func_name)
      throw (ModuleNotFound, SymbolNotFound);
    
    /*!
     * @if jp
     * @brief モジュールロードパスを指定する
     * @else
     * @brief Set default module load path
     * @endif
     */
    void setLoadpath(const std::vector<std::string>& load_path);
    inline std::vector<std::string> getLoadPath()
    {
      return m_loadPath;
    }
    
    /*!
     * @if jp
     * @brief モジュールロードパスを追加する
     * @else
     * @brief Add module load path
     * @endif
     */
    void addLoadpath(const std::vector<std::string>& load_path);
    
    
    /*!
     * @if jp
     * @brief ロード済みのモジュールリストを取得する
     * @else
     * @brief Get loaded module names
     * @endif
     */
    std::vector<std::string> getLoadedModules();
    
    
    /*!
     * @if jp
     * @brief ロード可能なモジュールリストを取得する
     * @else
     * @brief Get loadable module names
     * @endif
     */
    std::vector<std::string> getLoadableModules();
    
    
    /*!
     * @if jp
     * @brief モジュールの絶対パス指定許す
     * @else
     * @brief Allow absolute load path
     * @endif
     */
    inline void allowAbsolutePath()
    {
      m_absoluteAllowed = true;
    }
    
    /*!
     * @if jp
     * @brief モジュールの絶対パス指定禁止する
     * @else
     * @brief Forbid absolute load path
     * @endif
     */
    inline void disallowAbsolutePath()
    {
      m_absoluteAllowed = false;
    }
    
    
    /*!
     * @if jp
     * @brief モジュールのダウンロードを許す
     * @else
     * @brief Allow module download
     * @endif
     */
    inline void allowModuleDownload()
    {
      m_downloadAllowed = true;
    }
    
    
    /*!
     * @if jp
     * @brief モジュールのダウンロードを禁止する
     * @else
     * @brief Forbid module download
     * @endif
     */
    inline void disallowModuleDownload()
    {
      m_downloadAllowed = false;
    }
    
    
    /*!
     * @if jp
     * @brief LoadPath からのファイルの検索
     * @else
     * @brief Search file from load path
     * @endif
     */
    std::string findFile(const std::string& fname,
			 const std::vector<std::string>& load_path);
    
    
    /*!
     * @if jp
     * @brief ファイルが存在するかどうかのチェック
     * @else
     * @brief Check file existance
     * @endif
     */
    bool fileExist(const std::string& filename);
    
    
    /*!
     * @if jp
     * @brief 初期化関数シンボルを生成する
     * @else
     * @brief Create initialize function symbol
     * @endif
     */
    std::string getInitFuncName(const std::string& file_path);
    
    
  protected:
    struct DLL
    {
      ACE_DLL dll;
    };
    
    typedef std::vector<std::string>     StringVector;
    typedef StringVector::iterator       StringVectorItr;
    typedef StringVector::const_iterator StringVectorConstItr;
    
    typedef std::map<std::string, DLL> DllMap;
    typedef DllMap::iterator           DllMapItr;
    typedef DllMap::const_iterator     DllMapConstItr;
    
    Properties& m_properties;
    
    DllMap m_modules;
    
    StringVector m_loadPath;
    StringVector m_configPath;
    bool m_downloadAllowed;
    bool m_absoluteAllowed;
    
    std::string m_initFuncSuffix;
    std::string m_initFuncPrefix;
    
  };   // class ModuleManager
};     // namespace RTC  
  
#endif // ModuleManager_h
  
