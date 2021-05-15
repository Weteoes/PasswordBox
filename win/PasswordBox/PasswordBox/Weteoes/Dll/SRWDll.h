#ifndef SRWDll_H
#define SRWDll_H

class SRWDll {
private:
	typedef int(__stdcall* Web_Entrance_)(const char* webPath);
	typedef int(__stdcall* RSA_Encode_)(char* data, int dataLen, char* key, char*& result);
	typedef int(__stdcall* RSA_UnEncode_)(char* data, int dataLen, char* key, char*& result);
	typedef int(__stdcall* AES_Encode_)(char* data, int dataLen, char* key, char*& result);
	typedef int(__stdcall* AES_UnEncode_)(char* data, int dataLen, char* key, char*& result);
	typedef bool(__stdcall* Set_Variable_)(char* key, char* value);
	typedef char*(__stdcall* Get_Variable_)(char* key);

public:
	static bool Ready();
	static Web_Entrance_ Web_Entrance;		// Web入口
	static RSA_Encode_ RSA_Encode;			// RSA 加密
	static RSA_UnEncode_ RSA_UnEncode;		// RSA 解密
	static AES_Encode_ AES_Encode;			// AES 加密
	static AES_UnEncode_ AES_UnEncode;		// AES 解密
	static Set_Variable_ Set_Variable;		// Dll全局变量保存
	static Get_Variable_ Get_Variable;		// Dll全局变量获取
};
#endif