#include <pch.h>
#include "XML.h"
#include <Weteoes\Application\ConfigFile.h>

bool XMLClass::GetXmlDocument(tinyxml2::XMLDocument& xml, std::string file, bool replace) {
	if (!WeteoesDll::IO_Exists((char*)file.c_str())) {
		// 配置文件不存在
		WeteoesDll::IO_CreatePath((char*)file.c_str());
		return CreateXML(xml, file);
	}
	char* result;
	int result_len = WeteoesDll::IO_ReadFile((char*)file.c_str(), result);
	std::string XmlDataEncode = string(result, result_len);
	std::string XmlData = VariableClass::xmlClass.ReadXmlParse(XmlDataEncode);
	if (xml.Parse(XmlData.c_str(), XmlData.length()) != 0) { 
		//读取文件失败
		if (replace == true) {
			// 如果需要替换
			return CreateXML(xml, file);
		}
		return false; 
	}
	return true;
}

bool XMLClass::SaveXML(tinyxml2::XMLDocument& xml, std::string XmlFile) {
	tinyxml2::XMLPrinter s;
	xml.Accept(&s); //获取内容到变量
	std::string data = s.CStr();
	char* XmlFile_C = (char*)XmlFile.c_str();
	// 获取KEY
	string aes = VariableClass::getVariable("AES_Password");
	if (aes.empty()) { return false; }
	char* result;
	int result_l = SRWDll::AES_Encode((char*)data.c_str(), (int)data.length(), (char*)aes.c_str(), result);
	data = string(result, (size_t)result_l);
	if (data.empty()) { return false; }

	if (WeteoesDll::IO_Exists(XmlFile_C)) {
		WeteoesDll::IO_Remove(XmlFile_C);
	}

	WeteoesDll::IO_WriteFile((char*)XmlFile.c_str(), (char*)data.c_str(), (int)data.length());
	return true;
}

std::string XMLClass::ReadXmlParse(std::string data) {
	// 获取KEY
	string aes = VariableClass::getVariable("AES_Password");
	if (aes.empty()) { return ""; }
	char* result;
	int result_l = SRWDll::AES_UnEncode((char*)data.c_str(), (int)data.length(), (char*)aes.c_str(), result);
	data = string(result, (size_t)result_l);
	if (data.empty()) { return ""; }
	return data;
}

bool XMLClass::CreateXML(tinyxml2::XMLDocument& xml, std::string XMLPath) {
	if (WeteoesDll::IO_Exists((char*)XMLPath.c_str())) { //存在
		WeteoesDll::IO_Remove((char*)XMLPath.c_str()); //删除文件
	}
	//添加申明可以使用如下两行
	tinyxml2::XMLDeclaration* declaration = xml.NewDeclaration();
	xml.InsertFirstChild(declaration);
	return true;
}