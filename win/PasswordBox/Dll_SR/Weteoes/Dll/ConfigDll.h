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
	typedef bool(__stdcall * Config_CreateUserAndPassword_)(const char* host, const char* user, const char* pass);
	typedef Struct_UserAndPassword(__stdcall* Config_ReadUserAndPassword_)(const char* host);
	typedef std::vector<Struct_UserAndPassword>(__stdcall * Config_ReadAllUserAndPassword_)();
	typedef bool(__stdcall * Config_DelUserAndPassword_)(const char* host);

public:
	bool Loading();
	static Config_CreateUserAndPassword_ Config_CreateUserAndPassword;
	static Config_ReadUserAndPassword_ Config_ReadUserAndPassword;
	static Config_ReadAllUserAndPassword_ Config_ReadAllUserAndPassword;
	static Config_DelUserAndPassword_ Config_DelUserAndPassword;

};
#endif

