#include "ReadXMLConfig.h"
#include <Weteoes/Application/ConfigFile.h>
#include <Weteoes/XML.h>
#include <Weteoes/Dll/WeteoesDll.h>
#include <Weteoes/Dll/SRWDll.h>

ReturnXMLStruct::UserConfig_ ReadXMLConfigClass::User()
{
	std::string XmlFile = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::User,
		XmlDataEncode = ReadFile(XmlFile);
	if (XmlDataEncode.empty()) { return ReturnXMLStruct::UserConfig;}
	std::string XmlData = XMLClass().ReadXmlParse(XmlDataEncode.c_str());
	tinyxml2::XMLDocument xml;
	if (xml.Parse(XmlData.c_str(), XmlData.length()) != 0) { //读取文件失败
		return ReturnXMLStruct::UserConfig;
	}
	tinyxml2::XMLElement *root = xml.RootElement();
	if (root != NULL) { //读取字段
		ReturnXMLStruct::UserConfig_ *Config = &ReturnXMLStruct::UserConfig;
		tinyxml2::XMLElement *w_ = root->FirstChildElement("w");
		if (w_ && w_->FirstChild() != NULL) { strcpy_s(Config->w, w_->GetText()); }
	}
	return ReturnXMLStruct::UserConfig;
}
ReturnXMLStruct::ComputerConfig_ ReadXMLConfigClass::Computer()
{
	std::string XmlFile = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::Computer,
		XmlDataEncode = ReadFile(XmlFile);
	if (XmlDataEncode.empty()) { return ReturnXMLStruct::ComputerConfig; }
	std::string XmlData = XMLClass().ReadXmlParse(XmlDataEncode.c_str());
	tinyxml2::XMLDocument xml;
	if (xml.Parse(XmlData.c_str(), XmlData.length()) != 0) { //读取文件失败
		return ReturnXMLStruct::ComputerConfig;
	}
	tinyxml2::XMLElement *root = xml.RootElement();
	if (root != NULL) { //读取字段
		ReturnXMLStruct::ComputerConfig_ *Config = &ReturnXMLStruct::ComputerConfig;
		tinyxml2::XMLElement *XML_ComputerName = root->FirstChildElement("ComputerName");
		if (XML_ComputerName && XML_ComputerName->FirstChild() != NULL) { strcpy_s(Config->ComputerName, XML_ComputerName->GetText()); }
		tinyxml2::XMLElement *XML_Language = root->FirstChildElement("Language");
		if (XML_Language && XML_Language->FirstChild() != NULL) { strcpy_s(Config->Language, XML_Language->GetText()); }
	}
	return ReturnXMLStruct::ComputerConfig;
}
std::string ReadXMLConfigClass::ReadFile(std::string file) {
	if (!WeteoesDll::IO_Exists((char*)file.c_str())) {
		return "";
	}
	return WeteoesDll::IO_ReadFile((char*)file.c_str());
}
