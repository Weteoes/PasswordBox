#pragma once
#ifndef LoginSSOClass_
#define LoginSSOClass_
class LoginSSOClass {
public:
	void Loginin(CefRefPtr<CefBrowser> browser);
	void Cookie(std::string key, std::string value);

public:
	bool PdLogin();						// 判断是否统一身份认证登录通过
	bool GetServerConfig();				// 获取服务器配置文件
	bool SumbitServerConfig();			// 提交服务器配置文件

private:
	bool SetLoginSession(std::string w);
};
#endif