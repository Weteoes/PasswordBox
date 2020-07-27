#include <pch.h>

#ifndef ReadXMLConfigClass_H
#define ReadXMLConfigClass_H

class ReadXMLConfigClass
{
public:
	ReturnXMLStruct::Struct_UserAndPassword ReadUserAndPassword(const char* host);
	vector<ReturnXMLStruct::Struct_UserAndPassword> ReadAllUserAndPassword();

public:
	std::string ServerGet(const char* key);

};
#endif 
