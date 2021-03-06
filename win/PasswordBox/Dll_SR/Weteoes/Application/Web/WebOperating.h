#include <pch.h>

#pragma once
#ifndef WebOperatingClass_H
#define WebOperatingClass_H

class WebOperatingClass {
public:
	bool Entrance(string operatingUrl, string &result);

private:
	string operating_operating_browser_get(string data);
	string operating_operating_browser_del(string data);
	string operating_operating_browser_create(string data);
	string operating_operating_console_getAll(string data);

private:
	std::mutex SSOMetux;		// 线程锁
	void SSOLoginGetConfig();	// 如果是统一身份认证，保持最新数据
	void SSOLoginUpdate();		// 如果是统一身份认证，更新服务器

};
#endif