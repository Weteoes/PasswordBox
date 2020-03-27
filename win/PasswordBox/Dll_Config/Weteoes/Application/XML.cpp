#include <pch.h>
#include "XML.h"

bool XMLClass::GetXmlDocument(tinyxml2::XMLDocument& xml, std::string file) {
	if (!WeteoesDll::IO_Exists((char*)file.c_str())) {
		// 配置文件不存在
		WeteoesDll::IO_CreatePath((char*)file.c_str());
		tinyxml2::XMLDocument xml = CreateXML(file);
		return true;
	}
	std::string XmlDataEncode = WeteoesDll::IO_ReadFile((char*)file.c_str());
	std::string XmlData = VariableClass::xmlClass.ReadXmlParse(XmlDataEncode.c_str());
	if (xml.Parse(XmlData.c_str(), XmlData.length()) != 0) { return false; } //读取文件失败
	return true;
}

void XMLClass::SaveXML(tinyxml2::XMLDocument& xml, std::string XmlFile) {
	tinyxml2::XMLPrinter s;
	xml.Accept(&s); //获取内容到变量
	std::string data = s.CStr();
	char* XmlFile_C = (char*)XmlFile.c_str();
	if (WeteoesDll::IO_Exists(XmlFile_C)) {
		WeteoesDll::IO_Remove(XmlFile_C);
	}
	data = SRWDll::RSA_Encode((char*)data.c_str(), (char*)PublicKey.c_str());
	if (data.empty()) { return; }
	WeteoesDll::IO_WriteFile((char*)XmlFile.c_str(), (char*)data.c_str());
}

std::string XMLClass::ReadXmlParse(std::string data) {
	data = SRWDll::RSA_UnEncode((char*)data.c_str(), (char*)PrivateKey.c_str());
	if (data.empty()) { return ""; }
	return data;
}


tinyxml2::XMLDocument* XMLClass::CreateXML(std::string XMLPath) {
	static tinyxml2::XMLDocument xml;
	if (WeteoesDll::IO_Exists((char*)XMLPath.c_str())) { //存在
		WeteoesDll::IO_Remove((char*)XMLPath.c_str()); //删除文件
	}
	//添加申明可以使用如下两行
	tinyxml2::XMLDeclaration* declaration = xml.NewDeclaration();
	xml.InsertFirstChild(declaration);
	return &xml;
}