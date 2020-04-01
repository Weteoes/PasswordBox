#include "pch.h"
#include "AESClass.h"

bool AESClass::setPassword(string pass) {
	VariableClass::setVariable("AES_Password", pass);
	std::string a = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::UserAndPassword;
	if (!WeteoesDll::IO_Exists((char*)a.c_str())) {
		// ≈‰÷√≤ª¥Ê‘⁄
		return false;
	}
	tinyxml2::XMLDocument xml;
	if (!VariableClass::xmlClass.GetXmlDocument(xml, a, true)) {
		return false;
	}
	return true;
}

bool AESClass::resetPassword(string oldPass, string newPass) {
	if (!setPassword(oldPass)) {
		// ‘≠√‹¬Î¥ÌŒÛ
		return false;
	}
	std::string a = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::UserAndPassword;
	tinyxml2::XMLDocument xml;
	if (!VariableClass::xmlClass.GetXmlDocument(xml, a)) {
		return false;
	}
	return VariableClass::xmlClass.SaveXML(xml, a);
}
