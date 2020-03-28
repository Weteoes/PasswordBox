#ifdef SRWDll_H
#else
#define SRWDll_H
#include <atlbase.h>
class SRWDll
{
private:
	typedef int(__stdcall* Web_Entrance_)(const char* webPath);
	typedef char*(__stdcall* RSA_Encode_)(char* data, char* key);
	typedef char*(__stdcall* RSA_UnEncode_)(char* data, char* key);
	typedef bool(__stdcall* Set_Variable_)(char* key, char* value);

public:
	bool Loading();
	static Web_Entrance_ Web_Entrance; // Web入口
	static RSA_Encode_ RSA_Encode; // 加密
	static RSA_UnEncode_ RSA_UnEncode; // 解密
	static Set_Variable_ Set_Variable; // dll变量保存
};
#endif