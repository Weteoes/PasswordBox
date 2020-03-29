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

public:
	bool Loading();
	static Web_Entrance_ Web_Entrance;		// Web���
	static RSA_Encode_ RSA_Encode;			// RSA ����
	static RSA_UnEncode_ RSA_UnEncode;		// RSA ����
	static AES_Encode_ AES_Encode;			// AES ����
	static AES_UnEncode_ AES_UnEncode;		// AES ����
	static Set_Variable_ Set_Variable;		// Dllȫ�ֱ�������
};
#endif