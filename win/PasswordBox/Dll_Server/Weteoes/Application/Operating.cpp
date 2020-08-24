#include "pch.h"
#include "Operating.h"
#include "Wininet.h"

bool OperatingClass::SumbitConfig() {
    // 判断网络连接
    if (!NetWorkisConnect()) { return false; }
    // 操作
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

    LogInfo("SumbitConfig JSON:" + a);
    Json::Value json = WJsonClass::GetJson((char*)a.c_str());
	if (json != NULL) {
		int all = json.size();
		if (all == 0) { return false; }
		int code = json["code"].asInt();
        if (code == 0) { return true; }
	}
    return false;
}


bool OperatingClass::GetConfig() {
    // 判断网络连接
    if (!NetWorkisConnect()) { return false; }
    // 操作
    std::string w = VariableClass::getVariable("w");
    std::map<std::string, std::string> cookies;
    cookies.insert(std::pair<std::string, std::string>("w", w));
    std::string a = HttpOperatingClass::HttpRequest(
        VariableClass::serverDomain, 
        VariableClass::serverPort, 
        VariableClass::serverDomainConfigGetUrl, 
        "", 
        "POST", 
        VariableClass::serverIsSSL, 
        cookies
    );

    // LogInfo("GetConfig JSON:" + a);
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

bool OperatingClass::PdLoginSession() {
    // 判断网络连接
    if (!NetWorkisConnect()) { return false; }
    // 操作
    std::string w = VariableClass::getVariable("w");
    std::map<std::string, std::string> cookies;
    cookies.insert(std::pair<std::string, std::string>("w", w));
    std::string a = HttpOperatingClass::HttpRequest(
        VariableClass::serverDomain,
        VariableClass::serverPort,
        VariableClass::serverDomainPdLoginUrl,
        "",
        "POST",
        VariableClass::serverIsSSL,
        cookies
    );

    LogInfo("PdLoginSession JSON:" + a);
    Json::Value json = WJsonClass::GetJson((char*)a.c_str());
    if (json != NULL) {
        int all = json.size();
        if (all == 0) { return false; }
        int code = json["code"].asInt();
        if (code == 0) { return true; }
    }
    return false;
}

// 判断网络是否连接
bool OperatingClass::NetWorkisConnect() {
    // 判断本地连接状态
    bool result = false;
    for (int i = 0; i < 6; i++) {
        DWORD flag;
        bool con = InternetGetConnectedState(&flag, 0);
        if (!con) { 
            Sleep(1000);
            continue; 
        }
        else { break; }
    }

    // 判断网页服务器状态
    for (int i = 0; i < 6; i++) {
        std::string a = HttpOperatingClass::HttpRequest(
            VariableClass::serverDomain,
            VariableClass::serverPort,
            "",
            "",
            "POST",
            VariableClass::serverIsSSL
        );
        if (a.empty()) {
            Sleep(1000);
            continue;
        }
        else { 
            result = true;
            break; 
        }
    }

    // Log
    if (result) {
        LogInfo("NetWorkisConnect Yes");
    }
    else {
        LogInfo("NetWorkisConnect No");
    }
    return result;
}

void OperatingClass::LogInfo(std::string msg) {
    msg = "[Dll_Server] OperatingClass::" + msg;
    LogDll::Info(msg.c_str());
}