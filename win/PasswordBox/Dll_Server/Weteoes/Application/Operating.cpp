#include "pch.h"
#include "Operating.h"

bool OperatingClass::sumbitConfig() {
    std::string w = VariableClass::getVariable("w");
    std::map<std::string, std::string> cookies;
    cookies.insert(std::pair<std::string, std::string>("w", w));
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
    cookies.insert(std::pair<std::string, std::string>("w", w));
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
            std::string configServerData = json["config"].asString();
            // 服务器没数据
            if (configServerData.empty()) { return false; }
            char* configFileChar = (char*)VariableClass::configFile.c_str();
            // 判断文件是否存在
            if (WeteoesDll::IO_Exists(configFileChar)) {
                // 判断内容是否相同
                char* configFileData;
                int configFileDataLen = WeteoesDll::IO_ReadFile(configFileChar, configFileData);
                std::string configFileDataStr(configFileData, configFileDataLen);
                if (configFileDataStr != configServerData) {
                    // 不相同数据需要覆盖，备份
                    CopyFile(configFileChar, (VariableClass::configFile + ".bak").c_str(), false);
                    WeteoesDll::IO_Remove(configFileChar);
                }
                else {
                    // 相同数据不用覆盖
                    return true;
                }
            }
            WeteoesDll::IO_WriteFile(
                configFileChar,
                (char*)configServerData.c_str(),
                (int)configServerData.length()
            );
            return true; 
        }
    }
    return false;
}

bool OperatingClass::pdLoginSession() {
    std::string w = VariableClass::getVariable("w");
    std::map<std::string, std::string> cookies;
    cookies.insert(std::pair<std::string, std::string>("w", w));
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