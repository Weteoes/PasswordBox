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
	string get_HtmlConfig(string data, string configName);

};
#endif