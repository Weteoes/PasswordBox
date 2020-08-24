#ifndef LogDll_
#define LogDll_
class LogDll {
private:
	typedef bool(__stdcall * Info_)		(const char*);
	typedef bool(__stdcall * Write_)	(const char*);

public:
	static bool Ready();
	static Write_	Write;
	static Info_	Info;
};
#endif