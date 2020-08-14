#ifndef ServerDll_H
#define ServerDll_H
class ServerDll
{
private:
	typedef bool			(__stdcall* SumbitConfig_)				();
	typedef bool			(__stdcall* GetConfig_)					();
	typedef bool			(__stdcall* PdLogin_)					();
	typedef bool			(__stdcall* NetWorkisConnect_)			();

	typedef bool			(__stdcall* Set_Variable_)				(char* key, char* value); 

public:
	bool Loading();
	static SumbitConfig_				SumbitConfig;
	static GetConfig_					GetConfig;
	static PdLogin_						PdLogin;
	static NetWorkisConnect_			NetWorkisConnect;

	static Set_Variable_				Set_Variable;
};
#endif