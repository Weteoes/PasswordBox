#ifdef SRWDll_H
#else
#define SRWDll_H
#include <atlbase.h>
class SRWDll
{
private:
	typedef int(__stdcall* Socket_Entrance_)();
	typedef int(__stdcall* Web_Entrance_)(const char* webPath);
	typedef char*(__stdcall *RSA_Encode_)(char* data, char* key);
	typedef char*(__stdcall *RSA_UnEncode_)(char* data, char* key);

public:
	bool Loading();
	static Web_Entrance_ Web_Entrance; //Web���
	static Socket_Entrance_ Socket_Entrance; //Socket���
	static RSA_Encode_ RSA_Encode; //����
	static RSA_UnEncode_ RSA_UnEncode; //����
};
#endif