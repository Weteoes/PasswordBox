#ifdef ManagementDll_
#else
#define ManagementDll_
#include <Windows.h>
class ManagementDll
{
private:
	typedef char*(__stdcall *Get_)(char*);

public:
	bool Loading();
	static Get_ Get;
};
#endif