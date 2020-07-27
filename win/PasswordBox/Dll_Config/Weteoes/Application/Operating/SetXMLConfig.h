#include <pch.h>
#ifndef SetXMLConfigClass_H
#define SetXMLConfigClass_H

#include <Weteoes/More/tinyxml2/tinyxml2.h>

class SetXMLConfigClass {
public:
	bool UserAndPasswordAdd(const char* host, const char* user, const char* pass);
	bool UserAndPasswordDel(const char* host);

public:
	bool ServerSet(const char* key, const char* value);

};
#endif 