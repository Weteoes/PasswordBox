#ifndef RSAClass_H
#define RSAClass_H
#include "Weteoes/Loading.h"

class RSAClass
{
public:
	std::string A_PublicEncode(std::string);
	std::string B_PrivateUnEncode(std::string);
	std::string UnEncode(std::string, std::string);
	std::string Encode(std::string, std::string);

private:
	std::string RSA_PublicEncode(std::string,const std::string&);
	std::string RSA_PrivateUnEncode(std::string,const std::string&);
	void GetChars(std::string data_s, char* data_c);
};
#endif