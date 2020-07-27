#include "pch.h"
#include "AESClass.h"

bool AESClass::setPassword(string pass) {
	VariableClass::setVariable("AES_Password", pass);
	std::string a = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::UserAndPassword;
	if (!WeteoesDll::IO_Exists((char*)a.c_str())) {
		// 配置不存在
		return VariableClass::createXMLConfigClass.UserAndPassword();
	}
	else {
		// 配置文件存在
		tinyxml2::XMLDocument xml;
		if (!VariableClass::xmlClass.GetXmlDocument(xml, a)) {
			return false;
		}
		return true;
	}
}

bool AESClass::resetPassword(string oldPass, string newPass) {
	if (!setPassword(oldPass)) {
		// 原密码错误
		return false;
	}
	std::string a = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::UserAndPassword;
	tinyxml2::XMLDocument xml;
	if (!VariableClass::xmlClass.GetXmlDocument(xml, a)) {
		return false;
	}
	VariableClass::setVariable("AES_Password", newPass);
	return VariableClass::xmlClass.SaveXML(xml, a);
}

std::string AESClass::getAESPassByFile(std::string file) {
	if (file.find(ConfigFileClass::UserAndPassword) != -1) return VariableClass::getVariable("AES_Password");
	return "WeteoesH1HseoeteW";
}
