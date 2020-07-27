#pragma once
#ifndef AESClass_H
#define AESClass_H
class AESClass {
public:
	bool setPassword(string pass);
	bool resetPassword(string oldPass,string newPass);

public:
	std::string getAESPassByFile(std::string file);
};
#endif