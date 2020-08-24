#ifndef ManagementDll_H
#define ManagementDll_H
class ManagementDll
{
private:
	typedef char*(__stdcall *Get_)(char*);

public:
	static bool Ready();
	static Get_ Get;
};
#endif