#include <pch.h>
#include "XML.h"
#include <Weteoes\Application\ConfigFile.h>

bool XMLClass::GetXmlDocument(tinyxml2::XMLDocument& xml, std::string file) {
	if (!WeteoesDll::IO_Exists((char*)file.c_str())) {
		// 配置文件不存在
		WeteoesDll::IO_CreatePath((char*)file.c_str());
		tinyxml2::XMLDocument xml = CreateXML(file);
		return true;
	}
	char* result;
	int result_len = WeteoesDll::IO_ReadFile((char*)file.c_str(), result);
	std::string XmlDataEncode = string(result, result_len);
	std::string XmlData = VariableClass::xmlClass.ReadXmlParse(XmlDataEncode);
	if (xml.Parse(XmlData.c_str(), XmlData.length()) != 0) { return false; } //读取文件失败
	return true;
}

bool XMLClass::SaveXML(tinyxml2::XMLDocument& xml, std::string XmlFile) {
	if (RSA_PublicKey.empty()) {
		Ready_RSA();
	}
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
	if (RSA_PrivateKey.empty()) {
		Ready_RSA();
	}
	// 获取KEY
	string aes = VariableClass::getVariable("AES_Password");
	if (aes.empty()) { return ""; }
	char* result;
	int result_l = SRWDll::AES_UnEncode((char*)data.c_str(), (int)data.length(), (char*)aes.c_str(), result);
	data = string(result, (size_t)result_l);
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

bool XMLClass::Ready_RSA() {
	string nowPath = WeteoesDll::Basics_GetNowFilePath();
	string pub_Key = nowPath + ConfigFileClass::RSA_public_key;
	string pri_Key = nowPath + ConfigFileClass::RSA_private_key;
	if (WeteoesDll::IO_Exists((char*)pri_Key.c_str()) && WeteoesDll::IO_Exists((char*)pub_Key.c_str())) {
		// RSA存在
		char* RSA_PrivateKey_c;
		int RSA_PrivateKey_len = WeteoesDll::IO_ReadFile((char*)pri_Key.c_str(), RSA_PrivateKey_c);
		RSA_PrivateKey = string(RSA_PrivateKey_c, RSA_PrivateKey_len);

		char* RSA_PublicKey_c;
		int RSA_PublicKey_len = WeteoesDll::IO_ReadFile((char*)pub_Key.c_str(), RSA_PublicKey_c);
		RSA_PublicKey = string(RSA_PublicKey_c, RSA_PublicKey_len);
	}
	return false;
}