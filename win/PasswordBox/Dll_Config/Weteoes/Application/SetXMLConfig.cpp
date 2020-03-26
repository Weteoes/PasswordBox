#include "SetXMLConfig.h"
#include <Weteoes/Application/ConfigFile.h>
#include <Weteoes/XML.h>
#include <Weteoes/Dll/WeteoesDll.h>

bool SetXMLConfigClass::Computer(char* menu,char* data)
{
	std::string XmlFile = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::Computer,
				XmlDataEncode = ReadFile(XmlFile);
	if (XmlDataEncode.empty()) { return false; }
	XMLClass xmlClass;
	std::string XmlData = xmlClass.ReadXmlParse(XmlDataEncode.c_str());
	tinyxml2::XMLDocument xml;
	if (xml.Parse(XmlData.c_str(), XmlData.length()) != 0) { return false; } //读取文件失败
	tinyxml2::XMLElement *root = xml.RootElement();
	if (root != NULL) { //读取字段
		tinyxml2::XMLElement *XML_menu = root->FirstChildElement(menu);
		if (!XML_menu || XML_menu->FirstChild() == NULL) { return false; } //找不到该行
		XML_menu->SetText(data);
		SaveXML(xml, XmlFile);
		return true;
	}
	return false;
}
std::string SetXMLConfigClass::ReadFile(std::string file) {
	if (!WeteoesDll::IO_Exists((char*)file.c_str())) {
		return "";
	}
	return WeteoesDll::IO_ReadFile((char*)file.c_str());
}
void SetXMLConfigClass::SaveXML(tinyxml2::XMLDocument &xml,std::string XmlFile) {
	tinyxml2::XMLPrinter s;
	xml.Accept(&s); //获取内容到变量
	std::string s_ = s.CStr();
	XMLClass().SaveXML(XmlFile, s_);
}