// -*- C++ -*-
/*!
 * @file   ManagerServantTests.cpp
 * @brief  ManagerServant test class
 * @date   $Date$ 
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$ 
 *
 */

/*
 * $Log$
 *
 */

#ifndef ManagerServant_cpp
#define ManagerServant_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <string>
#include <iostream>
#include <idl/SDOPackageSkel.h>
#include <idl/RTCSkel.h>
#include <ManagerServant.h>

/*!
 * @class ManagerServantTests class
 * @brief ManagerServant test
 */
namespace ManagerServant
{
  /*!
   * 
   * 
   *
   */
  class Logger
  {
  public:
    void log(const std::string& msg)
    {
      m_log.push_back(msg);
    }

    int countLog(const std::string& msg)
    {
      int count = 0;
      for (int i = 0; i < (int) m_log.size(); ++i)
        {
          if (m_log[i] == msg) ++count;
        }
     return count;
    }
		
  private:
    std::vector<std::string> m_log;
  };
/*
  class ManagerServantMock
    : public virtual ::\[POA_SDOPackage/POA_RTC\]::ManagerServant  {
  protected:
      std::vector<std::string> m_log;
  public :
      ManagerServantMock(){}
      virtual ~ManagerServantMock(){}

      void setLogger(Logger* logger)
      {
        m_logger = logger;
      }
  private:
    Logger* m_logger;

  };
*/
  class ManagerServantTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(ManagerServantTests);

//    CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST(test_load_module);
//    CPPUNIT_TEST(test_unload_module);
    CPPUNIT_TEST(test_get_loaded_modules);
    CPPUNIT_TEST(test_get_factory_profiles);
    CPPUNIT_TEST(test_create_component);
//    CPPUNIT_TEST(test_delete_component);
    CPPUNIT_TEST(test_get_components);
    CPPUNIT_TEST(test_get_component_profiles);
    CPPUNIT_TEST(test_get_profile);
    CPPUNIT_TEST(test_get_configuration);
    CPPUNIT_TEST(test_set_configuration);
    CPPUNIT_TEST(test_get_owner);
//    CPPUNIT_TEST(test_set_owner);
//    CPPUNIT_TEST(test_get_child);
//    CPPUNIT_TEST(test_set_child);
//    CPPUNIT_TEST(test_fork);
    CPPUNIT_TEST(test_shutdown);
//    CPPUNIT_TEST(test_restart);
//    CPPUNIT_TEST(test_get_service);
//    CPPUNIT_TEST(test_getObjRef);

    CPPUNIT_TEST_SUITE_END();
  
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
    /*!
     *
     */
    bool isFound(const ::RTM::ModuleProfileList* list, const std::string& mod)
    {
        char *pch;
        for (CORBA::ULong ic = 0; ic < list->length(); ++ic)
        {
            if( (*list)[ic].properties[0].value >>= pch )
            {
                if(mod == ::std::string(pch))
                {
                    return true;
                }
            }
        }
        return false;
    }
  
  public:
  
    /*!
     * @brief Constructor
     */
    ManagerServantTests()
    {

      int argc = 0;
      char** argv = NULL;
      m_pORB = CORBA::ORB_init(argc, argv);
      m_pPOA = PortableServer::POA::_narrow(
                       m_pORB->resolve_initial_references("RootPOA"));
      m_pPOA->the_POAManager()->activate();

    }
    
    /*!
     * @brief Destructor
     */
    ~ManagerServantTests()
    {
    }
  
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
    }
  
    /*! 
     * @brief tests for load_module()
     *
     *
     *
     */
    void test_load_module()
    {
        ::RTM::ManagerServant *pman = new ::RTM::ManagerServant();

        ::RTC::ReturnCode_t ret;
        try
        {
            ret = pman->load_module(".libs/DummyModule1.so","DummyModule1Init");
            CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);
            CPPUNIT_ASSERT(isFound(pman->get_loaded_modules(), 
                                   ".//.libs/DummyModule1.so"));
        }
        catch(...)
        {
	    CPPUNIT_FAIL("Exception thrown.");
        }

        //illegal file name.
        try
        {
            ret = pman->load_module("bar.so","DummyModule1Init");
	    CPPUNIT_FAIL("Exception not thrown.");
        }
        catch(...)
        {
            CPPUNIT_ASSERT(!isFound(pman->get_loaded_modules(), ".//bar.so"));
        }
        //illegal function name.
        try
        {
            ret = pman->load_module("DummyModule1i.so","foo");
	    CPPUNIT_FAIL("Exception not thrown.");
        }
        catch(...)
        {
            CPPUNIT_ASSERT(isFound(pman->get_loaded_modules(), 
                                   ".//.libs/DummyModule1.so"));
        }
        //loading overlaps
        ret = pman->load_module(".libs/DummyModule1.so","DummyModule1Init");
        CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);
        CPPUNIT_ASSERT(isFound(pman->get_loaded_modules(),
                               ".//.libs/DummyModule1.so"));

        //lodding another module
        ret = pman->load_module(".libs/DummyModule2.so","DummyModule2Init");
        CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);
        CPPUNIT_ASSERT(isFound(pman->get_loaded_modules(),
                               ".//.libs/DummyModule2.so"));

    }
    /*! 
     * @brief tests for unload_modules()
     *
     *
     *
     */
    void test_unload_modules()
    {
        ::RTM::ManagerServant *pman = new ::RTM::ManagerServant();
        ::RTC::ReturnCode_t ret;
        try
        {
            ret = pman->load_module(".libs/DummyModule1.so","DummyModule1Init");
            CPPUNIT_ASSERT(isFound(pman->get_loaded_modules(),
                                   ".//.libs/DummyModule1.so"));
            CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);
        }
        catch(...)
        {
	    CPPUNIT_FAIL("Exception thrown.");
        }
        try
        {
            ret = pman->load_module(".libs/DummyModule2.so","DummyModule2Init");
            CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);
            CPPUNIT_ASSERT(isFound(pman->get_loaded_modules(),
                                   ".//.libs/DummyModule2.so"));
        }
        catch(...)
        {
	    CPPUNIT_FAIL("Exception thrown.");
        }
        //
        try
        {
            ret = pman->unload_module("DummyModule2.so");
            CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);
        }
        catch(...)
        {
            CPPUNIT_FAIL( "unload error" );
        }
        //
        try
        {
            pman->unload_module("non-loaded-module.so");
	    CPPUNIT_FAIL("Exception not thrown.");
        }
        catch(...)
        {
            CPPUNIT_FAIL( "unload error" );
        }

    }
    /*! 
     * @brief tests for get_loaded_modules()
     *
     *
     *
     */
    void test_get_loaded_modules()
    {
        ::RTM::ManagerServant *pman = new ::RTM::ManagerServant();
        //Load modules.
        ::RTC::ReturnCode_t ret;
        try
        {
            ret = pman->load_module(".libs/DummyModule1.so","DummyModule1Init");
            CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);
            CPPUNIT_ASSERT(isFound(pman->get_loaded_modules(), 
                                   ".//.libs/DummyModule1.so"));
        }
        catch(...)
        {
	    CPPUNIT_FAIL("Exception thrown.");
        }
        try
        {
            ret = pman->load_module(".libs/DummyModule2.so","DummyModule2Init");
            CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);
            CPPUNIT_ASSERT(isFound(pman->get_loaded_modules(), 
                                   ".//.libs/DummyModule2.so"));
        }
        catch(...)
        {
	    CPPUNIT_FAIL("Exception thrown.");
        }

        //Execute the function
        ::RTM::ModuleProfileList* list;
        list = pman->get_loaded_modules();
        ::RTM::ModuleProfileList modlist(*list);
        delete list;

        //Check returns(ModuleProfileList).
        CPPUNIT_ASSERT_EQUAL((::CORBA::ULong)2, modlist.length());
        CPPUNIT_ASSERT_EQUAL(::std::string("file_path"), 
                             ::std::string(modlist[0].properties[0].name));
        char* ch;
        if( modlist[0].properties[0].value >>= ch )
        {
            CPPUNIT_ASSERT_EQUAL(::std::string(".//.libs/DummyModule1.so"), 
                                 ::std::string(ch));
        }
        else
        {
            CPPUNIT_FAIL( "ModuleProfileList is illegal." );
        }

        CPPUNIT_ASSERT_EQUAL(::std::string("file_path"), 
                             ::std::string(modlist[1].properties[0].name));

        if( modlist[1].properties[0].value >>= ch )
        {
            CPPUNIT_ASSERT_EQUAL(::std::string(".//.libs/DummyModule2.so"), 
                                 ::std::string(ch));
        }
        else
        {
            CPPUNIT_FAIL( "ModuleProfileList is illegal." );
        }
         
    }
    /*! 
     * @brief tests for get_factory_profiles()
     *
     *
     *
     */
    void test_get_factory_profiles()
    {
        typedef struct data_struct {
            ::std::string name;
            ::std::string value;
        } DATA_STRUCT;
        DATA_STRUCT composite_spec[] =
        {
            {"implementation_id", "PeriodicECSharedComposite"},
            {"type_name",         "PeriodicECSharedComposite"},
            {"description",       "PeriodicECSharedComposite"},
            {"version",           "1.0"},
            {"vendor",            "jp.go.aist"},
            {"category",          "composite.PeriodicECShared"},
            {"activity_type",     "DataFlowComponent"},
            {"max_instance",      "0"},
            {"language",          "C++"},
            {"lang_type",         "compile"},
            {"exported_ports",    ""},
            {"conf.default.members", ""},
            {"conf.default.exported_ports", ""},
            {"",""},
        };
        DATA_STRUCT consolein_spec[] =
        {
            {"implementation_id", "DummyModule1"},
            {"type_name",         "DummyModule1"},
            {"description",       "Console input component"},
            {"version",           "1.0"},
            {"vendor",            "Noriaki Ando, AIST"},
            {"category",          "example"},
            {"activity_type",     "DataFlowComponent"},
            {"max_instance",      "10"},
            {"language",          "C++"},
            {"lang_type",         "compile"},
            {"",""},
        };
        DATA_STRUCT consoleout_spec[] =
        {
            {"implementation_id", "DummyModule2"},
            {"type_name",         "DummyModule2"},
            {"description",       "Console output component"},
            {"version",           "1.0"},
            {"vendor",            "Noriaki Ando, AIST"},
            {"category",          "example"},
            {"activity_type",     "DataFlowComponent"},
            {"max_instance",      "10"},
            {"language",          "C++"},
            {"lang_type",         "compile"},
            {"",""},
        };
        ::RTM::ManagerServant *pman = new ::RTM::ManagerServant();

        //Load modules.
        ::RTC::ReturnCode_t ret;
        ret = pman->load_module(".libs/DummyModule1.so","DummyModule1Init");
        CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);
        CPPUNIT_ASSERT(isFound(pman->get_loaded_modules(),
                               ".//.libs/DummyModule1.so"));
        ret = pman->load_module(".libs/DummyModule2.so","DummyModule2Init");
        CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);
        CPPUNIT_ASSERT(isFound(pman->get_loaded_modules(),
                               ".//.libs/DummyModule2.so"));

        //Execute the function
        ::RTM::ModuleProfileList *list;
        list = pman->get_factory_profiles(); 
        ::RTM::ModuleProfileList profiles(*list);
        delete list;

        //Check returns(ModuleProfileList).
        ::CORBA::ULong len;
        CPPUNIT_ASSERT_EQUAL((::CORBA::ULong)3, profiles.length());
        len = profiles[0].properties.length(); 
        CPPUNIT_ASSERT_EQUAL((::CORBA::ULong)13, len);
        for (CORBA::ULong ic = 0; ic < len; ++ic)
        {
            CPPUNIT_ASSERT_EQUAL(composite_spec[ic].name,
                           ::std::string(profiles[0].properties[ic].name));
             
            char* ch;
            if( profiles[0].properties[ic].value >>= ch )
            {
                CPPUNIT_ASSERT_EQUAL(composite_spec[ic].value, 
                                     ::std::string(ch));
            }
            else
            {
                CPPUNIT_FAIL( "ModuleProfileList is illegal." );
            }
        }
        len =profiles[1].properties.length(); 
        CPPUNIT_ASSERT_EQUAL((::CORBA::ULong)10, len);
        for (CORBA::ULong ic = 0; ic < len; ++ic)
        {
            CPPUNIT_ASSERT_EQUAL(consolein_spec[ic].name,
                           ::std::string(profiles[1].properties[ic].name));
             
            char* ch;
            if( profiles[1].properties[ic].value >>= ch )
            {
                CPPUNIT_ASSERT_EQUAL(consolein_spec[ic].value, 
                                     ::std::string(ch));
            }
            else
            {
                CPPUNIT_FAIL( "ModuleProfileList is illegal." );
            }
        }
        len =profiles[2].properties.length(); 
        CPPUNIT_ASSERT_EQUAL((::CORBA::ULong)10, len);
        for (CORBA::ULong ic = 0; ic < len; ++ic)
        {
            CPPUNIT_ASSERT_EQUAL(consoleout_spec[ic].name,
                           ::std::string(profiles[2].properties[ic].name));
             
            char* ch;
            if( profiles[2].properties[ic].value >>= ch )
            {
                CPPUNIT_ASSERT_EQUAL(consoleout_spec[ic].value, 
                                     ::std::string(ch));
            }
            else
            {
                CPPUNIT_FAIL( "ModuleProfileList is illegal." );
            }
        }
    }
    /*! 
     *
     *
     *
     */
    void test_create_component()
    {
        ::RTM::ManagerServant *pman = new ::RTM::ManagerServant();
        //Load modules.
        ::RTC::ReturnCode_t ret;
        ret = pman->load_module(".libs/DummyModule1.so","DummyModule1Init");
        CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);
        CPPUNIT_ASSERT(isFound(pman->get_loaded_modules(),
                               ".//.libs/DummyModule1.so"));
        ret = pman->load_module(".libs/DummyModule2.so","DummyModule2Init");
        CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);
        CPPUNIT_ASSERT(isFound(pman->get_loaded_modules(),
                               ".//.libs/DummyModule2.so"));

        //Execute the function
        ::RTC::RTObject_ptr inobj;
        inobj = pman->create_component("DummyModule1AA");
        CPPUNIT_ASSERT(::CORBA::is_nil(inobj));
        inobj = pman->create_component("DummyModule1");
        CPPUNIT_ASSERT(!::CORBA::is_nil(inobj));

        ::RTC::RTObject_ptr outobj;
        outobj = pman->create_component("DummyModule2");
        CPPUNIT_ASSERT(!::CORBA::is_nil(outobj));
    }
    /*! 
     * @brief tests for delete_components()
     *
     *
     *
     */
    void test_delete_component()
    {
        ::RTM::ManagerServant *pman = new ::RTM::ManagerServant();
        //Load modules.
        ::RTC::ReturnCode_t ret;
        ret = pman->load_module(".libs/DummyModule1.so","DummyModule1Init");
        CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);
        CPPUNIT_ASSERT(isFound(pman->get_loaded_modules(),
                               ".//.libs/DummyModule1.so"));
        ret = pman->load_module(".libs/DummyModule2.so","DummyModule2Init");
        CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);
        CPPUNIT_ASSERT(isFound(pman->get_loaded_modules(),
                               ".//.libs/DummyModule2.so"));

        ::RTC::RTObject_ptr inobj;
        inobj = pman->create_component("DummyModule1");
        CPPUNIT_ASSERT(!::CORBA::is_nil(inobj));

        ::RTC::RTObject_ptr outobj;
        outobj = pman->create_component("DummyModule2");
        CPPUNIT_ASSERT(!::CORBA::is_nil(outobj));

        ::RTC::ComponentProfileList *list;
        list = pman->get_component_profiles();
        CPPUNIT_ASSERT(list!=NULL);
        ::RTC::ComponentProfileList profiles(*list);
        delete list;

        ret = pman->delete_component(profiles[0].instance_name);
        CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);

        ret = pman->delete_component(profiles[1].instance_name);
        CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);
    }
    /*! 
     * @brief tests for get_components()
     *
     *
     *
     */
    void test_get_components()
    {
        ::RTM::ManagerServant *pman = new ::RTM::ManagerServant();
        //Load modules.
        ::RTC::ReturnCode_t ret;
        ret = pman->load_module(".libs/DummyModule1.so","DummyModule1Init");
        CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);
        CPPUNIT_ASSERT(isFound(pman->get_loaded_modules(),
                               ".//.libs/DummyModule1.so"));
        ret = pman->load_module(".libs/DummyModule2.so","DummyModule2Init");
        CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);
        CPPUNIT_ASSERT(isFound(pman->get_loaded_modules(),
                               ".//.libs/DummyModule2.so"));

        ::RTC::RTObject_ptr inobj;
        inobj = pman->create_component("DummyModule1");
        CPPUNIT_ASSERT(!::CORBA::is_nil(inobj));

        ::RTC::RTObject_ptr outobj;
        outobj = pman->create_component("DummyModule2");
        CPPUNIT_ASSERT(!::CORBA::is_nil(outobj));

        //Execute the functions
        ::RTC::RTCList *list;
        list = pman->get_components();
        CPPUNIT_ASSERT(list != NULL);
        ::RTC::RTCList rtclist(*list);
        delete list;

        ::CORBA::ULong len(rtclist.length());
        bool bflag;
        bflag = false;
        for (::CORBA::ULong ic = 0; ic < len; ++ic)
        {
            if( rtclist[ic] == inobj )
            {
                bflag = true;
            }
        }
        CPPUNIT_ASSERT_EQUAL( bflag,true );

        bflag = false;
        for (::CORBA::ULong ic = 0; ic < len; ++ic)
        {
            if( rtclist[ic] == outobj )
            {
                bflag = true;
            }
        }
        CPPUNIT_ASSERT_EQUAL( bflag,true );
        
    }
    /*! 
     * @brief tests for get_component_profiles()
     *
     *
     */
    void test_get_component_profiles()
    {
        ::RTM::ManagerServant *pman = new ::RTM::ManagerServant();
        //Load modules.
        ::RTC::ReturnCode_t ret;
        ret = pman->load_module(".libs/DummyModule1.so","DummyModule1Init");
        CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);
        CPPUNIT_ASSERT(isFound(pman->get_loaded_modules(),
                               ".//.libs/DummyModule1.so"));
        ret = pman->load_module(".libs/DummyModule2.so","DummyModule2Init");
        CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);
        CPPUNIT_ASSERT(isFound(pman->get_loaded_modules(),
                               ".//.libs/DummyModule2.so"));

        //create components.
        ::RTC::RTObject_ptr inobj;
        inobj = pman->create_component("DummyModule1");
        CPPUNIT_ASSERT(!::CORBA::is_nil(inobj));

        ::RTC::RTObject_ptr outobj;
        outobj = pman->create_component("DummyModule2");
        CPPUNIT_ASSERT(!::CORBA::is_nil(outobj));

        //Execute the functions.
        ::RTC::ComponentProfileList *list;
        list = pman->get_component_profiles();
        CPPUNIT_ASSERT(list!=NULL);
        ::RTC::ComponentProfileList profiles(*list);
        delete list;
        
        //Execute the functions
        ::RTC::RTCList *plist;
        plist = pman->get_components();
        CPPUNIT_ASSERT(plist != NULL);
        ::RTC::RTCList rtclist(*plist);
        delete plist;

        ::CORBA::ULong len(rtclist.length());
        bool bflag;
        bflag = false;
        for (::CORBA::ULong ic = 0; ic < len; ++ic)
        {
            if( rtclist[ic] == inobj )
            {
                bflag = true;
                ::std::string str(profiles[ic].instance_name);
                CPPUNIT_ASSERT(str.find("DummyModule1") != ::std::string::npos);
                CPPUNIT_ASSERT_EQUAL(::std::string("DummyModule1"),
                                     ::std::string(profiles[ic].type_name));
                CPPUNIT_ASSERT_EQUAL(::std::string("Console input component"),
                                     ::std::string(profiles[ic].description));
                CPPUNIT_ASSERT_EQUAL(::std::string("1.0"),
                                     ::std::string(profiles[ic].version));
                CPPUNIT_ASSERT_EQUAL(::std::string("Noriaki Ando, AIST"),
                                     ::std::string(profiles[ic].vendor));
                CPPUNIT_ASSERT_EQUAL(::std::string("example"),
                                     ::std::string(profiles[ic].category));
                break;
            }
        }
        CPPUNIT_ASSERT_EQUAL( bflag,true );

        bflag = false;
        for (::CORBA::ULong ic = 0; ic < len; ++ic)
        {
            if( rtclist[ic] == outobj )
            {
                bflag = true;
                ::std::string str(profiles[ic].instance_name);
                CPPUNIT_ASSERT(str.find("DummyModule2") != ::std::string::npos);
                CPPUNIT_ASSERT_EQUAL(::std::string("DummyModule2"),
                                     ::std::string(profiles[ic].type_name));
                CPPUNIT_ASSERT_EQUAL(::std::string("Console output component"),
                                     ::std::string(profiles[ic].description));
                CPPUNIT_ASSERT_EQUAL(::std::string("1.0"),
                                     ::std::string(profiles[ic].version));
                CPPUNIT_ASSERT_EQUAL(::std::string("Noriaki Ando, AIST"),
                                     ::std::string(profiles[ic].vendor));
                CPPUNIT_ASSERT_EQUAL(::std::string("example"),
                                     ::std::string(profiles[ic].category));
                break;
            }
        }
        CPPUNIT_ASSERT_EQUAL( bflag,true );

        

    }
    /*! 
     * @brief tests for get_profile()
     *
     *
     *
     */
    void test_get_profile()
    {
        typedef struct data_struct {
            ::std::string name;
            ::std::string value;
        } DATA_STRUCT;
        DATA_STRUCT manager_profile[] =
        {
            {"instance_name",            "manager"},
            {"name",                     "manager"},
            {"naming_formats",           "%h.host_cxt/%n.mgr"},
            {"pid",                      ""},
            {"refstring_path",           "/var/log/rtcmanager.ref"},
            {"modules.load_path",        "./"},
            {"modules.abs_path_allowed", "YES"},
            {"modules.config_path",      ""},
            {"modules.download_allowed", ""},
            {"modules.init_func_suffix", ""},
            {"modules.init_func_prefix", ""},
            {"os.name",                  "Linux"},
            {"os.release",               ""},
            {"os.version",               ""},
            {"os.arch",                  ""},
            {"os.hostname",              ""},
            {"name",                     ""},
            {"",""},
        };

        ::RTM::ManagerServant *pman = new ::RTM::ManagerServant();

        //Execute the functions.
        ::RTM::ManagerProfile *list;
        list = pman->get_profile();
        ::RTM::ManagerProfile profile(*list);
        delete list;
        int  len;
        len = profile.properties.length(); 
        CPPUNIT_ASSERT_EQUAL(16,len);
        for(int ic = 0; ic < len; ++ic) 
        {
            CPPUNIT_ASSERT_EQUAL(manager_profile[ic].name,
                               ::std::string(profile.properties[ic].name));
            char* ch;
            if( profile.properties[ic].value >>= ch )
            {
                if(!manager_profile[ic].value.empty())
                {
                    CPPUNIT_ASSERT_EQUAL(manager_profile[ic].value,
                                         ::std::string(ch)); 
                }
            }
        }

    }
    /*! 
     * @brief tests for get_configuration()
     *
     *
     *
     */
    void test_get_configuration()
    {
        typedef struct data_struct {
            ::std::string name;
            ::std::string value;
        } DATA_STRUCT;
        DATA_STRUCT config[] =
        {
            {"config.version",                  "1.0.0"},
            {"openrtm.version",                 "OpenRTM-aist-1.0.0"},
            {"manager.instance_name",           "manager"},
            {"manager.name",                    "manager"},
            {"manager.naming_formats",          "%h.host_cxt/%n.mgr"},
            {"manager.pid",                     ""},
            {"manager.refstring_path",          "/var/log/rtcmanager.ref"},
            {"manager.modules.load_path",       "./"},
            {"manager.modules.abs_path_allowed","YES"},
            {"manager.modules.config_path",     ""},
            {"manager.modules.download_allowed",""},
            {"manager.modules.init_func_suffix",""},
            {"manager.modules.init_func_prefix",""},
            {"manager.os.name",                 "Linux"},
            {"manager.os.release",              ""},
            {"manager.os.version",              ""},
            {"manager.os.arch",                 ""},
            {"manager.os.hostname",             ""},
            {"os.name",                         ""},
            {"os.release",                      ""},
            {"os.version",                      ""},
            {"os.arch",                         ""},
            {"os.hostname",                     ""},
            {"logger.enable",                   "YES"},
            {"logger.file_name",                ""},
            {"logger.date_format",              "%b %d %H:%M:%S"},
            {"logger.log_level",                "NORMAL"},
            {"logger.stream_lock",              "NO"},
            {"logger.master_logger",            ""},
            {"module.conf_path",                ""},
            {"module.load_path",                ""},
            {"naming.enable",                   "YES"},
            {"naming.type",                     "corba"},
            {"naming.formats",                  "%h.host_cxt/%n.rtc"},
            {"naming.update.enable",            "YES"},
            {"naming.update.interval",          "10.0"},
            {"timer.enable",                    "YES"},
            {"timer.tick",                      "0.1"},
            {"corba.args",                      ""},
            {"corba.endpoint",                  ""},
            {"corba.id",                        "omniORB"},
            {"corba.name_servers",              ""},
            {"corba.nameservers",               ""},
            {"exec_cxt.periodic.type",          "PeriodicExecutionContext"},
            {"exec_cxt.periodic.rate",          "1000"},
            {"exec_cxt.evdriven.type",          "EventDrivenExecutionContext"},
            {"example.DummyModule10.config_file",  ""},
            {"example.DummyModule1.config_file",   ""},
            {"example.DummyModule20.config_file", ""},
            {"example.DummyModule2.config_file",  ""},
            {"example.DummyModule11.config_file",  ""},
            {"example.DummyModule21.config_file", ""},
            {"example.DummyModule12.config_file",  ""},
            {"example.DummyModule22.config_file", ""},
            {"",""},
        };

        ::RTM::ManagerServant *pman = new ::RTM::ManagerServant();
        ::RTM::NVList* list;
        list = pman->get_configuration();
        ::RTM::NVList conf(*list);
        delete list;
        ::CORBA::ULong  len;
        len = conf.length(); 
        CPPUNIT_ASSERT_EQUAL((::CORBA::ULong)54,len);
        for(::CORBA::ULong ic = 0; ic < len; ++ic) 
        {
            CPPUNIT_ASSERT_EQUAL(config[ic].name,
                               ::std::string(conf[ic].name));
            char* ch;
            if( conf[ic].value >>= ch )
            {
                if(!config[ic].value.empty())
                {
                    CPPUNIT_ASSERT_EQUAL(config[ic].value,
                                         ::std::string(ch)); 
                }
            }
        }
        
    }
    /*! 
     * @brief tests for set_configuration()
     *
     *
     *
     */
    void test_set_configuration()
    {
        typedef struct data_struct {
            ::std::string name;
            ::std::string value;
        } DATA_STRUCT;
        DATA_STRUCT config[] =
        {
            {"config.version",                  "1.0.0"},
            {"openrtm.version",                 "OpenRTM-aist-1.0.0"},
            {"manager.naming_formats",          "%n.rtc"},
            {"manager.modules.load_path",       "../"},
            {"manager.modules.abs_path_allowed","NO"},
            {"manager.os.release",              "2.6.22-14-generic"},
            {"manager.os.version",              "2008"},
            {"manager.os.arch",                 "64"},
            {"manager.os.hostname",             "ubuntur810"},
        };
        ::RTM::ManagerServant *pman = new ::RTM::ManagerServant();
        ::RTC::ReturnCode_t ret;
        int len;
        len = sizeof config/sizeof config[0]; 
        for(int ic = 0; ic < len; ++ic) 
        {
            ret = pman->set_configuration(config[ic].name.c_str(), 
                                          config[ic].value.c_str());
            CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, ret);
        }

        ::RTM::NVList* list;
        list = pman->get_configuration();
        ::RTM::NVList conf(*list);
        delete list;
        ::CORBA::ULong  leng;
        leng = conf.length(); 
        CPPUNIT_ASSERT_EQUAL((::CORBA::ULong)54,leng);
        for(::CORBA::ULong ic = 0; ic < leng; ++ic) 
        {
            if(config[0].name == ::std::string(conf[ic].name))
            {
                CPPUNIT_ASSERT_EQUAL(config[ic].name,
                                     ::std::string(conf[ic].name));
                char* ch;
                if( conf[ic].value >>= ch )
                {
                    if(!config[ic].value.empty())
                    {
                        CPPUNIT_ASSERT_EQUAL(config[ic].value,
                                             ::std::string(ch)); 
                    }
                }
            }
        }
    }
    /*! 
     * @brief tests for get_owner()
     *
     *
     *
     */
    void test_get_owner()
    {
        ::RTM::ManagerServant *pman = new ::RTM::ManagerServant();
        ::RTM::Manager_ptr obj;
        obj =  pman->get_owner();
        CPPUNIT_ASSERT(::CORBA::is_nil(obj));

    }
    /*! 
     * @brief tests for set_owner()
     *
     *
     *
     */
    void test_set_owner()
    {
    }
    /*! 
     * @brief tests for set_child()
     *
     *
     *
     */
    void test_set_child()
    {
    }
    /*! 
     * @brief tests for get_child()
     *
     *
     *
     */
    void test_get_child()
    {
    }
    /*! 
     * @brief tests for fork()
     *
     *
     *
     */
    void test_fork()
    {
    }
    /*! 
     * @brief tests for shutdown()
     *
     *
     *
     */
    void test_shutdown()
    {

        ::RTM::ManagerServant *pman = new ::RTM::ManagerServant();

        try
        {
            ::RTC::ReturnCode_t retcode;
            retcode = pman->shutdown();
            CPPUNIT_ASSERT_EQUAL(::RTC::RTC_OK, retcode);
            ::coil::sleep(3);
            delete pman;
        }
        catch(...)
        {
	    CPPUNIT_FAIL("Exception thrown.");
        }
    }
    /*! 
     * @brief tests for restart()
     *
     *
     *
     */
    void test_restart()
    {
    }
    /*! 
     * @brief tests for get_service()
     *
     *
     *
     */
    void test_get_service()
    {
    }
    /*! 
     * @brief tests for getObjRef()
     *
     *
     *
     */
    void test_getObjRef()
    {
    }
    /* test case */
    void test_case0()
    {
    }
  };
}; // namespace ManagerServant

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(ManagerServant::ManagerServantTests);

#ifdef LOCAL_MAIN
int main(int argc, char* argv[])
{
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    CppUnit::Outputter* outputter = 
      new CppUnit::TextOutputter(&runner.result(), std::cout);
    runner.setOutputter(outputter);
    bool retcode = runner.run();
    return !retcode;
}
#endif // MAIN
#endif // ManagerServant_cpp
