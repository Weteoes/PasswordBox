#include <pch.h>

#ifndef RSAClass_H
#define RSAClass_H

class RSAClass
{
public:
	std::string A_PublicEncode(std::string); // BEST64
	std::string B_PrivateUnEncode(std::string); // BEST64
	std::string UnEncode(std::string data, std::string key);
	std::string Encode(std::string data, std::string key);
	bool generateRSAKey(); // Éú³ÉRSAÃÜ³×

private:
	std::string RSA_PublicEncode(std::string,const std::string&);
	std::string RSA_PrivateUnEncode(std::string,const std::string&);
	void GetChars(std::string data_s, char *&data_c);
};
#endif