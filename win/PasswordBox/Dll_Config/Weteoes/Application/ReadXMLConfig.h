#include <Weteoes/Loading.h>
#include <Weteoes/Application/ReturnXMLStruct.h>

class ReadXMLConfigClass
{
public:
	ReturnXMLStruct::UserConfig_ User();
	ReturnXMLStruct::ComputerConfig_ Computer();
private:
	std::string ReadFile(std::string);
};

