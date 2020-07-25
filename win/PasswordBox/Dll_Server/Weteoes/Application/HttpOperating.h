#pragma once
#include <pch.h>
#ifndef HttpOperatingClass_
#define HttpOperatingClass_
#pragma comment(lib,"Wininet.lib")

class HttpOperatingClass {
public:
	static std::string HttpRequestUpdateFile(
		std::string ip, 
		int port, 
		std::string url, 
		std::string file,
		std::string type = "POST",
		bool isSSL = true,
		std::map<std::string, std::string> cookies = std::map<std::string, std::string>()
	);

private:
	static DWORD defaultHttpFlac;

private:
	static std::string getCookieStr(std::map<std::string, std::string> cookies);

};
#endif