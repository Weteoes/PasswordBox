#include <pch.h>

#ifndef CreateXMLConfigClass_H
#define CreateXMLConfigClass_H

#include <Weteoes/More/tinyxml2/tinyxml2.h>

class CreateXMLConfigClass {
public:
	bool CreateXML(string xmlFile); // ���������ļ�
	bool UserAndPassword(const char* host, const char* user, const char* pass); // �û��˻������ļ�
};
#endif 