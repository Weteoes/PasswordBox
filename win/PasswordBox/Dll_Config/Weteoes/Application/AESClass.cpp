#include "pch.h"
#include "AESClass.h"

bool AESClass::setPassword(string pass) {
	VariableClass::setVariable("AES_Password", pass);
	std::string a = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::UserAndPassword;
	if (!WeteoesDll::IO_Exists((char*)a.c_str())) {
		// ���ò�����
		return VariableClass::createXMLConfigClass.UserAndPassword();
	}
	else {
		// �����ļ�����
		tinyxml2::XMLDocument xml;
		if (!VariableClass::xmlClass.GetXmlDocument(xml, a)) {
			return false;
		}
		return true;
	}
}

bool AESClass::resetPassword(string oldPass, string newPass) {
	if (!setPassword(oldPass)) {
		// ԭ�������
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
