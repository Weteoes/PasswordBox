#include <Weteoes/Loading.h>
#include <Weteoes/More/tinyxml2/tinyxml2.h>

class CreateXMLConfigClass {
public:
	bool User(char*); //�û�����
	bool Computer(char*,char*); //��������
private:
	void SaveXML(tinyxml2::XMLDocument&, std::string); //����XML
};

