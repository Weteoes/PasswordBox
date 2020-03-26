#include <Weteoes/Loading.h>
#include <Weteoes/More/tinyxml2/tinyxml2.h>

class CreateXMLConfigClass {
public:
	bool User(char*); //用户配置
	bool Computer(char*,char*); //电脑配置
private:
	void SaveXML(tinyxml2::XMLDocument&, std::string); //保存XML
};

