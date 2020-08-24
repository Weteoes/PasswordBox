#ifdef ConfigDll_
#else
#define ConfigDll_
#include <Windows.h>

class ConfigDll
{
public:
	struct Struct_UserAndPassword {
		char Host[255];
		char User[255];
		char Pass[255];
	};

private:
	typedef bool								(__stdcall * Config_CreateUserAndPassword_)		(const char* host, const char* user, const char* pass);
	typedef Struct_UserAndPassword		        (__stdcall* Config_ReadUserAndPassword_)		(const char* host);
	typedef std::vector<Struct_UserAndPassword> (__stdcall * Config_ReadAllUserAndPassword_)	();
	typedef bool								(__stdcall * Config_DelUserAndPassword_)		(const char* host);

	typedef bool								(__stdcall* Config_ExsitsUserAndPassword_)		();
	typedef bool								(__stdcall* Config_ExsitsServer_)				();

	typedef bool								(__stdcall* Config_SetAESPassword_)				(char* pass);
	typedef bool								(__stdcall* Config_ResetAESPassword_)			(char* oldPass, char* newPass);

	typedef bool								(__stdcall* Config_ServerSetw_)					(const char* w);
	typedef int									(__stdcall* Config_ServerGetw_)					(char* &w);

	typedef bool								(__stdcall* Set_Variable_)						(char* key, char* value);

private:
	// 代理ServerDll
	typedef bool(__stdcall* Server_SumbitConfig_)				();
	typedef bool(__stdcall* Server_GetConfig_)					();
	typedef bool(__stdcall* Server_PdLogin_)					();
	typedef bool(__stdcall* Server_NetWorkisConnect_)			();

	typedef bool(__stdcall* Server_Set_Variable_)				(char* key, char* value);

public:
	static bool Ready();
	static Config_CreateUserAndPassword_	 Config_CreateUserAndPassword;
	static Config_ReadUserAndPassword_		 Config_ReadUserAndPassword;
	static Config_ReadAllUserAndPassword_	 Config_ReadAllUserAndPassword;
	static Config_DelUserAndPassword_		 Config_DelUserAndPassword;

	static Config_ExsitsUserAndPassword_	 Config_ExsitsUserAndPassword;
	static Config_ExsitsServer_				 Config_ExsitsServer;

	static Config_SetAESPassword_			 Config_SetAESPassword;
	static Config_ResetAESPassword_			 Config_ResetAESPassword;

	static Config_ServerSetw_				 Config_ServerSetw;
	static Config_ServerGetw_				 Config_ServerGetw;

	static Set_Variable_					 Set_Variable;		// Dll全局变量保存

public:
	// 代理ServerDll
	static Server_SumbitConfig_				 Server_SumbitConfig;
	static Server_GetConfig_				 Server_GetConfig;
	static Server_PdLogin_					 Server_PdLogin;
	static Server_NetWorkisConnect_			 Server_NetWorkisConnect;

	static Server_Set_Variable_				 Server_Set_Variable;

};
#endif

