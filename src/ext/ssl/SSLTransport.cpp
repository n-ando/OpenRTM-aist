#include <rtm/Manager.h>
#include <omniORB4/sslContext.h>

void SSLTransportSet(RTC::Manager *manager)
{
	coil::Properties &prop = manager->getConfig();

	std::string ssl_certificate_authority_file = prop["corba.ssl.certificate_authority_file"];
	std::string ssl_key_file = prop["corba.ssl.key_file"];
	std::string ssl_key_file_password = prop["corba.ssl.key_file_password"];
	if (!ssl_certificate_authority_file.empty())
#ifdef RTM_OMNIORB_43
		omni::sslContext::certificate_authority_file
#else
		sslContext::certificate_authority_file
#endif
			= CORBA::string_dup(ssl_certificate_authority_file.c_str());
	if (!ssl_key_file.empty())
#ifdef RTM_OMNIORB_43
		omni::sslContext::key_file
#else
		sslContext::key_file
#endif
			= CORBA::string_dup(ssl_key_file.c_str());
	if (!ssl_key_file_password.empty())
#ifdef RTM_OMNIORB_43
		omni::sslContext::key_file_password
#else
		sslContext::key_file_password
#endif
			= CORBA::string_dup(ssl_key_file_password.c_str());

	std::string corba_args = prop["corba.args"];

	if (corba_args.find("giop:ssl") == std::string::npos)
	{
		corba_args += " -ORBendPoint giop:ssl::";
	}

	if (!coil::toBool(prop["manager.is_master"], "YES", "NO", true))
	{
		if (prop.getProperty("corba.endpoints").empty())
		{
			if (prop.getProperty("corba.endpoint").empty())
			{
				if (prop["corba.args"].find("-ORBendPoint") == std::string::npos)
				{
					corba_args += " -ORBendPoint giop:tcp::";
				}
			}
		}
	}
	prop.setProperty("corba.args", corba_args);
}

extern "C"
{
	DLL_EXPORT void SSLTransportInit(RTC::Manager *manager)
	{

		SSLTransportSet(manager);
	}
}
