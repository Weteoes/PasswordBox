#include <pch.h>
#include "XML.h"
#include <Weteoes\Application\ConfigFile.h>

bool XMLClass::GetXmlDocument(tinyxml2::XMLDocument& xml, std::string file, bool isAes, bool replace) {
	if (!WeteoesDll::IO_Exists((char*)file.c_str())) {
		// 配置文件不存在
		WeteoesDll::IO_CreatePath((char*)file.c_str());
		return CreateXML(xml, file);
	}
	char* result;
	int result_len = WeteoesDll::IO_ReadFile((char*)file.c_str(), result);
	std::string XmlData = string(result, result_len);
	// 是否需要加密
	if (isAes) {
		// 获取AES Key
		string aes = VariableClass::aesClass.getAESPassByFile(file);
		if (aes.empty()) { return false; }
		XmlData = VariableClass::xmlClass.ReadXmlParse(XmlData, aes);
	}
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

void XMLClass::SetElementValue(tinyxml2::XMLDocument& xml, tinyxml2::XMLElement* rootElement, string key, string value) {
	tinyxml2::XMLElement* element = rootElement->FirstChildElement(key.c_str());
	if (!element) {
		// 找不到该行
		element = xml.NewElement(key.c_str());
		element->SetText(value.c_str());
		rootElement->InsertEndChild(element);
		xml.InsertEndChild(rootElement);
	}
	else {
		// 找到该行
		element->SetText(value.c_str());
	}
}

bool XMLClass::SaveXML(tinyxml2::XMLDocument& xml, std::string XmlFile, bool isAes) {
	tinyxml2::XMLPrinter s;
	xml.Accept(&s); //获取内容到变量
	std::string data = s.CStr();
	char* XmlFile_C = (char*)XmlFile.c_str();
	// 是否需要加密
	if (isAes) {
		// 获取AES Key
		string aes = VariableClass::aesClass.getAESPassByFile(XmlFile);
		if (aes.empty()) { return false; }
		char* result;
		int result_l = SRWDll::AES_Encode((char*)data.c_str(), (int)data.length(), (char*)aes.c_str(), result);
		data = string(result, (size_t)result_l);
	}
	if (data.empty()) { return false; }
	if (WeteoesDll::IO_Exists(XmlFile_C)) {
		WeteoesDll::IO_Remove(XmlFile_C);
	}
	WeteoesDll::IO_WriteFile((char*)XmlFile.c_str(), (char*)data.c_str(), (int)data.length());
	return true;
}

std::string XMLClass::ReadXmlParse(std::string data, std::string aesPass) {
	// 解密
	if (aesPass.empty()) { return ""; }
	char* result;
	int result_l = SRWDll::AES_UnEncode((char*)data.c_str(), (int)data.length(), (char*)aesPass.c_str(), result);
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