#include <Weteoes/Loading.h>
#include <Weteoes/More/tinyxml2/tinyxml2.h>

class SetXMLConfigClass {
public:
	bool Computer(char*,char*); //��������
private:
	std::string ReadFile(std::string); //��ȡXML
	void SaveXML(tinyxml2::XMLDocument&, std::string); //����XML
};

