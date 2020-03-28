#pragma once
#ifndef WebBasic_H
#define WebBasic_H

class WebBasicClass {
public:
	string get_HtmlConfig(string data, string configName);
	std::string UrlEncode(const std::string& str);
	std::string UrlDecode(const std::string& str);

private:
	unsigned char ToHex(unsigned char x);
	unsigned char FromHex(unsigned char x);
};
#endif