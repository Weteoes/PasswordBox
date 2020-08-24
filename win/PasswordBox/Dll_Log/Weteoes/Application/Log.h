#ifndef LogClass_
#define LogClass_
#include <pch.h>

class LogClass {
public:
	static bool Write(const char* msg);
	static bool Info(const char*);

private:
	static bool WriteLog(std::string);

};
#endif