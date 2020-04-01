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
	typedef bool								(__stdcall* Config_Exsits_)						();
	typedef bool								(__stdcall* Config_SetAESPassword_)				(char* pass);
	typedef bool								(__stdcall* Config_ResetAESPassword_)			(char* oldPass, char* newPass);
	typedef bool								(__stdcall* Set_Variable_)						(char* key, char* value);

public:
	bool Loading();
	static Config_CreateUserAndPassword_	 Config_CreateUserAndPassword;
	static Config_ReadUserAndPassword_		 Config_ReadUserAndPassword;
	static Config_ReadAllUserAndPassword_	 Config_ReadAllUserAndPassword;
	static Config_DelUserAndPassword_		 Config_DelUserAndPassword;
	static Config_Exsits_					 Config_Exsits;
	static Config_SetAESPassword_			 Config_SetAESPassword;
	static Config_ResetAESPassword_			 Config_ResetAESPassword;
	static Set_Variable_					 Set_Variable;		// Dll全局变量保存

};
#endif

