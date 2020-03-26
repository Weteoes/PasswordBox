#include <Weteoes/Loading.h>
#include <Weteoes/More/tinyxml2/tinyxml2.h>

class SetXMLConfigClass {
public:
	bool Computer(char*,char*); //µÁƒ‘≈‰÷√
private:
	std::string ReadFile(std::string); //∂¡»°XML
	void SaveXML(tinyxml2::XMLDocument&, std::string); //±£¥ÊXML
};

