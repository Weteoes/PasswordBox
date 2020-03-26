#include "XML.h"
#include <Weteoes/Dll/WeteoesDll.h>
#include <Weteoes/Dll/SRWDll.h>

tinyxml2::XMLDocument* XMLClass::CreateXML(std::string XMLPath)
{
	static tinyxml2::XMLDocument xml;
	if (WeteoesDll::IO_Exists((char*)XMLPath.c_str())) { //存在
		WeteoesDll::IO_Remove((char*)XMLPath.c_str()); //删除文件
	}
	//添加申明可以使用如下两行
	tinyxml2::XMLDeclaration* declaration = xml.NewDeclaration();
	xml.InsertFirstChild(declaration);
	return &xml;
}

void XMLClass::SaveXML(std::string XMLPath,std::string data)
{
	char* XMLPath_C = (char*)XMLPath.c_str();
	if (WeteoesDll::IO_Exists(XMLPath_C)) {
		WeteoesDll::IO_Remove(XMLPath_C);
	}
	std::string a = SRWDll::RSA_Encode((char*)data.c_str(), (char*)PublicKey.c_str());
	if (a.empty()) { return; }
	WeteoesDll::IO_WriteFile((char*)XMLPath.c_str(), (char*)a.c_str());
}

std::string XMLClass::ReadXmlParse(std::string data)
{
	std::string a = SRWDll::RSA_UnEncode((char*)data.c_str(), (char*)PrivateKey.c_str());
	if (a.empty()) { return ""; }
	return a;
}
