#include "pch.h"
#include "Operating.h"

bool OperatingClass::sumbitConfig() {
    std::string w = VariableClass::getVariable("w");
    std::map<std::string, std::string> cookies;
    cookies.insert(std::pair<std::string, std::string>("JSESSIONID", w));
    std::string a = HttpOperatingClass::HttpRequestUpdateFile(
        VariableClass::serverDomain, 
        VariableClass::serverPort, 
        VariableClass::serverDomainConfigSumbitUrl, 
        VariableClass::configFile, 
        "POST", 
        VariableClass::serverIsSSL, 
        cookies
    );
    Json::Value json = WJsonClass::GetJson((char*)a.c_str());
	if (json != NULL) {
		int all = json.size();
		if (all == 0) { return false; }
		int code = json["code"].asInt();
        if (code == 0) { return true; }
	}
    return false;
}


bool OperatingClass::getConfig() {
    std::string w = VariableClass::getVariable("w");
    std::map<std::string, std::string> cookies;
    cookies.insert(std::pair<std::string, std::string>("JSESSIONID", w));
    std::string a = HttpOperatingClass::HttpRequestUpdateFile(
        VariableClass::serverDomain, 
        VariableClass::serverPort, 
        VariableClass::serverDomainConfigGetUrl, 
        "", 
        "POST", 
        VariableClass::serverIsSSL, 
        cookies
    );
    Json::Value json = WJsonClass::GetJson((char*)a.c_str());
    if (json != NULL) {
        int all = json.size();
        if (all == 0) { return false; }
        int code = json["code"].asInt();
        if (code == 0) { 
            std::string configData = json["config"].asString();
            if (configData.empty()) { return true; }
            char* configFileChar = (char*)VariableClass::configFile.c_str();
            // 判断文件是否存在
            if (WeteoesDll::IO_Exists(configFileChar)) {
                // 存在就备份
                CopyFile(configFileChar, (VariableClass::configFile + ".bak").c_str(), false);
                WeteoesDll::IO_Remove(configFileChar);
            }
            WeteoesDll::IO_WriteFile(
                configFileChar,
                (char*)configData.c_str(),
                (int)configData.length()
            );
            return true; 
        }
    }
    return false;
}

bool OperatingClass::pdLoginSession() {
    std::string w = VariableClass::getVariable("w");
    std::map<std::string, std::string> cookies;
    cookies.insert(std::pair<std::string, std::string>("JSESSIONID", w));
    std::string a = HttpOperatingClass::HttpRequestUpdateFile(
        VariableClass::serverDomain,
        VariableClass::serverPort,
        VariableClass::serverDomainPdLoginUrl,
        "",
        "POST",
        VariableClass::serverIsSSL,
        cookies
    );
    Json::Value json = WJsonClass::GetJson((char*)a.c_str());
    if (json != NULL) {
        int all = json.size();
        if (all == 0) { return false; }
        int code = json["code"].asInt();
        if (code == 0) { return true; }
    }
    return false;
}