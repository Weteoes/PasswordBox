#ifndef ManagementDll_H
#define ManagementDll_H
class ManagementDll
{
private:
	typedef char*(__stdcall *Get_)(char*);

public:
	bool Loading();
	static Get_ Get;
};
#endif