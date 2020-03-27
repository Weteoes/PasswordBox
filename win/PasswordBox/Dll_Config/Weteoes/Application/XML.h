#include <pch.h>
#ifndef XMLClass_H
#define XMLClass_H
#include <Weteoes/More/tinyxml2/tinyxml2.h>

class XMLClass {
public:
	bool GetXmlDocument(tinyxml2::XMLDocument& xml, std::string file); 
	void SaveXML(tinyxml2::XMLDocument& xml, std::string XmlFile); // 保存XML

public:
	string RootElementName = "Weteoes";

private:
	tinyxml2::XMLDocument* CreateXML(std::string); // 创建XML
	std::string ReadXmlParse(std::string); // 解密XML


private:
	std::string PublicKey = "-----BEGIN RSA PUBLIC KEY-----\nMIIBCgKCAQEApLhgqr+rIjK6UXZuXxUlZZxGTY8mEC5vZVf2ub2MPaTvEEtUMhec\nnJu0/eLCyj+9V/4uCaAd58hafPL4dJwfu7B5VqkC6t0YHhG4gcKnGVjIN2GPbT5Z\nekWGsG+6LCVlDvGI5qgSDealH1yfWaXDdpMW6q62PIaCL9UizlpuHi74go6d4Qnm\nY3/ELoinKe6LGPGOGbmIaiBNmDex+X8NKUXGicEhcEI+fp+dhFIRbyOq3WFu0h1X\ndbdz2j5ELfpHXMnB36Xdq6M+UaeL/0FHBZg0CdzgB1szsmaYXMSydQuchM5Zl05U\nDC3oxcSNf/ogri5bTMkWyFyMdUSAyDgkdwIDAQAB\n-----END RSA PUBLIC KEY-----";
	std::string PrivateKey = "-----BEGIN RSA PRIVATE KEY-----\nMIIEowIBAAKCAQEApLhgqr+rIjK6UXZuXxUlZZxGTY8mEC5vZVf2ub2MPaTvEEtU\nMhecnJu0/eLCyj+9V/4uCaAd58hafPL4dJwfu7B5VqkC6t0YHhG4gcKnGVjIN2GP\nbT5ZekWGsG+6LCVlDvGI5qgSDealH1yfWaXDdpMW6q62PIaCL9UizlpuHi74go6d\n4QnmY3/ELoinKe6LGPGOGbmIaiBNmDex+X8NKUXGicEhcEI+fp+dhFIRbyOq3WFu\n0h1Xdbdz2j5ELfpHXMnB36Xdq6M+UaeL/0FHBZg0CdzgB1szsmaYXMSydQuchM5Z\nl05UDC3oxcSNf/ogri5bTMkWyFyMdUSAyDgkdwIDAQABAoIBACtIe7ZCeTCaTdU8\nHpKDlvkVUG/u7pyP5xulOqLiCOjl3x/T+4LSK4gHbk7MeEz25MUreGN1HIacYhK1\nMc5KfBgwriG0dZzLjhvQokAOqyQA7VOIIk0ddhuoC1VvdmdFSEHd/BBIF75pXfhY\nuVKwOSV+TyZJ1H8hBTKWeffpUUhCuYRLBXyjDCmiflq2rdqvzhd4Lu88jQejib3G\nZe1NknyqKfjwTIVozW82+GquWU+Grf9HoVf3opDBdUgcNt9+hoNlSF4M9Urh637J\nThmxEOcAlgIAs3SNQ+6xq9TK7ZTvKRBBMzL62aNDP2V8gKa/I8gT1Qk6ZHVtNN99\nSAzSoikCgYEAzrnNbrDL966oF+lcoFZvxGHKC7cCEK9YdYvxAPUfdtsl9CNMK/Wp\n+tsqxPsCYaDxNJF/hViYBr8MnYPAk5osqZSbLil92BClMxQFc6mUpRLOXApqpzCX\ngEIMdGmIs8jy+QRO/1mU0gvRu0YO/WJD2k/3h+Zn7BnThUAdfUnfjtsCgYEAy/tw\nL2MDyAQcXezxvsRtNVsWd6V8UEnWpPcXM02rCHRRs4XdIUb2O1fftH4XXHiOhEzm\nHBVEhfD8D+srRnijSz/eIMfmpyMZLs22mKtP+0ZLxMhjcFfceYIjIUhE3S6ieOfp\n0B9Ws7md1EPJoSIo8KZgnHiCWfEuvr4Tri2wrZUCgYBmqgmm9jBlkhyyu1cf3a1m\nBvaTeNCSvrIctmH7CsEUguNHapwynK9NALkt2Eane4kuhS+iZowhlZHLTBpAc2nI\n0h96/mob+rBAPKo0dbx3em53cUjkPRKQRLzwt1SHjL12A7jDwZZR9kKzUaiyF7IA\n4oPYvwlPTMgqPdwnU5+tzwKBgQCVbgsPC9AXVLubKxsljywZrDLXT4m0H4N4sfJz\nCPDEbsHza5tE54E2k/czeDOQ8FgnH1ZrOEFMhe+BkdvP8kxdsdn91bNouVOXb+fW\nC5m6EBMtg0clY5gGA4nMte6Mwb8QJ4SnjG2tl8rBVy98NVQchyW7OqTzUrXV0dUF\nAj+tyQKBgHca/Ax4jehft7ZGZQbgcxCwZaSGur6h1iGCT7kcNUjd45W/fKcOLmy0\nGkfwyaUG2johQe26rWd1k8bP2l/AYvVH174Xk4Z75BH0bSKrTm5tVQER2axKkh51\n9BC9BSmMFM0yz/ZBCUzVAOR0m/ErOoSCRqfFGCbkulb6NuwdYPXB\n-----END RSA PRIVATE KEY-----\n";
};
#endif